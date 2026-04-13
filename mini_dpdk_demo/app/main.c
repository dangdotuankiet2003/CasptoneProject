#include "mini_ethdev.h"
#include "mini_qdma_drivers.h"

#include <stdio.h>

int main(void)
{
	const struct mini_pci_device devices[] = {
		{ .name = "0000:01:00.0", .vendor_id = 0x10ee, .device_id = 0x903f },
		{ .name = "0000:01:00.1", .vendor_id = 0x10ee, .device_id = 0xa03f },
	};

	mini_qdma_pf_driver_register();
	mini_qdma_vf_driver_register();

	printf("=== PCI scan + probe ===\n");
	mini_pci_scan_and_probe(devices, 2);

	printf("\n=== Configure devices ===\n");
	rte_eth_dev_configure(0);
	rte_eth_dev_configure(1);

	printf("\n=== Start devices ===\n");
	rte_eth_dev_start(0);
	rte_eth_dev_start(1);

	printf("\n=== Stop devices ===\n");
	rte_eth_dev_stop(0);
	rte_eth_dev_stop(1);

	return 0;
}
