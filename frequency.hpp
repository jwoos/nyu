#ifndef ENCRYPTION_FREQUENCY_H
#define ENCRYPTION_FREQUENCY_H

#include "utils.hpp"

std::map<char, uint32_t> calculateCharFrequency(const std::string&);

std::map<char, uint32_t> generateFrequencyMap();

std::map<std::string, uint32_t> generateDigramFrequencyMap();

#endif
