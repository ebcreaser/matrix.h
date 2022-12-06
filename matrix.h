#ifndef MATRIX_H
#define MATRIX_H

struct matrix
{
	int rows, columns;
	float *elements;
};

struct matrix *matrix (int rows, int columns);
float *get_matrix_index(struct matrix *matrix_ptr, int row, int column);
void set_matrix_index(struct matrix *matrix_ptr, int row, int column, float n);

#endif
