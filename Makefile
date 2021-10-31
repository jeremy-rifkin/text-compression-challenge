BUILD_DIR = bin
CPP = g++
WFLAGS = -Wextra -Wpedantic -Wno-sign-compare -Wno-parentheses
CPPFLAGS = -std=c++17 -g -DDRIVER -fsanitize=address $(WFLAGS)
MKDIR_P ?= mkdir -p

.PHONY: all clean remake

all: bin/z bin/frequency

bin/frequency: frequency.cpp
	$(MKDIR_P) $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) $< -o $@

bin/z: main.cpp
	$(MKDIR_P) $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)

remake: clean
	$(MAKE)
