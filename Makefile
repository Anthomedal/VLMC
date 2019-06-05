compile_parallel:
	mkdir bin

	g++ -c -Wall -O3 -fopenmp src/SequenceIndices.cpp -I./include/ -o bin/SequenceIndices.o
	g++ -c -Wall -O3 -fopenmp src/SequenceNombre.cpp -I./include/ -o bin/SequenceNombre.o
	g++ -c -Wall -O3 -fopenmp src/Probability.cpp -I./include/ -o bin/Probability.o
	g++ -c -Wall -O3 -fopenmp src/VLMCModel_constructor.cpp -I./include/ -o bin/VLMCModel_constructor.o
	g++ -c -Wall -O3 -fopenmp src/VLMCModel_get.cpp -I./include/ -o bin/VLMCModel_get.o
	g++ -c -Wall -O3 -fopenmp src/VLMCModel_simulation.cpp -I./include/ -o bin/VLMCModel_simulation.o
	g++ -c -Wall -O3 -fopenmp src/VLMCModel_draw.cpp -I./include/ -o bin/VLMCModel_draw.o
	g++ -c -Wall -O3 -fopenmp src/VLMC_simulation.cpp -I./include/ -o bin/VLMC_simulation.o
	g++ -c -Wall -O3 -fopenmp src/VLMC_get.cpp -I./include/ -o bin/VLMC_get.o
	g++ -c -Wall -O3 -fopenmp src/VLMC_set.cpp -I./include/ -o bin/VLMC_set.o
	g++ -c -Wall -O3 -fopenmp src/VLMC_constructor.cpp -I./include/ -o bin/VLMC_constructor.o
	g++ -c -Wall -O3 -fopenmp src/utils.cpp -I./include/ -o bin/utils.o
	g++ -c -Wall -O3 -fopenmp src/VLMC_draw.cpp -I./include/ -o bin/VLMC_draw.o

	mkdir lib

	ar r lib/libVLMC.a bin/*.o

	ranlib lib/libVLMC.a

	rm -r bin

test_parallel:
	g++ src/main.cpp -O3 -fopenmp -L./lib -I./include -lVLMC -o exec

	./exec

compile:
	mkdir bin

	g++ -c -Wall -O3 src/SequenceIndices.cpp -I./include/ -o bin/SequenceIndices.o
	g++ -c -Wall -O3 src/SequenceNombre.cpp -I./include/ -o bin/SequenceNombre.o
	g++ -c -Wall -O3 src/Probability.cpp -I./include/ -o bin/Probability.o
	g++ -c -Wall -O3 src/VLMCModel_constructor.cpp -I./include/ -o bin/VLMCModel_constructor.o
	g++ -c -Wall -O3 src/VLMCModel_get.cpp -I./include/ -o bin/VLMCModel_get.o
	g++ -c -Wall -O3 src/VLMCModel_simulation.cpp -I./include/ -o bin/VLMCModel_simulation.o
	g++ -c -Wall -O3 src/VLMCModel_draw.cpp -I./include/ -o bin/VLMCModel_draw.o
	g++ -c -Wall -O3 src/VLMC_simulation.cpp -I./include/ -o bin/VLMC_simulation.o
	g++ -c -Wall -O3 src/VLMC_get.cpp -I./include/ -o bin/VLMC_get.o
	g++ -c -Wall -O3 src/VLMC_set.cpp -I./include/ -o bin/VLMC_set.o
	g++ -c -Wall -O3 src/VLMC_constructor.cpp -I./include/ -o bin/VLMC_constructor.o
	g++ -c -Wall -O3 src/utils.cpp -I./include/ -o bin/utils.o
	g++ -c -Wall -O3 src/VLMC_draw.cpp -I./include/ -o bin/VLMC_draw.o

	mkdir lib

	ar r lib/libVLMC.a bin/*.o

	ranlib lib/libVLMC.a

	rm -r bin

test:
	g++ src/main.cpp -O3 -L./lib -I./include -lVLMC -o exec

	./exec
e:
	#g++ -c -g -Wall src/SequenceIndices.cpp -I./include/ -o bin/SequenceIndices.o
	#g++ -c -g -Wall src/SequenceNombre.cpp -I./include/ -o bin/SequenceNombre.o
	#g++ -c -g -Wall src/Probability.cpp -I./include/ -o bin/Probability.o
	#g++ -c -g -Wall src/main.cpp -I./include/ -o bin/main.o
	#g++ -c -g -Wall src/VLMCModel_constructor.cpp -I./include/ -o bin/VLMCModel_constructor.o
	#g++ -c -g -Wall src/VLMCModel_get.cpp -I./include/ -o bin/VLMCModel_get.o
	#g++ -c -g -Wall src/VLMCModel_simulation.cpp -I./include/ -o bin/VLMCModel_simulation.o
	g++ -c -g -Wall src/VLMCModel_draw.cpp -I./include/ -o bin/VLMCModel_draw.o
	#g++ -c -g -Wall src/VLMC_simulation.cpp -I./include/ -o bin/VLMC_simulation.o
	#g++ -c -g -Wall src/VLMC_get.cpp -I./include/ -o bin/VLMC_get.o
	#g++ -c -g -Wall src/VLMC_set.cpp -I./include/ -o bin/VLMC_set.o
	#g++ -c -g -Wall src/VLMC_constructor.cpp -I./include/ -o bin/VLMC_constructor.o
	#g++ -c -g -Wall src/utils.cpp -I./include/ -o bin/utils.o
	g++ -c -g -Wall src/VLMC_draw.cpp -I./include/ -o bin/VLMC_draw.o

	g++ bin/*.o -I./include/ -o exec

	./exec
