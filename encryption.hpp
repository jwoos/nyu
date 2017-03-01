#ifndef ENCRYPTION_ENCRPYT_H
#define ENCRYPTION_ENCRPYT_H

#include "utils.hpp"

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>

std::map<char, std::set<unsigned int>* >* generateKeys();

std::string* encrypt(std::string);

#endif
