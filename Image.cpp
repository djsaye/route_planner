#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <iostream>

using cs225::HSLAPixel;

void Image::lighten() {
	lighten(.1);
}

void Image::lighten(double amount) {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			HSLAPixel &px = getPixel(x, y);
			double l_new = px.l + amount;
			if (l_new < 0.)
				l_new = 0.;
			if (l_new > 1.)
				l_new = 1.;
			px.l = l_new;
		}
	}
}

void Image::darken() {
	darken(.1);
}

void Image::darken(double amount) {
	for (unsigned x = 0; x < width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			HSLAPixel &px = getPixel(x, y);
			double l_new = px.l - amount;
			if (l_new < 0.)
				l_new = 0.;
			if (l_new > 1.)
				l_new = 1.;
			px.l = l_new;
		}
	}
}

void Image::saturate() {
	saturate(.1);
}

void Image::saturate(double amount) {
	for (unsigned x = 0; x < width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			HSLAPixel &px = getPixel(x, y);
			double s_new = px.s + amount;
			if (s_new < 0.)
				s_new = 0.;
			if (s_new > 1.)
				s_new = 1.;
			px.s = s_new;
		}
	}
}

void Image::desaturate() {
	desaturate(.1);
}

void Image::desaturate(double amount) {
	for (unsigned x = 0; x < width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			HSLAPixel &px = getPixel(x, y);
			double s_new = px.s - amount;
			if (s_new < 0.)
				s_new = 0.;
			if (s_new > 1.)
				s_new = 1.;
			px.s = s_new;
		}
	}
}

void Image::grayscale() {
	for (unsigned x = 0; x < width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			HSLAPixel &px = getPixel(x, y);
			px.s = 0.;
		}
	}
}

void Image::rotateColor(double degrees) {
	for (unsigned x = 0; x < width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			HSLAPixel &px = getPixel(x, y);
			double h_new = px.h + 360*999 + degrees; // :D
			if (h_new < 0.)
				h_new = 0.;
			if (h_new > 360.)
				h_new = std::fmod(h_new, 360.);
			px.h = h_new;
		}
	}
}

double angle_dist(double a, double b) {
	double diff = std::fabs(a - b);
	double rem = std::fmod(diff, 360.);
	return 180. - std::fabs(rem - 180.);
}

void Image::illinify() {
	const double ILLINI_ORANGE = 11;
	const double ILLINI_BLUE = 216;
	for (unsigned x = 0; x < width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			HSLAPixel &px = getPixel(x, y);
			double b_dist = angle_dist(px.h, ILLINI_BLUE);
			double o_dist = angle_dist(px.h, ILLINI_ORANGE);
			if (o_dist < b_dist)
				px.h = ILLINI_ORANGE;
			else
				px.h = ILLINI_BLUE;
		}
	}
}

void Image::scale(double factor) {
	unsigned w = width(),
	         h = height();
	unsigned nw = w * factor,
	         nh = h * factor;
	Image orig = *this;
	resize(nw, nh);
	for (unsigned x = 0; x < nw; x++) {
		for (unsigned y = 0; y < nh; y++) {
			HSLAPixel &npx = getPixel(x, y);
			HSLAPixel &opx = orig.getPixel(std::floor(x / factor), std::floor(y / factor));
			npx = opx;
		}
	}
}

void Image::scale(unsigned w, unsigned h) {
	unsigned ow = width(),
	         oh = height();
	double x_factor = (double) w / (double) ow,
	       y_factor = (double) h / (double) oh;
	if (x_factor < y_factor)
		scale(x_factor);
	else
		scale(y_factor);
}
