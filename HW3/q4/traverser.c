#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/init_task.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jayakrishnan");
MODULE_DESCRIPTION("Traverser");

void traverse(struct task_struct *task){

  struct list_head *list;
  struct task_struct *child;
  printk(KERN_INFO "name: %s, pid: %d, state: %ld", task->comm, task->pid, task->state);
  list_for_each(list, &task->children){
    child = list_entry(list, struct task_struct, sibling);
    traverse(child);
  }
  return 0;
}

static int __init traverse_init(void){
  printk(KERN_INFO "Initializing module");
  struct task_struct *task;
  task = current;
  while(task != &init_task){
    task = task->parent;
  }
  printk(KERN_INFO "name: %s, pid: %d", task->comm, task->pid);
  traverse(task);
}

static void __exit traverse_cleanup(void){
  printk(KERN_INFO "Exiting traverser");
}

module_init(traverse_init);
module_exit(traverse_cleanup);
