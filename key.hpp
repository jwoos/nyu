#ifndef ENCRYPTION_KEY_H
#define ENCRYPTION_KEY_H

#include "utils.hpp"
#include "frequency.hpp"

std::vector<char> generateKey(uint32_t);

std::vector<char> generateKey(const std::map<char, uint32_t>&);

#endif

