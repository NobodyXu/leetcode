# Define variables
CXX = c++
CXXFLAGS += -std=c++17 -flto

# Define targets
.PHONY: all clean run

all: a.out run

run: a.out
	echo CXXFLAGS = $(CXXFLAGS)
	run_google-benchmarks.sh ./a.out ${result_file}

a.out: vector_ctor_vs_manual_move_from_set.o
	$(CXX) -L /usr/local/lib -lbenchmark -lpthread $^

clean:
	rm -f *.o a.out
