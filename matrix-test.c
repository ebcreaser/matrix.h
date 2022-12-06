#include <stdlib.h>
#include <stdio.h>
#include "matrix-test.h"
#include "matrix.h"

static void matrix_test();
static void matrix_access_test();
static void matrix_print_test();

static void
matrix_test()
{
	struct matrix *matrix_ptr = NULL;

	matrix_ptr = matrix(10, 10);
	if (matrix_ptr != NULL) {
		fputs("matrix_test: test 1 passed\n", stdout);
	} else {
		fputs("matrix_test: test 1 failed\n", stdout);
		return;
	}
	if (matrix_ptr->rows == 10) {
		fputs("matrix_test: test 2 passed\n", stdout);
	} else {
		fputs("matrix_test: test 2 failed\n", stdout);
	}
	if (matrix_ptr->columns == 10) {
		fputs("matrix_test: test 3 passed\n", stdout);
	} else {
		fputs("matrix_test: test 3 failed\n", stdout);
	}
	free(matrix_ptr);
}

static void
matrix_access_test()
{
	struct matrix *matrix_ptr;
	int n = 100;
	int row = 5;
	int column = 5;

	matrix_ptr = matrix(10, 10);
	if (matrix_ptr == NULL) {
		return;
	}
	matrix_set_element(matrix_ptr, row, column, n);
	if (matrix_get_element(matrix_ptr, row, column) == n) {
		fputs("matrix_access_test: test 1 passed\n", stdout);
	} else {
		fputs("matrix_access_test: test 1 failed\n", stdout);
	}
	free(matrix_ptr);
}

static void
matrix_print_test()
{
	struct matrix *matrix_ptr;
	int n = 100;
	int i;

	matrix_ptr = matrix(10, 10);
	if (matrix_ptr == NULL) {
		return;
	}
	fputs("matrix_print_test:\n", stdout);
	for (i = 0; i < matrix_size(matrix_ptr); ++i) {
		matrix_ptr->elements[i] = n;
	}
	matrix_print(matrix_ptr);
	free(matrix_ptr);
}

void
matrix_test_all()
{
	matrix_test();
	matrix_access_test();
	matrix_print_test();
}
