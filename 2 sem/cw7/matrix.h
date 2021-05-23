#ifndef KP7_MATRIX_H
#define KP7_MATRIX_H
typedef struct {
    int m;
    int n;
    vector_d values;
    vector indices;
} matrix;
void read_matrix(matrix *mat);
void print_matrix(matrix *mat);
int coords_to_index(matrix*mat, int i, int j);
double m_get(matrix *mat, int i, int j);
matrix *mult(matrix * mat, vector_d * v);
#endif
