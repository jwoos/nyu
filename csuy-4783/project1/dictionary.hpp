#ifndef ENCRYPTION_DICTIONARY_H
#define ENCRYPTION_DICTIONARY_H

#include "utils.hpp"

std::string randomWords(uint32_t);

std::set<std::string> loadDictionary(std::string);

#endif
