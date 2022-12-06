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
	for (i = 0; i < matrix_size(matrix_ptr); ++i) {
		matrix_ptr->elements[i] = 0;
	}
	matrix_set_element(matrix_ptr, 5, 5, n);
	if (matrix_get_element(matrix_ptr, 5, 5) == n) {
		fputs("matrix_ptr test 3 passed\n", stdout);
	} else {
		fputs("matrix_ptr test 3 failed\n", stdout);
	}
	matrix_print(matrix_ptr);
	free(matrix_ptr);
}
