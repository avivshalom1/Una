/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *  ~ *
~ Author        Aviv Shalom                  ~
* Version       1.0                          *
~ Description   SortWords.cpp             ~
* Group         RD 133-4                     *
~ Company       ILRD Ramat Gan               ~
* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~~ */
#include <algorithm>
#include <functional>
#include <bits/stdc++.h>

#include "sort_words.hpp"

namespace ilrd
{
    SortWords::SortWords(const char *f1,
                         const char *f2,
                         const char *f3,
                         const char *_output) : m_filesToRead({f1, f2, f3}),
                                                m_vectors(3),
                                                m_outputFile(_output)
    {

        for (std::size_t i = 0; i < filesNum; i++)
        {
            std::thread thread(&SortWords::ThreadHandler, std::ref(*this), i);
            m_workingThreads.push_back(std::move(thread));
        }

        for (auto &thread : m_workingThreads)
        {
            thread.join();
        }

        std::cout << "enter your sorting option:" << std::endl;
        std::cout << "sort: ";
        std::cin >> m_sorting_option;

        std::cout << "enter your split option:" << std::endl;
        std::cout << "split:";
        std::cin >> m_spliting_option;
    }

    void SortWords::ThreadHandler(size_t fileNum)
    {
        std::ifstream inputFile(m_filesToRead[fileNum]); // Replace "example.txt" with your file name

        std::string word;

        if (!inputFile.is_open())
        {
            std::cout << "Failed to open file" << std::endl;
            return;
        }

        while(inputFile >> word)
        {
            word[0] = std::tolower(word[0]);
            m_vectors[fileNum].push_back(word);
        }

        inputFile.close();
    }


    SortWords::~SortWords()
    {
        std::ofstream outputFile(m_outputFile); // Replace "output.txt" with your desired file name

        if (!outputFile.is_open())
        {
            std::cout << "Failed to open output file" << std::endl;
            return;
        }

        for (const auto &vector : m_vectors)
        {
            m_output_vector.insert(m_output_vector.end(), vector.begin(), vector.end());      
        }

        if(m_sorting_option == 'a')
        {
            std::sort(m_output_vector.begin(), m_output_vector.end());
        }

        else if(m_sorting_option == 'd')
        {
             std::sort(m_output_vector.begin(), m_output_vector.end(), [](std::string a, std::string b) {
        return a > b;
    });
        }


        size_t occurrences = 1;
        size_t max_occurrence = 1;
        std::string max_occurrence_string;

        for (auto it = m_output_vector.begin(); it != m_output_vector.end() - 1; )
        {
            if(*it == *(it + 1)) 
            {
                occurrences++;

                if(occurrences > max_occurrence)
                {
                    max_occurrence = occurrences;
                    max_occurrence_string = *it;
                }

                m_output_vector.erase(it);
            }

            else
            {
                occurrences = 1;
                ++it;
            }
       }

        std::string word;

        for(auto& word: m_output_vector)
        {
            outputFile << word << m_spliting_option;
        }

        std::cout << max_occurrence_string << " appeared: " << max_occurrence << " times" << std::endl;

        outputFile.close();
    }

}