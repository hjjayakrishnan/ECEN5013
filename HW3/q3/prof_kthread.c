#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jayakrishnan");
MODULE_DESCRIPTION("Kthread Profiler");

static struct task_struct *kthread;
ktime_t start, stop, delay;

int thread1(void *data){
  printk(KERN_INFO "In thread1");
  delay = ktime_to_ns(ktime_sub(stop, start));
  printk(KERN_INFO "kthread creation time: %ld ns",(long long)delay);
  do_exit(0);
  
}


static int __init thread_init(void){
  printk(KERN_INFO "Entering profiler");
  char sample_thread[20] = "test_thread";
  start = ktime_get();
  kthread = kthread_run(thread1, NULL, sample_thread);
  if(IS_ERR(kthread)){
    printk(KERN_INFO "Error!!");
    return PTR_ERR(kthread);
  }
  stop = ktime_get();
}


static void __exit profiler_cleanup(void){
  printk(KERN_INFO "Exiting profiler");
  if(!kthread)
    kthread_stop(kthread);
}

module_init(thread_init);
module_exit(profiler_cleanup);
