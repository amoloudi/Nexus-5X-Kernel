#include"linux/module.h"	/* Needed for all modules */
#include"linux/kernel.h"	/* Needed for KERN_INFO */

MODULE_LICENSE("GPL");		/*GNU Public License v2 or later*/

int init_module(void)
{
printk(KERN_INFO "Hello OS\n");	/*print in kernel info(dmesg)*/
return 0;
}

