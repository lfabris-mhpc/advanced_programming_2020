#include <utility>
#include <memory>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cassert>

#include "ap_error.h"

template<typename T>
class vector {
	//vector with allocator uses it instead of malloc, for construction (similar to placement new) and destruction
	//uses raw pointer instead of unique, since it has to do explicit memory management anyway
	//note that the destructor (and the reserve, on the old vector) needs to destroy size elements and deallocate capacity

	//"custom" destructor since now it's allocated with malloc and requires free
	//the default calls T's destructor
	std::unique_ptr<T, decltype(&free)> elem;
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
		assert(elem.get());
		//moving into uninitialized memory can result in segfault
		//e.g. an std::string cannot swap memory since the uninitialized one has nullptr
		//elem.get()[_size++] = std::forward<O>(v);
		new(elem.get() + _size++) T{std::forward<O>(v)};
		std::cout << "_push_back universal reference end" << std::endl;
	}

public:
	vector(): elem{nullptr, &free}, _size{}, _capacity{} {
		std::cout << "vector base ctor" << std::endl;
	}

	explicit vector(const std::size_t capacity): 
		//elem{new T[capacity]}
		elem{nullptr, &free}
		, _size{}, _capacity{capacity} {
		std::cout << "vector capacity ctor" << std::endl;
	}

	vector(std::initializer_list<T> list): 
		//elem{new T[list.size()]}
		elem{static_cast<T*>(malloc(sizeof(T) * list.size())), free} //with newest allocator_traits: std::allocator_traits<Allocator>::allocate
		, _size{list.size()}, _capacity{list.size()} {
		std::cout << "vector initializer list ctor" << std::endl;
		//std::copy(list.begin(), list.end(), elem.get());
		//in c++17 there's also uninitialized_move
		std::uninitialized_copy(list.begin(), list.end(), elem.get());

		//no for each loop; no subscripting op on initializer_list
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
		//using new calls the default constructor
		//T* tmp{new T[capacity]};
		//std::copy(this->begin(), this->end(), tmp);
		T* tmp{static_cast<T*>(malloc(sizeof(T) * capacity))};
		assert(tmp);
		for (std::size_t i = 0; i < _size; ++i) {
			//placement new; also, moving from old values
			new(tmp + i) T{std::move(elem.get()[i])};
		}

		elem.reset(tmp);
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
		//elem[_size++] = T{std::forward<Types>(args)...};
		new(elem.get() + _size++) T{std::forward<Types>(args)...};
	}

	T* begin() {
		return elem.get();
	}

	T* end() {
		return elem.get() + _size;
	}

	const T* begin() const {
		return elem.get();
	}

	const T* end() const {
		return elem.get() + _size;
	}
	
	const T* cbegin() const {
		return elem.get();
	}

	const T* cend() const {
		return elem.get() + _size;
	}

	auto& operator[](const std::size_t i) {
		AP_ASSERT(elem) << "uninitialized vector" << std::endl;
		return elem[i];
	}
	
	const auto& operator[](const std::size_t i) const {
		AP_ASSERT(elem) << "uninitialized vector" << std::endl;
		return elem[i];
	}

	~vector() {
		//since using malloc, must explicitly destroy each element
		for (auto i = 0; i < _size; ++i) {
			elem.get()[i].~T();
		}
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
