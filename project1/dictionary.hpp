#ifndef ENCRYPTION_DICTIONARY_H
#define ENCRYPTION_DICTIONARY_H

#include "utils.hpp"

std::string randomWords(uint32_t);

std::set<std::string> loadDictionary(std::string);

std::set<std::string> loadWords(uint32_t);

#endif
