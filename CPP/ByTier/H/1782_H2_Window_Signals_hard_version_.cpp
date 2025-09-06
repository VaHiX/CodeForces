/*
 * Problem URL : https://codeforces.com/problemset/problem/1782/H2
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>

using namespace std;

template <typename T> T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a;
    swap(a, m);
    u -= t * v;
    swap(u, v);
  }
  assert(m == 1);
  return u;
}

template <typename T> class Modular {
public:
  using Type = typename decay<decltype(T::value)>::type;

  constexpr Modular() : value() {}
  template <typename U> Modular(const U &x) { value = normalize(x); }

  template <typename U> static Type normalize(const U &x) {
    Type v;
    if (-mod() <= x && x < mod())
      v = static_cast<Type>(x);
    else
      v = static_cast<Type>(x % mod());
    if (v < 0)
      v += mod();
    return v;
  }

  const Type &operator()() const { return value; }
  template <typename U> explicit operator U() const {
    return static_cast<U>(value);
  }
  constexpr static Type mod() { return T::value; }

  Modular &operator+=(const Modular &other) {
    if ((value += other.value) >= mod())
      value -= mod();
    return *this;
  }
  Modular &operator-=(const Modular &other) {
    if ((value -= other.value) < 0)
      value += mod();
    return *this;
  }
  template <typename U> Modular &operator+=(const U &other) {
    return *this += Modular(other);
  }
  template <typename U> Modular &operator-=(const U &other) {
    return *this -= Modular(other);
  }
  Modular operator-() const { return Modular(-value); }

  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value,
                     Modular>::type &
  operator*=(const Modular &rhs) {
    value = normalize(static_cast<int64_t>(value) *
                      static_cast<int64_t>(rhs.value));
    return *this;
  }

  Modular &operator/=(const Modular &other) {
    return *this *= Modular(inverse(other.value, mod()));
  }

  template <typename V, typename U>
  friend V &operator>>(V &stream, Modular<U> &number);

private:
  Type value;
};

template <typename T>
Modular<T> operator+(const Modular<T> &lhs, const Modular<T> &rhs) {
  return Modular<T>(lhs) += rhs;
}
template <typename T, typename U>
Modular<T> operator+(const Modular<T> &lhs, U rhs) {
  return Modular<T>(lhs) += rhs;
}
template <typename T, typename U>
Modular<T> operator+(U lhs, const Modular<T> &rhs) {
  return Modular<T>(lhs) += rhs;
}

template <typename T>
Modular<T> operator-(const Modular<T> &lhs, const Modular<T> &rhs) {
  return Modular<T>(lhs) -= rhs;
}
template <typename T, typename U>
Modular<T> operator-(const Modular<T> &lhs, U rhs) {
  return Modular<T>(lhs) -= rhs;
}
template <typename T, typename U>
Modular<T> operator-(U lhs, const Modular<T> &rhs) {
  return Modular<T>(lhs) -= rhs;
}

template <typename T>
Modular<T> operator*(const Modular<T> &lhs, const Modular<T> &rhs) {
  return Modular<T>(lhs) *= rhs;
}
template <typename T, typename U>
Modular<T> operator*(const Modular<T> &lhs, U rhs) {
  return Modular<T>(lhs) *= rhs;
}
template <typename T, typename U>
Modular<T> operator*(U lhs, const Modular<T> &rhs) {
  return Modular<T>(lhs) *= rhs;
}

template <typename T, typename U>
Modular<T> power(const Modular<T> &a, const U &b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1)
      res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}

template <typename U, typename T>
U &operator<<(U &stream, const Modular<T> &number) {
  return stream << number();
}

template <typename U, typename T> U &operator>>(U &stream, Modular<T> &number) {
  typename common_type<typename Modular<T>::Type, long long>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

class dsu {
public:
  vector<int> p;
  vector<int> sz;
  int n;

  dsu(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
    sz.assign(n, 1);
  }

  inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x]))); }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      sz[y] += sz[x];
      return true;
    }
    return false;
  }
};

int main() {
  int tt;
  cin >> tt;
  while (tt--) {
    int h, w, k;
    cin >> h >> w >> k;
    vector<Mint> fib(h * w + 1);
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i <= h * w; i++) {
      fib[i] = fib[i - 1] + fib[i - 2];
    }
    vector<pair<int, int>> p(k);
    for (int i = 0; i < k; i++) {
      cin >> p[i].first >> p[i].second;
      --p[i].first;
      --p[i].second;
    }
    Mint ans = 0;
    for (int ww = 1; ww <= w; ww++) {
      for (int top = 0; top < 2; top++) {
        for (int left = 0; left < 2; left++) {
          for (int right = 0; right < 2; right++) {
            if (ww == 1 && left + right > 0) {
              continue;
            }
            int sign = ((top + left + right) % 2 == 0 ? 1 : -1);
            dsu d(h * ww);
            vector<vector<int>> g(h * ww);
            vector<bool> must(h * ww);
            bool done = false;
            Mint prod = power(Mint(2), (h - top) * (ww - left - right));
            for (int i = 0; i < h; i++) {
              for (int j = 0; j <= w - ww; j++) {
                vector<pair<int, int>> here;
                for (auto &c : p) {
                  if (c.first >= i + top && c.second >= j + left &&
                      c.second < j + ww - right) {
                    here.emplace_back(c.first - i, c.second - j);
                  }
                }
                if (here.size() == 0) {
                  ans += sign * prod;
                  done = true;
                  break;
                }
                if (here.size() == 1) {
                  int x = here[0].first * ww + here[0].second;
                  if (!must[x]) {
                    must[x] = true;
                    int px = d.get(x);
                    prod /= fib[d.sz[px]];
                    d.sz[px] -= 1;
                    int sub = 0;
                    for (int y : g[x]) {
                      if (!must[y]) {
                        sub += 1;
                      }
                    }
                    ans += sign * prod * fib[d.sz[px] - sub];
                    prod *= fib[d.sz[px]];
                  }
                }
                if (here.size() == 2) {
                  int x = here[0].first * ww + here[0].second;
                  int y = here[1].first * ww + here[1].second;
                  int px = d.get(x);
                  int py = d.get(y);
                  assert(px != py);
                  prod /= fib[d.sz[px]];
                  prod /= fib[d.sz[py]];
                  if (!must[x] && !must[y]) {
                    int subx = 1;
                    for (int t : g[x]) {
                      if (!must[t]) {
                        subx += 1;
                      }
                    }
                    int suby = 1;
                    for (int t : g[y]) {
                      if (!must[t]) {
                        suby += 1;
                      }
                    }
                    ans += sign * prod * fib[d.sz[px] - subx] *
                           fib[d.sz[py] - suby];
                    g[x].push_back(y);
                    g[y].push_back(x);
                  }
                  d.unite(px, py);
                  prod *= fib[d.sz[py]];
                }
              }
              if (done) {
                break;
              }
              for (int j = left; j < ww - right; j++) {
                int x = (h - 1 - i) * ww + j;
                if (must[x]) {
                  done = true;
                  break;
                }
                int px = d.get(x);
                prod /= fib[d.sz[px]];
                d.sz[px] -= 1;
                prod *= fib[d.sz[px]];
                for (int y : g[x]) {
                  if (!must[y]) {
                    must[y] = true;
                    int py = d.get(y);
                    prod /= fib[d.sz[py]];
                    d.sz[py] -= 1;
                    prod *= fib[d.sz[py]];
                  }
                }
              }
              if (done) {
                break;
              }
            }
          }
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}