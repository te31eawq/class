#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
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

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x3d82956c, "gpio_to_desc" },
	{ 0x7a7a17a, "gpiod_get_raw_value" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x92997ed8, "_printk" },
	{ 0xd1948ef, "gpiod_set_raw_value" },
	{ 0xa68613dd, "get_jiffies_64" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0xfe990052, "gpio_free" },
	{ 0xdc0e4855, "timer_delete" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x24d273d1, "add_timer" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x504b3a4, "gpiod_direction_output_raw" },
	{ 0xe498c05c, "gpiod_direction_input" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x99409edb, "param_ops_int" },
	{ 0xa400a71f, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "39D3744FE80939D3661A89A");