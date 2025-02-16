CXX = g++
CXXFLAGS = -Wall -Wextra

SRCS = src/main.cpp src/password_cracker.cpp src/encrypt.cpp src/constants.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = quebra_senhas

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) 