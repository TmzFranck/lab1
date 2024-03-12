#include "test.h"

#include "encryption/FES.h"
#include "image/pixel.h"
#include "io/image_parser.h"

#include <fstream>
#include <sstream>
#include <type_traits>

BitmapImage::BitmapPixel construct_pixel_encryption_fabian(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue) {
	switch (BitmapImage::BitmapPixel::channel_order) {
	case ChannelOrder::BGR:
		return { blue, green, red };
	case ChannelOrder::BRG:
		return { blue, red, green };
	case ChannelOrder::GBR:
		return { green, blue, red };
	case ChannelOrder::GRB:
		return { green, red, blue };
	case ChannelOrder::RBG:
		return { red, blue, green };
	case ChannelOrder::RGB:
		return { red, green, blue };
	default:
		EXPECT_TRUE(false) << "ChannelOrder for BitmapImage::BitmapPixel has no valid value!\n";
	}

	return {};
}

FES::row_type get_zero_row_fabian() {
	auto zero_row = FES::row_type{};
	for (auto i = 0; i < 16; i++) {
		zero_row[i] = construct_pixel_encryption_fabian(0, 0, 0);
	}
	return zero_row;
}

FES::row_type get_full_row_fabian() {
	auto zero_row = FES::row_type{};
	for (auto i = 0; i < 16; i++) {
		zero_row[i] = construct_pixel_encryption_fabian(255, 255, 255);
	}
	return zero_row;
}

FES::block_type get_zero_block_fabian() {
	auto zero_block = FES::block_type{};

	for (auto& half_block : zero_block) {
		for (auto& row : half_block) {
			row = get_zero_row_fabian();
		}
	}

	return zero_block;
}

FES::block_type get_full_block_fabian() {
	auto full_block = FES::block_type{};

	for (auto& half_block : full_block) {
		for (auto& row : half_block) {
			row = get_full_row_fabian();
		}
	}

	return full_block;
}

template<typename _ChannelTy>
[[nodiscard]] Pixel<_ChannelTy> combine_pixel_test_fabian(const Pixel<_ChannelTy>& lhs, const Pixel<_ChannelTy>& rhs) noexcept {
	const _ChannelTy new_red = lhs.get_red_channel() ^ rhs.get_red_channel();
	const _ChannelTy new_green = lhs.get_green_channel() ^ rhs.get_green_channel();
	const _ChannelTy new_blue = lhs.get_blue_channel() ^ rhs.get_blue_channel();

	switch (Pixel<_ChannelTy>::channel_order) {
	case ChannelOrder::BGR:
		return Pixel<_ChannelTy>{ new_blue, new_green, new_red };
	case ChannelOrder::BRG:
		return Pixel<_ChannelTy>{ new_blue, new_red, new_green };
	case ChannelOrder::GBR:
		return Pixel<_ChannelTy>{ new_green, new_blue, new_red };
	case ChannelOrder::GRB:
		return Pixel<_ChannelTy>{ new_green, new_red, new_blue };
	case ChannelOrder::RBG:
		return Pixel<_ChannelTy>{ new_red, new_blue, new_green };
	case ChannelOrder::RGB:
		return Pixel<_ChannelTy>{ new_red, new_green, new_blue };
	}

	EXPECT_TRUE(false) << "ChannelOrder for Pixel<std::uint32_t> has no valid value!\n";
	return {};
}

class EncryptionTest : public LabTest {};

TEST_F(EncryptionTest, test_three_a_fabian_war_krank) {
	using expected_key_type = Key::key_type;
	using implemented_key_type = FES::key_type;

	using expected_row_type = std::array<BitmapImage::BitmapPixel, 16>;
	using implemented_row_type = FES::row_type;

	using expected_block_type = std::array<std::array<expected_row_type, 3>, 3>;
	using implemented_block_type = FES::block_type;

	static_assert(std::is_same<expected_key_type, implemented_key_type>::value);
	static_assert(std::is_same<expected_row_type, implemented_row_type>::value);
	static_assert(std::is_same<expected_block_type, implemented_block_type>::value);
}

TEST_F(EncryptionTest, test_three_b_fabian_war_krank) {
	auto key = FES::key_type{};

	for (auto i = 0; i < 48; i++) {
		key[i] = i;
	}

	const auto row = FES::convert_key_to_row(key);

	for (auto i = 0; i < 48; i += 3) {
		const auto index = i / 3;

		const auto pixel_1 = row[index];
		const auto pixel_2 = construct_pixel_encryption_fabian(i, i + 1, i + 2);

		ASSERT_EQ(pixel_1, pixel_2);
	}

	const auto block = FES::convert_key_to_block(key);

	ASSERT_EQ(block[0][0], row);
	ASSERT_EQ(block[0][1], row);
	ASSERT_EQ(block[0][2], row);
	ASSERT_EQ(block[1][0], row);
	ASSERT_EQ(block[1][1], row);
	ASSERT_EQ(block[1][2], row);
	ASSERT_EQ(block[2][0], row);
	ASSERT_EQ(block[2][1], row);
	ASSERT_EQ(block[2][2], row);
}

