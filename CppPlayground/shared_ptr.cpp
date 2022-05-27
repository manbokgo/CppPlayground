// owner_less example
#include <iostream>
#include <memory>
#include <set>

int main()
{
	{
		int* p = new int(10);

		std::shared_ptr<int> a(new int(20));
		std::shared_ptr<int> b(a, p); // alias constructor: co-owns a, points to p

		// standard set container: cannot contain duplicates.
		std::set < std::shared_ptr<int> >                                        value_based; // uses std::less
		std::set < std::shared_ptr<int>, std::owner_less<std::shared_ptr<int>> > owner_based;

		value_based.insert(a);
		value_based.insert(b); // ok, different value

		owner_based.insert(a);
		owner_based.insert(b); // overwrites (same owned pointer)

		std::cout << "value_based.size() is " << value_based.size() << '\n';
		std::cout << "owner_based.size() is " << owner_based.size() << '\n';

		delete p;
	}

	struct T { int x, y; };

	std::shared_ptr<T> a = std::make_shared<T>();
	std::shared_ptr<T> b = a;

	std::shared_ptr<int> c(a, &a->y); // aliasing constructor

	std::shared_ptr<T> d(a.get(), [](T*) {}); // null deleter to avoid no double delete
	std::shared_ptr<T> e(std::shared_ptr<T>(), a.get()); // "non-owning" empty shared_ptr with a non-null stored pointer

	return 0;
}
