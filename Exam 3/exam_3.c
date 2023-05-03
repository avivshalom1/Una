/***********************************
* Developer:      Aviv Shalom      *
* Description:    DS 2 Exam        * 
************************************/
#include <stdio.h>  /*For printf */
#include <string.h> /*For strlen, strcpy, strncpy, strcmp, strcat */
#include <stdlib.h> /*for free */
#include <assert.h> /*for assert */ 	
#include <stddef.h> /*for size_t */ 

/* local API's*/
#include "singly_linked_list.h"
#include "stack.h"
#include "bst.h"

#define PASSED "\033[0;32mPassed all function tests!\n\033[0m\n"
#define FAILED "\033[0;31mFAILED!\033[0m\n"
#define RED "\033[0;31m"
#define DEFAULT "\033[0m"

typedef struct node node_t;

typedef struct node_singly
{	
	void *data;
	struct node_singly *next; 
} node_s_t;

struct node
{
	node_t *parent;
	node_t *children[2];
	void *data;
};

struct bst
{
	node_t dummy_root;
	cmpfunc_t cmpfunc;
};

/* EXAM FUNCTIONS */
node_s_t *FlipIterativeExam(node_s_t *head);
node_s_t *FlipRecursiveExam(node_s_t *head);
int MaxSumArray(int nums[], size_t len, int *left, int *right);
void SortStack(stack_t *stack);
static void SortedInsert(stack_t *stack, int data);
int SortedCharsInFile(const char *file_name, char *result);
static int CharCmp(const void *lhs, const void *rhs);
bst_iterator_t BSTInsertIterative(bst_t *bst, void *data);
bst_iterator_t BSTInsertRecursive(node_t *root, void *data);
void BSTInsertFSA(int **arr, size_t size, void *data);
void StringReverseRec(char *str, size_t i, size_t len);
void StringPermutations(char *str, size_t left, size_t right);

/* TESTING FUNCTIONS */
void TestingFlip(int *flag);
void TestingMaxSumArray(int *flag);
void TestingSortStack(int *flag);
void TestingSortedCharsInFile(int *flag);
void TestingInsert(int *flag);
void TestingStringReverseRec(int *flag);
void TestingStringPermutations(int *flag);

/* TESTING UTILITY FUNCTIONS */
int Compare(const void *lhs, const void *rhs);
static void CompareAndResultInts(int object1, int object2, int *flag, int line);
static void CompareAndResultStrings(char *str1, char *str2, int *flag, int line);
static void CompareAndResultPointers(void *object1, void *object2, int *flag, int line);
void print2DUtil(node_t* root, int space);
static void CheckPassed(int *flag);
static void Swap(char *lhs, char *rhs);
node_s_t *ListCreate10Nodes(void);
static void PrintLinkedList(node_s_t *head);
void PrintElements(stack_t *stack);
static node_t *NodeCreate(node_t *node_parent, void *data);

int main()
{
	int flag = 0;
		
	TestingFlip(&flag);
	
	TestingMaxSumArray(&flag);
	
	TestingSortStack(&flag);
	
	TestingSortedCharsInFile(&flag);

	TestingInsert(&flag);

	TestingStringReverseRec(&flag);

	TestingStringPermutations(&flag);

	CheckPassed(&flag);
	
	return 0;
}

/*****************************************************************************/	
void TestingFlip(int *flag)
{
	int data[10] = {1, 2, 3, 4 ,5 , 6, 7, 8, 9 ,10};
	size_t i = 0;
	
	node_s_t *list_for_flipping = ListCreate10Nodes();
	node_s_t *head = list_for_flipping;

	printf("%sTesting Flip functions %s \n", RED, DEFAULT);	
					
	for(i = 0; i < 10; i++)
	{
		list_for_flipping->data = &data[i];
		list_for_flipping = list_for_flipping->next;
	}

	printf("Printing the original list:\n");	
	PrintLinkedList(head);

	printf("\nPrinting the iterative flipped list:\n");		
	head = FlipIterativeExam(head);
	PrintLinkedList(head);

	printf("\nPrinting the recursive double flipped list:\n");		
	head = FlipRecursiveExam(head);
	PrintLinkedList(head);

	CompareAndResultPointers(0, 0, flag, __LINE__);
}
	
