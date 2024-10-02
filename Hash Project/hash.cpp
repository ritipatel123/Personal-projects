//
//  hash.cpp
//  projectfinal
//
//  Created by Riti Patel on 6/13/24.
//

#include "hash.h"
#include <functional>
#include <iostream>


HashTable::HashTable()
{
    m_hash.resize(m_size);
}

void HashTable::insert(string subString, unsigned long offset)
{
    size_t hashKey = std::hash<string>()(subString);
    // Determine the index in the hash table by taking the modulo of the hash key with the hash table size minus one
        // This ensures the index falls within the bounds of the hash table
    size_t index = hashKey % (m_size - 1);
    // Create a new node with the given substring and offset
    Node nodeAtBucket(subString, offset);
    // Insert the new node at the calculated index in the hash table
    m_hash.at(index).push_back(nodeAtBucket);
}

bool HashTable::contains(string subString, unsigned long& offset) const
{
    size_t hashKey = std::hash<string>()(subString);
    size_t index = hashKey % (m_size - 1);
    size_t sizeLL = m_hash.at(index).size();
    if(sizeLL == 0)
    {
        return false;
    }
    // loop through list with iterators
    for(auto itLL = m_hash.at(index).begin(); itLL != m_hash.at(index).end(); itLL++)
    {

        if(subString == itLL->m_subString)
        {
            offset = itLL->m_offset;
            return true;
        }
    }
    // no strings matched in the list
    return false;
}

int HashTable::findBestCopyIndex(const string& oldFile,const string& newFile, string subString,
                        unsigned long &bestlen, size_t initialIndex) const
{
    int bestIndex = -1;
    bestlen = 0;
    auto subStringLength = subString.length(); // Get the length of the substring to match
    size_t hashkey = std::hash<string>()(subString);
    size_t index = hashkey % (m_size - 1); // Determine the index in the hash table using modulo operation
    for(auto itLL = m_hash.at(index).begin();
        itLL != m_hash.at(index).end();
        itLL++)
    {
        if(itLL->m_subString == subString)
        {
            int consecutive = 0;
            // Continue matching characters beyond the initial matching substring
            while(itLL->m_offset + subStringLength + consecutive < oldFile.length() &&
                  initialIndex + subStringLength + consecutive < newFile.length())
            {
                // Break the loop if characters do not match
                if(oldFile[itLL->m_offset + subStringLength + consecutive] != newFile[initialIndex + subStringLength + consecutive])
                {
                    break;
                }
                consecutive++;
            }
            if(consecutive >= bestlen)
            {
                bestIndex = static_cast<int>(itLL->m_offset);
                bestlen = consecutive;
            }
        }
    }
    // Update bestlen to include the length of the initial matching substring
    bestlen = subStringLength + bestlen;
    return bestIndex;
}
