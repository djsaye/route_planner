#include "DrawText.h"

/**
 * Render the given text string, `text`, to the PNG object `img` using the color
 * specified in the `color` pixel at the position specified by `x_start` and
 * `y_start`.
 *
 * @param img     PNG image to draw onto.
 * @param color   A pixel of the desired text foreground color.
 * @param x_start The starting position x coordinate (0 is the left edge of the image).
 * @param y_start The starting position y coordinate (0 is the top edge of the image).
 * @param text    The text to render.
 *
 * @return Status of operation.
 */
enum status DrawText::DrawTextPNG(cs225::PNG &img, const cs225::HSLAPixel &color,
	unsigned int x_start, unsigned int y_start, const std::string &text)
{
	unsigned int x = x_start,
	             y = y_start;
	for (char c: text) {
		for (unsigned row = 0; row < char_height; ++row) {
			for (int8_t off = 0; off < 16; ++off) {
				if (font[c][row] & (0x8000 >> off)) { // active pixel?
					cs225::HSLAPixel &px = img.getPixel(x + off, y + row);
					px.h = color.h;
					px.s = color.s;
					px.l = color.l;
				}
			}
		}
		if (x + 2*char_width <= img.width())
			x += char_width; // continue on same line
		else if (y + 2*char_height < img.height()) {
			// wrap to next line
			x = x_start;
			y += char_height;
		} else
			return ERROR_DRAW_RESTRICTED; // we ran out of space at the bottom; stop
	}
	return OK;
}

/**
 * Render the given text string, `text`, in a debug format to standard output
 * with characters stacked vertically. This function is intended for debugging
 * and quick font previews.
 *
 * @param text The text to render.
 *
 * @return Status of operation.
 */
enum status DrawText::DrawTextConsole(const std::string &text)
{
	for (char c: text) {
		for (uint16_t row: font[c]) {
			printf("%04X ", row);
			for (int8_t off = 0; off < 16; ++off) {
				if (row & (0x8000 >> off))
					std::cout << 'X'; // active pixel
				else
					std::cout << '.'; // inactive pixel
			}
			std::cout << std::endl;
		}
	}
	return OK;
}

/**
 * Load a font in Adobe BDF format from a file on disk specified by the given
 * filename.
 *
 * @param filename The filename of the file containing the font.
 *
 * @return Status of operation.
 */
enum status DrawText::LoadFont(const std::string filename)
{
	std::ifstream f_font(filename);
	if (!f_font.is_open()) {
		std::cerr << __func__ << ": Could not open font file." << std::endl;
		return ERROR_FILE;
	}
	std::string line_raw;
	enum ParseState st = NONE;
	uint16_t codepoint = 0;
	while (std::getline(f_font, line_raw)) {
		size_t i = line_raw.find(ARG_SEP);
		if (st == NONE) {
			if (!line_raw.compare(0, i, "STARTCHAR"))
				st = CHAR_METADATA;
			else if (!line_raw.compare(0, i, "FONTBOUNDINGBOX")) {
				// gather the first two params, which specify bounding box dims
				size_t i_fld_start, i_fld_end;
				std::string field;
				i_fld_start = line_raw.find_first_not_of(ARG_SEP, i);
				i_fld_end = line_raw.find_first_of(ARG_SEP, i_fld_start);
				field = line_raw.substr(i_fld_start, i_fld_end - i_fld_start);
				char_width = atoi(field.c_str());
				i_fld_start = line_raw.find_first_not_of(ARG_SEP, i_fld_end);
				i_fld_end = line_raw.find_first_of(ARG_SEP, i_fld_start);
				field = line_raw.substr(i_fld_start, i_fld_end - i_fld_start);
				char_height = atoi(field.c_str());
			}
		} else if (st == CHAR_METADATA) {
			if (!line_raw.compare(0, i, "ENCODING")) {
				// gather codepoint value
				size_t i_enc_no_start = line_raw.find_first_not_of(ARG_SEP, i);
				std::string enc_str = line_raw.substr(i_enc_no_start, std::string::npos);
				codepoint = atoi(enc_str.c_str());
			} else if (!line_raw.compare(0, i, "BITMAP"))
				st = CHAR_BITMAP;
			else if (!line_raw.compare(0, i, "ENDCHAR"))
				st = NONE;
		} else if (st == CHAR_BITMAP) {
			if (!line_raw.compare(0, i, "ENDCHAR")) {
				st = NONE;
				continue;
			}
			// gather and store bitmap row
			uint16_t bitmap = std::stoul(line_raw, nullptr, 16);
			if (char_width <= 8)
				bitmap <<= 8;
			//printf("%04X %04X\n", codepoint, bitmap); // DEBUG
			font[codepoint].push_back(bitmap);
		}
	}
	//std::cout << "Imported font with char. dimensions " << char_width << "x" << char_height << "." << std::endl; // DEBUG

	return OK;
}
