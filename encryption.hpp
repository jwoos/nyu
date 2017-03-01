#ifndef ENCRYPTION_ENCRPYT_H
#define ENCRYPTION_ENCRPYT_H

#include "utils.hpp"

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>

std::map<char, std::set<uint32_t>*>* generateKeys();

std::string* encrypt(std::map<char, std::set<uint32_t>*>* keyMap, std::string plaintext);

#endif
