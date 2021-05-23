#include <stdlib.h>
#include <stdbool.h>
#include "vector_c.h"

bool v_create(vector *v, int size) {
    char **new_data = malloc(sizeof(char *) * size);
    if (new_data == NULL) {
        return false;
    } else {
        v->size = size;
        v->body = new_data;
        return true;
    }
}

bool v_empty(vector *v) {
    return v->size == 0;
}

int v_size(vector *v) {
    return v->size;
}

char *v_get(vector *v, int i) {
    if (i >= 0 && i < v->size) {
        return v->body[i];
    }
    return 0;
}

bool v_set(vector *v, int i, char *elem) {
    if (i < 0 || i >= v->size) {
        return false;
    } else {
        v->body[i] = elem;
        return true;
    }
}

bool v_push(vector *v, char *elem) {
    char **new_data = realloc(v->body, sizeof(char *) * (v->size + 1));
    if (new_data == NULL) {
        return false;
    } else {
        v->body = new_data;
        v->body[v->size] = elem;
        v->size++;
        return true;
    }
}

bool v_resize(vector *v, int size) {
    char **new_data = realloc(v->body, sizeof(char *) * size);
    if (new_data == NULL && size != 0) {
        return false;
    } else {
        v->body = new_data;
        v->size = size;
        return true;
    }
}

void v_destroy(vector *v) {
    if (v->size != 0) {
        v->size = 0;
        free(v->body);
    }
}