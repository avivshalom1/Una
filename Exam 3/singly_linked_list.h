/*********************************************
* Developer:      Yana                    	 *
* Reviewer:       Tal                        *
* Version:        2.1                        *    
* Description: API for singly_linked_list.c  * 
**********************************************/
#ifndef __OL134_SINGLY_LINKED_LIST_H__
#define __OL134_SINGLY_LINKED_LIST_H__

#include <stddef.h> /* for size_t */
typedef struct node *list_iterator_t; 
typedef struct list list_t;
typedef int (*is_match_function_t)(const void *data, void *criteria);
typedef int (*action_function_t)(void *data, void *param);


/*-----------------------------------------------------*/

/* ListCreate:

	Parameters:
		none
	Returns:
		success : return List
		Failure : return NULL
	Complexity:	
		O(1)
*/
list_t *ListCreate(void);

/*-----------------------------------------------------*/

/* ListHead:

	Parameters:
		list - list from user
	Returns:
			Iterator to first element 
			List is empty : return List tail
	Complexity:	
			O(1)
*/
list_iterator_t ListHead(const list_t *list);

/*------------------------------------------------------*/

/* ListTail:

	Parameters:
		list - list from user
	Returns:
			List tail
	Complexity:	
		O(1)
*/
list_iterator_t ListTail(const list_t *list);

/*-----------------------------------------------------*/

/* ListInsert:
 
	Parameters:
		data - data to insert
		position - where to insert
	Returns:
		success - newly created node
		fail - List tail
	Complexity:	
		O(1) if the func succeeded / O(N) if not 
*/
list_iterator_t ListInsert( void *data, list_iterator_t position);

/*-----------------------------------------------------*/

/* ListNext:

	Parameters:
		position - from where to go
	Returns:
		next node
	Complexity:	
		O(1) */
list_iterator_t ListNext(list_iterator_t position);

/*-----------------------------------------------------*/

/* ListDestroy:

	Parameters:
		list - list to destroy
	Returns:
		none
	Complexity:	
		O(n)
*/
void ListDestroy(list_t *list);

/*-----------------------------------------------------*/

/* ListRemove:

	Parameters:
		position - which node to remove
	Returns:
		iterator to the node after the one that removed 
	Complexity:	
		O(1)
*/
list_iterator_t ListRemove(list_iterator_t position);

/*-----------------------------------------------------*/

/* ListSetData:

	Parameters:
		data - data to set
		position - where to set the new data
	Returns:
			
	Complexity:	
		O(1)
*/
void ListSetData(void *data, list_iterator_t position);

/*-----------------------------------------------------*/

/* ListGetData:

	Parameters:
		position - from where to get the data
	Returns:
		returns the data
	Complexity:	
		O(1)
*/
void *ListGetData(list_iterator_t position);

/*-----------------------------------------------------*/

/* ListSize:

	Parameters:
		list - list to check
	Returns:
		Number of element in the list 
	Complexity:	
		O(N)
*/
size_t ListSize(const list_t *list);

/*-----------------------------------------------------*/

/* ListIsEmpty:
	Parameters:
		list - list to check
	Returns:
		returns 1 if the list is empty, 0 if not
	Complexity:	
		O(1)
*/
int ListIsEmpty(const list_t *list);

/*-----------------------------------------------------*/

/* ListIsSame:

	Parameters:
		iter1 - first element 
		iter2 - secoend element 
	Returns:
		returns 1 if the iterators are same, 0 if not
	Complexity:	
		O(1)
*/
int ListIsSame(list_iterator_t iter1, list_iterator_t iter2);

/*-----------------------------------------------------*/

/* ListFindData:

	Parameters:
		from - starting node (included)
		to - ending node (excluded)
		function - is match function
		param - parameter to find
	Returns:
		returns matching node
		Not found : return iterator to "to" 
	Complexity:	
		O(N)
*/
list_iterator_t ListFindData(list_iterator_t from, list_iterator_t to, is_match_function_t function, void *param);

/*-----------------------------------------------------*/

/*ListForEach:

	Parameters:
		from - starting node (included)
		to - ending node (excluded)
		function - action function
		param - parameter sent by user
	Returns:
		returns action function status
	Complexity:	
		O(N)
	Note : the func stop running on first action function failure
*/
int ListForEach(list_iterator_t from, list_iterator_t to, action_function_t function, void *param); 

/*-----------------------------------------------------*/
/*ListAppend: 

	Description: concatenate all the elements from src and appends them to dest
 				 list concatenation causes src to be empty after concatenation
	Params:
		Dest - list to be concatenate 
		Source - list appended to dest
	Complexity:
		Time - O(1) */

void ListAppend(list_t *dest, list_t *src);

#endif /* __OL134_SINGLY_LINKED_LIST_H__*/

