#pragma once

template<unsigned int n>
constexpr unsigned long long factorial = factorial<n - 1> * n;

template<>
constexpr unsigned long long factorial<0> = 1;

template<>
constexpr unsigned long long factorial<1> = 1;

