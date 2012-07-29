#include <linux/module.h>
#include <asm-generic/gpio.h>
#include <linux/kobject.h>

#define VERSION "v0.1"
#define LED1	150
#define LED0	149
struct kobject *kobj;
const static char *ledon = "led on";
const static char *ledoff = "led off";

static ssize_t led_show_led0(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	char *s = buf;
	if(gpio_get_value_cansleep(LED0))
		s += sprintf(s, "%s\n", ledon);
	else
		s += sprintf(s, "%s\n", ledoff);
	if(s != buf)
		*(s-1) = '\n';
	return (s - buf);
}
static ssize_t led_store_led0(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t n)
{
	//p = memchr(buf, '\n', n);
	//len = p ? p - buf : n;
	//len =;
	//printk(KERN_INFO "%s:enter\n", __func__);
	//printk(KERN_INFO "buf = %s, sizeof buf = %d, ledoff = %s, strlen(ledoff) = %d, n = %d\n", buf, sizeof(buf), ledoff, strlen(ledoff), n);		
		if(strlen(ledon) == n-1  && !strncmp(buf, ledon, n-1))
		{
//			printk(KERN_INFO "%s:1\n", __func__);
			gpio_direction_output(LED0, 1);
		}
		else if(strlen(ledoff) == n-1 && !strncmp(buf, ledoff, n-1))
		{
//			printk(KERN_INFO "%s:2\n", __func__);
			gpio_direction_output(LED0, 0);
		}
	return n;
}
static ssize_t led_show_led1(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        char *s = buf;
        if(gpio_get_value_cansleep(LED1))
                s += sprintf(s, "%s\n", ledon);
        else
                s += sprintf(s, "%s\n", ledoff);
        if(s != buf)
                *(s-1) = '\n';
        return (s - buf);
}
static ssize_t led_store_led1(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t n)
{
        //p = memchr(buf, '\n', n);
        //len = p ? p - buf : n;
        //len =;
        //printk(KERN_INFO "%s:enter\n", __func__);
                if(strlen(ledon) == n-1  && !strncmp(buf, ledon, n-1))
                {
//                      printk(KERN_INFO "%s:1\n", __func__);
                        gpio_direction_output(LED1, 1);
                }
                else if(strlen(ledoff) == n-1 && !strncmp(buf, ledoff, n-1))
                {
//                      printk(KERN_INFO "%s:2\n", __func__);
                        gpio_direction_output(LED1, 0);
                }
        return n;
}

static struct kobj_attribute kobj_attr_led0 =
{
	.attr = 
	{
		.name = __stringify(led0),
		.mode = 0666,
	},
	.show = led_show_led0,
	.store = led_store_led0,
};
static struct kobj_attribute kobj_attr_led1 =
{
	.attr =
	{
		.name = __stringify(led1),
		.mode = 0666,
	},
	.show = led_show_led1,
	.store = led_store_led1,
};

static struct attribute *attr_g[] =
{
	&kobj_attr_led0.attr,
	&kobj_attr_led1.attr,
	NULL,
};

static struct attribute_group grp =
{
	.name = __stringify(gpio),
	.attrs = attr_g,
};

static int __init led_init(void)
{
	if(gpio_request(LED1, "LED") < 0)
	{
		printk(KERN_ERR "can't request gpio %d\n", LED1);
//		return -EAGAIN;
	}
	kobj = kobject_create_and_add("led", NULL);
	if(!kobj)
	{
		printk(KERN_INFO "kobject didn't create\n");
		return -ENOMEM;
	}
	sysfs_create_group(kobj, &grp);
	printk(KERN_INFO "LED driver loaded, %s\n", VERSION);
	return 0;
}

static void __exit led_exit(void)
{
	printk(KERN_INFO "LED driver exit\n");
	sysfs_remove_group(kobj, &grp);
	kobject_del(kobj);
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
