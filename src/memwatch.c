/* Memshare, quick and easy IPC.                                                   */
/* Copyright (C) 2012  Tommy Wiklund                                               */
/* This file is part of Memshare.                                                  */
/*                                                                                 */
/* Memshare is free software: you can redistribute it and/or modify                */
/* it under the terms of the GNU Lesser General Public License as published by     */
/* the Free Software Foundation, either version 3 of the License, or               */
/* (at your option) any later version.                                             */
/*                                                                                 */
/* Memshare is distributed in the hope that it will be useful,                     */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of                  */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   */
/* GNU Lesser General Public License for more details.                             */
/*                                                                                 */
/* You should have received a copy of the GNU Lesser General Public License        */
/* along with Memshare.  If not, see <http://www.gnu.org/licenses/>.               */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memshare.h"
#include "memshare_api.h"

void print_usage()
{
	printf("Usage: memwatch [arguments]\n");
	printf("\t-l\t\tList every proc registered\n");
	printf("\t-ld <proc name>\t\tList detailed info of proc\n");
	printf("\tv 1.0\n");
}

int main(int argc, char *argv[])
{
	int send, rec, data_size, mode = 0, index, i;
	char dest_proc[PROC_NAME_SIZE], *procptr;

	memset(dest_proc, '\0', PROC_NAME_SIZE);

	/* Parse the parameters */
	if (argc < 2) {
		print_usage();
		exit(2);
	}
	if (!strcmp(argv[1], "-l")) {
		if (argc != 2) {
			print_usage();
			exit(2);
		}
		mode = 1;
	} else if (!strcmp(argv[1], "-ld")) {
		if (argc != 3) {
			print_usage();
			exit(2);
		}
		mode = 2;
		strncpy(dest_proc, argv[2], (PROC_NAME_SIZE - 1));
	}
	if (mode == 0) {
		print_usage();
		exit(3);
	}

	/*set_print_level(CH_DEBUG); */
	init_memshare("memwatch", 0, 0);

	switch (mode) {
	case 2:
		if ((index = get_proc_index(dest_proc)) != -1) {
			get_proc_info(index, &send, &rec, &data_size, &procptr);
			printf
			    ("Index %2d %18s  Sent %2d  Received %2d, Data size of %2d\n",
			     index, procptr, send, rec, data_size);
			exit(0);
		}
		printf("No such process %s\n", dest_proc);
		exit(1);
		break;

	case 1:
		for (i = 0; i < NUMBER_OF_PROCS; i++) {
			if (check_proc_entry(i)) {
				get_proc_info(i, &send, &rec, &data_size,
					      &procptr);
				printf
				    ("Index %2d %18s  Sent %2d  Received %2d, Data size of %2d\n",
				     i, procptr, send, rec, data_size);
			}
		}
		exit(0);
		break;

	default:
		/* No place to be */
		break;
	}

	/* No place to be */
	exit(2);
}
