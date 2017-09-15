#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jayakrishnan");
MODULE_DESCRIPTION("Timer Module");

static struct timer_list my_timer;
int interval = 500;
static int count = 0;

void timer_callback(unsigned long data){
  ++count;
  printk(KERN_INFO "timer_callback called %d times", count);
  mod_timer(&my_timer, jiffies+ msecs_to_jiffies(interval));
  return 0;
}

static int __init timer_specs_init(void){

  int ret;
  printk(KERN_INFO " Timer initializing");
  setup_timer(&my_timer, timer_callback, 0);
  ret = mod_timer(&my_timer, jiffies+ msecs_to_jiffies(interval));
  if (ret)
    printk(KERN_INFO "error mod_timer");
  return 0;
}

static void __exit timer_cleanup(void){
  del_timer(&my_timer);
  printk(KERN_INFO "timer deleted and cleaned up");
  return 0;
}

module_init(timer_specs_init);
module_exit(timer_cleanup);
