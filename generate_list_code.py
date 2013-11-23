#!/usr/bin/env python3

NAME_MAX_LEN = 32;
LIST_TYPES = ["fset", "anim", "rect", "body"]

for t in LIST_TYPES:
    header_fn = "src/{}_list.h".format(t)
    source_fn = "src/{}_list.c".format(t)
    
    header_lines = []
    source_lines = []
    
    header_lines.append("#ifndef {0}_list_h".format(t))
    header_lines.append("#define {0}_list_h".format(t))
    header_lines.append("#include <wchar.h>")
    header_lines.append("#include \"{0}.h\"".format(t))

    header_lines.append("""
typedef struct {0}_node_t {0}_node_t;
struct {0}_node_t{{
    {0}_t *data;
    {0}_node_t *next;
    wchar_t name[{1}];
}};

typedef struct {0}_list_t {0}_list_t;
struct {0}_list_t{{
    {0}_node_t *head;
}};
""".format(t, NAME_MAX_LEN));
    
    header_lines.append("{0}_list_t *{0}_list_create(void);".format(t))
    header_lines.append("{0}_t *{0}_list_get({0}_list_t *list, const wchar_t *name);".format(t))
    header_lines.append("void {0}_list_delete({0}_list_t *list);".format(t))

    header_lines.append("\n#endif")
    
    source_lines.append("#include \"{}_list.h\"".format(t))

    source_lines.append("""
{0}_node_t *_{0}_node_create(const wchar_t *name){{
    {0}_node_t *node = malloc(sizeof({0}_node_t));
    node->data = {0}_create();
    node->next = NULL;
    wcsncpy(node->name, name, {1}-1);
    return node;
}}

void _{0}_node_delete({0}_node_t *node){{
    {0}_delete(node->data);
    free(node);
}}

{0}_list_t *{0}_list_create(void){{
    {0}_list_t *temp = malloc(sizeof({0}_list_t));
    temp->head = _{0}_node_create(L"HEAD");
    return temp;
}}

{0}_t *{0}_list_get({0}_list_t *list, const wchar_t *name){{
    {0}_node_t *iter = list->head;
    
    while(iter->next != NULL){{
        if(wcscmp(name, iter->name)){{
            return iter->data;
        }}else{{
            iter = iter->next;
        }}
    }}

    iter->next = _{0}_node_create(name);
    return iter->next->data;
}}

void {0}_list_delete({0}_list_t *list){{
    {0}_node_t *iter = list->head;
    {0}_node_t *next = NULL;
    
    while(iter != NULL){{
        next = iter->next;
        _{0}_node_delete(iter);
        iter = next;
    }}
    
    free(list);
}}
""".format(t, NAME_MAX_LEN))
    
    with open(header_fn, "w") as fh:
        for line in header_lines:
            print(line, file=fh);

    with open(source_fn, "w") as fh:
        for line in source_lines:
            print(line, file=fh);
    

