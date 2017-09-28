#include "test_config.h"
#include "test_core.h"

typedef struct {
	test_rbtree_node_t node;
	test_uint_t num;
}TestRBTreeNode;

static void test_rbtree_node_echo(test_rbtree_node_t rb_node, const char *pre)
{
	PRINT_Y("%skey:%d", pre, rb_node.key);
	PRINT_Y("%sLeft:%p", pre, rb_node.left);
	PRINT_Y("%sRight:%p", pre, rb_node.right);
	PRINT_Y("%sParent:%p", pre, rb_node.parent);
	PRINT_Y("%sColor:%d", pre, rb_node.color);
	PRINT_Y("%sData:%d\n", pre, rb_node.data);

	return;
}

static void test_rbtree_echo(test_rbtree_t rb)
{
	PRINT_Y("root:%p", rb.root);
	if(rb.root)
	{
		test_rbtree_node_echo(*rb.root, "Root:");	
	}
	PRINT_Y("sentinel:%p", rb.sentinel);
	if (rb.sentinel)
	{
		test_rbtree_node_echo(*rb.sentinel, "Sentinel:");
	}
	PRINT_Y("insert:%p\n", rb.insert);

	return;
}

int main(int argc, char **argv)
{
	PRINT_Y("");
	int i;
	char buf[512];
	test_rbtree_t rbtree;
	test_rbtree_node_t sentinel;
	test_rbtree_node_t *tmpnode = NULL;
	TestRBTreeNode rbTreeNode[10];

	test_rbtree_init(&rbtree, &sentinel, test_rbtree_insert_value);

	rbTreeNode[0].num = 1;
	rbTreeNode[1].num = 6;
	rbTreeNode[2].num = 8;
	rbTreeNode[3].num = 11;
	rbTreeNode[4].num = 13;
	rbTreeNode[5].num = 15;
	rbTreeNode[6].num = 17;
	rbTreeNode[7].num = 22;
	rbTreeNode[8].num = 25;
	rbTreeNode[9].num = 0;
	test_rbtree_echo(rbtree);
	for (i = 0; i < 10; i ++)
	{
		rbTreeNode[i].node.key = rbTreeNode[i].num;
		test_rbtree_insert(&rbtree, &rbTreeNode[i].node);
	}
	tmpnode = test_rbtree_min(rbtree.root , &sentinel);
	test_rbtree_node_echo(*tmpnode, "Min:");

	{
		test_uint_t lookupkey = 0;
		tmpnode = rbtree.root;
		TestRBTreeNode *lookupNode;

		while (tmpnode != &sentinel)
		{
			if (lookupkey != tmpnode->key)
			{
				tmpnode = (lookupkey < tmpnode->key) ? tmpnode->left : tmpnode->right;
				continue;
			}
			lookupNode = (TestRBTreeNode *)tmpnode;
			break;
		}
		test_rbtree_node_echo(lookupNode->node, "Lookup:");
		test_rbtree_delete(&rbtree, &lookupNode->node);
		tmpnode = test_rbtree_min(rbtree.root , &sentinel);
		test_rbtree_node_echo(*tmpnode, "Min:");		
	}

	return 0;
}

static unsigned char special_character_tab[] = {'\r', '\n', '\b', '\f', '\t', '\v'};

static int isSpecial(unsigned char c)
{
	int size;
	int iLoop = 0;
	int iRet = -1;

	size = sizeof(special_character_tab)/sizeof(unsigned char);
	for (iLoop = 0; iLoop < size; iLoop ++)
	{
		if (special_character_tab[iLoop] == c)
		{
			iRet = 0;
			break;
		}
	}

	return iRet;
}

void buf_print_hex(void *buf, size_t len, const char *prefix)
{
	unsigned char tmp[256];
	unsigned char *uchar;
	unsigned char *lineStart, *lineEnd;
	unsigned char *start = NULL;
	unsigned char *end = NULL;
	unsigned char *pos = 0;
	int iLoop = 0;
	int ood = 0;

	if (buf)
	{
		start = (unsigned char *)buf;
		end = start + len;
		pos = start;
		PRINT_Y("%sbuff:%p Len:%d", prefix, buf, len);
		while (pos < end)
		{
			// 按行打印(16字节一行)
			printf("%p:", pos);
			lineStart = pos;
			if (end - lineStart > 16)
			{
				ood = 16;
			}
			else
			{
				ood = end - lineStart;
			}
			for (iLoop = 0; iLoop < 16; iLoop ++)
			{
				if (iLoop < ood)
				{
					uchar = (unsigned char *)lineStart + iLoop;
					printf("%02x ", *uchar);
					if (0 == isSpecial(*uchar))
					{
						tmp[iLoop] = '.';	
					}
					else
					{
						tmp[iLoop] = *uchar;	
					}
				}
				else
				{
					printf("   ");	
				}
				if (iLoop == 15)
				{
					printf("; ");
				}
			}
			tmp[ood] = '\0';
			printf("%s", tmp);
			printf("\n");
			lineEnd = lineStart + ood;
			pos = lineEnd;
		}
	}

	return ;
}