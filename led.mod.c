#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
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
	{ 0x42c712ef, "module_layout" },
	{ 0x97255bdf, "strlen" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x956a91ba, "gpio_get_value_cansleep" },
	{ 0x64134fdf, "kobject_del" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xdd898587, "sysfs_remove_group" },
	{ 0x1a01225a, "kobject_create_and_add" },
	{ 0xea147363, "printk" },
	{ 0xc1e5077d, "sysfs_create_group" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x84b183ae, "strncmp" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "0175DDADC14CFDB99138D87");
