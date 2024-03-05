#include "io/image_parser.h"
#include <fstream>

BitmapImage ImageParser::read_bitmap(const std::filesystem::path& path) {
  // Öffne die Datei
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::exception();
  }

  // Lies die Kopfzeile
  char header[14];
  file.read(header, sizeof(header));

  // Prüfe, ob die Datei ein gültiger Bitmap ist
  if (header[0] != 'P' || header[1] != '6') {
    throw std::exception();
  }

  // Lies die Höhe und Breite des Bildes
  int height = header[7] * 256 + header[8];
  int width = header[9] * 256 + header[10];

  // Berechne die Größe des Bilddatenbereichs
  int size = width * height * 3;

  // Lies die Bilddaten
  std::vector<uint8_t> data(size);
  file.read(reinterpret_cast<char*>(data.data()), size);

  // Erstelle ein BitmapImage-Objekt
  BitmapImage image(height, width);

  // Fülle das BitmapImage-Objekt mit den Bilddaten
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      // Die Bilddaten sind im BGR-Format gespeichert
      int index = (y * width + x) * 3;
      image.set_pixel(x, y, Pixel<uint8_t>(data[index], data[index + 1], data[index + 2]));
    }
  }

  return image;
}

void ImageParser::write_bitmap(const std::filesystem::path& path, const BitmapImage& image) {
  // Öffne die Datei
  std::ofstream file(path);
  if (!file.is_open()) {
    throw std::exception();
  }

  // Schreibe die Kopfzeile
  file << "P6\n" << image.get_height() << " " << image.get_width() << "\n255\n";

  // Schreibe die Bilddaten
  for (int y = 0; y < image.get_height(); ++y) {
    for (int x = 0; x < image.get_width(); ++x) {
      // Die Bilddaten sind im BGR-Format gespeichert
      int index = (y * image.get_width() + x) * 3;
      file << image.get_pixel(x, y).get_blue_channel() << " " << image.get_pixel(x, y).get_green_channel() << " " << image.get_pixel(x, y).get_red_channel() << "\n";
    }
  }
}
