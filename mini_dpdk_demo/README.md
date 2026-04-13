Mini DPDK QDMA Demo

Muc tieu:
- Minh hoa co che DPDK probe driver, gan dev_ops, va goi callback cua driver.
- Giu cau truc rat nho de de doi chieu voi `drivers/net/qdma`.

Cau truc:
- `framework/mini_ethdev.h`: kieu du lieu va API chung kieu DPDK.
- `framework/mini_ethdev.c`: framework scan PCI, probe driver, va `rte_eth_dev_start()`.
- `drivers/mini_qdma_pf.c`: driver PF.
- `drivers/mini_qdma_vf.c`: driver VF.
- `app/main.c`: app mo phong viec goi DPDK APIs.

Flow chinh:
1. App goi `mini_pci_scan_and_probe()`
2. Framework match PCI ID voi driver PF/VF
3. Framework goi `probe()`
4. Driver `init()` va gan `dev->dev_ops`
5. App goi `rte_eth_dev_start(port_id)`
6. Framework goi callback `dev->dev_ops->dev_start`
7. PF se chay `mini_qdma_dev_start()`, VF se chay `mini_qdma_vf_dev_start()`

Build nhanh:

```sh
cc -Wall -Wextra -std=c11 \
  framework/mini_ethdev.c \
  drivers/mini_qdma_pf.c \
  drivers/mini_qdma_vf.c \
  app/main.c \
  -Iframework -Idrivers \
  -o mini_demo
./mini_demo
```
