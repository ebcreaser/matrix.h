#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

static int _ptrv_push(struct matrix *ptr);
static void _ptrv_free();

static struct matrix **_ptrv = NULL;
static int _ptrv_size = 0;
static int _ptrc      = 0;
static int const _PTRV_BLOCK = 4;

static int
_ptrv_push(struct matrix *ptr)
{
	static struct matrix **_temp;

	if (_ptrc == 0) {
		atexit(_ptrv_free);
	}
	if (_ptrc >= _ptrv_size) {
		_temp = realloc(_temp, (_ptrv_size + _PTRV_BLOCK) * sizeof(struct matrix *));
		if (_temp == NULL) {
			return -1;
		}
		_ptrv = _temp;
		_ptrv_size += _PTRV_BLOCK;
	}
	_ptrv[_ptrc] = ptr;
	++_ptrc;

	return 0;
}

static void
_ptrv_free()
{
	int i;

	if (_ptrv == NULL) {
		return;
	}
	for (i = 0; i < _ptrc; ++i) {
		free(_ptrv[i]->elements);
		free(_ptrv[i]);
		printf("freeing pointer %d...\n", i + 1);
	}
	free(_ptrv);
}

struct matrix *
matrix(int rows, int columns)
{
	struct matrix *matrix_ptr;

	matrix_ptr = malloc(sizeof(struct matrix));
	if (matrix_ptr == NULL) {
		return NULL;
	}
	if (_ptrv_push(matrix_ptr) < 0) {
		free(matrix_ptr);
		return NULL;
	}
	matrix_ptr->elements = malloc(rows * columns * sizeof(float));
	if (matrix_ptr->elements == NULL) {
		return NULL;
	}
	matrix_ptr->rows = rows;
	matrix_ptr->columns = columns;

	return matrix_ptr;
}

float *
get_matrix_index(struct matrix *matrix_ptr, int row, int column)
{
	return matrix_ptr->elements + matrix_ptr->columns * (row - 1) + column - 1;
}

void
set_matrix_index(struct matrix *matrix_ptr, int row, int column, float n)
{
	matrix_ptr->elements[matrix_ptr->columns * (row - 1) + column - 1] = n;
}
