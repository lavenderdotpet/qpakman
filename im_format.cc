//------------------------------------------------------------------------
//  Image Handling
//------------------------------------------------------------------------
//
//  Copyright (c) 2008  Andrew J Apted
//  Copyright (c) 2015  Anton Leontiev
//  Copyright (c) 2024  Ivy Bowling
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

#include "headers.h"
#include "main.h"

#include "im_format.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_ONLY_BMP
#define STBI_ONLY_TGA
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

rgb_image_c *Image_Load(FILE *fp)
{
  rgb_image_c * img = 0;

  int image_width;
  int image_height;
  int bits_per_pixel;

  byte * image_pixels = stbi_load_from_file(fp, &image_width, &image_height, &bits_per_pixel, 4);

  if (image_pixels == NULL) {
    printf("Image_Load : Could not load image, STBI returns: \"%s\" !\n", stbi_failure_reason());
    goto failed;
  }

  img = new rgb_image_c(image_width, image_height);

  img->pixels = (u32_t*)image_pixels;

  // cypress (25 aug 2024) -- "is_solid" is completely unused, though seems out of scope
  // to purge. leaving it here.
  img->is_solid = true;

  return img;

  /* -AJA- Normally I don't like gotos.  In this situation where there
   * are lots of points of possible failure and a growing set of
   * things to be undone, it makes for nicer code.
   */
failed:

  if (img)
  {
    delete img;
    img = 0;
  }

  return 0;
}


bool Image_Save(const char *filename, rgb_image_c *img, int compress)
{
  int result = stbi_write_png(filename, img->width, img->height, 4, img->pixels, 4 * img->width);

  // 1 = success
  if (!result)
  {
    printf("Image_Save : Error saving PNG image, STBIW returns: \"%s\" !\n", stbi_failure_reason());
    return false;
  }

  return true;
}

//--- editor settings ---
// vi:ts=2:sw=2:expandtab
