#ifndef GET_PID_INFO_H
#define GET_PID_INFO_H

struct pid_info {
	int pid;
	long state;
	void *stack;
};

#endif
