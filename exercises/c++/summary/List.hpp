#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream>
#include <iterator>
#include <memory>
#include <utility>

enum class Insertion_method { push_back, push_front };

template <class value_type> class List {
public:
	template<typename O>
	class _iterator;

	using iterator = _iterator<value_type>;
	using const_iterator = _iterator<const value_type>;

	iterator begin() noexcept {
		return iterator{head.get()};
	}
	iterator end() noexcept {
		return iterator{nullptr};
	}

	const_iterator begin() const noexcept {
		return const_iterator{head.get()};
	}
	const_iterator end() const noexcept {
		return const_iterator{nullptr};
	}

	/*
	const_iterator cbegin() const noexcept {
		return const_iterator{head.get()};
	}
	const_iterator cend() const noexcept {
		return const_iterator{nullptr};
	}
	*/

    // insert a new node with the value v according to the method m
    // this method should be used to fill the list
    // two flavors: one with l-value refs, one with l-value refs
    // both will feed into a universal ref internal method
    // must not have universal ref in the interface: type deduction must be
    // avoided
    void insert(const value_type &v, const Insertion_method m) {
        _insert(v, m);
    }

    void insert(value_type &&v, const Insertion_method m) {
        _insert(std::move(v), m);
    }

    // return the size of the list
    std::size_t size() const { return _size; }

    // delete all the nodes of the list
    void reset() {
        head.reset();
        _size = 0;
    }

    // constructor(s) for List
    List() = default;

    // copy semantics (deep copy)
    List(const List<value_type> &rhs) : _size{rhs._size}, head{} {
        if (rhs.head) {
            head.reset(new node{rhs.head->value});
            auto *last = head.get();
            for (const auto *iter = rhs.head->next.get(); iter;
                 iter = iter->next.get()) {
                last->next.reset(new node{iter->value});
                last = last->next.get();
            }
        }
    }

    List &operator=(const List &rhs) {
        // not needed as the following move takes care of deleting the old
        // values this->reset();
        return *this = List<value_type>{rhs};
    }

    // move semantics
    // defaults are fine as they steal head and thus all the linked nodes
    List(List &&rhs) = default;

    List &operator=(List &&rhs) = default;

    // destructor
    // destructor of head cascades to linked nodes
    ~List() = default;

    friend void swap(List &a, List &b) {
        auto tmp = std::move(a);
        a = std::move(b);
        b = std::move(tmp);
    }

    friend std::ostream &operator<<(std::ostream &os, const List &l) {
        os << "List(" << l._size << ")[";
        for (const auto *iter = l.head.get(); iter; iter = iter->next.get()) {
            os << iter->value << " ";
        }
        os << "]";

        return os;
    }

private:
    // private struct node with the proper value_type
    struct node {
        value_type value;
        std::unique_ptr<node> next;

        // implement suitable constructor(s) for node
        explicit node(const value_type &value) : value{value}, next{} {
            std::cout << "l-value node ctor, nullptr" << std::endl;
        }

        explicit node(value_type &&value) : value{value}, next{} {
            std::cout << "r-value node ctor, nullptr" << std::endl;
        }

        explicit node(const value_type &value, node *p)
            : value{value}, next{p} {
            std::cout << "l-value node ctor, ptr" << std::endl;
        }

        explicit node(value_type &&value, node *p) : value{value}, next{p} {
            std::cout << "r-value node ctor, ptr" << std::endl;
        }

        explicit node(const std::unique_ptr<node> &x)
            : next{}, value{x->value} {
            std::cout << "'deep copy' node ctor from unique_ptr&" << std::endl;
            if (x->next) {
                // this calls recursively this ctor
                next.reset(new node{x->next});
            }
        }

        node(const value_type &value, std::unique_ptr<node> &next)
            : value{value}, next{std::move(next)} {
            std::cout << "l-value node ctor" << std::endl;
        }

        // copy and move semantics if needed
        node(const node &rhs) = delete;
        node &operator=(const node &rhs) = delete;

        node(node &&rhs) = default;
        node &operator=(node &&rhs) = default;

        // destructor
        ~node() = default;
    };

    // helper function with universal ref and forwarding
    template <typename O> void _insert(O &&v, const Insertion_method m) {
        switch (m) {
        case Insertion_method::push_back:
            this->push_back(std::forward<O>(v));
            break;
        case Insertion_method::push_front:
            this->push_front(std::forward<O>(v));
            break;
        default:
            break;
        }
    }

    /*
    //after having the universal ref versions, no need to overload the internals
    void push_back(const value_type& v) {}
    void push_front(const value_type& v) {}
    */

    // forwarding - compare with Effective Modern C++ items 24, 26, 27
    // type deduction takes place, this is a universal reference and must use
    // forward note: when outside class decl, templates for class and for funcs
    // must be on different lines having type deduction makes these "universal
    // references" eg: template<typename used_by_class, ...>
    //    template<typename used_by_method, ...>
    template <typename O> void push_back(O &&v) {
        std::cout << "universal ref push_back" << std::endl;
        if (head) {
            auto *iter = head.get();
            while (iter->next) {
                iter = iter->next.get();
            }

            iter->next.reset(new node{std::forward<O>(v)});
        } else {
            head.reset(new node{std::forward<O>(v)});
        }

        ++_size;
    }

    template <typename O> void push_front(O &&v) {
        std::cout << "universal ref push_front" << std::endl;
        head.reset(new node{std::forward<O>(v), head.release()});
        ++_size;
    }

    std::unique_ptr<node> head;
    std::size_t _size;
};

//iterator outside class - first template arg is for the List that contains the forward declaration
template<typename T>
template<typename O>
class List<T>::_iterator {
	//the typename is necessary due to the T belonging to another class
	using node = typename List<T>::node;
	node* current;
public:
	using value_type = O;
	using reference = value_type&;
	using pointer = value_type*;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::forward_iterator_tag;

	//think if ok: explicit
	_iterator(node* v): current{v} {
	}

	reference operator*() const {
		return current->value;
	}

	pointer operator->() const {
		return &**this;
	}

	//preincrement
	_iterator& operator++() {
		current = current->next.get();
		return *this;
	}
	//postincrement
	_iterator operator++(int) {
		auto tmp{*this};
		++(*this);
		return tmp;
	}

	friend
	bool operator==(_iterator& lhs, _iterator& rhs) {
		return lhs.current == rhs.current;
	}
	
	friend
	bool operator!=(_iterator& lhs, _iterator& rhs) {
		return !(lhs == rhs);
	}
};

#endif
