
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>

SYSCALL_DEFINE3(sortem, unsigned long*, src, unsigned long*, dst, unsigned long, len)
{
	unsigned long *buffer;
	unsigned long i;
	unsigned long j;
	unsigned long temp;
  printk(KERN_INFO "Entering sys_sortem");
  printk(KERN_INFO "buffer size: %lu", len);

  buffer = kmalloc(len*sizeof(long), GFP_KERNEL);
  if(!buffer){
    printk(KERN_INFO "Kmalloc failed");
    return -EFAULT;
  }
  /* copy from user space (src) to kernel memory (buffer) */
  /* (to, from, number of bytes to copy) */
  if(copy_from_user(buffer, src, len*sizeof(long)))
    return -EFAULT;

	for(i=0;i<len;i++)
		printk(KERN_INFO "Element %lu: %lu", i, *(buffer+i));
  printk(KERN_INFO "Sorting..");
  /* sort buffer */

  for(i=0;i<len;i++){
    for(j=0;j<len;j++){
      if (*(buffer+i)< *(buffer+j)){
        temp = *(buffer+i);
        *(buffer+i) = *(buffer+j);
        *(buffer+j) = temp;
      }
    }
  }
  printk(KERN_INFO "Completed sorting");
	for(i=0;i<len;i++)
		printk(KERN_INFO "Element %lu: %lu", i, *(buffer+i));
  /* copy from kernel space (src) to kernel memory (buffer) */
  /* (to, from, number of bytes to copy) */
  if(copy_to_user(dst, buffer, len*sizeof(long)));
    return -EFAULT;

  kfree(buffer);
  printk(KERN_INFO "Exiting syscall");
}
