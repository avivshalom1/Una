/************************************
* Developer:  --			      	*
* Reviewer:   --	   			    *
* Version:    1.0                   *    
* Description: API for              *
*			   bst.c    			* 
*************************************/
#ifndef __OL134_BST_H__
#define __OL134_BST_H__

#include <stddef.h>		/* size_t */

typedef int (*cmpfunc_t)(const void *data, const void *param);
typedef struct bst bst_t;
typedef struct node* bst_iterator_t;

/*
move to source file

typedef node node_t;

struct bst
{
    node_t dummy_root;
    cmpfunc_t cmpfunc;
};

enum child_node_pos
{
    LEFT = 0;
    RIGHT = 1;
    NUM_OF_CHILDREN = 2;
};

struct node
{
    node_t *parent;
	node_t *children[NUM_OF_CHILDREN];
	void *data;
};

*/

/*------------------------------------*/
/* BSTCreate:
    param
        cmp - the function that compares the data
	Return:
		succeed : returns pointer to the new bst
		fail : returns NULL
	Complexity:
		Time - O(1) */
bst_t *BSTCreate(cmpfunc_t cmp);

/*------------------------------------*/
/* BSTDestroy:
	param:
		bst - bst to destroy
	Complexity:
		Time - O(n) */
void BSTDestroy(bst_t *bst);

/*------------------------------------*/
/* BSTSize:
	param:
		bst - the tree to check the size for
	Return:
		the number of elements in the tree
	Complexity:
		Time - O(n) */
size_t BSTSize(const bst_t *bst);

/*------------------------------------*/
/* BSTIsEmpty:
	param:
		bst - the tree to check emptiness
	return
	    1 - empty
	    0 - not empty
	Complexity:
		Time - O(1) */
int BSTIsEmpty(const bst_t *bst);

/*------------------------------------*/
/* BSTInsert:
Description:
	param:
		bst - bst to begin the search
	return:
		success - the new element
		fail - The return value of BSTEnd() \\ end iterator
	Complexity:
		Time - O(log(n)) average, O(n) worst, O(1) fail*/
bst_iterator_t BSTInsert(bst_t *bst, void *data);

/*------------------------------------*/
/* BSTRemove:
	param:
		which - iterator to which element to remove
	return:
		iterator to the next great element
	Complexity:
		Time - O(log(n)) average, O(n) worst */
bst_iterator_t BSTRemove(bst_iterator_t which);

/*------------------------------------*/
/* BSTBegin:
	param:
		bst - the tree
	return:
		iterator to the smallest element
	Complexity:
		Time - O(log(n)) average, O(n) worst */
bst_iterator_t BSTBegin(const bst_t *bst);

/*------------------------------------*/
/* BSTEnd:
	param:
		bst - the tree
	return:
		iterator to end of the tree
	Complexity:
		Time - O(1) */
bst_iterator_t BSTEnd(const bst_t *bst);

/*------------------------------------*/
/* BSTPrev:
	param:
		from - from which element to go
	return:
		the prev element under In-Order traversal type
	Complexity:
		Time - O(1) */
bst_iterator_t BSTPrev(bst_iterator_t from);

/*------------------------------------*/
/* BSTNext:
	param:
		from - from where to go to prev tree 
	return:
		the next element under In-Order traversal type
	Complexity:
		Time - O(1) */
bst_iterator_t BSTNext(bst_iterator_t from);

/*------------------------------------*/
/* BSTIsSameIter:
	param:
		iter1 - iter1 to compare
		iter2 - iter2 to compare 
	return:
		1 - if iterators are the same
		0 - if iterators are not the same
	Complexity:
		Time - O(1) */
int BSTIsSameIter(bst_iterator_t iter1, bst_iterator_t iter2);

/*------------------------------------*/
/* BSTGetData:
	param:
		from - which iterator to take the data from
	return:
	    data from iterator
	Complexity:
		Time - O(1) */
void *BSTGetData(bst_iterator_t from);

/*------------------------------------*/

/* BSTFind:
	param:
	    bst - the tree to search in
	return:
		success - iterator to the element with the matching data
		fail - iterator to dummy
	Complexity:
		Time - O(log(n)) average, O(n) worst */
bst_iterator_t BSTFind(const bst_t *bst, void *param);

/*------------------------------------*/
/* BSTForEach:
    note: 	the client should make sure not to change key 
    		values that affect tree formation\ inner order
	param:
		from - iterator to the beginning of the range
		to - iterator to the end of the range (excluded)
	return:
	    the status from the action function
	Complexity:
		Time - O(n) */
int BSTForEach(	bst_iterator_t from, bst_iterator_t to, 
				int (*action_func)(void *data, void *param), void *param);

/*------------------------------------*/

#endif/*__OL134_BST_H__*/
