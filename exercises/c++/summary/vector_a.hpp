#include <utility>
#include <memory>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cassert>

#include "ap_error.h"

template<typename T, typename Allocator = std::allocator<T>>
class vector {
	//vector with allocator
	Allocator allocator;
	T* elem;
	std::size_t _size, _capacity;

	static const std::size_t DEFAULT_CAPACITY = 8;
	static const std::size_t RESIZE_FACTOR = 2;

	void check_and_increase_capacity() {
		std::cout << "check_and_increase_capacity" << std::endl;
		if (!_capacity) {
			this->reserve(DEFAULT_CAPACITY);
		} else if (_size == _capacity) {
			this->reserve(RESIZE_FACTOR * _capacity);
		}
	}

	template<typename O>
	void _push_back(O&& v) {
		std::cout << "_push_back universal reference" << std::endl;
		this->check_and_increase_capacity();
		allocator.construct(elem + _size++, std::forward<O>(v));
		std::cout << "_push_back universal reference end" << std::endl;
	}

public:
	vector() = default;
	~vector() {
		for (std::size_t i = 0; i < _size; ++i) {
			allocator.destroy(elem + i);
		}
		
		allocator.deallocate(elem, _capacity);
	}

	explicit vector(const std::size_t capacity):
		//allocator is deprecated; std::allocator_traits<T>::allocate(capacity)
		elem{allocator.allocate(capacity)}
		, _size{}, _capacity{capacity} {
		std::cout << "vector capacity ctor" << std::endl;
	}

	vector(std::initializer_list<T> list): 
		elem{allocator.allocate(list.size())}
		, _size{list.size()}, _capacity{list.size()} {
		std::cout << "vector initializer list ctor" << std::endl;
		std::uninitialized_copy(list.begin(), list.end(), elem);
	}

	auto size() const {
		return _size;
	}

	auto capacity() const {
		return _capacity;
	}

	void reserve(const std::size_t capacity) {
		//AP_ASSERT(_capacity > capacity) << "cannot reserve less than current capacity" << std::endl;
		if (_capacity > capacity) {
			return;
		}

		std::cout << "reserve" << std::endl;
		T* tmp{allocator.allocate(capacity)};
		assert(tmp);
		for (std::size_t i = 0; i < _size; ++i) {
			allocator.construct(tmp + i, std::move(elem[i]));
		}

		for (std::size_t i = 0; i < _size; ++i) {
			allocator.destroy(elem + i);
		}
		
		allocator.deallocate(elem, _capacity);

		elem = tmp;
		_capacity = capacity;
	}

	void push_back(const T& v) {
		_push_back(v);
	}

	void push_back(T&& v) {
		_push_back(std::move(v));
	}

	template<typename... Types>
	void emplace_back(Types&&... args) {
		std::cout << "emplace_back" << std::endl;
		check_and_increase_capacity();
		allocator.construct(elem + _size++, T{std::forward<Types>(args)...}); 
	}

	T* begin() {
		return elem;
	}

	T* end() {
		return elem + _size;
	}

	const T* begin() const {
		return elem;
	}

	const T* end() const {
		return elem + _size;
	}
	
	const T* cbegin() const {
		return elem;
	}

	const T* cend() const {
		return elem + _size;
	}

	auto& operator[](const std::size_t i) {
		AP_ASSERT(elem) << "uninitialized vector" << std::endl;
		return elem[i];
	}
	
	const auto& operator[](const std::size_t i) const {
		AP_ASSERT(elem) << "uninitialized vector" << std::endl;
		return elem[i];
	}

	vector(const vector& rhs) = delete;
	vector& operator=(const vector&rhs) = delete;
	
	vector(vector&& rhs) = default;
	vector& operator=(vector&& rhs) = default;

	friend
	std::ostream& operator<<(std::ostream& os, const vector& v) {
		os << "vector(size: " << v.size() << ", capacity: " << v.capacity() << ") [";
		for (auto& e: v) {
			os << e << " ";
		}
		return os << "]";
	}
};
