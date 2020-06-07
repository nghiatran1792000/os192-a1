#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/types.h>
#include <asm/unistd.h>
#include <asm/current.h>

struct proc_info { //info about a single process
	pid_t pid; //pid of the process
	char name[16]; //file name of the program executed
};

struct procinfos { //info about processes we need
	long studentID; //for the assignment testing
	struct proc_info proc; //process with pid or current process
	struct proc_info parent_proc; //parent process
	struct proc_info oldest_child_proc; //oldest child process
};



asmlinkage long sys_get_proc_info(pid_t pid, struct procinfos *info){
	// TODO: implement the system call
	info->studentID = 1813233;
	struct task_struct *task;
	printk("Student ID: %ld", info->studentID);
	if (pid == -1) {
		strcpy(info->proc.name, current->comm);
		info->proc.pid = current->pid;
	}
	else {
		info->proc.pid = pid;
		for_each_process(task) {
			if (task->pid == pid) {
				strcpy(info->proc.name, task->comm);
			}
		}
	}	
	for_each_process(task) {
		if (task->pid == info->proc.pid) {
			info->parent_proc.pid = task_ppid_nr(task);
		}
	}
	for_each_process(task) {
		if (task->pid == info->parent_proc.pid) {
			strcpy(info->parent_proc.name, task->comm);
		}
	}
	printk("Process ID: %d", info->proc.pid);
	printk("Process Name: %s", info->proc.name);
	printk("Parent ID: %d", info->parent_proc.pid);
	printk("Parent Name: %s", info->parent_proc.name);
    return 0;
}
