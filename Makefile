CXX=g++
CXXFLAGS=-std=c++17 -Wall -I"C:/sqlite"
LDFLAGS=-L"C:/sqlite" -lsqlite3

SRC=src/main.cpp src/engine.cpp src/db.cpp
BIN=bin
TARGET=$(BIN)/ride_matching.exe

all:
	if not exist $(BIN) mkdir $(BIN)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	if exist $(BIN) rmdir /s /q $(BIN)
