# Makefile for Java project

# Compiler
JAVAC = javac

# Compiler flags
JFLAGS = -d bin

# Source directory
SRC_DIR = src

# Package directories
PACKAGE1 = Homework3/Package1
PACKAGE2 = Homework3/Package2

# Source files
SOURCE_FILES = $(SRC_DIR)/$(PACKAGE1)/JavaSet.java \
               $(SRC_DIR)/$(PACKAGE1)/JavaVector.java \
               $(SRC_DIR)/$(PACKAGE2)/JavaContainer.java \
               $(SRC_DIR)/$(PACKAGE1)/JavaDriver.java

# Output directory
OUTPUT_DIR = bin

# Target: all (default target)
all: clean compile run

# Target: compile
compile:
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@$(JAVAC) $(JFLAGS) $(SOURCE_FILES)

# Target: run
run:
	@echo "-------------------------------------------"
	@echo "Running JavaDriver..."
	@java -cp $(OUTPUT_DIR) Homework3.Package1.JavaDriver
	@echo "-------------------------------------------"
	@echo "Completed running JavaDriver."

# Target: clean
clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -rf $(OUTPUT_DIR)/*