/*****************************************************************************/	
void TestingMaxSumArray(int *flag)
{
	int nums[] = {-2, 1, -3 , 4, -1, 2, 3, -5, -30};
	size_t arr_size = 9;
	int r = 0, l = 0;
	int *right = &r;
	int *left = &l;
	(void)flag;

	printf("%sTesting TestingMaxSumArray %s \n", RED, DEFAULT);	

	printf("Right index: %d\nLeft index: %d\nMax sum:%d\n",r ,l, MaxSumArray(nums, arr_size, left, right));

}
/*****************************************************************************/
void TestingSortStack(int *flag)
{
	int data[10] = {11, 22, 33, 44 , 55, 66, 77, 88, 99, 100};
	stack_t *stack = StackCreate(10, 4);
	(void)flag;

	printf("%sTesting Sorting Stack %s", RED, DEFAULT);	

	StackPush(stack, &data[7]);
	StackPush(stack, &data[1]);
	StackPush(stack, &data[4]);
	StackPush(stack, &data[0]);
	StackPush(stack, &data[5]);				
	StackPush(stack, &data[6]);
	StackPush(stack, &data[2]);	

	SortStack(stack);
	PrintElements(stack);
	StackDestroy(stack);
}	

/*****************************************************************************/
void TestingSortedCharsInFile(int *flag)
{
	const char *file_name = "testing.txt";
	char result[30];
	(void)flag;

	printf("%sTesting Sorted Chars In File %s \n", RED, DEFAULT);	

	SortedCharsInFile(file_name, result);
}

/*****************************************************************************/
void TestingInsert(int *flag)
{
	int data[10] = {65, 22, 33, 44 , 55, 66, 77, 88, 99, 100};
	bst_t *bst = BSTCreate(Compare);
	int *fsa[10] = {NULL};
	size_t i = 0;
	(void)flag;

	printf("%sTesting TestingInsert iterative & recursive %s \n", RED, DEFAULT);	

	BSTInsertIterative(bst, &data[0]);
	BSTInsertIterative(bst, &data[3]);
	BSTInsertIterative(bst, &data[1]);
	BSTInsertIterative(bst, &data[8]);
	BSTInsertIterative(bst, &data[6]);
	BSTInsertIterative(bst, &data[2]);	

	BSTInsertRecursive(&bst->dummy_root, &data[3]);
	BSTInsertRecursive(&bst->dummy_root, &data[2]);
	BSTInsertRecursive(&bst->dummy_root, &data[4]);
	BSTInsertRecursive(&bst->dummy_root, &data[8]);
	BSTInsertRecursive(&bst->dummy_root, &data[6]);
	BSTInsertRecursive(&bst->dummy_root, &data[3]);

	print2DUtil(bst->dummy_root.children[0], 0);
	BSTDestroy(bst);

	printf("%sTesting BSTInsertFSA %s \n", RED, DEFAULT);	

	BSTInsertFSA(fsa, 10, &data[0]);
	BSTInsertFSA(fsa, 10, &data[3]);
	BSTInsertFSA(fsa, 10, &data[1]);
	BSTInsertFSA(fsa, 10, &data[8]);
	BSTInsertFSA(fsa, 10, &data[6]);
	BSTInsertFSA(fsa, 10, &data[2]);
 	BSTInsertFSA(fsa, 10, &data[4]);
	BSTInsertFSA(fsa, 10, &data[5]);
	BSTInsertFSA(fsa, 10, &data[7]);
	BSTInsertFSA(fsa, 10, &data[9]);
	BSTInsertFSA(fsa, 10, &data[5]); 

	for(i = 0; i < 10; i++)
	{
		if(fsa[i] != NULL)
		{
			printf("%d ", *(int *)fsa[i]);
		}

		else
		{
			printf("NULL ");
		}
	}

	puts("");

}	
/*****************************************************************************/

