TARGET = uni.exe
ODIR = obj
IDIR = include
SDIR = src
LDIR = lib

vpath %.cpp $(SDIR)
vpath %.h $(IDIR)

__CXX_OBJS = uni_main.o uni_window.o uni_render.o uni_enemy.o uni_util.o \
			 uni_button.o uni_tower.o uni_mouse.o uni_keyboard.o uni_font.o \
			 uni_game.o
CXX_OBJS = $(patsubst %.o,$(ODIR)/%.o,$(__CXX_OBJS))
CXX_OBJS_WIN32_COMPAT = $(subst /,\,$(CXX_OBJS))

LIBS = -L $(LDIR) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

CLEAN = $(CXX_OBJS_WIN32_COMPAT) $(TARGET)

CXX = g++
CXXFLAGS = -g -I include -Wall -Wno-missing-braces -Wconversion -pedantic \
		   -std=c++17 -D DEBUG

all: $(TARGET)
	echo Build complete!

$(TARGET): $(CXX_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(ODIR)/%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean
clean:
	rm $(CLEAN)