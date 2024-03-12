#include "test.h"

#include "image/bitmap_image.h"

#include <exception>

class BitmapTest : public LabTest {};

TEST_F(BitmapTest, test_one_d_one_fabian_war_krank) {
	ASSERT_THROW(auto val = BitmapImage(0, 0), std::exception);
	ASSERT_THROW(auto val = BitmapImage(10, 0), std::exception);
	ASSERT_THROW(auto val = BitmapImage(0, 10), std::exception);

	ASSERT_THROW(auto val = BitmapImage(8193, 8193), std::exception);
	ASSERT_THROW(auto val = BitmapImage(10, 8193), std::exception);
	ASSERT_THROW(auto val = BitmapImage(8193, 10), std::exception);

	ASSERT_THROW(auto val = BitmapImage(10000, 10000), std::exception);
	ASSERT_THROW(auto val = BitmapImage(4096, 8193), std::exception);
	ASSERT_THROW(auto val = BitmapImage(8193, 4096), std::exception);
}

TEST_F(BitmapTest, test_one_d_two_fabian_war_krank) {
	ASSERT_NO_THROW(auto val = BitmapImage(1, 1));
	ASSERT_NO_THROW(auto val = BitmapImage(10, 10));
	ASSERT_NO_THROW(auto val = BitmapImage(1024, 768));
	ASSERT_NO_THROW(auto val = BitmapImage(4096, 3456));
	ASSERT_NO_THROW(auto val = BitmapImage(3456, 4096));
	ASSERT_NO_THROW(auto val = BitmapImage(8192, 8192));

	const auto picture_1 = BitmapImage(4096, 3456);
	ASSERT_EQ(picture_1.get_height(), 4096);
	ASSERT_EQ(picture_1.get_width(), 3456);

	const auto picture_2 = BitmapImage(3456, 4096);
	ASSERT_EQ(picture_2.get_height(), 3456);
	ASSERT_EQ(picture_2.get_width(), 4096);

	const auto picture_3 = BitmapImage(1, 1);
	ASSERT_EQ(picture_3.get_height(), 1);
	ASSERT_EQ(picture_3.get_width(), 1);

	using dependent_type = BitmapImage::BitmapPixel;
	using expected_type = Pixel<std::uint8_t>;

	static_assert(std::is_same<dependent_type, expected_type>::value);
}

