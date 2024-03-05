#include "encryption/FES.h"

    using key_type = Key::key_type;
    using row_type = std::array<BitmapImage::BitmapPixel, 16>;
    using block_type = std::array<std::array<row_type, 3>, 3>;

 row_type FES::convert_key_to_row(const key_type& key) {
        row_type result;
        for (int i = 0; i < 16; ++i) {
            result[i] = {key[i * 3 + 2], key[i * 3 + 1], key[i * 3]};
        }
        return result;
    }

 block_type FES::convert_key_to_block(const key_type& key) {
        block_type result;
        result[0][0] = convert_key_to_row(key);

        // Setzen der restlichen Reihen im Block gleich der ersten Reihe
        for (int i = 1; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result[i][j] = result[0][j];
            }
        }

        return result;
    }


 row_type FES::combine_rows(const row_type& row1, const row_type& row2) {
        row_type result;

        for (int i = 0; i < 16; ++i) {
            result[i] = BitmapImage::BitmapPixel(
                row1[i].get_blue_channel() ^ row2[i].get_blue_channel(),
                row1[i].get_green_channel() ^ row2[i].get_green_channel(),
                row1[i].get_red_channel() ^ row2[i].get_red_channel()
            );
        }

        return result;
    }



block_type FES::encrypt_block(const block_type& current_block, const block_type& previous_block) {
        block_type encrypted;

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            row_type combined_row = combine_rows(current_block[y][x], previous_block[y][x]);

            for (int i = 0; i < 16; ++i) {
                encrypted[y][x][i] = combined_row[i];
            }
        }
    }

    return encrypted;
    }


BitmapImage FES::encrypt(const BitmapImage& image, const key_type& key) {
        BitmapImage encrypted_image(image.get_height(), image.get_width());

        for (int y = 0; y < image.get_height(); y += 3) {
            for (int x = 0; x < image.get_width(); x += 48) {
                block_type current_block;
                block_type previous_block;

                // Initialize the current block with pixels from the image
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < 16; ++k) {
                            int pixel_x = x + (j * 16) + (k % 16);
                            int pixel_y = y + i;
                            current_block[i][j][k] = image.get_pixel(pixel_x, pixel_y);
                        }
                    }
                }

                // Calculate the previous block based on the key
                previous_block = convert_key_to_block(key);

                // Encrypt the block
                block_type encrypted_block = encrypt_block(current_block, previous_block);

                // Store the encrypted block in the encrypted image
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < 16; ++k) {
                            int pixel_x = x + (j * 16) + (k % 16);
                            int pixel_y = y + i;
                            encrypted_image.set_pixel(pixel_x, pixel_y, encrypted_block[i][j][k]);
                        }
                    }
                }
            }
        }

        return encrypted_image;
    }
