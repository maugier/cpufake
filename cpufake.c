#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/smp.h>

#define CM_SIZE 64

static char *cpuname = "B0FHProc 256-bit, LightingTurboBoost enabled";

void set_cpu_name(struct cpuinfo_x86 *c) {
	strncpy(c->x86_model_id, cpuname, CM_SIZE-1);
	c->x86_model_id[CM_SIZE-1] = '\0';
}

int init_module() {
    loff_t i;

    printk(KERN_INFO "cpufake loaded.\n");

    for (i=0; i < nr_cpu_ids; i++) {
	set_cpu_name(&cpu_data(i));
    }

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

