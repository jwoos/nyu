#ifndef ENCRYPTION_DICTIONARY_H
#define ENCRYPTION_DICTIONARY_H

#include "utils.hpp"
#include <fstream>

std::string randomWords(uint32_t numWords);
std::set<std::string> loadDictionary(std::string filename);


#endif