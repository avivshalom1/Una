/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *  ~ *
~ Author        Aviv Shalom                  ~
* Version       1.0                          *
~ Description   findSynonyms.hpp             ~
* Group         RD 133-4                     *
~ Company       ILRD Ramat Gan               ~
* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~~ */
#ifndef __FIND_SYNONYMS__
#define __FIND_SYNONYMS__

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

    class findSynonyms
    {
    public:
        findSynonyms(const char *f1, 
                     const char *f2, 
                     const char *f3, 
                     const char *output); // the desired file name with the actuall result
        ~findSynonyms();
        



    private:
        size_t filesNum = 3;
        size_t m_setIndex;
        std::vector<std::string> m_filesToRead; // files to read from
        std::vector<std::thread> m_workingThreads;
        std::mutex m_mutex;
        std::vector<std::set<std::string>> m_synonymsOutput;
        std::map<std::string, size_t> m_allWords;
        std::string m_outputFile;


        void ThreadHandler(size_t fileNum);
    };













}






#endif //__FIND_SYNONYMS__
