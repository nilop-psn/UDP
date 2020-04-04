#pragma once

#include <utility>

namespace Ubpa {
	// when Reflection regist, it will be T Friend::*
	// so you should treat it as T but read only
	template<typename Friend, typename T>
	struct Read {
		template<typename... Args>
		Read(Args&&... args) : val{ std::forward<Args>(args)... } {}

		Read(const Read& read) noexcept : val{ read.val } {}
		Read(Read&& read) noexcept : val{ std::move(read.val) } {}
		Read& operator=(const Read& read) noexcept { val = read.val; return *this; }
		Read& operator=(Read&& read) noexcept { val = std::move(read.val); return *this; }

		const T& get() const noexcept { return val; }
		operator T() const noexcept { return val; }

		T* operator->() noexcept { return &val; }
		const T* operator->() const noexcept { return &val; }

		template<typename U>
		auto operator+(const U& y) const noexcept { return val + y; }
		template<typename U>
		auto operator-(const U& y) const noexcept { return val - y; }
		template<typename U>
		auto operator*(const T& y) const noexcept { return val * y; }
		template<typename U>
		auto operator/(const U& y) const noexcept { return val / y; }
		template<typename U>
		auto operator%(const U& y) const noexcept { return val % y; }
		const auto& operator[](size_t n) const noexcept { return val[n]; }
		bool operator==(const T& y) const noexcept { return val == y; }
		bool operator!=(const T& y) const noexcept { return val != y; }
		bool operator>(const T& y) const noexcept { return val > y; }
		bool operator>=(const T& y) const noexcept { return val >= y; }
		bool operator<(const T& y) const noexcept { return val < y; }
		bool operator<=(const T& y) const noexcept { return val <= y; }
		auto operator*() const noexcept { return *val; }

		auto begin() const noexcept { return val.begin(); }
		auto end() const noexcept { return val.end(); }

	private:
		friend Friend;
		T val;
	};

	template<typename Friend, typename T>
	struct Read<Friend, T*> {
		template<typename... Args>
		Read(Args&&... args) : val{ std::forward<Args>(args)... } {}

		T* get() const noexcept { return val; }

		operator T*() const noexcept { return val; }

		T* operator->() const noexcept { return val; }

		Read(const Read& read) noexcept : val{ read.val } {}
		Read(Read&& read) noexcept : val{ std::move(read.val) } {}
		Read& operator=(const Read& read) noexcept { val = read.val; return *this; }
		Read& operator=(Read&& read) noexcept { val = std::move(read.val); return *this; }

	private:
		friend Friend;
		T* val;
	};
}