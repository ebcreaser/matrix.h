#ifndef MATRIX_H
#define MATRIX_H

struct matrix
{
	int rows;
	int columns;
	int size;
	float *elements;
};

void matrix_construct(struct matrix *m_ptr, int rows, int columns);
struct matrix *matrix_get_unit(int rows);
void matrix_free(struct matrix *m_ptr);
float matrix_get_element(struct matrix *m_ptr, int row, int col);
void matrix_set_element(struct matrix *m_ptr, int row, int col, float n);
int matrix_is_equal(struct matrix *A, struct matrix *B);
struct matrix *matrix_sum(struct matrix *A, struct matrix *B);
struct matrix *matrix_scalar_product(struct matrix *m_ptr, float scalar);
struct matrix *matrix_product(struct matrix *A, struct matrix *B);
void matrix_print(struct matrix *m_ptr);

#endif
