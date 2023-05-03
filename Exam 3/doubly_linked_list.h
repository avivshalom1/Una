/*********************************************
* Developer:      Aviv Shalom              	 *
* Reviewer:       Shalev                     *
* Version:        1.0                        *   
* Description: API for doubly_linked_list.c  *
**********************************************/
#ifndef __OL134_DOUBLY_LINKED_LIST_H__
#define __OL134_DOUBLY_LINKED_LIST_H__

#include <stddef.h> /* for size_t */

typedef struct node* dlist_iterator_t; 
typedef struct dlist dlist_t;

/* TODO this will go to source file

typedef node node_t;

struct node
{
	void *data;
	node_t *previous;
	node_t *next;
};

struct dlist
{
	node_t begin;
	node_t end;
};

*/

/*-----------------------------------------------------*/

/* DListCreate:

	Parameters:
		none
	Returns:
		success : return DList
		Failure : return NULL
	Complexity:	
		O(1)
*/
dlist_t *DListCreate(void);

/*-----------------------------------------------------*/

/* DListDestroy:

	Parameters:
		dlist - list to destroy
	Returns:
		none
	Complexity:	
		O(n)
*/
void DListDestroy(dlist_t *dlist);

/*-----------------------------------------------------*/

/* DListBegin:

	Parameters:
		dlist - list from user
	Returns:
		Iterator to first element
		List is empty : return List end
	Complexity:	
		O(1)
*/
dlist_iterator_t DListBegin(const dlist_t *dlist);

/*------------------------------------------------------*/

/* DListEnd:

	Parameters:
		dlist - list from user
	Returns:
		List end
	Complexity:	
		O(1)
*/
dlist_iterator_t DListEnd(const dlist_t *dlist);

/*-----------------------------------------------------*/

/* DListInsert:
    Description: inserts the given @data before where iterator
	Parameters:
		@data - data to insert
		@where - where to insert
	Returns:
		success - newly created node
		fail - List end
	Complexity:	
		O(1) if the func succeeded / O(N) if not 
*/
dlist_iterator_t DListInsert(void *data, dlist_iterator_t where);

/*-----------------------------------------------------*/

/* DListRemove:

	Parameters:
		which - which data indicated by iterator to remove
	Returns:
		iterator to the data after the one that was removed 
	Complexity:	
		O(1)
*/
dlist_iterator_t DListRemove(dlist_iterator_t which);

/*-----------------------------------------------------*/
/* DListPushFront:
	Parameters:
		list - list from user
		data - data from user
	Returns:
		success - return the new iterator
		fail - return the list end iterator
	Complexity:	
		O(1)
*/

dlist_iterator_t DListPushFront(dlist_t *dlist, void *data);

/*-----------------------------------------------------*/
/* DListPopFront:
	Parameters:
		dlist - list from user
	Returns:
		return data of the removed iterator
	Complexity:	
		O(1)
*/

void *DListPopFront(dlist_t *dlist);

/*-----------------------------------------------------*/
/* DListPushBack:
	Parameters:
		dlist - list from user
		data - data from user
	Returns:
		success - return the new iterator
		fail - return the end iterator
	Complexity:	
		O(1)
*/

dlist_iterator_t DListPushBack(dlist_t *dlist, void *data);

/*-----------------------------------------------------*/
/* DListPopBack:
	Parameters:
		list - list from user
	Returns:
		return data of the removed iterator
	Complexity:	
		O(1)
*/

void *DListPopBack(dlist_t *dlist);

/*-----------------------------------------------------*/

/* DListSetData:

	Parameters:
		data - data to set
		where - where to set the new data
	Returns:
			
	Complexity:	
		O(1)
*/
void DListSetData(dlist_iterator_t where, void *data);

/*-----------------------------------------------------*/

/* DListGetData:

	Parameters:
		from - from where to get the data
	Returns:
		returns the data
	Complexity:	
		O(1)
*/
void *DListGetData(dlist_iterator_t from);

/*-----------------------------------------------------*/

/* DListNext:

	Parameters:
		current - current where to go
	Returns:
		next iterator
	Complexity:	
		O(1)
*/
dlist_iterator_t DListNext(dlist_iterator_t current);

/*-----------------------------------------------------*/

/* DListPrevious:

	Parameters:
		current - current where to go
	Returns:
		previous iterator
	Complexity:	
		O(1)
*/
dlist_iterator_t DListPrev(dlist_iterator_t current);

/*-----------------------------------------------------*/

/* DListSize:

	Parameters:
		dlist - list to check
	Returns:
		Number of element in the list 
	Complexity:	
		O(N)
*/
size_t DListSize(const dlist_t *dlist);

/*-----------------------------------------------------*/

/* DListIsEmpty:
	Parameters:
		dlist - list to check
	Returns:
		returns 1 if the list is empty, 0 if not
	Complexity:	
		O(1)
*/
int DListIsEmpty(const dlist_t *dlist);

/*-----------------------------------------------------*/

/* DListIsSame:

	Parameters:
		iter1 - first element 
		iter2 - secoend element 
	Returns:
		returns 1 if the iterators are same, 0 if not
	Complexity:	
		O(1)
*/
int DListIsSameIter(dlist_iterator_t iter1, dlist_iterator_t iter2);

/*-----------------------------------------------------*/

/* DListFindData:

	Parameters:
		from - starting iterator (included)
		to - ending iterator (excluded)
		function - is match function, compare right to left
		    lhs/rhs - left/right hand side
		param - parameter to find
	Returns:
		returns matching iterator
		Not found : return iterator to "to" 
	Complexity:	
		O(N)
*/
dlist_iterator_t DListFindData( dlist_iterator_t from,
                                dlist_iterator_t to, 
								int (*is_match)(const void *lhs, const void *rhs),
								void *params );

/*-----------------------------------------------------*/

/* DListForEach 

	Parameters:
		from - starting iterator (included)
		to - ending iterator (excluded)
		function - action function
		param - parameter sent by user
	Returns:
		returns action function status
	Complexity:	
		O(N)
	Note : the func stop running on first action function failure
*/
int DListForEach(   dlist_iterator_t from,
                    dlist_iterator_t to, 
				    int (*action)(void *data, void *param),
				    void *param ); 

/*-----------------------------------------------------*/

/* DListMultifind

	Parameters:
		from - starting iterator (included)
		to - ending iterator (excluded)
		result_list - list of resulted iterators
		function - is match function, compare right to left
		    lhs/rhs - left/right hand side
		param - parameter to find
	Returns:
		returns ist of matching iterators
		Not found : return iterator to "to" 
	Complexity:	
		O(N)
*/

int DListMultifind( dlist_iterator_t from,
                    dlist_iterator_t to, 
					int (*is_match)(const void *lhs, const void *rhs), 
					void *param,
					dlist_t *output_list); 

/*-----------------------------------------------------*/

/* DListSplice 

	Parameters:
		from - starting node (included)
		to - ending node (excluded)
		function - action function
		param - parameter sent by user
	Returns:
		returns action function status
	Complexity:	
		O(N)
	Note : connect from-to before the where. (excluding to)
*/
void DListSplice(dlist_iterator_t from, dlist_iterator_t to, dlist_iterator_t where); 

/*-----------------------------------------------------*/
#endif /* __OL134_DOUBLY_LINKED_LIST_H__*/
