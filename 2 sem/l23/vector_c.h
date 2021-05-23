#ifndef L23_VECTOR_C_H
#define L23_VECTOR_C_H
typedef struct {
    int size;
    char **body;
} vector;

bool v_create(vector *v, int size);

bool v_empty(vector *v);

int v_size(vector *v);

char* v_get(vector *v, int i);

bool v_set(vector *v, int i, char *elem);

bool v_push(vector *v, char *elem);

bool v_resize(vector *v, int size);

void v_destroy(vector *v);

#endif //L23_VECTOR_C_H
