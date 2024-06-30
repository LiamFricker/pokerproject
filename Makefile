# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++11 -pthread
OBJDIR = src
BINDIR = bin
SRCDIR = src

# GTK flags
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-2.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-2.0)

# Target directories
BIN_DIR = bin

# Poker_Beta directory and contents
USERDIR = ../Poker_V1.0
USER_TAR_CONTENTS = $(USERDIR)/README.md $(USERDIR)/COPYRIGHT $(USERDIR)/INSTALL.md $(USERDIR)/bin/ $(USERDIR)/doc/

DEVDIR = ../Poker_V1.0_src
DEV_TAR_CONTENTS = $(DEVDIR)/README.md $(DEVDIR)/COPYRIGHT $(DEVDIR)/INSTALL.md $(DEVDIR)/bin/ $(DEVDIR)/doc/ $(DEVDIR)/src/ $(DEVDIR)/Makefile

# Target executables
TARGET_SERVER = $(BIN_DIR)/server
TARGET_CLIENT = $(BIN_DIR)/client
TARGET_TEST_GAME = $(SRCDIR)/gameGUITest
TARGET_TEST_MENU = $(SRCDIR)/menuGUITest
TARGET_TEST_SERVER = $(SRCDIR)/server_UnitTest
TARGET_TEST_CLIENT = $(SRCDIR)/client_UnitTest
TARGET_TEST_AI = $(SRCDIR)/ai_UnitTest

# Source files
SRCS_COMMON = $(SRCDIR)/Card.cpp $(SRCDIR)/Deck.cpp $(SRCDIR)/Player.cpp $(SRCDIR)/HandEvaluator.cpp $(SRCDIR)/Game.cpp 
SRCS_SERVER = $(SRCDIR)/server.cpp $(SRCS_COMMON)
SRCS_CLIENT = $(SRCDIR)/client.cpp $(SRCDIR)/Menu.cpp $(SRCDIR)/GameGUI.cpp
SRCS_TEST_GAME = $(SRCDIR)/GUIGame_UnitTest.cpp
SRCS_TEST_MENU = $(SRCDIR)/GUIMenu_UnitTest.cpp
SRCS_TEST_SERVER = $(SRCDIR)/server_UnitTest.cpp $(SRCS_COMMON)
SRCS_TEST_CLIENT = $(SRCDIR)/client_UnitTest.cpp
SRCS_TEST_AI  = $(SRCDIR)/ai_UnitTest.cpp $(SRCDIR)/Card.cpp $(SRCDIR)/HandEvaluator.cpp $(SRCDIR)/ai.cpp

# Object files
OBJS_SERVER = $(SRCS_SERVER:.cpp=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.cpp=.o)
OBJS_TEST_GAME = $(SRCS_TEST_GAME:.cpp=.o)
OBJS_TEST_MENU = $(SRCS_TEST_MENU:.cpp=.o)
OBJS_TEST_SERVER = $(SRCS_TEST_SERVER:.cpp=.o)
OBJS_TEST_CLIENT = $(SRCS_TEST_CLIENT:.cpp=.o)
OBJS_TEST_AI = $(SRCS_TEST_AI:.cpp=.o)

# Default target
all: $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_TEST_GAME) $(TARGET_TEST_MENU) $(TARGET_TEST_SERVER) $(TARGET_TEST_CLIENT) $(TARGET_TEST_AI) copy_assets

# Rule to link object files and create the executable for the server
$(TARGET_SERVER): $(OBJS_SERVER)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET_SERVER) $(OBJS_SERVER) -lpthread

# Rule to link object files and create the executable for the client
$(TARGET_CLIENT): $(OBJS_CLIENT)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET_CLIENT) $(OBJS_CLIENT) -lpthread $(GTK_LIBS)

# Rule to compile source files into object files
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
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
	ln -sf $(TARGET_TEST_GAME) ./gameGUITest
	ln -sf $(TARGET_TEST_MENU) ./menuGUITest
	ln -sf $(TARGET_TEST_SERVER) ./server_UnitTest
	ln -sf $(TARGET_TEST_CLIENT) ./client_UnitTest
	ln -sf $(TARGET_TEST_AI) ./ai_UnitTest

# Copy assets to the bin directory
copy_assets:
	mkdir -p $(BINDIR)/Assets
	cp -r $(SRCDIR)/Assets/* $(BINDIR)/Assets/

# Clean up generated files
clean:
	rm -f $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_TEST_GAME) $(TARGET_TEST_MENU) $(TARGET_TEST_SERVER) $(TARGET_TEST_CLIENT) $(TARGET_TEST_AI) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_TEST_GAME) $(OBJS_TEST_MENU) $(OBJS_TEST_SERVER) $(OBJS_TEST_CLIENT) $(OBJS_TEST_AI) *.exe test gameGUITest GUIGame_UnitTest.o GUIMenu_UnitTest.o menuGUITest server client server_UnitTest client_UnitTest ai_UnitTest

# Run AI unit test
test_ai: $(TARGET_TEST_AI)
	cd $(SRCDIR) && ./$(notdir $(TARGET_TEST_AI))

# Run server unit test
test_server: $(TARGET_TEST_SERVER)
	cd $(SRCDIR) && ./$(notdir $(TARGET_TEST_SERVER))

# Run client unit test
test_client: $(TARGET_TEST_CLIENT)
	cd $(SRCDIR) && ./$(notdir $(TARGET_TEST_CLIENT))

# Run GUI tests
test_gui: $(TARGET_TEST_GAME) $(TARGET_TEST_MENU)
	cd $(SRCDIR) && ./$(notdir $(TARGET_TEST_GAME))
	cd $(SRCDIR) && ./$(notdir $(TARGET_TEST_MENU))

# Run all tests
test: test_gui test_server test_client test_ai
tar:
	tar cvzf Poker_Beta.tar.gz $(USER_TAR_CONTENTS)
	tar cvzf Poker_Beta_src.tar.gz $(DEV_TAR_CONTENTS)


# Phony targets
.PHONY: all clean test test_server test_client test_gui test_ai symlink
