#include "mini_ethdev.h"

#include <stdio.h>

struct mini_qdma_vf_priv {
	int is_vf;
	int assigned_qbase;
};

static int
mini_qdma_vf_dev_configure(struct mini_eth_dev *dev)
{
	struct mini_qdma_vf_priv *priv = dev->data->dev_private;

	priv->assigned_qbase = 512;
	dev->data->dev_configured = 1;
	printf("[qdma-vf] qdma_vf_dev_configure(port=%u), assigned_qbase=%d\n",
		dev->port_id, priv->assigned_qbase);
	return 0;
}

static int
mini_qdma_vf_dev_start(struct mini_eth_dev *dev)
{
	struct mini_qdma_vf_priv *priv = dev->data->dev_private;

	printf("[qdma-vf] qdma_vf_dev_start(port=%u)\n", dev->port_id);
	printf("[qdma-vf] request/start VF queues via PF mailbox, qbase=%d\n",
		priv->assigned_qbase);
	return 0;
}

static int
mini_qdma_vf_dev_stop(struct mini_eth_dev *dev)
{
	printf("[qdma-vf] qdma_vf_dev_stop(port=%u)\n", dev->port_id);
	return 0;
}

static const struct mini_eth_dev_ops mini_qdma_vf_ops = {
	.dev_configure = mini_qdma_vf_dev_configure,
	.dev_start = mini_qdma_vf_dev_start,
	.dev_stop = mini_qdma_vf_dev_stop,
};

static int
mini_qdma_vf_eth_dev_init(struct mini_eth_dev *dev)
{
	struct mini_qdma_vf_priv *priv = dev->data->dev_private;

	priv->is_vf = 1;
	dev->dev_ops = &mini_qdma_vf_ops;

	printf("[qdma-vf] init(port=%u) -> dev->dev_ops = &mini_qdma_vf_ops\n",
		dev->port_id);
	return 0;
}

static int
mini_qdma_vf_pci_probe(struct mini_pci_device *pdev)
{
	printf("[qdma-vf] eth_qdma_vf_pci_probe(%s)\n", pdev->name);
	return mini_eth_dev_pci_generic_probe(pdev,
		sizeof(struct mini_qdma_vf_priv), mini_qdma_vf_eth_dev_init);
}

static const struct mini_pci_id mini_qdma_vf_id_table[] = {
	{0x10ee, 0xa03f},
	{0, 0},
};

static struct mini_pci_driver mini_qdma_vf_driver = {
	.name = "net_qdma_vf",
	.id_table = mini_qdma_vf_id_table,
	.probe = mini_qdma_vf_pci_probe,
};

void mini_qdma_vf_driver_register(void)
{
	mini_register_pci_driver(&mini_qdma_vf_driver);
}
