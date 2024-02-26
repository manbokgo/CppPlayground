#include <iostream>

class Base
{
public:
    virtual void sayHello()
    {
        std::cout << "Hello world, I am Base" << std::endl;
    }
};

class Derived : public Base
{
public:
    void sayHello()
    {
        std::cout << "Hello world, I am Derived" << std::endl;
    }
};

class DD : public Derived
{
public:
    void sayHello()
    {
        std::cout << "Hello world, I am DD" << std::endl;
    }
};

void testPointer(Base* obj)
{
    obj->sayHello();
}


void testPointer(Derived* obj)
{
    obj->sayHello();
}



int main()
{
    {
        std::cout << "Testing with pointer argument: ";
        DD* dd = new DD;
        testPointer(dd);
    }
}