TEST_F(EncryptionTest, test_three_c_fabian_war_krank) {
	auto row_1 = FES::row_type{};
	auto row_2 = FES::row_type{};

	const auto zero_row = get_zero_row_fabian();

	for (auto i = 0; i < 16; i++) {
		row_1[i] = construct_pixel_encryption_fabian(i, i + 1, i + 2);
		row_2[i] = construct_pixel_encryption_fabian(i + 100, i + 101, i + 102);
	}

	ASSERT_EQ(zero_row, FES::combine_rows(zero_row, zero_row));
	ASSERT_EQ(zero_row, FES::combine_rows(row_1, row_1));
	ASSERT_EQ(zero_row, FES::combine_rows(row_2, row_2));

	ASSERT_EQ(row_1, FES::combine_rows(row_1, zero_row));
	ASSERT_EQ(row_1, FES::combine_rows(zero_row, row_1));
	ASSERT_EQ(row_2, FES::combine_rows(row_2, zero_row));
	ASSERT_EQ(row_2, FES::combine_rows(zero_row, row_2));

	auto combined_row_1 = FES::combine_rows(row_1, row_2);
	auto combined_row_2 = FES::combine_rows(row_2, row_1);

	ASSERT_EQ(combined_row_1, combined_row_2);

	for (auto i = 0; i < 16; i++) {
		const auto expected_pixel = combine_pixel_test_fabian(construct_pixel_encryption_fabian(i, i + 1, i + 2), construct_pixel_encryption_fabian(i + 100, i + 101, i + 102));
		const auto found_pixel = combined_row_1[i];
		ASSERT_EQ(expected_pixel, found_pixel);
	}
}

TEST_F(EncryptionTest, test_three_d_one_fabian_war_krank) {
	auto zero_block_1 = get_zero_block_fabian();
	auto zero_block_2 = get_zero_block_fabian();

	auto full_block_1 = get_full_block_fabian();
	auto full_block_2 = get_full_block_fabian();

	const auto encrypted_zero_zero = FES::encrypt_block(zero_block_1, zero_block_2);
	ASSERT_EQ(encrypted_zero_zero, zero_block_1);

	const auto encrypted_zero_full = FES::encrypt_block(zero_block_1, full_block_1);
	ASSERT_EQ(encrypted_zero_full[0][0], full_block_1[0][0]);
	ASSERT_EQ(encrypted_zero_full[0][1], zero_block_1[0][0]);
	ASSERT_EQ(encrypted_zero_full[0][2], zero_block_1[0][0]);

	ASSERT_EQ(encrypted_zero_full[1][0], zero_block_1[0][0]);
	ASSERT_EQ(encrypted_zero_full[1][1], zero_block_1[0][0]);
	ASSERT_EQ(encrypted_zero_full[1][2], zero_block_1[0][0]);

	ASSERT_EQ(encrypted_zero_full[2][0], zero_block_1[0][0]);
	ASSERT_EQ(encrypted_zero_full[2][1], zero_block_1[0][0]);
	ASSERT_EQ(encrypted_zero_full[2][2], zero_block_1[0][0]);

	const auto encrypted_full_zero = FES::encrypt_block(full_block_1, zero_block_1);
	ASSERT_EQ(encrypted_full_zero[0][0], full_block_1[0][0]);
	ASSERT_EQ(encrypted_full_zero[0][1], zero_block_1[0][0]);
	ASSERT_EQ(encrypted_full_zero[0][2], zero_block_1[0][0]);

	ASSERT_EQ(encrypted_full_zero[1][0], zero_block_1[0][0]);
	ASSERT_EQ(encrypted_full_zero[1][1], zero_block_1[0][0]);
	ASSERT_EQ(encrypted_full_zero[1][2], zero_block_1[0][0]);

	ASSERT_EQ(encrypted_full_zero[2][0], zero_block_1[0][0]);
	ASSERT_EQ(encrypted_full_zero[2][1], zero_block_1[0][0]);
	ASSERT_EQ(encrypted_full_zero[2][2], zero_block_1[0][0]);

	const auto encrypted_full_full = FES::encrypt_block(full_block_1, full_block_2);
	ASSERT_EQ(encrypted_full_full, zero_block_1);
}

TEST_F(EncryptionTest, test_three_d_two_fabian_war_krank) {
	auto key = FES::key_type{};
	for (auto i = FES::key_type::value_type(0); i < key.size(); i++) {
		key[i] = i;
	}

	auto block = FES::convert_key_to_block(key);
	auto encrypted = FES::encrypt_block(block, block);

	auto zero_block = FES::block_type{};

	ASSERT_EQ(encrypted, zero_block);
}

