/*
 * png.cpp
 *
 *  Created on: 26 de oct. de 2015
 *      Author: starkus
 */


#include "png.h"


GLuint PNG_load(const char* filename, int* width, int* height) {

	png_byte header[8];

	// Open file
	FILE *fp = fopen(filename, "rb");
	if (!fp){
		perror(filename);
		return -1;
	}

	// Read header
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8)) {
		fprintf(stderr, "ERROR: %s is not a valid PNG file.\n", filename);
		fclose(fp);
		return -1;
	}

	// Read struct
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) abort();

	// Info struct
	png_infop info = png_create_info_struct(png);
	if (!info) abort();

	// Endinfo struct
	png_infop end = png_create_info_struct(png);
	if (!end) abort();

	// If any error
	if (setjmp(png_jmpbuf(png)))
		abort();

	png_init_io(png, fp);

	// Tell libpng we read the header already
	png_set_sig_bytes(png, 8);

	png_read_info(png, info);

	*width =				png_get_image_width(png, info);
	*height =			png_get_image_height(png, info);
	png_byte color_type =	png_get_color_type(png, info);
	png_byte bit_depth =	png_get_bit_depth(png, info);


	// Read any format into 8bit depth RGBA

	if (bit_depth == 16)
		png_set_strip_16(png);

	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_expand(png);

	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand(png);

	if (png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_expand(png);

	// If no alpha channel, make it all FF
	if (color_type == PNG_COLOR_TYPE_RGB ||
		color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_PALETTE)

		//png_set_filter(png, 0xFF, PNG_FILLER_AFTER); THIS IS WRONG! Damn you random internet person that helped me for free!
		png_set_add_alpha(png, 0xff, PNG_FILLER_AFTER);

	if (color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_GRAY_ALPHA)

		png_set_gray_to_rgb(png);

	png_read_update_info(png, info);


	int rowbytes = png_get_rowbytes(png, info);
	// glTexImage2d requires rows to be 4-byte aligned
	rowbytes += 3 - ((rowbytes-1) % 4);

	int _height = *height;
	int _width = *width;

	// Image data block for opengl
	png_byte* image_data;
	image_data = (png_byte*) malloc(rowbytes * _height * sizeof(png_byte)+15);
	if (image_data == NULL) {
		fprintf(stderr, "ERROR: Couldn't allocate memory for PNG %s.\n", filename);
		abort();
	}

	// row_pointers are for reading png with libpng
	png_bytep *row_pointers;
	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * _height);
	for (int y = 0; y < _height; y++)
		row_pointers[_height - 1 - y] = image_data + y * rowbytes;

	// Read the PNG
	png_read_image(png, row_pointers);


	// Generate OpenGL texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// Clean up
	png_destroy_read_struct(&png, &info, &end);
	free(image_data);
	free(row_pointers);
	fclose(fp);

	return texture;
}
