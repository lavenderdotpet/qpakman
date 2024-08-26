//------------------------------------------------------------------------
//  Image Handling
//------------------------------------------------------------------------
//
//  Copyright (c) 2008  Andrew J Apted
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------

#ifndef __IMAGE_FORMAT_H__
#define __IMAGE_FORMAT_H__

#include "headers.h"

#include "im_image.h"

rgb_image_c * Image_Load(FILE *fp);
// loads the given PNG/JPG/TGA/BMP image.  Returns 0 if something went wrong.
// The image will be BGR or BGRA (never paletted).

bool Image_Save(const char *filename, rgb_image_c *img, int compress = 3);
// saves the image (in PNG format) to the given file.  The compression
// level should be between 1 (Z_BEST_SPEED) and 9 (Z_BEST_COMPRESSION).
// Returns false if failed to save.
// NOTE: Alpha channel is IGNORED.

#endif  /* __IMAGE_FORMAT_H__ */

//--- editor settings ---
// vi:ts=2:sw=2:expandtab
