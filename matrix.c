#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

struct matrix *
matrix(int rows, int columns)
{
	struct matrix *matrix_ptr;

	matrix_ptr = malloc(sizeof(struct matrix));
	if (matrix_ptr == NULL) {
		return NULL;
	}
	matrix_ptr->elements = malloc(rows * columns * sizeof(float));
	if (matrix_ptr->elements == NULL) {
		free(matrix_ptr);
		return NULL;
	}
	matrix_ptr->rows = rows;
	matrix_ptr->columns = columns;

	return matrix_ptr;
}

void
matrix_free(struct matrix *matrix_ptr)
{
	free(matrix_ptr->elements);
	free(matrix_ptr);
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
matrix_size(struct matrix *matrix_ptr)
{
	return matrix_ptr->rows * matrix_ptr->columns;
}

void
matrix_scalar_multiply(struct matrix *matrix_ptr, float scalar)
{
	int i;

	for (i = 0; i < matrix_size(matrix_ptr); ++i) {
		matrix_ptr->elements[i] *= scalar;
	}

	return;
}

void
matrix_print(struct matrix *matrix_ptr)
{
	int size;
	int column;
	int i;

	size = matrix_size(matrix_ptr);
	for (i = 0; i < size; ++i) {
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
