#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/kthread.h>

MODULE_LICENSE("Gibe Moni Ples");

int prevs[5000];
int running = 1;

void dfs(struct task_struct *task, int calc)
{
  struct task_struct *task_next;
  struct list_head *list;

  list_for_each(list, &task->children) 
  {
    task_next = list_entry(list, struct task_struct, sibling);
    if(!calc)
    {
      prevs[task_next->pid] = task_next->mm->total_vm;
    }
    else
    {
      if(task_next->mm->total_vm != prevs[task_next->pid])
      {
        if(task_next->mm->total_vm > prevs[task_next->pid])
        {
          printk(KERN_INFO "pid: %d | allocated: %d\n", task_next->pid, task_next->mm->total_vm - prevs[task_next->pid]);
        }
        else
        {
          printk(KERN_INFO "pid: %d | freed: %d\n", task_next->pid, prevs[task_next->pid] - task_next->mm->total_vm);
        }
      }
    }
    dfs(task_next, calc);
  }  
}

int while_func(void *data)
{
  while(running)
  {
    dfs(&init_task, 0);
    ssleep(1);
    dfs(&init_task, 1);
    ssleep(10);
  }
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
  return 0;
}

module_init(mm_reporter_init);
module_exit(mm_reporter_cleanup);
