#pragma once

#include <format>
#include <iostream>
#include <vector>

namespace
{
size_t choose(size_t n, size_t k)
{
  size_t r = n - k;
  size_t top = 1;
  size_t bottom = 1;
  for (size_t i = 0; i < k; i++)
  {
    // std::cout << k - i << "\n";
    top *= n - i;
    bottom *= k - i;
  }
  return top / bottom;
}
}

template <typename T = float, typename P = float>
class Bernstein {
public:
  Bernstein(std::vector<T> controls = {T{}})
    : ctrl{controls}
  {
    n = ctrl.size() - 1;
  }
  
  Bernstein(std::initializer_list<T> controls)
    : ctrl(controls)
  {
    n = ctrl.size() - 1;
  }

  std::vector<T>& control_points()
  {
    return ctrl;
  }

  T evaluate(P t)
  {
    std::vector<T> coeffs = ctrl;
    // std::cout << ctrl.size() << "\n";
    for (size_t degree = ctrl.size() - 1; degree != 0; degree--)
    {
      for (size_t j = 0; j < degree; j++)
      {
	// std::cout << std::format("degree: {} | j: {}\n", degree, j);
	coeffs[j] = (static_cast<P>(1) - t) * coeffs[j] + t * coeffs[j + 1];
      }
    }
    return coeffs[0];
  }

  

  Bernstein<T> operator+(const Bernstein<T>& other) const
  {
    const Bernstein<T>& greater = n >= other.n ? *this : other;
    const Bernstein<T>& lesser = n >= other.n ? other : *this;
    int g = static_cast<int>(greater.n);
    int l = static_cast<int>(lesser.n);
    std::vector<T> result_ctrl;
    result_ctrl.reserve(greater.n + 1);
    for (int k = 0; k <= g; k++)
    {
      T b{};
      // std::cout << "operator+\n";
      for (int j = std::max(0, k - g + l); j <= std::min(l, k); j++)
      {
	// std::cout << "operator+\n";
	P e = static_cast<P>(choose(greater.n - lesser.n, k - j) * choose(lesser.n, j)) /
	      static_cast<P>(choose(greater.n, k));
	b += e * lesser.ctrl[j];
      }
      result_ctrl.emplace_back(greater.ctrl[k] + b);
    }
    return Bernstein<T>{result_ctrl};
  }

  Bernstein<T> operator+(const T& constant) const
  {
    std::vector<T> new_coefficients;
    new_coefficients.reserve(ctrl.size());
    for (T c : ctrl)
    {
      new_coefficients.emplace_back(c + constant);
    }
    return Bernstein<T>{new_coefficients};
  }

  Bernstein<T> operator-() const
  {
    std::vector<T> new_ctrl;
    new_ctrl.reserve(ctrl.size());
    for (T c : ctrl)
    {
      new_ctrl.push_back(-c);
    }
    return Bernstein<T>{new_ctrl};
  }

  Bernstein<T> operator-(const T& constant) const
  {
    return *this + (-constant);
  }

  Bernstein<T> operator-(const Bernstein<T>& other) const
  {
    return *this + (-other);
  }

  Bernstein<T> operator*(const Bernstein<T>& other) const
  {
    const Bernstein<T>& greater = (n >= other.n ? *this : other);
    const Bernstein<T>& lesser = (n >= other.n ? other : *this);
    int g = static_cast<int>(greater.n);
    int l = static_cast<int>(lesser.n);
    std::vector<T> result_ctrl;
    // std::cout << std::format("greater: {}| lesser: {}\n", g, l);
    result_ctrl.reserve(greater.n + lesser.n + 1);
    // std::cout << "reserved\n";
    for (int k = 0; k <= g + l; k++)
    {
      // std::cout << std::format("k: {}, lesser: {}, greater: {}\n", k, l, g);
      // std::cout << std::format("lower: {}, upper {}\n", std::max(0, k - l), std::min(g, k));
      T c{};
      for (int j = std::max(0, k - l); j <= std::min(g, k); j++)
      {
	// std::cout << std::format("j = {}\n", j);
	// std::cout << std::format("{} / {}\n", choose(greater.n, j) * choose(lesser.n, k - j),
					      // choose(greater.n + lesser.n, k));
	P e = static_cast<P>(choose(greater.n, j) * choose(lesser.n, k - j)) /
	      static_cast<P>(choose(greater.n + lesser.n, k));
	c += e * greater.ctrl[j] * lesser.ctrl[k - j];
      }
      result_ctrl.push_back(c);
    }
    // std::cout << "finished *\n";
    return Bernstein<T>{result_ctrl};
  }

  Bernstein<T> operator*(const T& constant) const
  {
    std::vector<T> new_ctrl;
    new_ctrl.reserve(ctrl.size());
    for (T c : ctrl)
    {
      new_ctrl.push_back(constant * c);
    }
    return Bernstein<T>{new_ctrl};
  }

  Bernstein<T> derivative(size_t order = 1)
  {
    std::vector<T> o_ctrl = ctrl;
    std::vector<T> d_ctrl;
    d_ctrl.reserve(n);
    for (size_t r = 0; r < order; r++)
    {
      if (o_ctrl.size() == 1)
      {
	return Bernstein<T>{T{}};
      }
      for (size_t k = 0; k < n - r; k++)
      {
	d_ctrl.emplace_back(static_cast<P>(k) * (o_ctrl[k + 1] - o_ctrl[k]));
      }
      o_ctrl.swap(d_ctrl);
      d_ctrl.clear();
    }
    return Bernstein<T>{o_ctrl};
  }

  Bernstein<T> integral(T c0 = T{})
  {
    std::vector<T> i_ctrl;
    i_ctrl.reserve(n + 2);
    i_ctrl.push_back(c0);
    for (size_t k = 1; k <= n + 1; k++)
    {
      T new_control{};
      // std::cout << "integral\n";
      for (size_t j = 0; j <= k - 1; j++)
      {
	// std::cout << "integral\n";
	new_control = new_control + ctrl[j];
      }
      new_control = new_control / static_cast<P>(n + 1);
      i_ctrl.push_back(new_control);
    }
    return Bernstein<T>{i_ctrl};
  }

private:
  size_t n;
  std::vector<T> ctrl;
};
