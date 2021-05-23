#include <stdio.h>
#include <stdlib.h>
#include "vector_i.h"
#include "vector_d.h"
#include "matrix.h"

vector_d * scan_vector(vector_d *v, matrix *mat) {
    double a;
    puts("Ввдите вектор");
    for (int i = 0; i < mat->m; ++i) {
        if(scanf("%lf", &a) > 0) {
            d_append(v, a);
        } else continue;
    }
    return v;
}

int main() {
    vector_d  v;
    d_create(&v);
    matrix mat;
    read_matrix(&mat);
    puts("");
    print_matrix(&mat);
    v = *scan_vector(&v, &mat);
    for (int i = 0; i < mat.m; ++i) {
        printf("%0.3lf ", d_get(&v, i));
    }
    puts("");
    matrix ans;
    if (d_size(&mat.values) > 0) {
        ans = * mult(&mat, &v);
        puts("Ответ:");
        print_matrix(&ans);

    } else {
        puts("Ответ:");
        printf("Нулевой вектор");
    }
    d_destroy(&v);
    v_clear(&mat.indices);
    d_destroy(&mat.values);
    return 0;
}
