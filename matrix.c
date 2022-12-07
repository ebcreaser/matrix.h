#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

struct matrix
matrix_construct(int rows, int columns)
{
	struct matrix matrix;

	matrix.elements = malloc(rows * columns * sizeof(float));
	if (matrix.elements == NULL) {
		return matrix;
	}
	matrix.rows = rows;
	matrix.columns = columns;
 	matrix.size = rows * columns;

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

struct matrix
matrix_scalar_product(struct matrix *matrix_ptr, float scalar)
{
	struct matrix product;
	int i;

	product = matrix_construct(matrix_ptr->rows, matrix_ptr->columns);
	if (product.elements == NULL) {
		return product;
	}
	for (i = 0; i < product.size; ++i) {
		product.elements[i] = matrix_ptr->elements[i] * scalar;
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
