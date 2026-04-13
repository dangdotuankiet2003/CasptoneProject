#ifndef MINI_ETHDEV_H
#define MINI_ETHDEV_H

#include <stddef.h>
#include <stdint.h>

#define MINI_MAX_ETHPORTS 8

struct mini_eth_dev;

struct mini_eth_dev_ops {
	int (*dev_configure)(struct mini_eth_dev *dev);
	int (*dev_start)(struct mini_eth_dev *dev);
	int (*dev_stop)(struct mini_eth_dev *dev);
};

struct mini_pci_id {
	uint16_t vendor_id;
	uint16_t device_id;
};

struct mini_pci_device {
	const char *name;
	uint16_t vendor_id;
	uint16_t device_id;
};

typedef int (*mini_eth_dev_init_t)(struct mini_eth_dev *dev);
typedef int (*mini_pci_probe_t)(struct mini_pci_device *pdev);

struct mini_pci_driver {
	const char *name;
	const struct mini_pci_id *id_table;
	mini_pci_probe_t probe;
};

struct mini_eth_dev_data {
	int dev_configured;
	int dev_started;
	void *dev_private;
};

struct mini_eth_dev {
	uint16_t port_id;
	const char *name;
	struct mini_pci_device *pci_dev;
	const struct mini_eth_dev_ops *dev_ops;
	struct mini_eth_dev_data *data;
};

extern struct mini_eth_dev mini_eth_devices[MINI_MAX_ETHPORTS];

void mini_register_pci_driver(struct mini_pci_driver *driver);
int mini_pci_scan_and_probe(const struct mini_pci_device *devices, int count);
int mini_eth_dev_pci_generic_probe(struct mini_pci_device *pdev,
	size_t private_size, mini_eth_dev_init_t init);
int rte_eth_dev_configure(uint16_t port_id);
int rte_eth_dev_start(uint16_t port_id);
int rte_eth_dev_stop(uint16_t port_id);

#endif
