#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "cs225/PNG.h"

enum status {
	OK = 0,
	ERROR_MISC,  // miscellaneous error
	ERROR_FILE,  // file I/O error
	ERROR_DRAW_RESTRICTED,  // draw operation exceeded image extents
};

class DrawText {
public:
	enum status LoadFont(const std::string filename);
	enum status DrawTextPNG(cs225::PNG &img, const cs225::HSLAPixel &color,
		unsigned int x, unsigned int y, const std::string &text);
	enum status DrawTextConsole(const std::string &text);
private:
	std::unordered_map<uint16_t, std::vector<uint16_t>> font;  // font bitmap data
	unsigned int char_width = 0, char_height = 0;  // bounding box dimensions
	const char ARG_SEP = ' ';  // BDF field/argument separation character
	enum ParseState {
		NONE = 0,
		CHAR_METADATA,
		CHAR_BITMAP,
	};
};
