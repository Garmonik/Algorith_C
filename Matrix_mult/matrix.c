#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

/* 2x2   1 1
 *       1 0
 *
 * Matrix *m:
 * 4 bytes: 2 (cols)
 * 4 butes: 2 (rows)
 * 16 bytes: 1 (data)
 *           1
 *           1
 *           0
 * MAT_IND(m, 1, 1)  --->  (m->data + m->cols * 1 + 1)  ---> (m->data + 2 + 1)
 *
 * 3x3
 * 1 2 3
 * 4 5 6
 * 7 8 9
 *
 * 3
 * 3
 * 1
 * 2
 * 3
 * 4
 * 5
 * 6
 * 7
 * 8
 * 9
 *
 * A * B = C
 *
 * C   = Sum A   * B
 *  ij    k   ik    kj
 *
 */

// Инициализация памяти
Matrix* matrix_init(int cols, int rows){
	Matrix* m = calloc(sizeof(int), 2 + cols * rows);
	if(m){
		m->cols = cols;
		m->rows = rows;
	}
	return m;
}

// Очищение матрицы
void matrix_free(Matrix* m){
	free(m);
}

// Умножение матриц
void matrix_mul(Matrix* a, Matrix* b, Matrix* c){
	int i, j, k;
	for(i = 0; i < a -> rows; i++){
		for(j = 0; j < b -> cols; j++){
			MAT_IND(c, i, j) = 0;
			for(k = 0; k < a->cols; k++){
				MAT_IND(c, i, j) += MAT_IND(a, i, k) * MAT_IND(b, k, j);
			}
		}
	}
}

// Печетает матрицу
void matrix_print(const char* name, Matrix* m){
	int i, j;
	printf("Matrix: %s (%dx%d)\n", name, m -> rows, m -> cols);
	for(i = 0; i < m->rows; i++){
		for( j = 0; j < m->cols; j++){
			printf(" %d ", MAT_IND(m, i, j));
		}
		printf("\n");
	}
}

// Копируем матрицу
void matrix_copy(Matrix *a, Matrix* b){
	int i, j;
	for (i = 0; i < a -> rows; i++){
		for(j = 0; j < a -> cols; j++){
			MAT_IND(b, i, j) = MAT_IND(a, i, j);
		}
	}
}