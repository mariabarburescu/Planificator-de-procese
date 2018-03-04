#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structura.h"
#include "FCFS.h"
#include "SJF.h"
#include "RR.h"
#include "PP.h"
#include "Bonus.h"

int main(int argc, char *argv[])
{
	int plan, cuanta, niv_priority;
	FILE *in;
	FILE *out;
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	fscanf(in, "%d", &plan);
	if (plan == 1)
		FCFS_function(in, out);
	if (plan == 2)
		SJF_function(in, out);
	if (plan == 3)
	{
		fscanf(in, "%d", &cuanta);
		RR_function(in, out, cuanta);
	}
	if (plan == 4)
	{
		fscanf(in, "%d", &cuanta);
		fscanf(in, "%d", &niv_priority);
		PP_function(in, out, cuanta, niv_priority);
	}
	if (plan == 5)
	{
		fscanf(in, "%d", &cuanta);
		fscanf(in, "%d", &niv_priority);
		Bonus_function(in, out, cuanta, niv_priority);
	}
	fclose(in);
	fclose(out);
	return 0;
}