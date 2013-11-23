#ifndef list_macros_h
#define list_macros_h

// Macros to generate standard linked list functions for any given type.

// Macro to prototype the list functions, for use in headers.
#define PRT_LIST_FUNCS(type) \
void type ## _list_add(type ## _t *head, type ## _t *x); \
type ## _t * type ## _list_get(type ## _t *head, const wchar_t *name); \
void type ## _list_delete(type ## _t *head);

// Macro to define the list functions, for use in c files.
#define DEF_LIST_FUNCS(type) \
void type ## _list_add(type ## _t *head, type ## _t *x){ \
    type ## _t *iter = head; \
    while(iter->next != NULL){ if(iter == x){ return; }else{ iter = iter->next; }} \
    iter->next = x; \
} \
  \
type ## _t * type ## _list_get(type ## _t *head, const wchar_t *name){ \
    type ## _t *iter = head; \
    while(wcscmp(name, iter->name) != 0){ if(iter->next == NULL){ return NULL; }else{ iter = iter->next; }} \
    return iter; \
} \
  \
void type ## _list_delete(type ## _t *head){ \
    type ## _t *iter = head; \
    type ## _t *next = NULL; \
    while(iter != NULL){ next = iter->next; type ## _delete(iter); iter = next; } \
}

#endif