TEST_F(BitmapTest, test_one_e_one_fabian_war_krank) {
	const auto picture_1_const = BitmapImage(1024, 1576);
	const auto picture_2_const = BitmapImage(8192, 8192);

	ASSERT_THROW(auto val = picture_1_const.get_pixel(1024, 1576), std::exception);
	ASSERT_THROW(auto val = picture_1_const.get_pixel(1576, 1024), std::exception);

	ASSERT_THROW(auto val = picture_1_const.get_pixel(1, 1576), std::exception);
	ASSERT_THROW(auto val = picture_1_const.get_pixel(1576, 1), std::exception);

	ASSERT_THROW(auto val = picture_1_const.get_pixel(8192, 8192), std::exception);
	ASSERT_THROW(auto val = picture_1_const.get_pixel(8192, 8192), std::exception);

	ASSERT_THROW(auto val = picture_2_const.get_pixel(1024, 8192), std::exception);
	ASSERT_THROW(auto val = picture_2_const.get_pixel(8192, 1024), std::exception);

	ASSERT_THROW(auto val = picture_2_const.get_pixel(1, 8192), std::exception);
	ASSERT_THROW(auto val = picture_2_const.get_pixel(8192, 1), std::exception);

	ASSERT_THROW(auto val = picture_2_const.get_pixel(8192, 8192), std::exception);
	ASSERT_THROW(auto val = picture_2_const.get_pixel(8192, 8192), std::exception);

	auto picture_1 = BitmapImage(1024, 1576);
	auto picture_2 = BitmapImage(8192, 8192);

	ASSERT_THROW(auto val = picture_1.get_pixel(1024, 1576), std::exception);
	ASSERT_THROW(auto val = picture_1.get_pixel(1576, 1024), std::exception);

	ASSERT_THROW(auto val = picture_1.get_pixel(1, 1576), std::exception);
	ASSERT_THROW(auto val = picture_1.get_pixel(1576, 1), std::exception);

	ASSERT_THROW(auto val = picture_1.get_pixel(8192, 8192), std::exception);
	ASSERT_THROW(auto val = picture_1.get_pixel(8192, 8192), std::exception);

	ASSERT_THROW(auto val = picture_2.get_pixel(1024, 8192), std::exception);
	ASSERT_THROW(auto val = picture_2.get_pixel(8192, 1024), std::exception);

	ASSERT_THROW(auto val = picture_2.get_pixel(1, 8192), std::exception);
	ASSERT_THROW(auto val = picture_2.get_pixel(8192, 1), std::exception);

	ASSERT_THROW(auto val = picture_2.get_pixel(8192, 8192), std::exception);
	ASSERT_THROW(auto val = picture_2.get_pixel(8192, 8192), std::exception);

	const auto pixel = Pixel<std::uint8_t>{ 126, 145, 199 };

	ASSERT_THROW(picture_1.set_pixel(1024, 1576, pixel), std::exception);
	ASSERT_THROW(picture_1.set_pixel(1576, 1024, pixel), std::exception);

	ASSERT_THROW(picture_1.set_pixel(1, 1576, pixel), std::exception);
	ASSERT_THROW(picture_1.set_pixel(1576, 1, pixel), std::exception);

	ASSERT_THROW(picture_1.set_pixel(8192, 8192, pixel), std::exception);
	ASSERT_THROW(picture_1.set_pixel(8192, 8192, pixel), std::exception);

	ASSERT_THROW(picture_2.set_pixel(1024, 8192, pixel), std::exception);
	ASSERT_THROW(picture_2.set_pixel(8192, 1024, pixel), std::exception);

	ASSERT_THROW(picture_2.set_pixel(1, 8192, pixel), std::exception);
	ASSERT_THROW(picture_2.set_pixel(8192, 1, pixel), std::exception);

	ASSERT_THROW(picture_2.set_pixel(8192, 8192, pixel), std::exception);
	ASSERT_THROW(picture_2.set_pixel(8192, 8192, pixel), std::exception);
}

