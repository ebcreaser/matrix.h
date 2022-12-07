#include <stdlib.h>
#include <stdio.h>
#include "matrix-test.h"
#include "matrix.h"

static void matrix_test();
static void matrix_access_test();
static void matrix_scalar_product_test();
static void matrix_print_test();

static void
matrix_test()
{
	struct matrix matrix;
	int rows = 10;
	int columns = 20;
	int size = rows * columns;

	matrix = matrix_construct(rows, columns);
	if (matrix.elements != NULL) {
		fputs("matrix_test: test 1 passed\n", stdout);
	} else {
		fputs("matrix_test: test 1 failed\n", stdout);
		return;
	}
	if (matrix.rows == rows) {
		fputs("matrix_test: test 2 passed\n", stdout);
	} else {
		fputs("matrix_test: test 2 failed\n", stdout);
	}
	if (matrix.columns == columns) {
		fputs("matrix_test: test 3 passed\n", stdout);
	} else {
		fputs("matrix_test: test 3 failed\n", stdout);
	}
	if (matrix.size == size) {
		fputs("matrix_test: test 4 passed\n", stdout);
	} else {
		fputs("matrix_test: test 4 failed\n", stdout);
	}
	matrix_free(&matrix);
}

static void
matrix_access_test()
{
	struct matrix matrix;
	float n = 100;
	int row = 5;
	int column = 5;

	matrix = matrix_construct(10, 10);
	if (matrix.elements == NULL) {
		fputs("matrix_access_test: failed to allocate memory\n", stdout);
		return;
	}
	matrix_set_element(&matrix, row, column, n);
	if (matrix_get_element(&matrix, row, column) == n) {
		fputs("matrix_access_test: test 1 passed\n", stdout);
	} else {
		fputs("matrix_access_test: test 1 failed\n", stdout);
	}
	matrix_free(&matrix);
}

static void
matrix_scalar_product_test()
{
	struct matrix matrix;
	struct matrix product;
	float n = 100;
	float scalar = 5;
	float expected = n * scalar;
	int i;

	matrix = matrix_construct(10, 10);
	if (matrix.elements == NULL) {
		fputs("matrix_scalar_product_test: failed to allocate memory\n", stdout);
		return;
	}
	for (i = 0; i < matrix.size; ++i) {
		matrix.elements[i] = n;
	}
	product = matrix_scalar_product(&matrix, scalar);
	if (product.elements == NULL) {
		fputs("matrix_scalar_product_test: failed to allocate memory\n", stdout);
		return;
	}
	for (i = 0; i < product.size; ++i) {
		if (product.elements[i] != expected) {
			fputs("matrix_scalar_product_test: test 1 failed\n", stdout);
			return;
		}
	}
	fputs("matrix_scalar_product_test: test 1 passed\n", stdout);
	matrix_free(&matrix);
	matrix_free(&product);
}

static void
matrix_print_test()
{
	struct matrix matrix;
	float n = 100;
	int i;

	matrix = matrix_construct(10, 10);
	if (matrix.elements == NULL) {
		return;
	}
	fputs("matrix_print_test:\n", stdout);
	for (i = 0; i < matrix.size; ++i) {
		matrix.elements[i] = n;
	}
	matrix_print(&matrix);
	matrix_free(&matrix);
}

void
matrix_test_all()
{
	matrix_test();
	matrix_access_test();
	matrix_scalar_product_test();
	matrix_print_test();
}
