#include <rte_common.h>
#include <rte_dev.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_errno.h>
#include <rte_log.h>
#include <rte_malloc.h>
#include <rte_pci.h>
#include "qdma_com_e.h"

static int
qdma_program_mac_entry(struct rte_eth_dev *dev,
                       uint16_t entry_id,
                       uint16_t q_base,
                       uint16_t q_range,
                       const struct rte_ether_addr *addr)
{
    struct qdma_pci_dev *qdma_dev = qdma_dev = dev->data->dev_private;;
    uint32_t mac_lo, mac_hi, data;
    uint32_t user_bar;

    if (!dev || !addr)
        return -EINVAL;

    if (!rte_is_valid_assigned_ether_addr(addr))
        return -EINVAL;

    if (!qdma_dev)
        return -ENODEV;

    user_bar = qdma_dev->user_bar_idx;

    mac_lo = ((uint32_t)addr->addr_bytes[2] << 24) |
             ((uint32_t)addr->addr_bytes[3] << 16) |
             ((uint32_t)addr->addr_bytes[4] << 8)  |
             ((uint32_t)addr->addr_bytes[5]);

    mac_hi = ((uint32_t)addr->addr_bytes[0] << 8) |
             ((uint32_t)addr->addr_bytes[1]);

    data = ((uint32_t)q_range << 16) | q_base;

    printf("MAC_ENTRY: user_bar=%u entry=%u q_base=%u q_range=%u\n",
           user_bar, entry_id, q_base, q_range);

    printf("WRITE BAR%u reg=0x%x val=0x%x\n",
           user_bar, QDMA_MAC_TABLE_BASE + QDMA_MAC_KEY_ADDR_L, mac_lo);
    qdma_pci_write_reg(dev, user_bar,
                       QDMA_MAC_TABLE_BASE + QDMA_MAC_KEY_ADDR_L, mac_lo);

    printf("WRITE BAR%u reg=0x%x val=0x%x\n",
           user_bar, QDMA_MAC_TABLE_BASE + QDMA_MAC_KEY_ADDR_H, mac_hi);
    qdma_pci_write_reg(dev, user_bar,
                       QDMA_MAC_TABLE_BASE + QDMA_MAC_KEY_ADDR_H, mac_hi);

    printf("WRITE BAR%u reg=0x%x val=0x%x\n",
           user_bar, QDMA_MAC_TABLE_BASE + QDMA_MAC_DATA, data);
    qdma_pci_write_reg(dev, user_bar,
                       QDMA_MAC_TABLE_BASE + QDMA_MAC_DATA, data);

    printf("WRITE BAR%u reg=0x%x val=0x%x\n",
           user_bar, QDMA_MAC_TABLE_BASE + QDMA_MAC_SET_ADDR, entry_id);
    qdma_pci_write_reg(dev, user_bar,
                       QDMA_MAC_TABLE_BASE + QDMA_MAC_SET_ADDR, entry_id);

    printf("WRITE BAR%u reg=0x%x val=0x%x\n",
           user_bar, QDMA_MAC_TABLE_BASE + QDMA_MAC_TABLE_ID,
           QDMA_MAC_TABLE_SEL);
    qdma_pci_write_reg(dev, user_bar,
                       QDMA_MAC_TABLE_BASE + QDMA_MAC_TABLE_ID,
                       QDMA_MAC_TABLE_SEL);

    printf("WRITE BAR%u reg=0x%x val=0x%x\n",
           user_bar, QDMA_MAC_TABLE_BASE + QDMA_MAC_SET_CLR,
           QDMA_MAC_SET);
    qdma_pci_write_reg(dev, user_bar,
                       QDMA_MAC_TABLE_BASE + QDMA_MAC_SET_CLR,
                       QDMA_MAC_SET);

    printf("WRITE BAR%u reg=0x%x val=0x%x\n",
           user_bar, QDMA_MAC_TABLE_BASE + QDMA_MAC_VLD, 1);
    qdma_pci_write_reg(dev, user_bar,
                       QDMA_MAC_TABLE_BASE + QDMA_MAC_VLD, 1);

    return 0;
}