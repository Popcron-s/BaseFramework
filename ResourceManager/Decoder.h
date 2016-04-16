#pragma once

#include "BaseType.h"
#include "Text.h"

bool Decode(const char* filename, _BaseType** data);

/*****************************************************
 * *Image Decoder*
 *  BMP
 *  PNG
 *****************************************************/
bool BMPDecoder(const char* filename, ImageData** data);
bool PNGDecoder(const char* filename, ImageData** data);
