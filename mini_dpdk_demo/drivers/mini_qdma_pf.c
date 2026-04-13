#include "mini_ethdev.h"

#include <stdio.h>

struct mini_qdma_priv {
	int is_vf;
	int queue_base;
};

static int
mini_qdma_dev_configure(struct mini_eth_dev *dev)
{
	struct mini_qdma_priv *priv = dev->data->dev_private;

	priv->queue_base = 128;
	dev->data->dev_configured = 1;
	printf("[qdma-pf] qdma_dev_configure(port=%u), queue_base=%d\n",
		dev->port_id, priv->queue_base);
	return 0;
}

static int
mini_qdma_dev_start(struct mini_eth_dev *dev)
{
	struct mini_qdma_priv *priv = dev->data->dev_private;

	printf("[qdma-pf] qdma_dev_start(port=%u)\n", dev->port_id);
	printf("[qdma-pf] program PF contexts, enable queues, queue_base=%d\n",
		priv->queue_base);
	return 0;
}

static int
mini_qdma_dev_stop(struct mini_eth_dev *dev)
{
	printf("[qdma-pf] qdma_dev_stop(port=%u)\n", dev->port_id);
	return 0;
}

static const struct mini_eth_dev_ops mini_qdma_pf_ops = {
	.dev_configure = mini_qdma_dev_configure,
	.dev_start = mini_qdma_dev_start,
	.dev_stop = mini_qdma_dev_stop,
};

static int
mini_qdma_eth_dev_init(struct mini_eth_dev *dev)
{
	struct mini_qdma_priv *priv = dev->data->dev_private;

	priv->is_vf = 0;
	dev->dev_ops = &mini_qdma_pf_ops;

	printf("[qdma-pf] init(port=%u) -> dev->dev_ops = &mini_qdma_pf_ops\n",
		dev->port_id);
	return 0;
}

static int
mini_qdma_pci_probe(struct mini_pci_device *pdev)
{
	printf("[qdma-pf] eth_qdma_pci_probe(%s)\n", pdev->name);
	return mini_eth_dev_pci_generic_probe(pdev, sizeof(struct mini_qdma_priv),
		mini_qdma_eth_dev_init);
}

static const struct mini_pci_id mini_qdma_pf_id_table[] = {
	{0x10ee, 0x903f},
	{0, 0},
};

static struct mini_pci_driver mini_qdma_pf_driver = {
	.name = "net_qdma_pf",
	.id_table = mini_qdma_pf_id_table,
	.probe = mini_qdma_pci_probe,
};

void mini_qdma_pf_driver_register(void)
{
	mini_register_pci_driver(&mini_qdma_pf_driver);
}
