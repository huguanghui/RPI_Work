#ifndef TEST_RBTREE__H
#define TEST_RBTREE__H

#include "test_config.h"
#include "test_core.h"

typedef unsigned int  test_rbtree_key_t;
typedef int test_rbtree_key_int_t;


typedef struct test_rbtree_node_s  test_rbtree_node_t;

struct test_rbtree_node_s {
    test_rbtree_key_t       key;
    test_rbtree_node_t     *left;
    test_rbtree_node_t     *right;
    test_rbtree_node_t     *parent;
    u_char                 color;
    u_char                 data;
};

typedef struct test_rbtree_s  test_rbtree_t;

typedef void (*test_rbtree_insert_pt) (test_rbtree_node_t *root,
    test_rbtree_node_t *node, test_rbtree_node_t *sentinel);

struct test_rbtree_s {
    test_rbtree_node_t     *root;
    test_rbtree_node_t     *sentinel;
    test_rbtree_insert_pt   insert;
};

#define test_rbtree_init(tree, s, i)                                           \
    test_rbtree_sentinel_init(s);                                              \
    (tree)->root = s;                                                         \
    (tree)->sentinel = s;                                                     \
    (tree)->insert = i

void test_rbtree_insert(test_rbtree_t *tree, test_rbtree_node_t *node);
void test_rbtree_delete(test_rbtree_t *tree, test_rbtree_node_t *node);
void test_rbtree_insert_value(test_rbtree_node_t *root, test_rbtree_node_t *node,
    test_rbtree_node_t *sentinel);
void test_rbtree_insert_timer_value(test_rbtree_node_t *root,
    test_rbtree_node_t *node, test_rbtree_node_t *sentinel);

#define test_rbt_red(node)               ((node)->color = 1)
#define test_rbt_black(node)             ((node)->color = 0)
#define test_rbt_is_red(node)            ((node)->color)
#define test_rbt_is_black(node)          (!test_rbt_is_red(node))
#define test_rbt_copy_color(n1, n2)      (n1->color = n2->color)

/* a sentinel must be black */

#define test_rbtree_sentinel_init(node)  test_rbt_black(node)


static test_inline test_rbtree_node_t *
test_rbtree_min(test_rbtree_node_t *node, test_rbtree_node_t *sentinel)
{
    while (node->left != sentinel) {
        node = node->left;
    }

    return node;
}

#endif