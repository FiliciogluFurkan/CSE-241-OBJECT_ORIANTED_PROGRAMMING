all: clean compile run

compile: main.cpp board.cpp pieces.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o homework1 main.cpp board.cpp pieces.cpp -lm

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./homework1
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f homework1

