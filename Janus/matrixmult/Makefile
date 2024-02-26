SHELL := /bin/bash
# List of source files
SOURCES := matrixmult_janus.cpp matrixmult_manual.cpp
# List of executable files, derived from source file names
EXECUTABLES := $(SOURCES:.cpp=.gpp_run)

# Rule to build all executables
all: $(EXECUTABLES)

# Rule to build an executable from an object file
%.gpp_run: %.cpp
	/usr/bin/g++ -O0 $< -o $@

# Rule to measure energy consumption of all executables
measure: $(EXECUTABLES)
	sudo modprobe msr
	$(foreach exec,$(EXECUTABLES),\
		for n in $$(seq 50 50 1000); do \
			echo "$(exec) $$n"; \
			for j in {1..40}; do \
				sudo ../../RAPL/main "./$(exec) $$n" 1 Janus $$(basename $(exec) .gpp_run)_$$n; \
			done; \
		done;)

# Rule to run all executables
run: $(EXECUTABLES)
	$(foreach exec,$(EXECUTABLES),./$(exec);)

# Rule to measure memory usage of all executables
mem: $(EXECUTABLES)
	$(foreach exec,$(EXECUTABLES),/usr/bin/time -v ./$(exec);)

# Rule to run valgrind on all executables
valgrind: $(EXECUTABLES)
	$(foreach exec,$(EXECUTABLES),valgrind --tool=massif --stacks=yes ./$(exec) 21;)

# Rule to clean up generated files
clean:
	rm -f $(EXECUTABLES)
