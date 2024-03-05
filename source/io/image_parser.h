#ifndef IMAGE_PARSER_H
#define IMAGE_PARSER_H
#pragma once

#include <cstdint>                  // Für std::uint8_t
#include <filesystem>               // Für std::filesystem::path
#include <fstream>                  // Für std::ifstream
#include <vector>                   // Für std::vector
#include "image/bitmap_image.h"     // Annahme: BitmapImage-Klasse ist bereits definiert

class ImageParser {
public:
  static BitmapImage read_bitmap(const std::filesystem::path& path);
  static void write_bitmap(const std::filesystem::path& path, const BitmapImage& image);
};

#endif // IMAGE_PARSER_H
