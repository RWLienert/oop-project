# define relevant libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
# define compiler and conditions
CXX = g++
# selects every .cpp file except for main
SRCS = $(filter-out src/Main.cpp, $(wildcard src/*.cpp))
# turn all of the files from SRCS to .o files
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))
BIN = bin/game
SUBMIT = oop_project.zip

all: $(BIN)

# build game
$(BIN): $(OBJS) src/Main.cpp
	@echo "** Building the game"
	$(CXX) src/Main.cpp $(OBJS) -o $@ $(LIBS)
	@./$(BIN)

# convert scripts to .o files
obj/%.o: src/%.cpp
	@echo "** Converts .cpp files to .o"
	$(CXX) -c $< -o $@

# delete executable and objects
clean:
	@echo "** Removing object files and executable..."
	$(RM) -r bin/* obj/*

submit:
	@echo "** Zipping game..."
	$(RM) $(SUBMIT)
	zip $(SUBMIT) $(BIN)

unsubmit:
	@echo "** Deleting zipped game..."
	$(RM) -r $(SUBMIT)