void TestingStringReverseRec(int *flag)
{
	char to_reverse[] = "reversing ds 2 exam";
	size_t len = strlen(to_reverse);
	(void)flag;

	printf("%sTesting StringReverseRec %s \n", RED, DEFAULT);	

	printf("B4 reversing: %s\n", to_reverse);

	StringReverseRec(to_reverse, 0, len);

	printf("AFTER reversing: %s\n", to_reverse);

}

/*****************************************************************************/
void TestingStringPermutations(int *flag)
{
	char perm[] = "eat";
	size_t len = strlen(perm);
	(void)flag;

	printf("%sTesting StringPermutations %s \n", RED, DEFAULT);	

	StringPermutations(perm, 0, len - 1);
}

/*****************************************************************************/

/*	Question 1.a	*/
node_s_t *FlipIterativeExam(node_s_t *head)
{	
	node_s_t *temp = NULL;
	node_s_t *next = NULL;

	assert(head);
	
	temp = head->next;
	next = head->next;
	head->next = NULL;

	while(temp)
	{
		next = temp;
		temp = next->next;
		next->next = head;
		head = next;
	}

	return next;
}

/*	Question 1.b	*/
node_s_t *FlipRecursiveExam(node_s_t *head)
{	
	node_s_t *head_start = NULL;
	
	assert(head);

	if(NULL == head->next)
	{		
		return head;
	}

	head_start = FlipRecursiveExam(head->next);
	head->next->next = head;
	head->next = NULL;

	return head_start;

}

/*	Question 2	*/
int MaxSumArray(int nums[], size_t len, int *left, int *right)
{
	size_t i = 0, left_index_keeper = 0;
	int max_sum = 0;
	int current_sum= 0;
	
	
	for(i = 0; i < len; i++)
	{
		current_sum += nums[i];
		
		if(current_sum < 0)
		{
			current_sum = 0;
			left_index_keeper = i + 1;
		}
		
		if(current_sum > max_sum)
		{
			max_sum = current_sum;
			*right = i;
			*left = left_index_keeper;
		}	
	}
	
	return max_sum;
}

