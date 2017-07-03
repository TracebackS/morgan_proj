# Server's files should be named as 'filename_s.h' or 'filename_s.cpp'
# Client's files should be named as 'filename_c.h' or 'filename_c.cpp'
# Shared files should be named as 'filename_sh.h' or 'filename_sh.cpp'
# After make all, the LD_LIBRARY_PATH should be set to point the .so lib (.../boost_1_64_0/stage/lib), or it will lead to error.

PROGRAM_SERVER = Server
PROGRAM_CLIENT = Client

# CXXFLAGS should be set to point the boost_1_64_0 path

CXX = g++
CXXFLAGS=-std=c++11 -Wall -I /home/xys/boost/boost_1_64_0

S_CPP_FILES = $(wildcard *_s.cpp)
C_CPP_FILES = $(wildcard *_c.cpp)
SH_CPP_FILES = $(wildcard *_sh.cpp)
S_H_FILES = $(wildcard *_s.h)
C_H_FILES = $(wildcard *_c.h)
SH_H_FILES = $(wildcard *_sh.h)

# LDFLAGS should be set to point the .so path

LDFLAGS=-lboost_system -lpthread -L /home/xys/boost/boost_1_64_0/stage/lib

all: $(PROGRAM_SERVER) $(PROGRAM_CLIENT)

$(PROGRAM_SERVER): $(S_CPP_FILES) $(S_H_FILES) $(SH_H_FILES) $(SH_CPP_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(S_H_FILES) $(SH_H_FILES) $(S_CPP_FILES) $(SH_CPP_FILES) $(PROGRAM_SERVER).cpp -o $(PROGRAM_SERVER)

$(PROGRAM_CLIENT): $(C_CPP_FILES) $(C_H_FILES) $(SH_H_FILES) $(SH_CPP_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(C_H_FILES) $(SH_H_FILES) $(C_CPP_FILES) $(SH_CPP_FILES) $(PROGRAM_CLIENT).cpp -o $(PROGRAM_CLIENT)

clean:
	rm -rf *.o *.a $(PROGRAM_SERVER) $(PROGRAM_CLIENT)
