#ifndef QDMA_COM_E_H
#define QDMA_COM_E_H

/**
 * @file qdma_com_e.h
 * @brief QDMA common enumerations and definitions
 */
#include <stdint.h>
#include <rte_ethdev.h>
#include <rte_ether.h>

#define QDMA_MAC_TABLE_BASE      0x1000
#define QDMA_MAC_SET_ADDR        0x004
#define QDMA_MAC_KEY_ADDR_L      0x018
#define QDMA_MAC_KEY_ADDR_H      0x01C
#define QDMA_MAC_DATA            0x0A8
#define QDMA_MAC_SET_CLR         0x0BC
#define QDMA_MAC_TABLE_ID        0x0C0
#define QDMA_MAC_VLD             0x0C4

#define QDMA_MAC_TABLE_SEL       16
#define QDMA_MAC_SET             1

#ifdef __cplusplus

extern "C" {
#endif

static int qdma_program_mac_entry(struct rte_eth_dev *dev,
                                  uint16_t entry_id,
                                  uint16_t q_base,
                                  uint16_t q_range,
                                  const struct rte_ether_addr *addr);

#ifdef __cplusplus
}
#endif

#endif /* QDMA_COM_E_H */