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

# allows for unittesting of all .cpp scripts by compiling them into binary executables
TEST = tests
TESTS = $(wildcard $(TEST)/*.cpp)
TESTBINS=$(patsubst $(TEST)/%.cpp, $(TEST)/bin/%, $(TESTS))

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

# turns all .cpp to binary files with the testing framework lcriterion
$(TEST)/bin/%: $(TEST)/%.cpp
	$(CXX) $< $(OBJS) -o $@ -lcriterion $(LIBS)

$(TEST)/bin:
	mkdir $@

# each test in the test binary variable is conducted
test: $(BIN) $(Test)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

# delete executable and objects
clean:
	@echo "** Removing object files and executable..."
	$(RM) -r bin/* obj/*

# zips game
submit:
	@echo "** Zipping game..."
	$(RM) $(SUBMIT)
	zip $(SUBMIT) $(BIN)

# deletes zip
unsubmit:
	@echo "** Deleting zipped game..."
	$(RM) -r $(SUBMIT)

