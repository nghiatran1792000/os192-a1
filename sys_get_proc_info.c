#include <linux/kernel.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/sched.h>
#include <string.h>
#include <sys/utsname.h>
#include <errno.h>

struct procinfos { //info about processes we need
	long studentID; //for the assignment testing
	struct proc_info proc; //process with pid or current process
	struct proc_info parent_proc; //parent process
	struct proc_info oldest_child_proc; //oldest child process
};

struct proc_info { //info about a single process
	pid_t pid; //pid of the process
	char name[16]; //file name of the program executed
};

asmlinkage ;long sys_get_proc_info(pid_t pid, struct procinfos *info){
	// TODO: implement the system call
	info->studentID = 1813233;
	info->proc.pid = pid;
	char* nameTemp = (char*)calloc(16,sizeof(char));
    if(nameTemp){
        sprintf(nameTemp, "/proc/%d/cmdline",pid);
        FILE* f = fopen(nameTemp,"r");
        if(f){
            size_t size;
            size = fread(nameTemp, sizeof(char), 16, f);
            if(size>0){
                if('\n'==nameTemp[size-1])
                    nameTemp[size-1]='\0';
            }
            fclose(f);
        }
		else return EINVAL;
    }
	for (int i = 0; i < 16; i++) info->proc.name[i] = nameTemp[i];
	

}
