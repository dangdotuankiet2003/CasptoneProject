#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x201d9cdc, "pci_clear_master" },
	{ 0x9dd4105e, "free_irq" },
	{ 0x00f6575c, "pci_free_irq_vectors" },
	{ 0x2c3ab3e8, "uio_event_notify" },
	{ 0x26a72629, "pci_check_and_mask_intx" },
	{ 0x201d9cdc, "pci_set_master" },
	{ 0x9126ce86, "request_threaded_irq" },
	{ 0x9b1de7cb, "_dev_info" },
	{ 0x9b1de7cb, "_dev_err" },
	{ 0x9b1de7cb, "_dev_notice" },
	{ 0x0eb89a5d, "pci_alloc_irq_vectors" },
	{ 0xd55e9359, "pci_irq_vector" },
	{ 0xbe011736, "__dynamic_dev_dbg" },
	{ 0xe3decb7e, "irq_get_irq_data" },
	{ 0x190674b3, "pci_cfg_access_lock" },
	{ 0x190674b3, "pci_cfg_access_unlock" },
	{ 0x96a73fa6, "pci_msi_mask_irq" },
	{ 0x772e1528, "pci_intx" },
	{ 0x96a73fa6, "pci_msi_unmask_irq" },
	{ 0x888b8f57, "strcmp" },
	{ 0xe8213e80, "_printk" },
	{ 0xe5c2991b, "__pci_register_driver" },
	{ 0x2b6f53b9, "pci_unregister_driver" },
	{ 0xbd03ed67, "random_kmalloc_seed" },
	{ 0xfaabfe5e, "kmalloc_caches" },
	{ 0xc064623f, "__kmalloc_cache_noprof" },
	{ 0x2437d1be, "pci_enable_device" },
	{ 0x9ef1423b, "dma_set_mask" },
	{ 0x12ad300e, "iounmap" },
	{ 0x201d9cdc, "pci_disable_device" },
	{ 0xcb8b6ec6, "kfree" },
	{ 0x9ef1423b, "dma_set_coherent_mask" },
	{ 0xeb5ade73, "sysfs_create_group" },
	{ 0x5bd6bd79, "__uio_register_device" },
	{ 0x7039d3ca, "dma_alloc_attrs" },
	{ 0x91d6d561, "dma_free_attrs" },
	{ 0x97dd6ca9, "ioremap" },
	{ 0x7320379d, "sysfs_remove_group" },
	{ 0x9b1de7cb, "_dev_warn" },
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0x2c3ab3e8, "uio_unregister_device" },
	{ 0x0040afbe, "param_ops_int" },
	{ 0x0040afbe, "param_ops_charp" },
	{ 0xd272d446, "__fentry__" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0xbd069841, "kstrtoull" },
	{ 0x5ce2c68b, "pci_num_vf" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x190674b3, "pci_disable_sriov" },
	{ 0x061b5352, "pci_enable_sriov" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x5a844b26, "__x86_indirect_thunk_rax" },
	{ 0x40a621c5, "snprintf" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x201d9cdc,
	0x9dd4105e,
	0x00f6575c,
	0x2c3ab3e8,
	0x26a72629,
	0x201d9cdc,
	0x9126ce86,
	0x9b1de7cb,
	0x9b1de7cb,
	0x9b1de7cb,
	0x0eb89a5d,
	0xd55e9359,
	0xbe011736,
	0xe3decb7e,
	0x190674b3,
	0x190674b3,
	0x96a73fa6,
	0x772e1528,
	0x96a73fa6,
	0x888b8f57,
	0xe8213e80,
	0xe5c2991b,
	0x2b6f53b9,
	0xbd03ed67,
	0xfaabfe5e,
	0xc064623f,
	0x2437d1be,
	0x9ef1423b,
	0x12ad300e,
	0x201d9cdc,
	0xcb8b6ec6,
	0x9ef1423b,
	0xeb5ade73,
	0x5bd6bd79,
	0x7039d3ca,
	0x91d6d561,
	0x97dd6ca9,
	0x7320379d,
	0x9b1de7cb,
	0x90a48d82,
	0x2c3ab3e8,
	0x0040afbe,
	0x0040afbe,
	0xd272d446,
	0xbd03ed67,
	0xbd069841,
	0x5ce2c68b,
	0xd272d446,
	0x190674b3,
	0x061b5352,
	0xd272d446,
	0x5a844b26,
	0x40a621c5,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"pci_clear_master\0"
	"free_irq\0"
	"pci_free_irq_vectors\0"
	"uio_event_notify\0"
	"pci_check_and_mask_intx\0"
	"pci_set_master\0"
	"request_threaded_irq\0"
	"_dev_info\0"
	"_dev_err\0"
	"_dev_notice\0"
	"pci_alloc_irq_vectors\0"
	"pci_irq_vector\0"
	"__dynamic_dev_dbg\0"
	"irq_get_irq_data\0"
	"pci_cfg_access_lock\0"
	"pci_cfg_access_unlock\0"
	"pci_msi_mask_irq\0"
	"pci_intx\0"
	"pci_msi_unmask_irq\0"
	"strcmp\0"
	"_printk\0"
	"__pci_register_driver\0"
	"pci_unregister_driver\0"
	"random_kmalloc_seed\0"
	"kmalloc_caches\0"
	"__kmalloc_cache_noprof\0"
	"pci_enable_device\0"
	"dma_set_mask\0"
	"iounmap\0"
	"pci_disable_device\0"
	"kfree\0"
	"dma_set_coherent_mask\0"
	"sysfs_create_group\0"
	"__uio_register_device\0"
	"dma_alloc_attrs\0"
	"dma_free_attrs\0"
	"ioremap\0"
	"sysfs_remove_group\0"
	"_dev_warn\0"
	"__ubsan_handle_out_of_bounds\0"
	"uio_unregister_device\0"
	"param_ops_int\0"
	"param_ops_charp\0"
	"__fentry__\0"
	"__ref_stack_chk_guard\0"
	"kstrtoull\0"
	"pci_num_vf\0"
	"__x86_return_thunk\0"
	"pci_disable_sriov\0"
	"pci_enable_sriov\0"
	"__stack_chk_fail\0"
	"__x86_indirect_thunk_rax\0"
	"snprintf\0"
	"module_layout\0"
;

MODULE_INFO(depends, "uio");


MODULE_INFO(srcversion, "477CD0B44C1D25E57128F06");