TEST_F(BitmapTest, test_one_e_two_fabian_war_krank) {
	auto image = BitmapImage(3, 3);

	ASSERT_EQ(image.get_height(), 3);
	ASSERT_EQ(image.get_width(), 3);

	using pixel_type = BitmapImage::BitmapPixel;

	image.set_pixel(0, 0, pixel_type(0, 0, 12));
	image.set_pixel(0, 1, pixel_type(0, 1, 12));
	image.set_pixel(0, 2, pixel_type(0, 2, 12));

	image.set_pixel(1, 0, pixel_type(1, 0, 255));
	image.set_pixel(1, 1, pixel_type(1, 1, 255));
	image.set_pixel(1, 2, pixel_type(1, 2, 255));

	image.set_pixel(2, 0, pixel_type(2, 0, 137));
	image.set_pixel(2, 1, pixel_type(2, 1, 137));
	image.set_pixel(2, 2, pixel_type(2, 2, 137));

	ASSERT_EQ(image.get_height(), 3);
	ASSERT_EQ(image.get_width(), 3);

	ASSERT_EQ(image.get_pixel(0, 0), pixel_type(0, 0, 12));
	ASSERT_EQ(image.get_pixel(0, 1), pixel_type(0, 1, 12));
	ASSERT_EQ(image.get_pixel(0, 2), pixel_type(0, 2, 12));

	ASSERT_EQ(image.get_pixel(1, 0), pixel_type(1, 0, 255));
	ASSERT_EQ(image.get_pixel(1, 1), pixel_type(1, 1, 255));
	ASSERT_EQ(image.get_pixel(1, 2), pixel_type(1, 2, 255));

	ASSERT_EQ(image.get_pixel(2, 0), pixel_type(2, 0, 137));
	ASSERT_EQ(image.get_pixel(2, 1), pixel_type(2, 1, 137));
	ASSERT_EQ(image.get_pixel(2, 2), pixel_type(2, 2, 137));

	ASSERT_THROW(auto val = image.get_pixel(0, 4), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(0, 10), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(0, 12), std::exception);

	ASSERT_THROW(auto val = image.get_pixel(1, 4), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(1, 10), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(1, 12), std::exception);

	ASSERT_THROW(auto val = image.get_pixel(2, 4), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(2, 10), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(2, 12), std::exception);

	ASSERT_THROW(auto val = image.get_pixel(3, 0), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(3, 1), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(3, 2), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(3, 3), std::exception);

	ASSERT_THROW(auto val = image.get_pixel(8, 0), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(8, 1), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(8, 2), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(8, 3), std::exception);

	ASSERT_THROW(auto val = image.get_pixel(1023, 0), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(1023, 1), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(1023, 2), std::exception);
	ASSERT_THROW(auto val = image.get_pixel(1023, 3), std::exception);

	ASSERT_EQ(image.get_pixel(0, 0), pixel_type(0, 0, 12));
	ASSERT_EQ(image.get_pixel(0, 1), pixel_type(0, 1, 12));
	ASSERT_EQ(image.get_pixel(0, 2), pixel_type(0, 2, 12));

	ASSERT_EQ(image.get_pixel(1, 0), pixel_type(1, 0, 255));
	ASSERT_EQ(image.get_pixel(1, 1), pixel_type(1, 1, 255));
	ASSERT_EQ(image.get_pixel(1, 2), pixel_type(1, 2, 255));

	ASSERT_EQ(image.get_pixel(2, 0), pixel_type(2, 0, 137));
	ASSERT_EQ(image.get_pixel(2, 1), pixel_type(2, 1, 137));
	ASSERT_EQ(image.get_pixel(2, 2), pixel_type(2, 2, 137));

	ASSERT_EQ(image.get_height(), 3);
	ASSERT_EQ(image.get_width(), 3);
}

TEST_F(BitmapTest, test_one_f_fabian_war_krank) {
	auto picture_rectangle = BitmapImage{ 1024, 576 };

	for (auto y = BitmapImage::index_type{ 0 }; y < BitmapImage::index_type{ 576 }; y++) {
		for (auto x = BitmapImage::index_type{ 0 }; x < BitmapImage::index_type{ 576 }; x++) {
			const auto first_channel = static_cast<std::uint8_t>(y % 256);
			const auto second_channel = static_cast<std::uint8_t>((x + 3) % 256);
			const auto third_channel = static_cast<std::uint8_t>((x * y + x) % (y + 1));

			picture_rectangle.set_pixel(y, x, Pixel<std::uint8_t>{first_channel, second_channel, third_channel});
		}
	}

	const auto picture_transposed = static_cast<const BitmapImage&>(picture_rectangle).transpose();

	for (auto y = BitmapImage::index_type{ 0 }; y < BitmapImage::index_type{ 576 }; y++) {
		for (auto x = BitmapImage::index_type{ 0 }; x < BitmapImage::index_type{ 576 }; x++) {
			const auto& pixel_original = picture_rectangle.get_pixel(y, x);
			const auto& pixel_transposed = picture_transposed.get_pixel(x, y);

			ASSERT_EQ(pixel_original.get_blue_channel(), pixel_transposed.get_blue_channel());
			ASSERT_EQ(pixel_original.get_green_channel(), pixel_transposed.get_green_channel());
			ASSERT_EQ(pixel_original.get_red_channel(), pixel_transposed.get_red_channel());
		}
	}

	if (picture_rectangle.get_height() == 1024) {
		ASSERT_EQ(picture_rectangle.get_width(), 576);
		ASSERT_EQ(picture_transposed.get_height(), 576);
		ASSERT_EQ(picture_transposed.get_width(), 1024);
	}
	else if (picture_rectangle.get_height() == 576) {
		ASSERT_EQ(picture_rectangle.get_width(), 1024);
		ASSERT_EQ(picture_transposed.get_height(), 1024);
		ASSERT_EQ(picture_transposed.get_width(), 576);
	}
	else {
		ASSERT_TRUE(false);
	}
}

