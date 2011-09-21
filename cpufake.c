#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


static char *cpuname = "B0FHProc 256-bit, LightingTurboBoost enabled";

int init_module() {
    printk(KERN_INFO "cpufake loaded.\n");
    return 0;
}

void cleanup_module() {
    printk(KERN_INFO "cpufake unloaded.\n");
}


MODULE_AUTHOR("Maxime Augier <max@xolus.net>");
MODULE_DESCRIPTION("Make /proc/cpuinfo lie about the CPU model");
MODULE_LICENSE("GPL");

module_param(cpuname, charp, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(cpuname, "Name of CPU to fake");
