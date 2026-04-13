#include "mini_ethdev.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINI_MAX_DRIVERS 8

struct mini_eth_dev mini_eth_devices[MINI_MAX_ETHPORTS];

static struct mini_eth_dev_data mini_eth_data[MINI_MAX_ETHPORTS];
static struct mini_pci_driver *registered_drivers[MINI_MAX_DRIVERS];
static int driver_count;
static int next_port_id;

static int
mini_pci_id_match(const struct mini_pci_id *ids, const struct mini_pci_device *pdev)
{
	int i = 0;

	while (ids[i].vendor_id || ids[i].device_id) {
		if (ids[i].vendor_id == pdev->vendor_id &&
		    ids[i].device_id == pdev->device_id)
			return 1;
		i++;
	}

	return 0;
}

void
mini_register_pci_driver(struct mini_pci_driver *driver)
{
	if (driver_count < MINI_MAX_DRIVERS)
		registered_drivers[driver_count++] = driver;
}

int
mini_eth_dev_pci_generic_probe(struct mini_pci_device *pdev,
	size_t private_size, mini_eth_dev_init_t init)
{
	struct mini_eth_dev *dev;

	if (next_port_id >= MINI_MAX_ETHPORTS)
		return -1;

	dev = &mini_eth_devices[next_port_id];
	memset(dev, 0, sizeof(*dev));
	memset(&mini_eth_data[next_port_id], 0, sizeof(mini_eth_data[next_port_id]));

	dev->port_id = (uint16_t)next_port_id;
	dev->name = pdev->name;
	dev->pci_dev = pdev;
	dev->data = &mini_eth_data[next_port_id];

	if (private_size) {
		dev->data->dev_private = calloc(1, private_size);
		if (!dev->data->dev_private)
			return -1;
	}

	printf("[framework] allocate ethdev port=%u for %s\n",
		dev->port_id, dev->name);

	if (init(dev) != 0) {
		free(dev->data->dev_private);
		memset(dev, 0, sizeof(*dev));
		memset(dev->data, 0, sizeof(*dev->data));
		return -1;
	}

	next_port_id++;
	return 0;
}

int
mini_pci_scan_and_probe(const struct mini_pci_device *devices, int count)
{
	int i;
	int j;

	for (i = 0; i < count; i++) {
		printf("[framework] scan pci device %s (vid=%#x did=%#x)\n",
			devices[i].name, devices[i].vendor_id, devices[i].device_id);

		for (j = 0; j < driver_count; j++) {
			if (!mini_pci_id_match(registered_drivers[j]->id_table, &devices[i]))
				continue;

			printf("[framework] match driver %s -> call probe()\n",
				registered_drivers[j]->name);
			registered_drivers[j]->probe((struct mini_pci_device *)&devices[i]);
			break;
		}
	}

	return 0;
}

int
rte_eth_dev_configure(uint16_t port_id)
{
	struct mini_eth_dev *dev = &mini_eth_devices[port_id];

	if (!dev->dev_ops || !dev->dev_ops->dev_configure)
		return -1;

	return dev->dev_ops->dev_configure(dev);
}

int
rte_eth_dev_start(uint16_t port_id)
{
	struct mini_eth_dev *dev = &mini_eth_devices[port_id];
	int ret;

	printf("[framework] rte_eth_dev_start(port=%u)\n", port_id);

	if (!dev->dev_ops || !dev->dev_ops->dev_start)
		return -1;

	if (!dev->data->dev_configured) {
		printf("[framework] device port=%u not configured\n", port_id);
		return -1;
	}

	ret = dev->dev_ops->dev_start(dev);
	if (ret == 0)
		dev->data->dev_started = 1;

	return ret;
}

int
rte_eth_dev_stop(uint16_t port_id)
{
	struct mini_eth_dev *dev = &mini_eth_devices[port_id];
	int ret;

	if (!dev->dev_ops || !dev->dev_ops->dev_stop)
		return -1;

	ret = dev->dev_ops->dev_stop(dev);
	if (ret == 0)
		dev->data->dev_started = 0;

	return ret;
}
