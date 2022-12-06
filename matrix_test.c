#include <stdlib.h>
#include <stdio.h>
#include "matrix_test.h"
#include "matrix.h"

void
matrix_test()
{
	struct matrix *matrix_ptr;
	float n = 100;
	int i;

	matrix_ptr = matrix(10, 10);
	if (matrix_ptr == NULL) {
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < 16; ++i)
	{
		matrix(10,10);
	}
	if (matrix_ptr->rows == 10) {
		fputs("matrix_ptr test 1 passed\n", stdout);
	} else {
		fputs("matrix_ptr test 1 failed\n", stdout);
	}
	if (matrix_ptr->columns == 10) {
		fputs("matrix_ptr test 2 passed\n", stdout);
	} else {
		fputs("matrix_ptr test 2 failed\n", stdout);
	}
	set_matrix_index(matrix_ptr, 5, 5, n);
	if (*get_matrix_index(matrix_ptr, 5, 5) == n) {
		fputs("matrix_ptr test 3 passed\n", stdout);
	} else {
		fputs("matrix_ptr test 3 failed\n", stdout);
	}
}
