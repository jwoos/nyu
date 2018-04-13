#ifndef INTERACTIVE_CG_UTILS_H
#define INTERACTIVE_CG_UTILS_H


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Angel-yjc.h"


using namespace std;


typedef struct Entity {
	vec3* vertices;
	vec3* colors;

	GLuint buffer;

	int size;
} Entity;


void drawObj(GLuint, int, GLuint);

void readFile(const string&, const string&, vector<vec3>&, vector<vec3>&);

float distance(const vec3&, const vec3&);


#endif
