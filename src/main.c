#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	prodCons_problem(atoi(argv[1]),atoi(argv[2]));
	
	philosopher_problem(atoi(argv[3]));

	return (0);
}
