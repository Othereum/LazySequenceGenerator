#pragma once
#include <iterator>

namespace LSG
{
	template <class T = int>
	class Arithmetic
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using reference = const T &;
		using pointer = const T*;

		constexpr Arithmetic(T Init = T{}, T CD = 1) :Num{ std::move(Init) }, CD{ std::move(CD) } {}

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
		[[nodiscard]] constexpr T operator[](difference_type N) const { return *(*this + N); }

		// WARNING: Using with having different common difference is undefined behavior.
		[[nodiscard]] constexpr difference_type operator-(const Arithmetic& I) const { return (Num - I.Num) * CD; }
		[[nodiscard]] constexpr bool operator==(const Arithmetic& R) const { return Num == R.Num; }
		[[nodiscard]] constexpr bool operator!=(const Arithmetic& R) const { return !(*this == R); }
		[[nodiscard]] constexpr bool operator<(const Arithmetic& R) const { return R - *this > 0; }
		[[nodiscard]] constexpr bool operator>(const Arithmetic& R) const { return R < *this; }
		[[nodiscard]] constexpr bool operator>=(const Arithmetic& R) const { return !(*this < R); }
		[[nodiscard]] constexpr bool operator<=(const Arithmetic& R) const { return !(*this > R); }

	private:
		T Num, CD;
	};

	template <class T>
	[[nodiscard]] static constexpr Arithmetic<T> operator+
		(typename Arithmetic<T>::difference_type N, const Arithmetic<T>& I)
	{
		return I + N;
	}

	template <class T>
	class Range
	{
	public:
		// [0, Last)
		constexpr Range(T Last) :Range{ T{}, std::move(Last), 1 } {}

		// [First, Last)
		// An integer N that satisfies { First + N*CD = Last } must exist.
		// If not, the comparison of Arithmetic returned by begin and end is an undefined behavior.
		constexpr Range(T First, T Last, T CD = 1)
			: First{ std::move(First) }, Last{ std::move(Last) }, CD{ std::move(CD) } {}

		[[nodiscard]] constexpr Arithmetic<T> begin() const { return { First, CD }; }
		[[nodiscard]] constexpr Arithmetic<T> end() const { return { Last, CD }; }

	private:
		T First, Last, CD;
	};
}
