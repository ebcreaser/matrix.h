#include <stdlib.h>
#include <stdio.h>
#include "matrix-test.h"
#include "matrix.h"

static void matrix_constuct_test();
static void matrix_access_test();
static void matrix_scalar_product_test();
static void matrix_product_test();
static void matrix_print_test();

static void
matrix_constuct_test()
{
	struct matrix matrix;
	float elements[200] = {0};
	int rows = 10;
	int columns = 20;
	int size = rows * columns;

	matrix = matrix_construct(elements, rows, columns);
	if (matrix.elements == elements) {
		fputs("matrix_construct_test: test 1 passed\n", stdout);
	} else {
		fputs("matrix_construct_test: test 1 failed\n", stdout);
	}
	if (matrix.rows == rows) {
		fputs("matrix_construct_test: test 2 passed\n", stdout);
	} else {
		fputs("matrix_construct_test: test 2 failed\n", stdout);
	}
	if (matrix.columns == columns) {
		fputs("matrix_construct_test: test 3 passed\n", stdout);
	} else {
		fputs("matrix_construct_test: test 3 failed\n", stdout);
	}
	if (matrix.size == size) {
		fputs("matrix_construct_test: test 4 passed\n", stdout);
	} else {
		fputs("matrix_construct_test: test 4 failed\n", stdout);
	}
}

static void
matrix_access_test()
{
	struct matrix matrix;
	float elements[100];
	float n = 100;
	int row = 5;
	int column = 5;

	matrix = matrix_construct(elements, 10, 10);
	matrix_set_element(&matrix, row, column, n);
	if (matrix_get_element(&matrix, row, column) == n) {
		fputs("matrix_access_test: test 1 passed\n", stdout);
	} else {
		fputs("matrix_access_test: test 1 failed\n", stdout);
	}
}

static void
matrix_scalar_product_test()
{
	struct matrix matrix;
	struct matrix product;
	float elements[100];
	float n = 100;
	float scalar = 5;
	float expected = n * scalar;
	int i;

	matrix = matrix_construct(elements, 10, 10);
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
	matrix_free(&product);
}

static void
matrix_print_test()
{
	struct matrix matrix;
	float elements[] =
	{
		1, 2,
		3, 4
	};

	matrix = matrix_construct(elements, 2, 2);
	fputs("matrix_print_test:\n", stdout);
	matrix_print(&matrix);
}

static void
matrix_product_test()
{
	struct matrix A;
	struct matrix B;
	struct matrix product;
	float elements_A[] =
	{
		2, 2,
		2, 2,
		2, 2
	};
	float elements_B[] =
	{
		3, 3, 3, 3,
		3, 3, 3, 3
	};

	A = matrix_construct(elements_A, 3, 2);
	B = matrix_construct(elements_B, 2, 4);
	product = matrix_product(&A, &B);
	if (product.elements == NULL) {
		fputs("matrix_product_test: failed to allocate memory\n", stdout);
		return;
	}
	matrix_print(&product);
	matrix_free(&product);

	return;
}

void
matrix_test_all()
{
	matrix_constuct_test();
	matrix_access_test();
	matrix_scalar_product_test();
	matrix_product_test();
	matrix_print_test();
}
