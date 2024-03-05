#ifndef PIXEL_H
#define PIXEL_H
#pragma once

// DO NOT CHANGE THIS ENUM
enum class ChannelOrder {
	BGR,
	BRG,
	GBR,
	GRB,
	RBG,
	RGB
};

template <typename T>
class Pixel {
public:
    // Standardkonstruktor
    Pixel() {}

    // Konstruktor mit expliziten Werten
    Pixel(const T& redValue, const T& greenValue, const T& blueValue)
        : red(redValue), green(greenValue), blue(blueValue) {}

    // Getter-Funktionen für die Farbkanäle
    T get_blue_channel() const {
        return blue;
    }
    T get_green_channel() const {
        return green;
    }
    T get_red_channel() const {
        return red;
    }

	// Gleichheitsoperator
    bool operator==(const Pixel<T>& other) const {
        return (blue == other.get_blue_channel()) && (green == other.get_green_channel()) && (red == other.get_red_channel());
    }

	static ChannelOrder channel_order;

private:
    // Farbkanäle
    T red;
    T green;
    T blue;
};

template <typename T>
ChannelOrder Pixel<T>::channel_order = ChannelOrder::RGB;

#endif // PIXEL_H

