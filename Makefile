# ==============================================================================
# Makefile for CineSort (COP3530 - Project 2b, Group 99)
# ==============================================================================

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -Iinclude

SRCDIR = src
INCDIR = include
BINDIR = bin

TARGET = $(BINDIR)/cinesort.exe

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BINDIR)/%.o, $(SOURCES))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)
	@echo [Build] Successfully generated $(TARGET)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	@rm -rf $(BINDIR)
	@echo [Clean] Cleaned build artifacts.
