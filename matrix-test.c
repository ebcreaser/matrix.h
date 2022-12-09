#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "matrix-test.h"

static void matrix_construct_test();
static void matrix_get_unit_test();
static void matrix_access_test();
static void matrix_is_equal_test();
static void matrix_sum_test();
static void matrix_scalar_product_test();
static void matrix_product_test();
static void matrix_print_test();

static void
matrix_construct_test()
{
	struct matrix matrix;
	float elements[200] = {0};
	int rows = 10;
	int columns = 20;
	int size = rows * columns;

	matrix_construct(&matrix, rows, columns);
	matrix.elements = elements;
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
matrix_get_unit_test()
{
	struct matrix A;
	struct matrix *u_ptr;
	struct matrix *p_ptr;
	float elements[] =
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	};

	matrix_construct(&A, 3, 3);
	A.elements = elements;
	u_ptr = matrix_get_unit(A.rows);
	if (u_ptr == NULL) {
		fputs("matrix_get_unit_test: failed to allocate memory\n", stdout);
		return;
	}
	p_ptr = matrix_product(u_ptr, &A);
	if (p_ptr == NULL) {
		fputs("matrix_get_unit_test: failed to allocate memory\n", stdout);
		matrix_free(u_ptr);
		return;
	}
	if (matrix_is_equal(&A, p_ptr)) {
		fputs("matrix_get_unit_test: test 1 passed\n", stdout);
	} else {
		fputs("matrix_get_unit_test: test 1 failed\n", stdout);
	}
	matrix_free(u_ptr);
	matrix_free(p_ptr);
}

static void
matrix_access_test()
{
	struct matrix matrix;
	float elements[100];
	float n = 100;
	int row = 5;
	int column = 5;

	matrix_construct(&matrix, 10, 10);
	matrix.elements = elements;
	matrix_set_element(&matrix, row, column, n);
	if (matrix_get_element(&matrix, row, column) == n) {
		fputs("matrix_access_test: test 1 passed\n", stdout);
	} else {
		fputs("matrix_access_test: test 1 failed\n", stdout);
	}
}

static void
matrix_is_equal_test()
{
	struct matrix A;
	struct matrix B;
	float elements[] =
	{
		1, 2, 3,
	};
	
	matrix_construct(&A, 1, 3);
	A.elements = elements;
	matrix_construct(&B, 1, 3);
	B.elements = elements;
	if (matrix_is_equal(&A, &B)) {
		fputs("matrix_is_equal_test: test 1 passed\n", stdout);
	} else {
		fputs("matrix_is_equal_test: test 1 failed\n", stdout);
	}
}

static void
matrix_scalar_product_test()
{
	struct matrix matrix;
	struct matrix *p_ptr;
	float elements[100];
	float n = 100;
	float scalar = 5;
	int i;

	matrix_construct(&matrix, 10, 10);
	matrix.elements = elements;
	for (i = 0; i < matrix.size; ++i) {
		matrix.elements[i] = n;
	}
	p_ptr = matrix_scalar_product(&matrix, scalar);
	if (p_ptr->elements == NULL) {
		fputs("matrix_scalar_product_test: failed to allocate memory\n", stdout);
		return;
	}
	for (i = 0; i < matrix.size; ++i) {
		if (p_ptr->elements[i] != n * scalar) {
			fputs("matrix_scalar_product_test: test 1 failed\n", stdout);
			matrix_free(p_ptr);
			return;
		}
	}
	fputs("matrix_scalar_product_test: test 1 passed\n", stdout);

	matrix_free(p_ptr);
}

static void
matrix_sum_test()
{
	struct matrix A;
	struct matrix B;
	struct matrix *s_ptr;
	struct matrix expected;
	float A_elements[] =
	{
		1, 1, 1,
		1, 1, 1,
		1, 1, 1
	};
	float B_elements[] =
	{
		2, 2, 2,
		2, 2, 2,
		2, 2, 2
	};
	float expected_elements[] = 
	{
		3, 3, 3,
		3, 3, 3,
		3, 3, 3
	};

	matrix_construct(&A, 3, 3);
	A.elements = A_elements;
	matrix_construct(&B, 3, 3);
	B.elements = B_elements;
	matrix_construct(&expected, 3, 3);
	expected.elements = expected_elements;
	s_ptr = matrix_sum(&A, &B);
	if (matrix_is_equal(&expected, s_ptr)) {
		fputs("matrix_sum_test: test 1 passed\n", stderr);
	} else {
		fputs("matrix_sum_test: test 1 failed\n", stderr);
	}
	matrix_free(s_ptr);

	return;
}

static void
matrix_product_test()
{
	struct matrix A;
	struct matrix B;
	struct matrix *p_ptr;
	struct matrix expected;
	float A_elements[] =
	{
		2, 2,
		2, 2,
		2, 2
	};
	float B_elements[] =
	{
		3, 3, 3, 3,
		3, 3, 3, 3
	};
	float expected_elements[] =
	{
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12
	};

	matrix_construct(&A, 3, 2);
	A.elements = A_elements;
	matrix_construct(&B, 2, 4);
	B.elements = B_elements;
	matrix_construct(&expected, 3, 4);
	expected.elements = expected_elements;
	p_ptr = matrix_product(&A, &B);
	if (matrix_is_equal(p_ptr, &expected)) {
		fputs("matrix_product_test: test 1 passed\n", stdout);
	} else {
		fputs("matrix_product_test: test 1 failed\n", stdout);
	}

	matrix_free(p_ptr);

	return;
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

	matrix_construct(&matrix, 2, 2);
	matrix.elements = elements;
	fputs("matrix_print_test:\n", stdout);
	matrix_print(&matrix);
}

void
matrix_test_all()
{
	matrix_construct_test();
	matrix_get_unit_test();
	matrix_access_test();
	matrix_is_equal_test();
	matrix_sum_test();
	matrix_scalar_product_test();
	matrix_product_test();
	matrix_print_test();
}
