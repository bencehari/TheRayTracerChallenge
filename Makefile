SOURCE_FILES := $(shell find src/ -name '*.c')
CFLAGS := -gdwarf-2 -O0 -std=c11 -Wall -Winline -pedantic
SDL_FLAGS := $(shell pkg-config --cflags sdl2)
SDL_LIBS := $(shell pkg-config --libs sdl2)

OUTPUT_PATH := -o .build/output

build:
	@echo "Build initiated..."
	@mkdir -p .build/
	@gcc $(CFLAGS) -DAD_CHK $(SOURCE_FILES) $(OUTPUT_PATH) $(SDL_FLAGS) $(SDL_LIBS) -lm
	@.build/output
