#ifndef TYPE_wmap_h
#define TYPE_wmap_h

#include <wchar.h>
#include "TYPE.h"

typedef struct TYPE_node_t TYPE_node_t;
struct TYPE_node_t{
    TYPE_t *data;
    TYPE_node_t *next;
    wchar_t name[32];
};

typedef struct TYPE_wmap_t TYPE_wmap_t;
struct TYPE_wmap_t{
    TYPE_node_t *head;
};

TYPE_wmap_t *TYPE_wmap_create(void);
TYPE_t *TYPE_wmap_get(TYPE_wmap_t *wmap, const wchar_t *name);
void TYPE_wmap_delete(TYPE_wmap_t *wmap);

#endif
