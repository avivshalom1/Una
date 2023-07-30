#include <map>
#include <iostream>

template <typename K, typename V>
class interval_map
{
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K, V> m_map;

public:
    interval_map(V const &val) : m_valBegin(val) {}

    void assign(K const &keyBegin, K const &keyEnd, V const &val)
    {
        V curr_val = (*this)[keyBegin];
        V end_val = (*this)[keyEnd];

        if (val != curr_val)
        {
            m_map[keyBegin] =  val;
            std::cout << m_map[keyBegin] << std::endl;
        }

        auto nextKeyIterator = m_map.upper_bound(keyBegin);
        K nextKey = nextKeyIterator->first;            

        // if there is a next key
        if(nextKeyIterator != m_map.end())
        {
            while(nextKeyIterator != m_map.end() && keyEnd > nextKey)
            {
                m_map.erase(nextKey);
                end_val = nextKeyIterator->second;         
                nextKeyIterator = m_map.upper_bound(nextKey);
                nextKey = nextKeyIterator->first;
            }

            m_map[keyEnd] = end_val;
        }

        else
        {
            m_map.insert({keyEnd, curr_val});
        }
    }

    V const &operator[](K const &key) const
    {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin())
        {
            return m_valBegin;
        }
        else
        {
            return (--it)->second;
        }
    }

    void Print()
    {
        for (auto it = m_map.begin(); it != m_map.end(); ++it)
        {
            std::cout << (*it).first << " " << (*it).second << std::endl;
        }

        std::cout << '\n'
                  << std::endl;
    }
};

void IntervalMapTest()
{
    interval_map<int, char> inter_map('A');

    inter_map.assign(3, 10, 'B');
    inter_map.Print();

    inter_map.assign(3, 10, 'C');
    inter_map.Print();

    inter_map.assign(4, 10, 'D');
    inter_map.Print();

    inter_map.assign(4, 7, 'E');
    inter_map.Print();

    inter_map.assign(5, 11, 'F');
    inter_map.Print();

    for(size_t i = 0; i < 20; i++)
    {
        std::cout << i << " " << inter_map[i] << std::endl;
    }
    


}

int main()
{
    IntervalMapTest();

    return 0;
}