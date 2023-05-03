/***********************************************
* Developer:  Israel 		                   *
* Reviewer:   Israeli	                       *
* Version:    1.0                              *    
* Description: API for Fixed Sized Allocator.c *           
************************************************/
#ifndef __OL134_FIXED_SIZE_ALLOCATOR_H__
#define __OL134_FIXED_SIZE_ALLOCATOR_H__

#include <stddef.h> /* For size_t */

typedef struct fsa fsa_t;

/*
struct fsa
{
    
    
}

*/

/*--------------------------------------------------*/

/* FSASuggestSize:
	Description:
		Recieves size of each block and total number of blocks requested by user 
	Params:
	    block_size - number of bytes
		num_blocks - total ammount of blocks
	return:
	    min size required
    Complexity:
		Time - O(1)
*/
size_t FSASuggestSize(size_t block_size, size_t num_blocks);

/*--------------------------------------------------*/

/* Init:
	Description:
		initialize blocks of memory in "memory"
	Params:
	    memory - the memory block we want to init the FSA on.
		memory_size - the size of memory passed by the client
		block_size - size of block
	return
	    success- poiner to fsa                  
    	fail- NULL
	Complexity:
		Time - O(n)
*/
fsa_t *FSAInit(void *memory, size_t memory_size, size_t block_size);

/*--------------------------------------------------*/

/*
Alloc:
    Description: 
        returns a pointer to the begining of the free block to use.
    Params:
        fsa - pool of memory
    Return: 
        success - pointer to allocated blocks
        fail - NULL
    Complexity: 0(1)
*/
void *FSAAlloc(fsa_t *fsa);

/*--------------------------------------------------*/
/*
Free
    Description: 
        frees the allocated block given by user
    Params:
        fsa - where we want to free block
        block_to_free 
    Complexity: O(1)
*/
void FSAFree(fsa_t *fsa, void *block_to_free);

/*--------------------------------------------------*/
/*
FSACountFree
    Description:
        counts the number of free blocks
    Params:
        fsa - the memory pool
    Return:
        number of free blocks in the memory pool
    Complexity: O(n)
*/
size_t FSACountFree(const fsa_t *fsa);


#endif /*__OL134_FIXED_SIZE_ALLOCATOR_H__*/

