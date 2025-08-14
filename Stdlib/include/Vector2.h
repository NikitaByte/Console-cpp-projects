#pragma once

#include <concepts>
#include <type_traits>
#include <limits>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <stdexcept>

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric T>
class Vector2 {
public:
	// Constructors
	constexpr Vector2() noexcept;
	constexpr Vector2(T x, T y) noexcept;
	constexpr Vector2(T value) noexcept;
	~Vector2() = default;

	// Copying and moving
	constexpr Vector2(const Vector2&) = default;
	constexpr Vector2(Vector2&&) = default;
	constexpr Vector2& operator=(const Vector2&) = default;
	constexpr Vector2& operator=(Vector2&&) = default;

	// Type conversion constructor (explicit)
	template<Numeric U>
	constexpr explicit Vector2(const Vector2<U>& other) noexcept
		: x_(static_cast<T>(other.getX())), y_(static_cast<T>(other.getY())) { }

	// Getters
	[[nodiscard]] constexpr T getX() const noexcept;
	[[nodiscard]] constexpr T getY() const noexcept;

	// Setters
	constexpr void setX(T x) noexcept;
	constexpr void setY(T y) noexcept;
	constexpr void set(T x, T y) const noexcept;

	// Arithmetic operators
	template<Numeric T>
	constexpr Vector2 operator+(const Vector2& other) const noexcept {
		return Vector2(x_ + other.getX(), y_ + other.getY());
	}
	
	template<Numeric T>
	constexpr Vector2 operator-(const Vector2& other) const noexcept {
		return Vector2(x_ - other.getX(), y_ - other.getY());
	}

	template<Numeric U>
	constexpr auto operator*(U scalar) const noexcept;

	template<Numeric U>
	constexpr auto operator/(U scalar) const noexcept;

	// Unary operators
	constexpr Vector2 operator-() const noexcept { return Vector2(-x, -y); }
	constexpr Vector2 operator+() const noexcept { return *this; }

	// Assignment operators
	constexpr Vector2& operator+=(const Vector2& other) noexcept {
		x += other.x;
		y += other.y;
		return *this;
	}

	constexpr Vector2& operator-=(const Vector2& other) noexcept {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	template <Numeric U>
	constexpr Vector2& operator*=(U scalar) noexcept {
		x = static_cast<T>(x * scalar);
		y = static_cast<T>(y * scalar);
		return *this;
	}

	template <Numeric U>
	constexpr Vector2& operator/=(U scalar) {
		if constexpr (std::floating_point<U>) {
			x = static_cast<T>(x / scalar);
			y = static_cast<T>(y / scalar);
		}
		else {
			if (scalar == 0) throw std::invalid_argument("Division by zero.");
			x = static_cast<T>(x / scalar);
			y = static_cast<T>(y / scalar);
		}
		return *this;
	}

	// Comparison operators
	constexpr bool operator==(const Vector2& other) const noexcept;

	constexpr auto operator<=>(const Vector2& other) const noexcept {
		if (auto cmp = x <=> other.x; cmp != 0) return cmp;
		return y <=> other.y;
	}
	
private:
	T x_, y_;
};

template<Numeric T>
inline constexpr Vector2<T>::Vector2() noexcept
	: x_(0), y_(0) {
}

template<Numeric T>
inline constexpr Vector2<T>::Vector2(T x, T y) noexcept
	: x_(x), y_(y) { }

template<Numeric T>
inline constexpr Vector2<T>::Vector2(T value) noexcept
	:x_(value), y_(value) { }

template<Numeric T>
inline constexpr T Vector2<T>::getX() const noexcept { return x_; }

template<Numeric T>
inline constexpr T Vector2<T>::getY() const noexcept { return y_; }

template<Numeric T>
inline constexpr void Vector2<T>::setX(T x) noexcept { x_ = x; }

template<Numeric T>
inline constexpr void Vector2<T>::setY(T y) noexcept { y_ = y; }

template<Numeric T>
inline constexpr void Vector2<T>::set(T x, T y) const noexcept { x_ = x; y_ = y; }

template<Numeric T>
inline constexpr bool Vector2<T>::operator==(const Vector2& other) const noexcept {
	if constexpr (std::floating_point<T>) {
		constexpr T epsilon = std::numeric_limits<T>::epsilon() * 100;
		return std::abs(x_ - other.x_) < epsilon &&
			std::abs(y_ - other.y_) < epsilon;
	}
	else {
		return x_ == other.x_ && y_ == other.y_;
	}
}

template<Numeric T>
template<Numeric U>
inline constexpr auto Vector2<T>::operator*(U scalar) const noexcept {
	using ResultType = std::common_type<T, U>;
	return Vector2<ResultType>(x_ * scalar, y_ * scalar);
}

template<Numeric T>
template<Numeric U>
inline constexpr auto Vector2<T>::operator/(U scalar) const noexcept {
	using ResultType = std::common_type_t<T, U>;
	if constexpr (std::floating_point<U>) {
		return Vector2<ResultType>(x_ / scalar, y_ / scalar);
	}
	else {
		if (scalar == 0) throw std::invalid_argument("Division by zero.");
		return Vector2<ResultType>(x_ / scalar, y_ / scalar);
	}
}

