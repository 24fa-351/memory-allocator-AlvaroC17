# Targets for building different versions of the test program
all: memtest_sys memtest_dev

# Build memtest with the system malloc
memtest_sys: memtest.c
	gcc -o memtest_sys -DSYSTEM_MALLOC memtest.c

# Build memtest with the custom malloc implementation
memtest_dev: memtest.c malloc.c malloc.h heap.c heap.h
	gcc -o memtest_dev memtest.c malloc.c heap.c

# Clean up build artifacts
clean:
	rm -f memtest_sys memtest_dev
