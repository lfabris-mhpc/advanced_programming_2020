#include <iostream>

/* no main:
/usr/bin/ld: /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/Scrt1.o: in function `_start':
(.text+0x24): undefined reference to `main'
collect2: error: ld returned 1 exit status
*/

/* typo in function name (but std::cout is actually an object; the error has the same meaning of identifier not found, though):
exercise1.cpp: In function ‘int main()’:
exercise1.cpp:14:7: error: ‘c0ut’ is not a member of ‘std’; did you mean ‘cout’?
   14 |  std::c0ut << "Hello, World!" << std::endl;
      |       ^~~~
      |       cout

actual misspelled function:
exercise1.cpp: In function ‘int main()’:
exercise1.cpp:33:2: error: ‘cOut’ was not declared in this scope; did you mean ‘cout’?
   33 |  cOut("Function call");
      |  ^~~~
      |  cout
*/

/* typo in variable name:
exercise1.cpp: In function ‘int main()’:
exercise1.cpp:23:15: error: ‘S’ was not declared in this scope
   23 |  std::cout << S << std::endl;
      |
*/

/* missing ";":
exercise1.cpp: In function ‘int main()’:
exercise1.cpp:45:1: error: expected ‘,’ or ‘;’ before ‘}’ token
   45 | }
      | ^
*/

/* missing include(s):
exercise1.cpp:43:23: error: variable or field ‘cout’ declared void
   43 | void cout(std::string const& txt) {
      |                       ^~~~~
exercise1.cpp:43:16: error: ‘string’ is not a member of ‘std’
   43 | void cout(std::string const& txt) {
      |                ^~~~~~
exercise1.cpp:1:1: note: ‘std::string’ is defined in header ‘<string>’; did you forget to ‘#include <string>’?
  +++ |+#include <string>
    1 | //#include <iostream>
exercise1.cpp: In function ‘int main()’:
exercise1.cpp:48:7: error: ‘cout’ is not a member of ‘std’
   48 |  std::cout << "Hello, World!" << std::endl;
      |       ^~~~
exercise1.cpp:1:1: note: ‘std::cout’ is defined in header ‘<iostream>’; did you forget to ‘#include <iostream>’?
  +++ |+#include <iostream>
    1 | //#include <iostream>
exercise1.cpp:48:39: error: ‘endl’ is not a member of ‘std’
   48 |  std::cout << "Hello, World!" << std::endl;
      |                                       ^~~~
exercise1.cpp:1:1: note: ‘std::endl’ is defined in header ‘<ostream>’; did you forget to ‘#include <ostream>’?
  +++ |+#include <ostream>
    1 | //#include <iostream>
exercise1.cpp:51:7: error: ‘size_t’ is not a member of ‘std’
   51 |  std::size_t s = 100;
      |       ^~~~~~
*/

/* illegal variable identifier:
exercise1.cpp: In function ‘int main()’:
exercise1.cpp:78:14: error: expected primary-expression before ‘float’
   78 |  std::size_t float{100};
      |      
*/

void cout(std::string const& txt) {
	std::cout << txt << std::endl;
}

int main() {
	std::cout << "Hello, World!" << std::endl;
	//cOut("Function call");

	std::size_t float{100};
	//std::cout << S << std::endl;
}