/*	Question 3	*/
void SortStack(stack_t *stack)
{
	int data = 0;

	assert(stack);

	if (!StackIsEmpty(stack))
	{
		data = *(int *)StackPeek(stack);

		StackPop(stack);
		SortStack(stack);
		SortedInsert(stack, data);
	}
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void SortedInsert(stack_t *stack, int data)
{
	int temp = 0;

	assert(stack);

	if (StackIsEmpty(stack) || data < *(int *)StackPeek(stack))
	{
		StackPush(stack, &data);
		return;
	}
	temp = *(int *)StackPeek(stack);
	StackPop(stack);

	SortedInsert(stack, data);

	StackPush(stack, &temp);
}

/*	Question 4	*/
int SortedCharsInFile(const char *file_name, char *result)
{
	int ret = 0;
	char c = '\0';
	FILE *fd = NULL;
	char *str = result;

	assert(file_name);
	assert(result);

	fd = fopen(file_name, "r");
	if (NULL == file_name)
    {
        printf("Could not open file %s", file_name);
        return 1;
    }

	for (c = fgetc(fd); c != EOF; c = fgetc(fd), result++)
    {
		*result = c;
 	}

	*result = '\0';

	qsort(str, strlen(str), 1, CharCmp);

    ret = fclose(fd);
	if (ret != 0)
    {
        printf("Could not close file %s", file_name);
        return 1;
    }

	printf("result: %s\n", str);

	return 0;
}

static int CharCmp(const void *lhs, const void *rhs)
{
	assert(lhs);
	assert(rhs);

	return *(char *)lhs - *(char *)rhs;
}

/*	Question 5.a	*/
bst_iterator_t BSTInsertIterative(bst_t *bst, void *data)
{
	int right_or_left = 0;
	node_t *node = &bst->dummy_root;

	assert(bst);
	assert(data);

	while(node->children[right_or_left] != NULL)
	{
		node = node->children[right_or_left];
		right_or_left = (bst->cmpfunc(data, BSTGetData(node)) > 0);
	}

	node->children[right_or_left] = NodeCreate(node, data);

	if(node->children[right_or_left] == NULL)
	{
		return NULL;
	}

	return node;
}

/*	Question 5.b	*/
bst_iterator_t BSTInsertRecursive(node_t *root, void *data)
{
	int right_or_left = 0;
	node_t *node = root;
	node_t *ret = NULL;

	assert(data);
	assert(root);

	right_or_left = ((root->parent != NULL) && (Compare(data, BSTGetData(node)) > 0));

	if(node->children[right_or_left] == NULL)
	{
		ret = node->children[right_or_left] = NodeCreate(node, data);

		if(node->children[right_or_left] == NULL)
		{
			ret = NULL;
		}

		return ret;
	}

	return BSTInsertRecursive(node->children[right_or_left], data);
}

/*	Question 5.c	*/
void BSTInsertFSA(int **arr, size_t size, void *data)
{
	int right_or_left = 0;
	size_t index = 0;

	assert(data);

	while(arr[index] != NULL && (index < (size - 1)))
	{
		right_or_left = (Compare(data, arr[index]) > 0);
		index = right_or_left * (index * 2 + 2) +
			   !right_or_left * (index * 2 + 1);
	}

	if(index < (size - 1))
	{
		arr[index] = data;
	}

}

/*  Question 7  */
void StringReverseRec(char *str, size_t i, size_t len)
{
	char c = 0;

	assert(str);

	if (i == len / 2)
	{
		return;
	}

	c = *(str + len - i - 1);
	*(str + len - i - 1) = *(str + i);
	*(str + i) = c;

	StringReverseRec(str, i + 1, len);
}

/*  Question 8  */
void StringPermutations(char *str, size_t left, size_t right)
{
	size_t i = 0;

	assert(str);

	if (left == right)
	{
		printf("%s\n", str);
	}
	else
	{
		for (i = left; i <= right; ++i)
		{
			Swap(str + left, str + i);
			StringPermutations(str, left + 1, right);
			Swap(str + left, str + i);
		}
	}
}


static node_t *NodeCreate(node_t *node_parent, void *data)
{
	node_t *new_node = NULL;

	new_node = (node_t *)malloc(sizeof(node_t));

	if (NULL == new_node)
	{
		return NULL;
	}

	new_node->parent = node_parent;
	new_node->data = data;
	new_node->children[0] = NULL;
	new_node->children[1] = NULL;

	return new_node;
}

int Compare(const void *lhs, const void *rhs)
{
	assert(lhs);
	assert(rhs);

	return (*(int *)lhs - *(int *)rhs);
}

void print2DUtil(node_t* root, int space)
{
    int i = 10;

    if (root == NULL)
    return;

    space += 10;

    print2DUtil(root->children[1], space);

    printf("\n");
    for (i = 10; i < space; i++)
    {
        printf(" ");
    }

    printf("%d\n", *(int *)root->data);

    print2DUtil(root->children[0], space);
} 

static void Swap(char *lhs, char *rhs)
{
	char temp = 0;

	temp = *lhs;
	*lhs = *rhs;
	*rhs = temp;
}

/*********** END OF THE EXAM ***********/

node_s_t *ListCreate10Nodes()
{
	node_s_t *node1 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node2 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node3 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node4 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node5 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node6 = (node_s_t *)malloc(sizeof(node_s_t));	
	node_s_t *node7 = (node_s_t *)malloc(sizeof(node_s_t));	
	node_s_t *node8 = (node_s_t *)malloc(sizeof(node_s_t));	
	node_s_t *node9 = (node_s_t *)malloc(sizeof(node_s_t));	
	node_s_t *node10 = (node_s_t *)malloc(sizeof(node_s_t));	

	if (NULL == node1 || NULL == node2 || NULL == node3 || NULL == node4 ||
		NULL == node5 || NULL == node6 || NULL == node7 || NULL == node8 ||
		NULL == node9 || NULL == node10 )
	{
		return NULL;
	}				

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;	
	node6->next = node7;
	node7->next = node8;
	node8->next = node9;	
	node9->next = node10;	
	node10->next = NULL;

    return node1;
}

/***** DATA STRUCTURES UTILITY FUNCTIONS ********/
node_s_t *ListCreateLooped(void)
{
	node_s_t *node1 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node2 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node3 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node4 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node5 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node6 = (node_s_t *)malloc(sizeof(node_s_t));	
	node_s_t *node7 = (node_s_t *)malloc(sizeof(node_s_t));	
	node_s_t *node8 = (node_s_t *)malloc(sizeof(node_s_t));	
	node_s_t *node9 = (node_s_t *)malloc(sizeof(node_s_t));	
	node_s_t *node10 = (node_s_t *)malloc(sizeof(node_s_t));	

	if (NULL == node1 || NULL == node2 || NULL == node3 || NULL == node4 ||
		NULL == node5 || NULL == node6 || NULL == node7 || NULL == node8 ||
		NULL == node9 || NULL == node10 )
	{
		return NULL;
	}				

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;	
	node6->next = node7;
	node7->next = node8;
	node8->next = node9;	
	node9->next = node10;	
	node10->next = NULL;

	node10->next = node4;
	
    return node1;
}
/*****************************************************************************/
node_s_t *ListCreateIntersect(node_s_t *mutual_node)
{
	int data[10] = {0, 1, 2, 3, 4 ,5 , 6, 7, 8, 9};
	
	node_s_t *node1 = (node_s_t *)malloc(sizeof(node_s_t));
	node_s_t *node2 = (node_s_t *)malloc(sizeof(node_s_t));
	
	if (NULL == node1 || NULL == node2)
	{
		return NULL;
	}	
	
	node1->next = node2;
	node2->next = mutual_node;
	
	node1->data =  (void *)&data[0];
	node1 = node1->next;
	node1->data = (void *)&data[1];

    return node1;
}


/*****************************************************************************/
static void PrintLinkedList(node_s_t *head)
{	
	while(head)
	{
		printf("%d  ", *(int *)head->data);
		head = head->next;
	}

	puts("");
}

/*****************************************************************************/
void PrintElements(stack_t *stack)
{
	size_t i = 0;	
	size_t stack_size = StackSize(stack);
	
	printf("\nPrinting exiting elements and poping the stack!\n");
	
	for(i = 0; i < stack_size; i++)
	{
		printf("Member %lu is: %d\n",stack_size - i, *(int *)StackPeek(stack));	
		
		if(1 != StackSize(stack))
		{
			StackPop(stack);
		}
	}
}

/***** TESTING UTILITY FUNCTIONS ********/
static void CompareAndResultInts(int object1, int object2, int *flag, int line)
{
	if(object1 != object2)
	{	
		printf("%s at line %d\n", FAILED, line);
		*flag += 1;
	}	
}	
/*****************************************************************************/
static void CheckPassed(int *flag)
{
	if(0 == *flag)
	{
		printf("%s", PASSED);
	}
	*flag = 0;	
}
/*****************************************************************************/
static void CompareAndResultStrings(char *str1, char *str2, int *flag, int line)
{
	if(strcmp(str1, str2))
	{	
		printf("%s at line %d\n", FAILED, line);
		*flag += 1;
	}	
}
/*****************************************************************************/
static void CompareAndResultPointers(void *object1, void *object2, int *flag, int line)
{
	if(object1 != object2)
	{	
		printf("%s at line %d\n", FAILED, line);
		*flag += 1;
	}	
}
