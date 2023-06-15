/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *  ~ *
~ Author        Aviv Shalom                  ~
* Version       1.0                          *
~ Description   findSynonyms.cpp             ~
* Group         RD 133-4                     *
~ Company       ILRD Ramat Gan               ~
* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~~ */

#include "findSynonyms.hpp"

namespace ilrd
{
    findSynonyms::findSynonyms(const char *f1,
                               const char *f2,
                               const char *f3,
                               const char *_output) : m_setIndex(0),
                                                      m_filesToRead({f1, f2, f3}),
                                                      m_outputFile(_output)
    {

        for (std::size_t i = 0; i < filesNum; i++)
        {
            std::thread thread(&findSynonyms::ThreadHandler, std::ref(*this), i);
            m_workingThreads.push_back(std::move(thread));
        }

        for (auto &thread : m_workingThreads)
        {
            thread.join();
        }
    }

    void findSynonyms::ThreadHandler(size_t fileNum)
    {
        std::ifstream inputFile(m_filesToRead[fileNum]); // Replace "example.txt" with your file name

        if (inputFile.is_open())
        {
            std::string firstWord;
            std::string secondWord;

            while (std::getline(inputFile, firstWord, '='))
            {
                std::getline(inputFile, secondWord, ' ');


                //if none of the words are not exists, creating new set, with the right index,
                //and pushing the new set to its vector. 

                firstWord[0] = std::tolower(firstWord[0]);
                secondWord[0] = std::tolower(secondWord[0]);

                if (m_allWords.find(firstWord) == m_allWords.end() && m_allWords.find(secondWord) == m_allWords.end())
                {
                    m_mutex.lock();

                    m_allWords.insert(std::make_pair(firstWord, m_setIndex));       // Inserting key-value pair using make_pair
                    m_allWords.insert(std::make_pair(secondWord, m_setIndex));       // Inserting key-value pair using make_pair

                    std::set<std::string> currSet = {firstWord, secondWord};

                    m_synonymsOutput.insert(m_synonymsOutput.begin() + m_setIndex, currSet);   

                    m_setIndex++;

                    m_mutex.unlock();
                } 

                else
                {
                    //handling the case that a third pair of synonyms is connecting between
                    //unrelated synonyms

                    if (m_allWords.find(firstWord) != m_allWords.end() && m_allWords.find(secondWord) != m_allWords.end())
                    {
                        if(m_allWords[firstWord] != m_allWords[secondWord])
                        {
                            //TODO combine the 2 sets
                            //TODO update the map indexes
                        }
                    }

                    m_mutex.lock();

                    //if the word already exists, pushing to the right set
                    m_synonymsOutput[m_allWords[firstWord]].insert(firstWord);
                    m_synonymsOutput[m_allWords[secondWord]].insert(secondWord);

                    m_mutex.unlock();
                }
            }

            inputFile.close();
        }
        else
        {
            std::cout << "Failed to open the file." << std::endl;
        }
    }

    findSynonyms::~findSynonyms()
    {
        std::ofstream outputFile(m_outputFile); // Replace "output.txt" with your desired file name

        if (outputFile.is_open())
        {
            for (const auto &wordSet : m_synonymsOutput)
            {
                for (const auto &word : wordSet)
                {
                    outputFile << word << " ";
                }

                outputFile << "\n";
            }

            outputFile.close();
        }


        else
        {
            std::cout << "Failed to open the file." << std::endl;
        }
    }

}