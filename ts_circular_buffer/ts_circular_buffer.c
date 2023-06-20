/************************************************
* Developer:      Aviv Shalom              	    *
* Version:        1.0                           *   
* Date:           08.03.23                      *   
* Description:    ts_circular_buffer            *
*************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CAPACITY 40
#define THREAD_COUNT 100
#define WRITERS 50
#define READERS 50
sem_t sem;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct circular_buffer
{
    int *buff;
    size_t capacity;
    size_t writing_index;
    size_t reading_index;
} circular_buffer_t;

void *Init(size_t capacity)
{
    circular_buffer_t  *circular_buffer = (circular_buffer_t *)malloc(sizeof(circular_buffer_t));

    if(!circular_buffer)
    {
        return NULL;
    }

    circular_buffer->buff = (int *)malloc(sizeof(int) * (capacity + 1));
    circular_buffer->reading_index = 0;
    circular_buffer->writing_index = 0;
    circular_buffer->capacity = capacity;

    return circular_buffer;
}

void Write(circular_buffer_t *circular_buffer, int data)
{

    if((circular_buffer->writing_index + 1) % (circular_buffer->capacity + 1) == circular_buffer->reading_index)
    {
        printf("buffer is full\n");
        return;
    }
    
    else
    {
        circular_buffer->buff[circular_buffer->writing_index] = data;
        circular_buffer->writing_index = (circular_buffer->writing_index + 1) % (circular_buffer->capacity + 1);
    }
      

}


int Read(circular_buffer_t *circular_buffer)
{

    int ret_data = 0;



    if((circular_buffer->writing_index) % (circular_buffer->capacity + 1) == circular_buffer->reading_index)
    {
        printf("buffer is empty\n");
        return -1;
    }
    
    else
    {
        ret_data = circular_buffer->buff[circular_buffer->reading_index];
        circular_buffer->reading_index = (circular_buffer->reading_index + 1) % (circular_buffer->capacity + 1);
    }



    return ret_data;
}




void *ReadThread(void *arg)
{
    printf("read\n");

    pthread_mutex_lock(&mutex);

    sem_wait(&sem);
    printf("%d\n", Read((circular_buffer_t *)arg));

    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *WriteThread(void *arg)
{
    static int counter = 0;

    printf("write\n");

    pthread_mutex_lock(&mutex);

    Write((circular_buffer_t *)arg, counter);

    counter++;

    sem_post(&sem);

    pthread_mutex_unlock(&mutex);


    return NULL;

}






int main()
{

    circular_buffer_t *circular_buffer = Init(CAPACITY);
    pthread_t threads[THREAD_COUNT];
    size_t i = 0;

    /* can defend full buffer or empty buffer, not both */
	sem_init(&sem, 0, 0);

    for(i = 0; i < WRITERS; i++)
    {
        pthread_create(&threads[i], NULL, WriteThread, circular_buffer);
    }

    for(; i < READERS + WRITERS; i++)
    {
        pthread_create(&threads[i], NULL, ReadThread, circular_buffer);
    }

    for(i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

 

    return 0;
}