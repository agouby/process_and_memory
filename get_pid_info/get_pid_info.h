#ifndef GET_PID_INFO_H
#define GET_PID_INFO_H

#include <linux/limits.h>

#define CHILD_MAX 512

struct pid_info {
	int pid;
	int parent_pid;
	int state;
	void const *stack;
	uint64_t age;
	int children[CHILD_MAX + 1];
	char root_path[PATH_MAX + 1];
	char pwd_path[PATH_MAX + 1];
};

#endif
