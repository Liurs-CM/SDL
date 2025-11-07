TARGET=demo
CXX=g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
LDFLAGS = `pkg-config --cflags --libs sdl2` -lSDL2_image
SRCDIR = src
OBJDIR = obj
INCDIR = include
SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:.o=.d)

all: $(TARGET) gen_tag

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "link done: $@"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -I$(INCDIR) -MMD -MP -c $< -o $@
	@echo "compile: $< -> $@"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

-include $(DEPENDS)

clean:
	rm -f $(OBJECTS) $(DEPENDS)
	rm -rf $(OBJDIR)
	rm -f $(TARGET)
	@echo "clean done."

rebuild: clean all

info:
	@echo "编译器: $(CXX)"
	@echo "编译标志: $(CXXFLAGS)"
	@echo "链接标志: $(LDFLAGS)"
	@echo "源文件: $(SOURCES)"
	@echo "对象文件: $(OBJECTS)"
	@echo "依赖文件: $(DEPENDS)"
	@echo "输出目录: $(OBJDIR)"

.PHONY: all clean rebuild info

gen_tag:
	@ctags -R src/
	@mv tags .tags

run:
	./$(TARGET)
