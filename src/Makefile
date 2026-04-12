CXX = g++
CXXFLAGS = -Wall -std=c++17

PROGRAMS = hello questions_3 ascii_image image_file ppm_menu

COMMON_OBJS = user_io.o controllers.o Image.o image_drawing.o image_output.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o

HELLO_OBJS = hello.o
QUESTIONS_OBJS = questions_3.o $(COMMON_OBJS)
ASCII_OBJS = ascii_image.o $(COMMON_OBJS)
IMAGE_FILE_OBJS = image_file.o $(COMMON_OBJS)
PPM_MENU_OBJS = ppm_menu.o $(COMMON_OBJS)

all: $(PROGRAMS)

hello: $(HELLO_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

hello.o: hello.cpp
	$(CXX) $(CXXFLAGS) -c $<

questions_3: $(QUESTIONS_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

questions_3.o: questions_3.cpp image_menu.h ActionData.h MenuData.h PPM.h Image.h
	$(CXX) $(CXXFLAGS) -c $<

ascii_image: $(ASCII_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

ascii_image.o: ascii_image.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c $<

image_file: $(IMAGE_FILE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

image_file.o: image_file.cpp PPM.h
	$(CXX) $(CXXFLAGS) -c $<

ppm_menu: $(PPM_MENU_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

ppm_menu.o: ppm_menu.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c $<

PPM.o: PPM.cpp PPM.h
	$(CXX) $(CXXFLAGS) -c $<

Image.o: Image.cpp Image.h
	$(CXX) $(CXXFLAGS) -c $<

user_io.o: user_io.cpp image_menu.h ActionData.h MenuData.h PPM.h Image.h
	$(CXX) $(CXXFLAGS) -c $<

controllers.o: controllers.cpp image_menu.h Image.h
	$(CXX) $(CXXFLAGS) -c $<

ActionData.o: ActionData.cpp ActionData.h
	$(CXX) $(CXXFLAGS) -c $<

MenuData.o: MenuData.cpp MenuData.h
	$(CXX) $(CXXFLAGS) -c $<

image_filters.o: image_filters.cpp image_menu.h 
	$(CXX) $(CXXFLAGS) -c $<

NumberGrid.o: NumberGrid.cpp NumberGrid.h
	$(CXX) $(CXXFLAGS) -c $<

ColorTable.o: ColorTable.cpp ColorTable.h
	$(CXX) $(CXXFLAGS) -c $<

ComplexFractal.o: ComplexFractal.cpp ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<


JuliaSet.o: JuliaSet.cpp JuliaSet.h
	$(CXX) $(CXXFLAGS) -c $<

MandelbrotSet.o: MandelbrotSet.cpp MandelbrotSet.h
	$(CXX) $(CXXFLAGS) -c $<	

clean:
	rm -f *.o $(PROGRAMS)