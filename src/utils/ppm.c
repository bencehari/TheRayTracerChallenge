#include "ppm.h"

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 70

enum PPM_ErrCode ppm_save(const char* _name, const int _width, const int _height, const uint8_t _colors[]) {
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
	
	// i: index, cpl: color per line, chpl: character per line
	for (int i = 0, cpl = 0, chpl = 0; i < _width * _height * 3; i++) {
		uint8_t c = _colors[i];
		
		int len = c > 99 ? 3 : c > 9 ? 2 : 1;
		if (chpl + len > MAX_LINE_LEN) {
			fseek(file, -1, SEEK_CUR);
			fputs("\n", file);
			chpl = 0;
		}
		
		char num[5];
		sprintf(num, "%d ", c);
		fputs(num, file);
		
		chpl += len + 1;

		if (++cpl % (_width * 3) == 0) {
			fseek(file, -1, SEEK_CUR);
			fputs("\n", file);
			chpl = 0;
		}
	}
	
	fclose(file);
	
	return PPM_NONE;
}
