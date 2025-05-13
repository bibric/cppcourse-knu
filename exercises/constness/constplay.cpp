#include <iostream>
#include <string>

// This is a dummy function to demonstrate pass by value.
 //* Since it doesn't do anything with the argument, we suppress
 //* possible compiler warnings using `maybe_unused`.

void copy(int a) {
    [[maybe_unused]] int val = a;
}

void copyConst(const int a) {
    [[maybe_unused]] int val = a;
}

void write(int* a) {
    *a = 42;
}
void write(int& a) {
    a = 42;
}

void read(const int* a) {
    [[maybe_unused]] int val = *a;
}

void read(int const & a) {//это даже компилировать не хотело, нельзя менять константу к 2
    [[maybe_unused]] int val = a;
}

struct Test {
    void hello(std::string &s) {
        std::cout << "Hello " << s << '\n';
    }
    void helloConst(std::string &s) const {
        std::cout << "Const Hello " << s << '\n';
    }
};

int main() {
    // try pointer to constant
    int a = 1, b = 2;
    int const *i = &a; //Попытка сохранить значение не зашищая адресс
    //*i = 5;
    std::cout<<"i="<<i<<" *i="<<*i<<std::endl;
    i = &b;
    std::cout<<"i="<<i<<" *i="<<*i<<std::endl;

    // try constant pointer
    int * const j = &a;//охраняем адресс не сохраняя значение по адресу
    std::cout<<"j="<<j<<" *j="<<*j<<std::endl;
    *j = 5;
    std::cout<<"j="<<j<<" *j="<<*j<<" a="<<&a<<std::endl;
    //j = &b;

    // try constant pointer to constant
    int const * const k = &a;//ничего не поменяем
    //*k = 5;
    //k = &b;

    // try constant arguments of functions
    int l = 0;
    const int m = 0;
    copy(l);
    copy(m);//мы ж ничего не меняем
    copyConst(l);
    copyConst(m);

    // try constant arguments of functions with pointers
    {
      int *p = &a;
      const int *r = &b;
      write(p);
      //write(r);//*r нельзя менять, r можно, но там ошибка из за того что пытаемся вместо int& всунуть int
      read(p);
      std::cout<<"r="<<r<<" *r="<<*r<<" &r="<<&r<<std::endl;
      read(r);
      std::cout<<"r="<<r<<" *r="<<*r<<" &r="<<&r<<std::endl;
    }

    // try constant arguments of functions with references
    {
      int p = 0;
      const int r = 0;
      //write(2);//no known conversion from 'int' to 'int *'
      //write(r);//no known conversion from 'const int' to 'int *'
      read(2);
      read(r);
    }

    // try constant method in a class
    Test t;
    Test const tc;
    std::string s("World");
    t.hello(s);
    //tc.hello(s);//константный объект вызывает неконстантный метод
    t.helloConst(s);
    tc.helloConst(s);

    return 0;
}
