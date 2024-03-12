#include "test.h"

#include "image/pixel.h"

#include <cstdint>
#include <memory>
#include <type_traits>

class PixelTest : public LabTest {};

TEST_F(PixelTest, test_one_a_fabian_war_krank) {
	const auto pixel_small_stack = Pixel<std::uint8_t>{};
	const auto pixel_small_heap = std::make_unique<Pixel<std::uint8_t>>();

	const auto pixel_large_stack = Pixel<std::uint32_t>{};
	const auto pixel_large_heap = std::make_unique<Pixel<std::uint32_t>>();
}

TEST_F(PixelTest, test_one_b_fabian_war_krank) {
	const auto b_small = std::uint8_t{ 0 };
	const auto g_small = std::uint8_t{ 255 };
	const auto r_small = std::uint8_t{ 137 };

	std::unique_ptr<Pixel<std::uint8_t>> pixel_small_heap{};

	switch (Pixel<std::uint8_t>::channel_order) {
	case ChannelOrder::BGR:
		pixel_small_heap = std::make_unique<Pixel<std::uint8_t>>(b_small, g_small, r_small);
		break;
	case ChannelOrder::BRG:
		pixel_small_heap = std::make_unique<Pixel<std::uint8_t>>(b_small, r_small, g_small);
		break;
	case ChannelOrder::GBR:
		pixel_small_heap = std::make_unique<Pixel<std::uint8_t>>(g_small, b_small, r_small);
		break;
	case ChannelOrder::GRB:
		pixel_small_heap = std::make_unique<Pixel<std::uint8_t>>(g_small, r_small, b_small);
		break;
	case ChannelOrder::RBG:
		pixel_small_heap = std::make_unique<Pixel<std::uint8_t>>(r_small, b_small, g_small);
		break;
	case ChannelOrder::RGB:
		pixel_small_heap = std::make_unique<Pixel<std::uint8_t>>(r_small, g_small, b_small);
		break;
	default:
		ASSERT_TRUE(false) << "ChannelOrder for Pixel<std::uint8_t> has no valid value!\n";
	}

	const auto returned_small_b = pixel_small_heap->get_blue_channel();
	const auto returned_small_g = pixel_small_heap->get_green_channel();
	const auto returned_small_r = pixel_small_heap->get_red_channel();

	static_assert(std::is_same<decltype(returned_small_b), const std::uint8_t>::value);
	static_assert(std::is_same<decltype(returned_small_g), const std::uint8_t>::value);
	static_assert(std::is_same<decltype(returned_small_r), const std::uint8_t>::value);

	ASSERT_EQ(returned_small_b, b_small);
	ASSERT_EQ(returned_small_g, g_small);
	ASSERT_EQ(returned_small_r, r_small);

	const auto b_large = std::uint32_t{ 3000000000 };
	const auto g_large = std::uint32_t{ 1 };
	const auto r_large = std::uint32_t{ 1257142641 };

	std::unique_ptr<Pixel<std::uint32_t>> pixel_large_heap{};

	switch (Pixel<std::uint32_t>::channel_order) {
	case ChannelOrder::BGR:
		pixel_large_heap = std::make_unique<Pixel<std::uint32_t>>(b_large, g_large, r_large);
		break;
	case ChannelOrder::BRG:
		pixel_large_heap = std::make_unique<Pixel<std::uint32_t>>(b_large, r_large, g_large);
		break;
	case ChannelOrder::GBR:
		pixel_large_heap = std::make_unique<Pixel<std::uint32_t>>(g_large, b_large, r_large);
		break;
	case ChannelOrder::GRB:
		pixel_large_heap = std::make_unique<Pixel<std::uint32_t>>(g_large, r_large, b_large);
		break;
	case ChannelOrder::RBG:
		pixel_large_heap = std::make_unique<Pixel<std::uint32_t>>(r_large, b_large, g_large);
		break;
	case ChannelOrder::RGB:
		pixel_large_heap = std::make_unique<Pixel<std::uint32_t>>(r_large, g_large, b_large);
		break;
	default:
		ASSERT_TRUE(false) << "ChannelOrder for Pixel<std::uint32_t> has no valid value!\n";
	}

	const auto returned_large_b = pixel_large_heap->get_blue_channel();
	const auto returned_large_g = pixel_large_heap->get_green_channel();
	const auto returned_large_r = pixel_large_heap->get_red_channel();

	static_assert(std::is_same<decltype(returned_large_b), const std::uint32_t>::value);
	static_assert(std::is_same<decltype(returned_large_g), const std::uint32_t>::value);
	static_assert(std::is_same<decltype(returned_large_r), const std::uint32_t>::value);

	ASSERT_EQ(returned_large_b, b_large);
	ASSERT_EQ(returned_large_g, g_large);
	ASSERT_EQ(returned_large_r, r_large);
}

TEST_F(PixelTest, test_one_c_fabian_war_krank) {
	const auto pixel_small_1 = Pixel<std::uint8_t>{ 255, 255, 255 };
	const auto pixel_small_2 = Pixel<std::uint8_t>{ 255, 255, 0 };
	const auto pixel_small_3 = Pixel<std::uint8_t>{ 255, 0, 255 };
	const auto pixel_small_4 = Pixel<std::uint8_t>{ 0, 255, 255 };

	const auto pixel_small_1_copy = Pixel<std::uint8_t>{ 255, 255, 255 };

	ASSERT_TRUE(pixel_small_1 == pixel_small_1);
	ASSERT_TRUE(pixel_small_1_copy == pixel_small_1);
	ASSERT_TRUE(pixel_small_1 == pixel_small_1_copy);

	ASSERT_FALSE(pixel_small_1 == pixel_small_2);
	ASSERT_FALSE(pixel_small_1 == pixel_small_3);
	ASSERT_FALSE(pixel_small_1 == pixel_small_4);

	ASSERT_FALSE(pixel_small_2 == pixel_small_1);
	ASSERT_FALSE(pixel_small_3 == pixel_small_1);
	ASSERT_FALSE(pixel_small_4 == pixel_small_1);

	const auto pixel_large_1 = Pixel<std::uint32_t>{ 132, 24531658, 2365 };
	const auto pixel_large_2 = Pixel<std::uint32_t>{ 132, 24531658, 2364 };
	const auto pixel_large_3 = Pixel<std::uint32_t>{ 132, 245316580, 2365 };
	const auto pixel_large_4 = Pixel<std::uint32_t>{ 133, 24531658, 2365 };

	const auto pixel_large_1_copy = Pixel<std::uint32_t>{ 132, 24531658, 2365 };

	ASSERT_TRUE(pixel_large_1 == pixel_large_1);
	ASSERT_TRUE(pixel_large_1_copy == pixel_large_1);
	ASSERT_TRUE(pixel_large_1 == pixel_large_1_copy);

	ASSERT_FALSE(pixel_large_1 == pixel_large_2);
	ASSERT_FALSE(pixel_large_1 == pixel_large_3);
	ASSERT_FALSE(pixel_large_1 == pixel_large_4);

	ASSERT_FALSE(pixel_large_2 == pixel_large_1);
	ASSERT_FALSE(pixel_large_3 == pixel_large_1);
	ASSERT_FALSE(pixel_large_4 == pixel_large_1);
}
