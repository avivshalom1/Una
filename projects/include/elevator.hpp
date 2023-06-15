/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *  ~ *
~ Author        Aviv Shalom                  ~
* Version       1.0                          *
~ Description   elevator.hpp                 ~
* Group         RD 133-4                     *
~ Company       ILRD Ramat Gan               ~
* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~~ */
#ifndef __ELEVATOR__
#define __ELEVATOR__

#include <cstddef>
#include <vector>
#include <iostream>
#include <queue>
#include <thread>
#include <unistd.h>
#include <semaphore>
#include <memory>


namespace ilrd
{

class Elevator;

class Building
{
public:
    Building(size_t floorsNum, size_t elevatorsNum);

    //choosing which elevator will get the request 
    void CallElevator(size_t currFloor); 


private:
    std::size_t m_floorsNum;
    std::vector<std::shared_ptr<Elevator>> m_elevators;
};


class Elevator
{
public:
    Elevator(Building *Building);
    ~Elevator();
    void AddRequest(size_t desiredFloor);
    void Display();

    void openDoor();
    void closeDoor();

    bool HasRequests() const;

    // algorithem for placing the requests in the queue
    class Compare
    {
    public:
       bool operator()(size_t a, size_t b)
       {
            return 1;
       }
    };

    enum Direction
    {
        STOP,
        DOWN,
        UP
    };


private:
    Direction direction;
    void ThreadHandler();
    std::thread m_thread;
    void GoTo(size_t desiredFloor);
    std::priority_queue<size_t, std::vector<size_t>, Compare> m_requests;
    Building *m_Building;
    size_t m_currFloor;
    size_t m_currCapacity;
    size_t startingFloor;
    size_t lastFloor;
    bool m_isFull;
    std::counting_semaphore<std::__semaphore_impl::_S_max> m_sem;
    bool m_toRun;


};





}






#endif //__ELEVATOR__
