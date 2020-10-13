PROJECT = dyna-dbg

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -fopenmp
INCL = ./include/KMC

CLI_ARG = /data/kmc-out/sars-cov-2.res

.PHONY: all

all: $(PROJECT)

$(PROJECT): src/main.o $(INCL)/kmc_api/kmc_file.o $(INCL)/kmc_api/kmer_api.o $(INCL)/kmc_api/mmer.o
	@echo "🔗 Linking $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	@echo "🚧 Compiling $<"
	$(CXX) $(CXXFLAGS) -I$(INCL) -o $@ -c $<

clean:
	@echo "🧹 Cleaning..."
	rm -rf *.o
	rm -rf **/*.o
	rm -r $(INCL)/kmc_api/*.o
	rm -r $(PROJECT)

run:
	./$(PROJECT) $(CLI_ARG)