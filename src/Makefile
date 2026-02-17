# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Default program to build
all: hello questions_3 ascii_image image_file ppm_menu



# -------------------------
# hello program
# -------------------------
hello: hello.o
	$(CXX) $(CXXFLAGS) -o hello hello.o

hello.o: hello.cpp
	$(CXX) $(CXXFLAGS) -c hello.cpp

# -------------------------
# questions_3 program
# -------------------------
questions_3: questions_3.o user_io.o controllers.o Image.o image_drawing.o image_output.o PPM.o ActionData.o MenuData.o
	$(CXX) $(CXXFLAGS) -o questions_3 questions_3.o user_io.o controllers.o Image.o image_drawing.o image_output.o PPM.o ActionData.o MenuData.o

questions_3.o: questions_3.cpp image_menu.h ActionData.h MenuData.h PPM.h Image.h
	$(CXX) $(CXXFLAGS) -c questions_3.cpp

user_io.o: user_io.cpp image_menu.h ActionData.h MenuData.h PPM.h Image.h
	$(CXX) $(CXXFLAGS) -c user_io.cpp

controllers.o: controllers.cpp image_menu.h Image.h 
	$(CXX) $(CXXFLAGS) -c controllers.cpp

# -------------------------
# ascii_image program
# -------------------------
ascii_image: ascii_image.o controllers.o image_drawing.o image_output.o Image.o user_io.o PPM.o ActionData.o MenuData.o
	$(CXX) $(CXXFLAGS) -o ascii_image ascii_image.o controllers.o image_drawing.o image_output.o Image.o user_io.o PPM.o ActionData.o MenuData.o

ascii_image.o: ascii_image.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c ascii_image.cpp

image_drawing.o: image_drawing.cpp image_menu.h Image.h
	$(CXX) $(CXXFLAGS) -c image_drawing.cpp

image_output.o: image_output.cpp image_menu.h Image.h
	$(CXX) $(CXXFLAGS) -c image_output.cpp

Image.o: Image.cpp Image.h
	$(CXX) $(CXXFLAGS) -c Image.cpp


# -------------------------
# image_file program
# -------------------------
image_file: image_file.o user_io.o PPM.o controllers.o image_drawing.o image_output.o Image.o ActionData.o MenuData.o
	$(CXX) $(CXXFLAGS) -o image_file image_file.o user_io.o PPM.o controllers.o image_drawing.o image_output.o Image.o ActionData.o MenuData.o

image_file.o: image_file.cpp PPM.h
	$(CXX) $(CXXFLAGS) -c image_file.cpp

PPM.o: PPM.cpp PPM.h
	$(CXX) $(CXXFLAGS) -c PPM.cpp


#Action and Menu Data


ActionData.o: ActionData.cpp ActionData.h
	$(CXX) $(CXXFLAGS) -c ActionData.cpp


MenuData.o: MenuData.cpp MenuData.h
	$(CXX) $(CXXFLAGS) -c MenuData.cpp


#Assignment 5
ppm_menu: ppm_menu.o user_io.o controllers.o Image.o image_drawing.o image_output.o PPM.o ActionData.o MenuData.o
	$(CXX) $(CXXFLAGS) -o ppm_menu ppm_menu.o user_io.o controllers.o Image.o image_drawing.o image_output.o PPM.o ActionData.o MenuData.o


ppm_menu.o: ppm_menu.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c ppm_menu.cpp


# -------------------------
# Clean up object files and executables
# -------------------------
clean:
	rm -f *.o hello questions_3 ascii_image image_file ppm_menu
