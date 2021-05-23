#include <stdio.h>
#include <stdlib.h>
#include "vector_i.h"
#include "vector_d.h"
#include "matrix.h"

void read_matrix(matrix *mat){
    d_create(&mat->values);
    v_create(&mat->indices);
    scanf("%d%d",&mat->m, &mat->n);
    double a;
    for(int i = 0; i < mat->m; i++) {
        for (int j = 0; j < mat->n; j++) {
            if (scanf("%lf", &a) > 0) {
            if (a != 0) {
                v_append(&mat->indices, mat->n * i + j);
                d_append(&mat->values, a);
            }
            } else continue;
        }
    }
}
void print_matrix(matrix *mat) {
    int cur = 0;
    for(int i = 0; i < mat->m; i++) {
        for(int j = 0; j < mat->n; j++) {
            if (d_size(&mat->values) > 0) {
                if (v_get(&mat->indices, cur) / mat->n == i && v_get(&mat->indices, cur) % mat->n == j &&
                    cur < mat->indices.size) {
                    printf("%0.3lf ", d_get(&mat->values, cur));
                    cur++;
                } else
                    printf("0 ");
            } else {printf("Нулевая матрица\n"); continue;}
        }
        puts("");
    }
}
int coords_to_index(matrix*mat, int i, int j){
    return i + j * mat->n;
}

void m_add(matrix *mat, int i, int j, double value){
    if(value == 0){
        return;
    }
    if(v_size(&mat->indices) == 0){
        v_append(&mat->indices, coords_to_index(mat, i, j));
        d_append(&mat->values, value);
        return;
    }
    int index = 0;
    while(v_get(&mat->indices, index) < coords_to_index(mat, i, j) && index < v_size(&mat->indices) - 1){
        index++;
    }
    if(v_get(&mat->indices, index) > coords_to_index(mat, i, j)){
        v_insert(&mat->indices, index, coords_to_index(mat, i, j));
        d_insert(&mat->values, index, value);
        return;
    }
    if(v_get(&mat->indices, index) < coords_to_index(mat, i, j)){
        v_append(&mat->indices, coords_to_index(mat, i, j));
        d_append(&mat->values, value);
        return;
    }
    // ==
    double v = d_get(&mat->values, index);
    d_set(&mat->values, index, v+value);
}

matrix *mult(matrix * mat, vector_d * v){
    matrix * a = malloc(sizeof(matrix));
    d_create(&a->values);
    v_create(&a->indices);
    a->m = 1; // количество строк
    a->n = mat->n; // количество столбцов
    for(int i = 0; i < d_size(&mat->values); i++){
        int idx = v_get(&mat->indices, i);  // coords_to_index(x, y) == idx
        int x = idx % mat->n;  // номер столбца
        int y = idx / mat->n;  // номер строки

        m_add(a, x, 0, d_get(&mat->values, i) * d_get(v, y));
    }
    return a;
}