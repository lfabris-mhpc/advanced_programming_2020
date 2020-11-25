#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream>
#include <utility>
#include <memory>

enum class Insertion_method { push_back, push_front };

template <class value_type>
class List {
	public:
		// insert a new node with the value v according to the method m
		// this method should be used to fill the list
		void insert(const value_type& v, const Insertion_method m) {
			switch (m) {
				case Insertion_method::push_back:
					this->push_back(v);
					break;
				case Insertion_method::push_front:
					this->push_front(v);
					break;
				default:
					break;
			}
		}

		// return the size of the list
		std::size_t size() const {
			return _size;
		}

		// delete all the nodes of the list
		void reset() {
			head.reset();
			_size = 0;
		}

		// constructor(s) for List
		List() : _size{}, head{} {
		}

		// copy semantics (deep copy)
		List(const List<value_type>& rhs) : List{} {
			//std::cout << "List copy ctor" << std::endl;
			for (const auto* iter = rhs.head.get(); iter; iter = iter->next.get()) {
				this->push_back(iter->value);
			}
		}

		List& operator=(const List& rhs) {
			//std::cout << "List copy assignment ctor" << std::endl;
			//not needed as the following move takes care of deleting the old values
			//this->reset();
			return *this = List<value_type>{rhs};
		}

		// move semantics
		//defaults are fine as they steal head and thus all the linked nodes
		List(List&& rhs) = default;
		
		List& operator=(List&& rhs) = default;

		// destructor
		//destructor of head cascades to linked nodes
		~List() = default;

		void pour(std::ostream& os) const {
			os << "List(" << _size << ")[";
			for (const auto* iter = this->head.get(); iter; iter = iter->next.get()) {
				os << iter->value << " ";
			}
			os << "]";
		}

	private:
		// private struct node with the proper value_type
		struct node {
			value_type value;
			std::unique_ptr<node> next;

			// implement suitable constructor(s) for node
			node(const value_type& value) : value{value}, next{} {
			}

			node(const value_type& value, std::unique_ptr<node>& next) : value{value}, next{std::move(next)} {
			}

			// copy and move semantics if needed
			node(const node& rhs) = delete;
			node& operator=(const node& rhs) = delete;

			node(node&& rhs) = default;
			node& operator=(node&& rhs) = default;

			// destructor
			~node() = default;
		};

		// append the newly created node at the end of the list
		void push_back(const value_type& v) {
			//std::cout << "push_back(" << v << ") from size " << _size << std::endl;
			if (head) {
				auto* iter = head.get();
				while (iter->next) {
					iter = iter->next.get();
				}

				iter->next = std::make_unique<node>(v);
			} else {
				head = std::make_unique<node>(v);
			}

			++_size;		
		}

		// insert the newly created node in front of the list
		void push_front(const value_type& v) {
			//std::cout << "push_front(" << v << ") from size " << _size << std::endl;
			head = std::make_unique<node>(v, head);

			++_size;
		}

		std::unique_ptr<node> head;
		std::size_t _size;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& l) {
	l.pour(os);

	return os;
}

#endif
