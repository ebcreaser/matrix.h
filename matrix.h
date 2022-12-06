#ifndef MATRIX_H
#define MATRIX_H

struct matrix
{
	int rows, columns;
	float *elements;
};

struct matrix *matrix (int rows, int columns);
void matrix_free(struct matrix *matrix_ptr);
float *matrix_get_element(struct matrix *matrix_ptr, int row, int column);
void matrix_set_element(struct matrix *matrix_ptr, int row, int column, float n);

#endif
