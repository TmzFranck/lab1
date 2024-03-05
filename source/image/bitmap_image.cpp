#include "image/bitmap_image.h"

BitmapImage::BitmapImage(int height, int width) {
        if (height <= 0 || height > 8192 || width <= 0 || width > 8192) {
            throw std::exception();
        }

        BitmapImage::height_ = height;
        BitmapImage::width_ = width;
        // Initialisierung des Bitmaps mit Standard-Pixeln
        bitmap_data_.resize(height_, std::vector<BitmapPixel>(width_, BitmapPixel()));
    }

    // Getter-Funktionen für Höhe und Breite
    int BitmapImage::get_height() const { return BitmapImage::height_; }
    int BitmapImage::get_width() const { return BitmapImage::width_; }

    // Abhängiger Typ für BitmapPixel
    using BitmapPixel = Pixel<std::uint8_t>;

    // Abhängiger Typ für Index
    using index_type = std::size_t;

    // Funktion zum Setzen eines Pixels
    void BitmapImage::set_pixel(index_type x, index_type y, const BitmapPixel& value) {
        if (x >= width_ || y >= height_) {
            throw std::exception();
        }

        bitmap_data_[y][x] = value;
    }

    // Funktion zum Abrufen eines Pixels
    BitmapPixel BitmapImage::get_pixel(index_type x, index_type y) const {
        if (x >= width_ || y >= height_) {
            throw std::exception();
        }

        return bitmap_data_[y][x];
    }

    // Funktion zum Transponieren des Bildes
    BitmapImage BitmapImage::transpose() const {
        BitmapImage transposedImage(width_, height_);

        for (index_type i = 0; i < height_; ++i) {
            for (index_type j = 0; j < width_; ++j) {
                transposedImage.set_pixel(j, i, get_pixel(i, j));
            }
        }

        return transposedImage;
    }
