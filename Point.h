//
// Created by jwscoggins on 10/16/20.
//

#ifndef REALMZ_TOOLS_POINT_H
#define REALMZ_TOOLS_POINT_H
#include <cstdint>
#include <type_traits>
#include <tuple>
namespace realmz {
    template<typename T, std::enable_if_t<std::is_integral_v<std::decay_t<T>>, int> = 0>
    class Point {
    public:
        static constexpr T zero = static_cast<T>(0);
    public:
        constexpr Point() = default;
        constexpr explicit Point(T xC, T yC) : x(xC), y(yC) { }
        constexpr explicit Point(const std::tuple<T, T>& pair) : Point(std::get<0>(pair), std::get<1>(pair)) { }
        [[nodiscard]] constexpr auto getX() const noexcept { return x; }
        [[nodiscard]] constexpr auto getY() const noexcept { return y; }
        void clear(T value = zero) noexcept {
            x = value;
            y = value;
        }
        void setX(T v) noexcept { x = v; }
        void setY(T v) noexcept { y = v; }
    private:
        T x = zero;
        T y = zero;
    };
    using Signed8Point = Point<int8_t>;
    using Unsigned8Point = Point<uint8_t>;
    using Signed16Point = Point<int16_t>;
    using Unsigned16Point = Point<uint16_t>;
    using Signed32Point = Point<int32_t>;
    using Unsigned32Point = Point<uint32_t>;
}

#endif //REALMZ_TOOLS_POINT_H
