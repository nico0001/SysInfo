#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	prodCons_problem(atoi(argv[1]),atoi(argv[2]));
	
	philosopher_problem(5);

	return (0);
}
