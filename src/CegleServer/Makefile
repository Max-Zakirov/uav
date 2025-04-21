CXX = arm-linux-gnueabihf-g++
#CXX = g++
CXXFLAGS = -std=c++11 -ICeglePacket -ICore -IProtocols
LDFLAGS = -static
SRC_DIR = .
OBJ_DIR = build
OUT = cegle-server

SRC = $(shell find $(SRC_DIR)/CeglePacket $(SRC_DIR)/Core $(SRC_DIR)/Protocols -name '*.cpp')

SRC += $(SRC_DIR)/main.cpp

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CORE_OBJ_DIR = $(OBJ_DIR)/Core
CEGLE_PACKET_OBJ_DIR = $(OBJ_DIR)/CeglePacket
PROTOCOLS_OBJ_DIR = $(OBJ_DIR)/Protocols

$(shell mkdir -p $(CEGLE_PACKET_OBJ_DIR) $(CORE_OBJ_DIR) $(PROTOCOLS_OBJ_DIR))

all: $(OUT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(OUT)

clean:
	rm -rf $(OBJ_DIR) $(OUT)
