#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x964ee563, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x9ae25973, __VMLINUX_SYMBOL_STR(snd_soc_pm_ops) },
	{ 0x37b77dde, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xe5590619, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xc2eb7bd0, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_sysclk) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x8426bbba, __VMLINUX_SYMBOL_STR(devm_snd_soc_register_card) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-soc-core";


MODULE_INFO(srcversion, "796C33403DAC7B61F394677");
