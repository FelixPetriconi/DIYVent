#include <modm/io/iostream.hpp>
#include <type_traits>
#include <cstdint>

namespace modm
{
	template <typename T>
	std::enable_if_t<std::is_floating_point_v<T>, IOStream&> 
	operator<<(IOStream& stream,  T value) {
		if (value < 0) {
			stream << "-";
			value = -value;
		}
		if (value >= T(1)) {
			auto intPart = static_cast<std::int32_t>(value);
			stream << intPart;
			value -= static_cast<T>(intPart);
		}
		for (auto i = 0; i < 3; ++i) {
			value *= T(10);
			auto intPart = static_cast<std::int8_t>(value);
			stream << intPart;
			value -= static_cast<T>(intPart);
		}
		return stream;
	}
}