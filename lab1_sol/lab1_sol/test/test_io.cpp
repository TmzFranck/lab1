#include "test.h"

#include "image/bitmap_image.h"
#include "io/image_parser.h"

#include <cstdint>
#include <exception>
#include <filesystem>

class IOTest : public LabTest {};

BitmapImage::BitmapPixel construct_pixel(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue) {
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

TEST_F(IOTest, test_two_a_one_fabian_war_krank) {
	const auto path = get_path();

	ASSERT_THROW(auto val = ImageParser::read_bitmap(path), std::exception);
	ASSERT_THROW(auto val = ImageParser::read_bitmap(path / "fabian_inputkeahw3z4dn8o3qtzdn9wz/"), std::exception);
	ASSERT_THROW(auto val = ImageParser::read_bitmap(path / "input/fabian_pic_sma6o239nhtdjq8odnztfqnll.txt"), std::exception);
	ASSERT_THROW(auto val = ImageParser::read_bitmap(path / "input/fabian_pic_small.pnq9nzrcq9zmg"), std::exception);
	ASSERT_THROW(auto val = ImageParser::read_bitmap(path / "input/fabian_please_dont_exist.owa3z58923q4724u.bmp"), std::exception);

	auto read_image = ImageParser::read_bitmap(path / "input/pic_small.bmp");

	ASSERT_EQ(read_image.get_height(), 768);
	ASSERT_EQ(read_image.get_width(), 1024);

	// Who knows in what order they store their pixel
	try {
		const auto pixel_0_0 = read_image.get_pixel(0, 0);
		const auto pixel_767_0 = read_image.get_pixel(767, 0);
		const auto pixel_0_1023 = read_image.get_pixel(0, 1023);
		const auto pixel_767_1023 = read_image.get_pixel(767, 1023);

		ASSERT_EQ(pixel_0_0, construct_pixel(77, 80, 67));
		ASSERT_EQ(pixel_767_0, construct_pixel(64, 82, 117));
		ASSERT_EQ(pixel_0_1023, construct_pixel(133, 131, 97));
		ASSERT_EQ(pixel_767_1023, construct_pixel(84, 100, 135));
	}
	catch (std::exception ex) {
		const auto pixel_0_0 = read_image.get_pixel(0, 0);
		const auto pixel_0_767 = read_image.get_pixel(0, 767);
		const auto pixel_1023_0 = read_image.get_pixel(1023, 0);
		const auto pixel_1023_767 = read_image.get_pixel(1023, 767);

		ASSERT_EQ(pixel_0_0, construct_pixel(77, 80, 67));
		ASSERT_EQ(pixel_0_767, construct_pixel(64, 82, 117));
		ASSERT_EQ(pixel_1023_0, construct_pixel(133, 131, 97));
		ASSERT_EQ(pixel_1023_767, construct_pixel(84, 100, 135));
	}
}

TEST_F(IOTest, test_two_a_two_fabian_war_krank) {
	const auto path = get_path();

	ASSERT_THROW(auto val = ImageParser::read_bitmap(path), std::exception);
	ASSERT_THROW(auto val = ImageParser::read_bitmap(path / "fabian_inputkeahw3z4dn8o3qtzdn9wz/"), std::exception);
	ASSERT_THROW(auto val = ImageParser::read_bitmap(path / "fabian_input/pic_sma6o239nhtdjq8odnztfqnll.txt"), std::exception);
	ASSERT_THROW(auto val = ImageParser::read_bitmap(path / "fabian_input/pic_small.pnq9nzrcq9zmg"), std::exception);
	ASSERT_THROW(auto val = ImageParser::read_bitmap(path / "fabian_input/please_dont_exist.owa3z58923q4724u.bmp"), std::exception);

	auto read_image = ImageParser::read_bitmap(path / "input/pic_01.bmp");

	ASSERT_EQ(read_image.get_height(), 3456);
	ASSERT_EQ(read_image.get_width(), 4608);

	// Who knows in what order they store their pixel
	try {
		const auto pixel_0_0 = read_image.get_pixel(0, 0);
		const auto pixel_3455_0 = read_image.get_pixel(3455, 0);
		const auto pixel_0_4607 = read_image.get_pixel(0, 4607);
		const auto pixel_3455_4607 = read_image.get_pixel(3455, 4607);

		ASSERT_EQ(pixel_0_0, construct_pixel(67, 97, 147));
		ASSERT_EQ(pixel_3455_0, construct_pixel(83, 119, 135));
		ASSERT_EQ(pixel_0_4607, construct_pixel(69, 87, 151));
		ASSERT_EQ(pixel_3455_4607, construct_pixel(79, 103, 129));
	}
	catch (std::exception ex) {
		const auto pixel_0_0 = read_image.get_pixel(0, 0);
		const auto pixel_0_3455 = read_image.get_pixel(0, 3455);
		const auto pixel_4607_0 = read_image.get_pixel(4607, 0);
		const auto pixel_4607_3455 = read_image.get_pixel(4607, 3455);

		ASSERT_EQ(pixel_0_0, construct_pixel(67, 97, 147));
		ASSERT_EQ(pixel_0_3455, construct_pixel(83, 119, 135));
		ASSERT_EQ(pixel_4607_0, construct_pixel(69, 87, 151));
		ASSERT_EQ(pixel_4607_3455, construct_pixel(79, 103, 129));
	}
}

TEST_F(IOTest, test_two_b_one_fabian_war_krank) {
	const auto path = get_path();

	auto read_image = ImageParser::read_bitmap(path / "input/pic_small.bmp");
	ASSERT_NO_THROW(ImageParser::write_bitmap(path / "output/pic_small.fabian.bmp", read_image););
}

TEST_F(IOTest, test_two_b_two_fabian_war_krank) {
	const auto path = get_path();

	auto read_image = ImageParser::read_bitmap(path / "input/pic_small.bmp");
	ImageParser::write_bitmap(path / "output/pic_small.fabian.bmp", read_image);

	auto read_image_2 = ImageParser::read_bitmap(path / "output/pic_small.fabian.bmp");

	ASSERT_EQ(read_image_2.get_height(), 768);
	ASSERT_EQ(read_image_2.get_width(), 1024);

	// Who knows in what order they store their pixel
	try {
		for (auto y = BitmapImage::index_type{ 0 }; y < BitmapImage::index_type{ 768 }; y++) {
			for (auto x = BitmapImage::index_type{ 0 }; x < BitmapImage::index_type{ 1024 }; x++) {
				ASSERT_EQ(read_image.get_pixel(y, x), read_image_2.get_pixel(y, x));
			}
		}
	}
	catch (std::exception ex) {
		for (auto y = BitmapImage::index_type{ 0 }; y < BitmapImage::index_type{ 768 }; y++) {
			for (auto x = BitmapImage::index_type{ 0 }; x < BitmapImage::index_type{ 1024 }; x++) {
				ASSERT_EQ(read_image.get_pixel(x, y), read_image_2.get_pixel(x, y));
			}
		}
	}
}
