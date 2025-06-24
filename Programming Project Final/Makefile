CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

TARGET1 = app_1.exe
TARGET2 = app_2.exe

SOURCES1 = app_1.cpp src/InventoryManager.cpp
OBJECTS1 = $(SOURCES1:.cpp=.o)

SOURCES2 = app_2.cpp src/WishlistManager.cpp src/InquiryManager.cpp
OBJECTS2 = $(SOURCES2:.cpp=.o)

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJECTS1)
	$(CXX) $(OBJECTS1) -o $(TARGET1)
	@echo "$(TARGET1) built successfully."

$(TARGET2): $(OBJECTS2)
	$(CXX) $(OBJECTS2) -o $(TARGET2)
	@echo "$(TARGET2) built successfully."

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /q *.exe *.o >nul 2>nul & if exist src\\*.o del /q src\\*.o