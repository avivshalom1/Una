/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *  ~ *
~ Author        Aviv Shalom                  ~
* Version       1.0                          *
~ Description   findSynonyms.cpp             ~
* Group         RD 133-4                     *
~ Company       ILRD Ramat Gan               ~
* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~~ */

#include "elevator.hpp"

namespace ilrd
{

    Building::Building(size_t floorsNum, size_t elevatorsNum) : 
    m_floorsNum(floorsNum)
    {
        for(size_t i = 0; i < elevatorsNum; i++)
        {
            std::shared_ptr<Elevator> ptr(new Elevator(this));
            m_elevators.push_back(ptr);
        }

    }


    void Building::CallElevator(size_t currFloor)
    {

        m_elevators[0]->AddRequest(currFloor);


/*         for(auto& it : m_elevators)
        {
            if(!(*it).HasRequests())
            {
                (*it).AddRequest(currFloor);
            }
        }
 */
    }

    Elevator::Elevator(Building *Building):
    direction(Elevator::STOP),
    m_Building(Building),
    m_currFloor(0),
    m_currCapacity(8),
    m_isFull(0),
    m_sem(0)
    {
        m_thread = std::thread(&Elevator::ThreadHandler, std::ref(*this));
    }

    Elevator::~Elevator()
    {
        m_thread.join();
    }

    void Elevator::AddRequest(size_t desiredFloor)
    {
        m_requests.push(desiredFloor);
        m_sem.release();
    }

    void Elevator::openDoor()
    {
        if(direction == Elevator::STOP)
        {
            std::cout << "opening door" << std::endl;
        }
    }

    void Elevator::closeDoor()
    {
        if(direction == Elevator::STOP)
        {
            std::cout << "closing door" << std::endl;
        }
    }

    bool Elevator::HasRequests() const
    {
        return !!m_requests.size();
    }


    void Elevator::ThreadHandler()
    {

        m_toRun = 1;

        while(m_toRun)
        {
            std::cout << "Handler" << std::endl;

            m_sem.acquire();
            GoTo(m_requests.top());
            m_requests.pop();
        }

    }

    void Elevator::GoTo(size_t desiredFloor)
    {
        std::cout << "Going to Floor: " << desiredFloor << std::endl;
        sleep(1);
    }
}