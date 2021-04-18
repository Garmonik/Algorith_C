#ifndef _MATRIX_H_
#define _MATRIX_H_

// Структура матрицы
struct _matrix {
	int cols;
	int rows;
	int data[];
};

typedef struct _matrix Matrix;

#define MAT_IND(m, i, j)  (*((m)->data + (m)->cols*(i) + (j)))

Matrix* matrix_init(int cols, int rows);
void matrix_mul(Matrix* a, Matrix* b, Matrix* c);
void matrix_free(Matrix* m);
void matrix_copy(Matrix *a, Matrix *b);
void matrix_print(const char* name, Matrix* m);

#endif /* _MATRIX_H_ */