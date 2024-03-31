CXX = g++
LIBS = -lGL -lSDL2 -lGLEW
FLAGS = -Wall -Wextra -Werror

SRCS = main.cpp init.cpp
OBJS = $(SRCS:.cpp=.o)

all: run

run: $(OBJS)
	$(CXX) -o $@ $^ $(LIBS) $(FLAGS)

%.o: %.cpp
	$(CXX) -c $< $(FLAGS)

clean:
	rm -f $(OBJS) run
