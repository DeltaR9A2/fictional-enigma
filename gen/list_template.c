#include "TYPE_list.h"

TYPE_node_t *_TYPE_node_create(void){
    TYPE_node_t *node = malloc(sizeof(TYPE_node_t));
    node->data = TYPE_create();
    node->next = NULL;
    return node;
}

void _TYPE_node_delete(TYPE_node_t *node){
    TYPE_delete(node->data);
    free(node);
}

TYPE_list_t *TYPE_list_create(void){
    TYPE_list_t *temp = malloc(sizeof(TYPE_list_t));
    temp->head = _TYPE_node_create();
    return temp;
}

TYPE_t *TYPE_list_get(TYPE_list_t *list){
    TYPE_node_t *iter = list->head;
    
    while(iter->next != NULL){
        iter = iter->next;
    }

    iter->next = _TYPE_node_create();
    return iter->next->data;
}

void TYPE_list_delete(TYPE_list_t *list){
    TYPE_node_t *iter = list->head;
    TYPE_node_t *next = NULL;
    
    while(iter != NULL){
        next = iter->next;
        _TYPE_node_delete(iter);
        iter = next;
    }
    
    free(list);
}

