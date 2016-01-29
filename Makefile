main:
	g++ $(FILE) -Wall -std=c++11

class:
	g++ class/$(FILE) -Wall -std=c++11

hw:
	g++ homework/$(FILE) -Wall -std=c++11

lab:
	g++ lab/$(FILE) -Wall -std=c++11
