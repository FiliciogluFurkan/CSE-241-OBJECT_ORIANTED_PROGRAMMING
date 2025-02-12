all: clean compile run

compile: main.cpp OS.cpp Directory.cpp Softlinked.cpp Regular.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o homework2 main.cpp OS.cpp Directory.cpp Softlinked.cpp Regular.cpp -lm

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./homework2
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f homework2

