# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11 -pthread

# GTK flags
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-2.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-2.0)

# Target directories
BIN_DIR = Poker_V1.0/bin

# Target executables
TARGET_SERVER = $(BIN_DIR)/server
TARGET_CLIENT = $(BIN_DIR)/client
TARGET_TEST_GAME = gameGUITest
TARGET_TEST_MENU = menuGUITest
TARGET_TEST_SERVER = server_UnitTest
TARGET_TEST_CLIENT = client_UnitTest
TARGET_TEST_AI = ai_UnitTest

# Source files
SRCS_COMMON = Card.cpp Deck.cpp Player.cpp HandEvaluator.cpp Game.cpp ai.cpp
SRCS_SERVER = server.cpp $(SRCS_COMMON)
SRCS_CLIENT = client.cpp Menu.cpp GameGUI.cpp
SRCS_TEST_GAME = GUIGame_UnitTest.cpp
SRCS_TEST_MENU = GUIMenu_UnitTest.cpp
SRCS_TEST_SERVER = server_UnitTest.cpp $(SRCS_COMMON)
SRCS_TEST_CLIENT = client_UnitTest.cpp #Menu.cpp #GameGUI.cpp
SRCS_TEST_AI  = ai_UnitTest.cpp Card.cpp HandEvaluator.cpp ai.cpp

# Object files
OBJS_SERVER = $(SRCS_SERVER:.cpp=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.cpp=.o)
OBJS_TEST_GAME = $(SRCS_TEST_GAME:.cpp=.o)
OBJS_TEST_MENU = $(SRCS_TEST_MENU:.cpp=.o)
OBJS_TEST_SERVER = $(SRCS_TEST_SERVER:.cpp=.o)
OBJS_TEST_CLIENT = $(SRCS_TEST_CLIENT:.cpp=.o)
OBJS_TEST_AI = $(SRCS_TEST_AI:.cpp=.o)

# Default target
all: $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_TEST_GAME) $(TARGET_TEST_MENU) $(TARGET_TEST_SERVER) $(TARGET_TEST_CLIENT) $(TARGET_TEST_AI) symlink

# Rule to link object files and create the executable for the server
$(TARGET_SERVER): $(OBJS_SERVER)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET_SERVER) $(OBJS_SERVER) -lpthread

# Rule to link object files and create the executable for the client
$(TARGET_CLIENT): $(OBJS_CLIENT)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET_CLIENT) $(OBJS_CLIENT) -lpthread $(GTK_LIBS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(GTK_CFLAGS) -c $< -o $@

# Rule to compile the server unit test
$(TARGET_TEST_SERVER): $(OBJS_TEST_SERVER)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST_SERVER) $(OBJS_TEST_SERVER) -lpthread

# Rule to compile the client unit test
$(TARGET_TEST_CLIENT): $(OBJS_TEST_CLIENT)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST_CLIENT) $(OBJS_TEST_CLIENT) -lpthread $(GTK_LIBS)

# Rule to compile the GUI Game Unit Test
$(TARGET_TEST_GAME): $(OBJS_TEST_GAME)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST_GAME) $(OBJS_TEST_GAME) $(GTK_LIBS)

# Rule to compile the GUI Menu Unit Test
$(TARGET_TEST_MENU): $(OBJS_TEST_MENU)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST_MENU) $(OBJS_TEST_MENU) $(GTK_LIBS)

# Rule to compile the AI Unit Test
$(TARGET_TEST_AI): $(OBJS_TEST_AI)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST_AI) $(OBJS_TEST_AI)

# Rule to create symbolic links in the current directory
symlink: $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_TEST_GAME) $(TARGET_TEST_MENU) $(TARGET_TEST_SERVER) $(TARGET_TEST_CLIENT) $(TARGET_TEST_AI)
	ln -sf $(TARGET_SERVER) ./server
	ln -sf $(TARGET_CLIENT) ./client
	ln -sf $(TARGET_TEST_GAME)
	ln -sf $(TARGET_TEST_MENU)
	ln -sf $(TARGET_TEST_SERVER)
	ln -sf $(TARGET_TEST_CLIENT)
	ln -sf $(TARGET_TEST_AI)

# Clean up generated files
clean:
	rm -f $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_TEST_GAME) $(TARGET_TEST_MENU) $(TARGET_TEST_SERVER) $(TARGET_TEST_CLIENT) $(TARGET_TEST_AI) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_TEST_GAME) $(OBJS_TEST_MENU) $(OBJS_TEST_SERVER) $(OBJS_TEST_CLIENT) $(OBJS_TEST_AI) *.exe test gameGUITest GUIGame_UnitTest.o GUIMenu_UnitTest.o menuGUITest server client server_UnitTest client_UnitTest ai_UnitTest

# Run AI unit test
test_ai: $(TARGET_TEST_AI)
	./$(TARGET_TEST_AI)

# Run server unit test
test_server: $(TARGET_TEST_SERVER)
	./$(TARGET_TEST_SERVER)

# Run client unit test
test_client: $(TARGET_TEST_CLIENT)
	./$(TARGET_TEST_CLIENT)

# Run GUI tests
test_gui: $(TARGET_TEST_GAME) $(TARGET_TEST_MENU)
	./$(TARGET_TEST_GAME)
	./$(TARGET_TEST_MENU)

# Run all tests
test: $(TARGET_TEST_GAME) $(TARGET_TEST_MENU) $(TARGET_TEST_SERVER) $(TARGET_TEST_CLIENT) $(TARGET_TEST_AI)
	./$(TARGET_TEST_GAME)
	./$(TARGET_TEST_MENU)
	./$(TARGET_TEST_SERVER)
	./$(TARGET_TEST_CLIENT)
	./$(TARGET_TEST_AI)

# Phony targets
.PHONY: all clean test test_server test_client test_gui test_ai symlink
