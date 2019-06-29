TARGET1 = client
TARGET2 = server

SRC_PATH = src/
INCLUDE_PATH = include/
BUILD_PATH = build/

all: $(TARGET1) $(TARGET2) clean
	
$(TARGET1): Error.o Client.o Client_test.o
	g++ $^ -o $(BUILD_PATH)$@

$(TARGET2): Error.o Server.o Server_test.o
	g++ $^ -o $(BUILD_PATH)$@  

%.o: $(SRC_PATH)%.cpp
	g++ -c $^ -I $(INCLUDE_PATH) -o $@ 

clean:
	rm -rf *.o