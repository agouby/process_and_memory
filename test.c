#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>

struct pid_info {
        int pid;
        long state;
        void *stack;
};

int	get_pid_info(struct pid_info *ret, int pid)
{
	return syscall(335, ret, pid);
}

int	main(int ac, char **av)
{
	struct pid_info p_info;
	int ret;

	if (ac < 2)
	{
		printf("Give PID plz\n");
		goto err;
	}
	ret = get_pid_info(&p_info, atoi(av[1]));
	if (ret)
		goto err;
	printf("PID = %d\nSTATE = %d\nSTACK = %p\n",
			p_info.pid, p_info.state, p_info.stack);
	return 0;
err:
	printf("Error\n");
	return 1;
}
