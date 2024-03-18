#pragma once

#include <iostream>
#include <vector>

template <typename T = float, typename P = float>
class Polynomial {
public:
  Polynomial(std::vector<T> base_coeffs = {T{}})
    : coeffs(base_coeffs)
  {
    prepare();
  }

  Polynomial(std::initializer_list<T> base_coeffs)
    : coeffs(base_coeffs)
  {
    prepare();
  }

  Polynomial(T constant)
    : coeffs{constant}
  {
  }

  size_t degree()
  {
    return n;
  }

  std::vector<T> coefficients() const
  {
    return coeffs;
  }

  T evaluate(P t)
  {
    T result = coeffs.back();

    for (auto coeff = ++coeffs.rbegin();
	coeff != coeffs.rend(); coeff++)
    {
      result = result * t + *coeff;
    }
    return result;
  }

  const T& operator[](size_t i) const
  {
    return coeffs[i];
  }

  T& operator[](size_t i)
  {
    return coeffs[i];
  }

  Polynomial<T> operator+(const Polynomial<T>& other) const
  {
    size_t new_degree = std::max(n, other.n);
    std::vector<T> result_coeffs;
    result_coeffs.reserve(new_degree + 1);
    for (int k = 0; k <= new_degree; k++) {
      T c1 = coeffs.size() > k ? coeffs[k] : T{};
      T c2 = other.coeffs.size() > k ? other.coeffs[k] : T{};
      result_coeffs.emplace_back(c1 + c2);
    }
    return Polynomial<T>{result_coeffs};
  }

  Polynomial<T> operator+(const T& constant) const
  {
    return *this + Polynomial<T>{constant};
  }

  Polynomial<T> operator-() const
  {
    std::vector<T> new_coeffs;
    new_coeffs.reserve(coeffs.size());
    for (T c : coeffs)
    {
      new_coeffs.push_back(-c);
    }
    return Polynomial<T>{new_coeffs};
  }

  Polynomial<T> operator-(const Polynomial<T>& other) const
  {
    return *this + (-other);
  }
  
  Polynomial<T> operator-(const T& constant) const
  {
    return *this + (-constant);
  }

  Polynomial<T> operator*(const Polynomial& other) const
  {
    size_t new_degree = n + other.n;
    std::vector<T> result_coeffs;
    result_coeffs.reserve(new_degree + 1);
    for (int k = 0; k <= new_degree; k++) {
      T coeff{};
      int i = k <= other.n ? 0 : k - other.n;
      while (i <= n && k - i >= 0)
      {
	coeff += coeffs[i] * other.coeffs[k - i];
	i++;
      }
      result_coeffs.push_back(coeff);
    }
    return Polynomial<T>{result_coeffs};
  }

  Polynomial<T> operator*(const T& constant) const
  {
    return *this * Polynomial<T>{constant};
  }

  Polynomial<T> derivative(size_t order = 1)
  {
    std::vector<T> o_coeffs = coeffs;
    std::vector<T> d_coeffs;
    d_coeffs.reserve(n);
    for (size_t k = 0; k < order; k++)
    {
      if (o_coeffs.size() == 1)
      {
	return Polynomial<T>{T{}};
      }
      for (size_t i = 0; i < n - k; i++)
      {
	d_coeffs.emplace_back(o_coeffs[i + 1] * static_cast<P>(i + 1));
      }
      o_coeffs.swap(d_coeffs);
      d_coeffs.clear();
    }
    return Polynomial<T>{o_coeffs};
  }

  Polynomial<T> integral(T c = T{})
  {
    std::vector<T> i_coeffs;
    i_coeffs.reserve(n + 2);
    i_coeffs.push_back(c);
    for (size_t i = 0; i <= n; i++)
    {
      i_coeffs.emplace_back(coeffs[i] / static_cast<P>(i + 1));
    }
    return Polynomial<T>{i_coeffs};
  }

private:
  std::vector<T> coeffs;
  size_t n;

  void prepare()
  {
    while (coeffs.size() != 1 && coeffs.back() == T{})
    {
      coeffs.pop_back();
    }
    coeffs.reserve(coeffs.size());
    n = coeffs.size() - 1;
  }
};
