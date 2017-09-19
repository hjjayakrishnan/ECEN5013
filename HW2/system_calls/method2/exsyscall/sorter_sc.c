
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>

SYSCALL_DEFINE3(sortem, int32_t*, src, int32_t*, dst, int32_t, len)
{
	int32_t *buffer;
	int32_t i;
	int32_t j;
	int32_t temp;
  printk(KERN_INFO "Entering sys_sortem");
  printk(KERN_INFO "buffer size: %ld", (long)len);

  buffer = kmalloc(len*sizeof(int32_t), GFP_KERNEL);
  if(!buffer){
    printk(KERN_INFO "Kmalloc failed");
    return -EFAULT;
  }
  /* copy from user space (src) to kernel memory (buffer) */
  /* (to, from, number of bytes to copy) */
  if(copy_from_user(buffer, src, len*sizeof(int32_t)))
    return -EFAULT;

  printk(KERN_INFO "Sorting..");
  /* sort buffer */

	for(i=0;i<(len-1);i++){
    for(j=0;j<(len-i-1);j++){
      if (*(buffer+j)< *(buffer+j+1)){
        temp = *(buffer+j);
        *(buffer+j) = *(buffer+j+1);
        *(buffer+j+1) = temp;
      }
    }
  }
  printk(KERN_INFO "Completed sorting");

  /* copy from kernel space (src) to kernel memory (buffer) */
  /* (to, from, number of bytes to copy) */
  if(copy_to_user(dst, buffer, len*sizeof(int32_t)));
    return -EFAULT;

  kfree(buffer);
  printk(KERN_INFO "Exiting syscall");
}
