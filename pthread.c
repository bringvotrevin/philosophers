#include "philosophers.h"

void	*t_func(void *data)
{
	int num;

	num = *(int *)data;
	printf("num %d\n", num);
	sleep(1);
	num *= num;
	printf("The end thread function\n");
	return ((void *)num);
}

int	main(void)
{
	pthread_t p_thread;
	int thr_id;
	int result;
	int	a;

	a = 200;
	thr_id = pthread_create(&p_thread, NULL, t_func, (void *)&a);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	pthread_join(p_thread, (void *)&result);
	printf("thread join : %d\n", result);
	printf("The end main function\n");
	return (0);
}