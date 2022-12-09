#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

void
matrix_construct(struct matrix *m_ptr, float *elements, int rows, int cols)
{
	m_ptr->elements = elements;
	m_ptr->rows = rows;
	m_ptr->columns = cols;
 	m_ptr->size = rows * cols;
}

struct matrix *
matrix_get_unit(int rows)
{
	struct matrix *m_ptr;
	int i;

	m_ptr = malloc(sizeof(struct matrix));
	if (m_ptr == NULL) {
		return NULL;
	}
	m_ptr->rows = rows;
	m_ptr->columns = rows;
	m_ptr->size = rows * rows;
	m_ptr->elements = malloc(m_ptr->size * sizeof(float));
	if (m_ptr->elements == NULL) {
		free(m_ptr);
		return NULL;
	}
	for (i = 0; i < m_ptr->size; ++i) {
		/* 1 if row and column are equal, 0 otherwise */
		m_ptr->elements[i] = (i / rows == i % rows);
	}

	return m_ptr;
}

void
matrix_free(struct matrix *m_ptr)
{
	free(m_ptr->elements);
	free(m_ptr);
}

int
matrix_is_equal(struct matrix *A_ptr, struct matrix *B_ptr)
{
	int i;

	if (A_ptr->rows != B_ptr-> rows || A_ptr->columns != B_ptr->columns) {
		return 0;
	}
	for (i = 0; i < A_ptr->size; ++i) {
		if (A_ptr->elements[i] != B_ptr->elements[i]) {
			return 0;
		}
	}

	return 1;
}

struct matrix *
matrix_sum(struct matrix *A_ptr, struct matrix *B_ptr)
{
	struct matrix *s_ptr;
	int i;

	s_ptr = malloc(sizeof(struct matrix));
	if (s_ptr == NULL) {
		return NULL;
	}
	if (A_ptr->rows != B_ptr->rows || A_ptr->columns != B_ptr->columns) {
		free(s_ptr);
		return NULL;
	}
	matrix_construct(s_ptr, NULL, A_ptr->rows, A_ptr->columns);
	s_ptr->elements = malloc(s_ptr->size * sizeof(float));
	if (s_ptr->elements == NULL) {
		free(s_ptr);
		return NULL;
	}
	for (i = 0; i < s_ptr->size; ++i) {
		s_ptr->elements[i] = A_ptr->elements[i] + B_ptr->elements[i];
	}

	return s_ptr;
}

struct matrix *
matrix_scalar_product(struct matrix *m_ptr, float scalar)
{
	struct matrix *p_ptr;
	int i;

	p_ptr = malloc(sizeof(struct matrix));
	if (p_ptr == NULL) {
		return p_ptr;
	}
	matrix_construct(p_ptr, NULL, m_ptr->rows, m_ptr->columns);
	p_ptr->elements = malloc(m_ptr->size * sizeof(float));
	if (p_ptr->elements == NULL) {
		free(p_ptr);
		return NULL;
	}
	for (i = 0; i < p_ptr->size; ++i) {
		p_ptr->elements[i] = m_ptr->elements[i] * scalar;
	}

	return p_ptr;
}

struct matrix *
matrix_product(struct matrix *A_ptr, struct matrix *B_ptr)
{
	struct matrix *p_ptr;
	int i, j, k;

	p_ptr = malloc(sizeof(struct matrix));
	if (p_ptr == NULL) {
		return NULL;
	}
	if (A_ptr->columns != B_ptr->rows) {
		free(p_ptr);
		return NULL;
	}
	matrix_construct(p_ptr, NULL, A_ptr->rows, B_ptr->columns);
	p_ptr->elements = malloc(p_ptr->size * sizeof(float));
	if (p_ptr->elements == NULL) {
		free(p_ptr);
		return NULL;
	}
	for (i = 0; i < A_ptr->rows; ++i) {
		for (j = 0; j < B_ptr->columns; ++j) {
			for (k = 0; k < A_ptr->columns; ++k) {
				p_ptr->elements[i * p_ptr->columns + j] +=
					A_ptr->elements[i * A_ptr->columns + k] *
					B_ptr->elements[k * B_ptr->columns + j]; 
			}
		}
	}

	return p_ptr;
}

void
matrix_print(struct matrix *m_ptr)
{
	int column;
	int i;

	for (i = 0; i < m_ptr->size; ++i) {
		column = i % m_ptr->columns;
		if (column == 0) {
			printf("[ %7.3f,", m_ptr->elements[i]);
		} else if (column == m_ptr->columns - 1) {
			printf(" %7.3f ]\n", m_ptr->elements[i]);
		} else {
			printf(" %7.3f, ", m_ptr->elements[i]);
		}
	}
}
