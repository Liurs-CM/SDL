PROJ=demo

all: comp gen_tag

comp:
	g++ src/*.cpp `pkg-config --cflags --libs sdl2` -lSDL2_image -o ${PROJ}

gen_tag:
	ctags -R src/
	mv tags .tags

run:
	./${PROJ}
