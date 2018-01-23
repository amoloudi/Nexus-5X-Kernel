#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/kthread.h>

MODULE_LICENSE("Gibe Moni Ples");

int prevs[5000] = {0};
int running = 1;

struct task_struct* loop_thread;

void tasks_foreach_func(int calc)
{
  struct task_struct *task;
  for_each_process(task)
  {
    if(!calc)
    {
      prevs[task->pid] = task->mm->total_vm;
    }
    else
    {
      if(!prevs[task->pid])
      {
        if(task->mm->total_vm != prevs[task->pid])
        {
          if(task->mm->total_vm > prevs[task->pid])
          {
            printk(KERN_INFO "pid: %d | pname: %s | state: %ld | allocated: %lu\n", task->pid, task->comm, task->state, task->mm->total_vm - prevs[task->pid]);
          }
          else
          {
            printk(KERN_INFO "pid: %d | pname: %s | state: %ld | freed: %lu\n", task->pid, task->comm, task->state, prevs[task->pid] - task->mm->total_vm);
          }  
        }
      }
    }
  }
}

int while_func(void *data)
{
  while(running)
  {
    tasks_foreach_func(0);
    ssleep(1);
    tasks_foreach_func(1);
    ssleep(10);
  }
  return 0;
}

static int __init module_init_func(void)
{
  printk(KERN_INFO "Behold! The log in which I log my logs.\n");
  loop_thread = kthread_create(&while_func,NULL,"mem_announce");
  loop_thread = kthread_run(&while_func,NULL,"mem_announce");
  return 0;
}

static void __exit module_exit_func(void) 
{
  running = 0;
  kthread_stop(loop_thread);
  ssleep(1);
  printk(KERN_INFO "Lay thine eyes upon it and thou shalt see that it will be barren.\n");
}

module_init(mm_reporter_init);
module_exit(mm_reporter_cleanup);
