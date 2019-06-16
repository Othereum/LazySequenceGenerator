#pragma once
#include <iterator>

namespace SeqIt
{
	template <class T = int, T CD = 1>
	class Arithmetic
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using reference = const T &;
		using pointer = const T *;

		constexpr Arithmetic(T Init = T{}) :Num{ std::move(Init) } {}

		[[nodiscard]] constexpr T operator*() const & { return Num; }
		[[nodiscard]] constexpr T operator*() && { return std::move(Num); }
		[[nodiscard]] constexpr const T* operator->() const { return &Num; }

		constexpr Arithmetic& operator++() & { Num += CD; return *this; }
		constexpr Arithmetic operator++(int) & { Arithmetic I = *this; ++(*this); return I; }
		constexpr Arithmetic& operator--() & { Num -= CD; return *this; }
		constexpr Arithmetic operator--(int) & { Arithmetic I = *this; --(*this); return I; }
		constexpr Arithmetic& operator+=(difference_type N) & { Num += CD * N; return *this; }
		[[nodiscard]] constexpr Arithmetic operator+(difference_type N) const { Arithmetic I = *this; return I += N; }
		constexpr Arithmetic& operator-=(difference_type N) & { return *this += -N; }
		[[nodiscard]] constexpr Arithmetic operator-(difference_type N) const { return *this + -N; }
		[[nodiscard]] constexpr difference_type operator-(const Arithmetic& I) const { return (Num - I.Num) * CD; }
		[[nodiscard]] constexpr T operator[](difference_type N) const { return *(*this + N); }

		[[nodiscard]] constexpr bool operator==(const Arithmetic& R) const { return Num == R.Num; }
		[[nodiscard]] constexpr bool operator!=(const Arithmetic& R) const { return !(*this == R); }
		[[nodiscard]] constexpr bool operator<(const Arithmetic& R) const { return R - *this > 0; }
		[[nodiscard]] constexpr bool operator>(const Arithmetic& R) const { return R < *this; }
		[[nodiscard]] constexpr bool operator>=(const Arithmetic& R) const { return !(*this < R); }
		[[nodiscard]] constexpr bool operator<=(const Arithmetic& R) const { return !(*this > R); }

	private:
		T Num;
	};

	template <class T, T CD>
	[[nodiscard]] static constexpr Arithmetic<T, CD> operator+
		(typename Arithmetic<T, CD>::difference_type N, const Arithmetic<T, CD>& I)
	{
		return I + N;
	}
}
