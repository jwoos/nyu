main:
	g++ $(FILE) -I. -Wall -std=c++11

# lazy
class:
	g++ class/$(FILE) -I. -Wall -std=c++11

hw:
	g++ homework/$(FILE) -I. -Wall -std=c++11

lab:
	g++ lab/$(FILE) -I. -Wall -std=c++11
