

SYSCALL_DEFINE3(sortem, unsigned long *, src, unsigned long *, dst, unsigned long, len){

  printk(KERN_INFO "Entering sys_sortem");
  printk(KERN_INFO "buffer size: %lu", len);
  unsigned long *buffer;
  buffer = kmalloc(sizeof(long), GFP_USER);
  if(!buffer){
    printk(KERN_INFO "Kmalloc failed");
    return -EFAULT;
  }
  /* copy from user space (src) to kernel memory (buffer) */
  /* (to, from, number of bytes to copy) */
  if(copy_from_user(buffer, src, len))
    return -EFAULT;
  printk(KERN_INFO "Sorting..");
  /* sort buffer */
  unsigned long i, j, temp;
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
  /* copy from kernel space (src) to kernel memory (buffer) */
  /* (to, from, number of bytes to copy) */
  if(copy_to_user(dst, buffer, len));
    return -EFAULT;

  kfree(buffer);
  printk(KERN_INFO "Exiting syscall");
}
