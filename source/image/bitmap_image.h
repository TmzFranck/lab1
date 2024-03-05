#ifndef BITMAP_IMAGE_H
#define BITMAP_IMAGE_H

#include <exception>
#include <cstdint>      // Für std::uint8_t
#include <stdexcept>    // Für std::exception
#include <vector>       // Für std::vector

#include "pixel.h"      // Annahme: Pixel-Klasse ist bereits definiert

class BitmapImage {
public:
    // Konstruktor
    BitmapImage(int height, int width);

    // Getter-Funktionen für Höhe und Breite
    int get_height() const;
    int get_width() const;

    // Abhängiger Typ für BitmapPixel
    using BitmapPixel = Pixel<std::uint8_t>;

    // Abhängiger Typ für Index
    using index_type = std::size_t;

    // Funktion zum Setzen eines Pixels
    void set_pixel(index_type x, index_type y, const BitmapPixel& value);

    // Funktion zum Abrufen eines Pixels
    BitmapPixel get_pixel(index_type x, index_type y) const;

    // Funktion zum Transponieren des Bildes
    BitmapImage transpose() const;

private:
    int height_;
    int width_;
    // Verwendung von Standardcontainer (std::vector) für Bitmap-Daten
    std::vector<std::vector<BitmapPixel>> bitmap_data_;
};

#endif // BITMAP_IMAGE_H

