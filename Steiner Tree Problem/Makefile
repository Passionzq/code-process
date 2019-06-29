TARGET = main

SRC_PATH = src/
INCLUDE_PATH = include/
BUILD_PATH = bulid/

all: $(TARGET) clean
	
$(TARGET): Graph.o GA.o RandomSlack.o main.o 
	g++ $^ -o $(BUILD_PATH)$@ -lpthread

%.o: $(SRC_PATH)%.cpp
	g++ -c $^ -I $(INCLUDE_PATH) -o $@ -lpthread

clean:
	rm -rf *.o
