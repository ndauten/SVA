// RUN: %clang_cc1 -x c++ -fms-extensions -fsyntax-only -emit-pch -o %t %s
// RUN: %clang_cc1 -x c++ -fms-extensions -fsyntax-only -include-pch %t %s -verify

#ifndef HEADER
#define HEADER
template<typename T>
void f(T t) {
  __if_exists(T::foo) {
    { }
    t.foo();
  }

  __if_not_exists(T::bar) {
    int *i = t; // expected-error{{no viable conversion from 'HasFoo' to 'int *'}}
    { }
  }
}
#else
struct HasFoo { 
  void foo();
};
struct HasBar { 
  void bar(int);
  void bar(float);
};

template void f(HasFoo); // expected-note{{in instantiation of function template specialization 'f<HasFoo>' requested here}}
template void f(HasBar);
#endif
