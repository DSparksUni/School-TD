TARGET = uni.exe
ODIR = obj
IDIR = include
SDIR = src
LDIR = lib

vpath %.cpp $(SDIR)
vpath %.h $(IDIR)

__CXX_OBJS = main.o window.o render.o enemy.o util.o \
			 button.o tower.o mouse.o keyboard.o font.o \
			 game.o json.o level.o
CXX_OBJS = $(patsubst %.o,$(ODIR)/uni_%.o,$(__CXX_OBJS))
CXX_OBJS_WIN32_COMPAT = $(subst /,\,$(CXX_OBJS))

LIBS = -L $(LDIR) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

CLEAN = $(CXX_OBJS_WIN32_COMPAT) $(TARGET)

CXX = g++
CXXFLAGS = -g -I include -Wall -Wno-missing-braces -Wconversion -Wextra \
		   -pedantic -std=c++17 -D DEBUG

TEST_TARGET = test.exe
__TEST_OBJS = test.o uni_util.o
TEST_OBJS = $(patsubst %.o,$(ODIR)/%.o,$(__TEST_OBJS))

test: $(TEST_TARGET)
	echo Test build complete!

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

all: $(TARGET)
	echo Build complete!

$(TARGET): $(CXX_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(ODIR)/%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean
clean:
	rm $(CLEAN)
