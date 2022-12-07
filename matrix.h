#ifndef MATRIX_H
#define MATRIX_H

struct matrix
{
	int rows;
	int columns;
	int size;
	float *elements;
};

struct matrix matrix_construct(int rows, int columns);
void matrix_free(struct matrix *matrix_ptr);
float matrix_get_element(struct matrix *matrix_ptr, int row, int column);
void matrix_set_element(struct matrix *matrix_ptr, int row, int column, float n);
struct matrix matrix_scalar_product(struct matrix *matrix_ptr, float scalar);
void matrix_print(struct matrix *matrix_ptr);

#endif
