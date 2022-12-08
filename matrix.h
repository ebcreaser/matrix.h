#ifndef MATRIX_H
#define MATRIX_H

struct matrix
{
	int rows;
	int columns;
	int size;
	float *elements;
};

struct matrix matrix_construct(float *elements, int rows, int columns);
void matrix_free(struct matrix *matrix_ptr);
float matrix_get_element(struct matrix *matrix_ptr, int row, int column);
void matrix_set_element(struct matrix *matrix_ptr, int row, int column, float n);
int matrix_is_equal(struct matrix *A, struct matrix *B);
struct matrix matrix_sum(struct matrix *A, struct matrix *B);
struct matrix matrix_scalar_product(struct matrix *matrix_ptr, float scalar);
struct matrix matrix_product(struct matrix *A, struct matrix *B);
void matrix_print(struct matrix *matrix_ptr);

#endif