TEST_F(EncryptionTest, test_three_d_three_fabian_war_krank) {
	auto key_1 = FES::key_type{};
	auto key_2 = FES::key_type{};
	for (auto i = FES::key_type::value_type(0); i < key_1.size(); i++) {
		key_1[i] = i;
		key_2[i] = i * i + 100;
	}

	auto block_1 = FES::convert_key_to_block(key_1);
	auto block_2 = FES::convert_key_to_block(key_2);

	auto encrypted = FES::encrypt_block(block_1, block_2);

	auto zero_row = get_zero_row_fabian();
	auto significant_row = FES::row_type{
		construct_pixel_encryption_fabian(100,100,106),
		construct_pixel_encryption_fabian(110,112,120),
		construct_pixel_encryption_fabian(142,146,172),
		construct_pixel_encryption_fabian(188,194,214),
		construct_pixel_encryption_fabian(248,0,38),
		construct_pixel_encryption_fabian(74,116,148),
		construct_pixel_encryption_fabian(186,222,224),
		construct_pixel_encryption_fabian(8,94,98),
		construct_pixel_encryption_fabian(188,204,18),
		construct_pixel_encryption_fabian(38,104,176),
		construct_pixel_encryption_fabian(246,58,68),
		construct_pixel_encryption_fabian(132,202,14),
		construct_pixel_encryption_fabian(80,152,46),
		construct_pixel_encryption_fabian(114,140,220),
		construct_pixel_encryption_fabian(98,182,216),
		construct_pixel_encryption_fabian(96,134,42) };

	ASSERT_EQ(encrypted[0][0], significant_row);
	ASSERT_EQ(encrypted[0][1], zero_row);
	ASSERT_EQ(encrypted[0][2], zero_row);

	ASSERT_EQ(encrypted[1][0], zero_row);
	ASSERT_EQ(encrypted[1][1], zero_row);
	ASSERT_EQ(encrypted[1][2], zero_row);

	ASSERT_EQ(encrypted[2][0], zero_row);
	ASSERT_EQ(encrypted[2][1], zero_row);
	ASSERT_EQ(encrypted[2][2], zero_row);
}

TEST_F(EncryptionTest, test_three_e_one_fabian_war_krank) {
	const auto path = get_path();

	auto read_image = ImageParser::read_bitmap(path / "input/pic_small.bmp");
	auto encrypted_image = ImageParser::read_bitmap(path / "output/fabian_encrypted_pic_small.bmp");

	auto key = FES::key_type{};
	for (auto i = FES::key_type::value_type(0); i < key.size(); i++) {
		key[i] = i;
	}

	auto encrypted = FES::encrypt(read_image, key);

	// Who knows in what order they store their pixel
	try {
		for (auto y = 0; y < read_image.get_height(); y++) {
			for (auto x = 0; x < read_image.get_width(); x++) {
				ASSERT_EQ(encrypted.get_pixel(y, x), encrypted_image.get_pixel(y, x)) << '\t' << y << '\t' << x;
			}
		}
	}
	catch (std::exception ex) {
		for (auto y = 0; y < read_image.get_height(); y++) {
			for (auto x = 0; x < read_image.get_width(); x++) {
				ASSERT_EQ(encrypted.get_pixel(x, y), encrypted_image.get_pixel(x, y)) << '\t' << y << '\t' << x;
			}
		}
	}
}

TEST_F(EncryptionTest, test_three_e_two_fabian_war_krank) {
	const auto path = get_path();

	auto read_image = ImageParser::read_bitmap(path / "input/pic_01.bmp");
	auto encrypted_image = ImageParser::read_bitmap(path / "output/fabian_encrypted_pic_01.bmp");

	auto key = FES::key_type{};
	for (auto i = FES::key_type::value_type(0); i < key.size(); i++) {
		key[i] = i;
	}

	auto encrypted = FES::encrypt(read_image, key);

	// Who knows in what order they store their pixel
	try {
		for (auto y = 0; y < read_image.get_height(); y++) {
			for (auto x = 0; x < read_image.get_width(); x++) {
				ASSERT_EQ(encrypted.get_pixel(y, x), encrypted_image.get_pixel(y, x)) << '\t' << y << '\t' << x;
			}
		}
	}
	catch (std::exception ex) {
		for (auto y = 0; y < read_image.get_height(); y++) {
			for (auto x = 0; x < read_image.get_width(); x++) {
				ASSERT_EQ(encrypted.get_pixel(x, y), encrypted_image.get_pixel(x, y)) << '\t' << y << '\t' << x;
			}
		}
	}
}
