/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *  ~ *
~ Author        Aviv Shalom                  ~
* Version       1.0                          *
~ Description   SortWords.hpp             ~
* Group         RD 133-4                     *
~ Company       ILRD Ramat Gan               ~
* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~~ */
#ifndef __SORT_WORDS__
#define __SORT_WORDS__

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <set>
#include <map>
#include <mutex>

namespace ilrd
{

    class SortWords
    {
    public:
        SortWords(const char *f1, 
                     const char *f2, 
                     const char *f3, 
                     const char *output); // the desired file name with the actuall result
        ~SortWords();
    
    private:
        size_t filesNum = 3;

        std::vector<std::vector<std::string>> m_vectors;
        std::vector<std::string> m_output_vector;
        std::vector<std::string> m_filesToRead; // files to read from
        std::vector<std::thread> m_workingThreads;
        std::string m_outputFile;
        char m_sorting_option;
        char m_spliting_option;

        void ThreadHandler(size_t fileNum);
    };













}






#endif //__SORT_WORDS__
