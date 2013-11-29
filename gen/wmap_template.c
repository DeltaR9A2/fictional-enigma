#include "TYPE_wmap.h"

TYPE_node_t *_TYPE_node_create(const wchar_t *name){
    TYPE_node_t *node = malloc(sizeof(TYPE_node_t));
    node->data = TYPE_create();
    node->next = NULL;
    wcsncpy(node->name, name, 31);
    return node;
}

void _TYPE_node_delete(TYPE_node_t *node){
    TYPE_delete(node->data);
    free(node);
}

TYPE_wmap_t *TYPE_wmap_create(void){
    TYPE_wmap_t *temp = malloc(sizeof(TYPE_wmap_t));
    temp->head = _TYPE_node_create(L"HEAD");
    return temp;
}

TYPE_t *TYPE_wmap_get(TYPE_wmap_t *wmap, const wchar_t *name){
    TYPE_node_t *iter = wmap->head;
    
    while(iter->next != NULL){
        if(wcscmp(name, iter->next->name) == 0){
            return iter->next->data;
        }

        iter = iter->next;
    }

    iter->next = _TYPE_node_create(name);
    return iter->next->data;
}

void TYPE_wmap_delete(TYPE_wmap_t *wmap){
    TYPE_node_t *iter = wmap->head;
    TYPE_node_t *next = NULL;
    
    while(iter != NULL){
        next = iter->next;
        _TYPE_node_delete(iter);
        iter = next;
    }
    
    free(wmap);
}

