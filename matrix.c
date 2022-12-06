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

float *
matrix_get_element(struct matrix *matrix_ptr, int row, int column)
{
	return matrix_ptr->elements + matrix_ptr->columns * (row - 1) + column - 1;
}

void
matrix_set_element(struct matrix *matrix_ptr, int row, int column, float n)
{
	matrix_ptr->elements[matrix_ptr->columns * (row - 1) + column - 1] = n;
}
