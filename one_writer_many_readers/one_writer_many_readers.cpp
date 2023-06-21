/************************************************
* Developer:      Aviv Shalom              	    *
* Version:        1.0                           *   
* Date:           08.03.23                      *   
* Description:    one_writer_many_reader        *
*************************************************/
#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <map>
#include <mutex>

#define CAPACITY 40
#define WRITERS 1
#define READERS 50
#define THREAD_COUNT (READERS + WRITERS)

class TSCircularBuffer
{
public:
    TSCircularBuffer(std::size_t capacity);
    void WriteHandler();
    void ReadHandler(int& ret_data);

private:
    std::vector<int> m_buff;
    size_t m_capacity;
    size_t m_reading_index;
    size_t m_writing_index;
    std::mutex m_mutex_w;
    std::mutex m_mutex_starvation;
    std::counting_semaphore<std::__semaphore_impl::_S_max> m_sem_w;
};


TSCircularBuffer::TSCircularBuffer(std::size_t capacity) : m_buff(capacity), m_capacity(capacity), m_reading_index(0), m_writing_index(0), m_sem_w(1)
{
}


void TSCircularBuffer::ReadHandler(int& ret_data)
{

    static size_t readers = 0;

    m_mutex_starvation.lock();
    m_mutex_starvation.unlock();

    m_mutex_w.lock();
    if(++readers == 1)
    {
        m_sem_w.acquire();
    }
    m_mutex_w.unlock();


    if((m_writing_index) % (m_capacity + 1) == m_reading_index)
    {
        std::cout << "buffer is empty" << std::endl;
    }
    
    else
    {
        ret_data = m_buff[m_reading_index];
        // i wont inc the index so it will possible for multiple reading
       // m_reading_index = (m_reading_index + 1) % (m_capacity + 1);
        std::cout << ret_data << std::endl;
    }


    m_mutex_w.lock();
    if(--readers == 0)
    {
        m_sem_w.release();
    }
    m_mutex_w.unlock();

}

void TSCircularBuffer::WriteHandler()
{
    static int counter = 0;

    // we used mutex inorder to prevent starvation. the mutex has fairness while the semaphore dont
    m_mutex_starvation.lock();
    m_sem_w.acquire();
    m_mutex_starvation.unlock();

    if((m_writing_index + 1) % (m_capacity + 1) == m_reading_index)
    {
        std::cout << "buffer is full" << std::endl;
        return;
    }
    
    else
    {
        m_buff[m_writing_index] = 5;
        m_writing_index = (m_writing_index + 1) % (m_capacity + 1);
    }
      
    counter++;

    m_sem_w.release();

}


int main()
{
    TSCircularBuffer circular_buffer(50);  // Create TSCircularBuffer object directly

    std::map<std::thread::id, std::thread> threads;

    size_t i = 0;

    for (i = 0; i < WRITERS; i++)
    {
        std::thread thread(&TSCircularBuffer::WriteHandler, std::ref(circular_buffer));  // Pass pointer to circular_buffer
        threads[thread.get_id()] = std::move(thread);
     }

    int ret_data = 0;

    for (; i < READERS + WRITERS; i++)
    {
        std::thread thread(&TSCircularBuffer::ReadHandler, std::ref(circular_buffer), std::ref(ret_data));  // Pass pointer to circular_buffer
        threads[thread.get_id()] = std::move(thread);  
    }

    for (auto& thread : threads)
    {
        thread.second.join();  // Join the thread using thread.second
    }

    return 0;
}