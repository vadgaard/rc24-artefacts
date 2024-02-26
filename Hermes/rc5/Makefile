SHELL := /bin/bash
# List of source files
SOURCES := rc5_hermes.c rc5_manual.c
# List of executable files, derived from source file names
EXECUTABLES := $(SOURCES:.c=.gcc_run)

# Rule to build all executables
all: $(EXECUTABLES)

# Rule to build an executable from an object file
%.gcc_run: %.c
	/usr/bin/gcc -O0 $< -o $@

# Rule to measure energy consumption of all executables
measure: $(EXECUTABLES)
	sudo modprobe msr
	$(foreach exec,$(EXECUTABLES),\
		for n in $$(seq 3750000 3750000 75000000); do \
			echo "$(exec) $$n"; \
			for j in {1..40}; do \
				sudo ../../RAPL/main "./$(exec) $$n" 1 Hermes $$(basename $(exec) .gcc_run)_$$n; \
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
