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

void set_all_names(void) {
    loff_t i;
    for (i=0; i < nr_cpu_ids; i++) {
	set_cpu_name(&cpu_data(i));
    }
}

static int cpufake_set_name(const char *buffer, struct kernel_param *kp) {
    int len = strlen(strncpy(cpuname,buffer,CM_SIZE-1));
    cpuname[CM_SIZE-1] = '\0';
    set_all_names();
    return len;
}

static int cpufake_get_name(char *buffer, struct kernel_param *kp) {
    return strlen(strcpy(buffer, cpuname));
}

int init_module() {

    printk(KERN_INFO "cpufake loaded.\n");

    set_all_names();

    return 0;
}


void cleanup_module() {
    printk(KERN_INFO "cpufake unloaded.\n");
}


MODULE_AUTHOR("Maxime Augier <max@xolus.net>");
MODULE_DESCRIPTION("Make /proc/cpuinfo lie about the CPU model");
MODULE_LICENSE("GPL");

module_param_call(cpuname, cpufake_set_name, cpufake_get_name, NULL, S_IRUSR | S_IWUSR);
__MODULE_PARM_TYPE(cpuname, "string");
MODULE_PARM_DESC(cpuname, "Name of CPU to fake");

