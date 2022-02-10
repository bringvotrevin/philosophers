#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int	main(void)
{
	char	 msg;
	char	bit;

	bit = 0b00000001;
	scanf("%c", &msg);
	if (msg & bit)
		printf("1\n");
	if (msg & bit<<1)
		printf("2\n");
	if (msg & bit<<2)
		printf("4\n");
	if (msg & bit<<3)
		printf("8\n");
	return (0);
}