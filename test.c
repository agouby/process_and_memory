#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <limits.h>
#include <inttypes.h>

#define CHILD_MAX	512

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

int	get_pid_info(struct pid_info *ret, int pid)
{
	return syscall(335, ret, pid);
}

char	*fetch_state(int state)
{
	char *str;

	switch (state) {
		case -1:
			str = "unrunnable";
			break;
		case 0:
			str = "runnable";
			break;
		default:
			str = "stopped";
			break;
	}
	return (str);
}

void	print_pid_info(int pid)
{
	struct pid_info p_info;
	int ret;
	int i;
	
	printf("\n\n*** PID_INFOS ***\n\n");
	ret = get_pid_info(&p_info, pid);
	if (ret)
		goto err;
	printf("PID = %d\n", p_info.pid);
	printf("STACK = %p\n", p_info.stack);
	printf("STATE = %d %s\n", p_info.state, fetch_state(p_info.state));
	printf("AGE = %lu\n", p_info.age);
	printf("ROOT PATH = %s\n", p_info.root_path);
	printf("PWD PATH = %s\n", p_info.pwd_path);

	printf("CHILDREN:\n");

	for (i = 0; p_info.children[i]; i++) {
		printf("\t CHILD PID: %d\n", p_info.children[i]);
	}
	
	for (i = 0; p_info.children[i]; i++) {
		print_pid_info(p_info.children[i]);
	}
	return ;
err:
	printf("Error\n");
}

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Give PID plz\n");
		return 1;
	}
	print_pid_info(atoi(av[1]));
	return 0;
}
