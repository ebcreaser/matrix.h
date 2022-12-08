#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

struct matrix
matrix_construct(float *elements, int rows, int columns)
{
	struct matrix matrix;

	matrix.rows = rows;
	matrix.columns = columns;
 	matrix.size = rows * columns;
	if (elements == NULL) {
		matrix.elements = malloc(matrix.size * sizeof(float));
		if (matrix.elements == NULL) {
			return matrix;
		}
	} else {
		matrix.elements = elements;
	}

	return matrix;
}

void
matrix_free(struct matrix *matrix_ptr)
{
	free(matrix_ptr->elements);
}

void
matrix_set_element(struct matrix *matrix_ptr, int row, int column, float n)
{
	matrix_ptr->elements[matrix_ptr->columns * (row - 1) + column - 1] = n;
}

float
matrix_get_element(struct matrix *matrix_ptr, int row, int column)
{
	return matrix_ptr->elements[matrix_ptr->columns * (row - 1) + column - 1];
}

int
matrix_is_equal(struct matrix *A, struct matrix *B)
{
	int i;

	if (A->rows != B-> rows || A->columns != B->columns) {
		return 0;
	}
	for (i = 0; i < A->size; ++i) {
		if (A->elements[i] != B->elements[i]) {
			return 0;
		}
	}

	return 1;
}

struct matrix
matrix_sum(struct matrix *A, struct matrix *B)
{
	struct matrix sum;
	int i;

	if (A->rows != B->rows || A->columns != B->columns) {
		sum.elements = NULL;
		return sum;
	}
	sum = matrix_construct(NULL, A->rows, A->columns);
	if (sum.elements == NULL) {
		return sum;
	}
	for (i = 0; i < sum.size; ++i) {
		sum.elements[i] = A->elements[i] + B->elements[i];
	}

	return sum;
}

struct matrix
matrix_scalar_product(struct matrix *matrix_ptr, float scalar)
{
	struct matrix product;
	int i;

	product = matrix_construct(NULL, matrix_ptr->rows, matrix_ptr->columns);
	if (product.elements == NULL) {
		return product;
	}
	for (i = 0; i < product.size; ++i) {
		product.elements[i] = matrix_ptr->elements[i] * scalar;
	}

	return product;
}

struct matrix
matrix_product(struct matrix *A, struct matrix *B)
{
	struct matrix product;
	int i, j, k;

	if (A->columns != B->rows) {
		product.elements = NULL;
		return product;
	}
	product = matrix_construct(NULL, A->rows, B->columns);
	if (product.elements == NULL) {
		return product;
	}
	for (i = 0; i < A->rows; ++i) {
		for (j = 0; j < B->columns; ++j) {
			for (k = 0; k < A->columns; ++k) {
				product.elements[i * product.columns + j] +=
					A->elements[i * A->columns + k] *
					B->elements[k * B->columns + j]; 
			}
		}
	}

	return product;

}

void
matrix_print(struct matrix *matrix_ptr)
{
	int column;
	int i;

	for (i = 0; i < matrix_ptr->size; ++i) {
		column = i % matrix_ptr->columns;
		if (column == 0) {
			printf("[ %7.3f,", matrix_ptr->elements[i]);
		} else if (column == matrix_ptr->columns - 1) {
			printf(" %7.3f ]\n", matrix_ptr->elements[i]);
		} else {
			printf(" %7.3f, ", matrix_ptr->elements[i]);
		}
	}
}
