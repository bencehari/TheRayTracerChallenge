#include "ppm.h"

#include <stdio.h>
#include <string.h>

enum PPM_ErrCode ppm_save(const char* _name, const int _width, const int _height, const int _colors[]) {
	size_t nameLen = strlen(_name);
	char nameWithExt[nameLen + 4 + 1];
	memcpy(nameWithExt, _name, nameLen);
	memcpy(nameWithExt + nameLen, ".ppm", 4);
	nameWithExt[nameLen + 4] = '\0';
	
	FILE* file = fopen(nameWithExt, "w");
	if (file == NULL) {
		printf("[PPM] Couldn't open file '%s'\n", nameWithExt);
		return PPM_FILE;
	}
	
	// magic number
	fputs("P3\n", file);
	
	// resolution
	char res[12];
	if (sprintf(res, "%d %d\n", _width, _height) <= 0) {
		fclose(file);
		return PPM_HEADER;
	}
	fputs(res, file);
	
	// max color value
	fputs("255\n", file);
	
	{
		char tmp[12];
		for (int i = 0, c = 0; i < _width * _height * 3; i += 3) {
			if (sprintf(tmp, "%d %d %d", _colors[i], _colors[i + 1], _colors[i + 2]) < 0) {
				fclose(file);
				return PPM_WRITE;
			}
			
			fputs(tmp, file);
			
			if (c++ == _width) {
				c = 0;
				fputs("\n", file);
			}
			else fputs(" ", file);
		}
	}
	
	fclose(file);
	
	return PPM_NONE;
}
