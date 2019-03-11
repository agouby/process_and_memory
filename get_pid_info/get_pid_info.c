#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/pid.h>

#include "get_pid_info.h"

SYSCALL_DEFINE2(get_pid_info, struct pid_info __user*, retinfo, int, pid)
{
	struct pid *pid_struct;
	struct task_struct *task_pid;

	pid_struct = find_get_pid(pid);
	if (pid_struct == NULL)
		return -EINVAL;
	task_pid = get_pid_task(pid_struct, PIDTYPE_PID);
	if (task_pid == NULL)
		return -EINVAL;
	retinfo->pid = task_pid->pid;
	retinfo->state = task_pid->state;
	retinfo->stack = task_pid->stack;
	return (0);
}
