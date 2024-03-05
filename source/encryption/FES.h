#ifndef FES_H
#define FES_H
#pragma once

#include "encryption/Key.h"

#include "image/bitmap_image.h" // Stellen Sie sicher, dass der korrekte Header eingebunden ist

class FES {
public:
    using key_type = Key::key_type;
    using row_type = std::array<BitmapImage::BitmapPixel, 16>;
    using block_type = std::array<std::array<row_type, 3>, 3>;

    static row_type convert_key_to_row(const key_type& key);

    static block_type convert_key_to_block(const key_type& key);

    static row_type combine_rows(const row_type& row1, const row_type& row2);

    static block_type encrypt_block(const block_type& current_block, const block_type& previous_block);

    static BitmapImage encrypt(const BitmapImage& image, const key_type& key);


};

#endif // FES_H
