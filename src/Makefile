CXX = g++
CXXFLAGS = -Wall -std=c++17

# Programs
all: hello questions_3

hello: hello.cpp
	$(CXX) $(CXXFLAGS) -o hello hello.cpp

questions_3: questions_3.o user_io.o controllers.o
	$(CXX) $(CXXFLAGS) -o questions_3 questions_3.o user_io.o controllers.o

questions_3.o: questions_3.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c questions_3.cpp

user_io.o: user_io.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c user_io.cpp

controllers.o: controllers.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c controllers.cpp

clean:
	rm -f *.o hello questions_3
