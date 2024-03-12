#include "encryption/Key.h"

#include <cstring>

Key::key_type Key::get_standard_key() noexcept {
	auto key = key_type{};
	for (auto i = key_type::value_type(0); i < key.size(); i++) {
		key[i] = i;
	}

	return key;
}
