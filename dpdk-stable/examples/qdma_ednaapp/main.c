#include <stdio.h>
#include <stdint.h>
#include <rte_eal.h>
#include <rte_ethdev.h>

static void dump_dpdk_ports(void)
{
    uint16_t port_id;
    struct rte_eth_dev_info info;

    printf("=== DPDK port list ===\n");
    printf("available ports: %u\n", rte_eth_dev_count_avail());

    RTE_ETH_FOREACH_DEV(port_id) {
        int ret = rte_eth_dev_info_get(port_id, &info);
        if (ret != 0) {
            printf("port_id=%u: dev_info_get failed: %d\n", port_id, ret);
            continue;
        }

        printf("port_id=%u, driver=%s\n",
               port_id,
               info.driver_name ? info.driver_name : "unknown");
    }

    printf("======================\n");

    struct rte_ether_addr mac = {
        .addr_bytes = {0x02, 0x11, 0x22, 0x33, 0x44, 0x55}
    };

    int ret = rte_eth_dev_default_mac_addr_set(0, &mac);

    printf("ret = %d\n", ret);

    printf("mac_addr_set: port_id=%u mac=%02x:%02x:%02x:%02x:%02x:%02x\n",
        0,
        mac.addr_bytes[0], mac.addr_bytes[1],
        mac.addr_bytes[2], mac.addr_bytes[3],
        mac.addr_bytes[4], mac.addr_bytes[5]);

    // PMD_DRV_LOG(INFO,
    // "PF mac set: port=%u entry=%u mac=%02x:%02x:%02x:%02x:%02x:%02x",
    // dev->data->port_id, entry_id,
    // mac_addr->addr_bytes[0], mac_addr->addr_bytes[1],
    // mac_addr->addr_bytes[2], mac_addr->addr_bytes[3],
    // mac_addr->addr_bytes[4], mac_addr->addr_bytes[5]);
    struct rte_ether_addr mac1 =
    {
        .addr_bytes = {0x02, 0x12, 0x23, 0x34, 0x45, 0x56}
    };

}

static int test_mac_add(uint16_t port_id)
{
    int ret;

    struct rte_ether_addr mac1 = {
        .addr_bytes = {0x02, 0xaa, 0xbb, 0xcc, 0xdd, 0x01}
    };
    printf("\n=== TEST: MAC ADD ===\n");

    printf("Add MAC1: %02x:%02x:%02x:%02x:%02x:%02x\n",
        mac1.addr_bytes[0], mac1.addr_bytes[1],
        mac1.addr_bytes[2], mac1.addr_bytes[3],
        mac1.addr_bytes[4], mac1.addr_bytes[5]);

    ret = rte_eth_dev_mac_addr_add(port_id, &mac1, 0);
    printf("ret = %d\n", ret);
    return 0;
}

static int test_mac_remove(uint16_t port_id)
{
    int ret;

    struct rte_ether_addr mac1 = {
        .addr_bytes = {0x02, 0xaa, 0xbb, 0xcc, 0xdd, 0x01}
    };

    printf("\n=== TEST: MAC REMOVE ===\n");

    printf("Remove MAC1: %02x:%02x:%02x:%02x:%02x:%02x\n",
        mac1.addr_bytes[0], mac1.addr_bytes[1],
        mac1.addr_bytes[2], mac1.addr_bytes[3],
        mac1.addr_bytes[4], mac1.addr_bytes[5]);

    ret = rte_eth_dev_mac_addr_remove(port_id, &mac1);
    printf("ret = %d\n", ret);

    return 0;
}

int main(int argc, char **argv)
{
    int ret;

    printf("QDMA testapp rte eal init...\n");
    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_panic("Cannot init EAL\n");
    }

    dump_dpdk_ports();

    uint16_t port_id = 1;
    // Test riêng ADD
    test_mac_add(port_id);

    // Test riêng REMOVE
    test_mac_remove(port_id);
    return 0;
}
