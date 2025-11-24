// Problem: CF 1656 H - Equal LCM Subsets
// https://codeforces.com/contest/1656/problem/H
//
// This solution finds subsets of two given arrays such that the LCM of the
// remaining elements in array A equals the LCM of the remaining elements
// in array B. The approach uses a prime basis (a factorization technique) to
// represent each number by its prime factors, then a greedy algorithm that
// iteratively removes elements that cause imbalance in prime power counts
// across the two arrays.
//
// Key insight: Two numbers have equal LCM if and only if they agree on the
// maximum power of each prime in their factorizations. The algorithm maintains
// these constraints by removing elements from either array whenever a prime
// power imbalance is detected.
//
// Data structures:
// - PrimeBasis<T>: Factorizes all numbers in both arrays into a common set
//   of "basis" primes (those actually appearing in the input). Each element
//   is then represented as a vector of exponents for these basis primes.
// - uint128_t: A 128-bit integer to handle potentially very large numbers.
//
// Algorithm:
// 1. Compute a prime basis from all elements of both arrays.
// 2. Factorize each element using the basis (exponent vectors).
// 3. For each prime, maintain sorted lists of elements by their exponent.
// 4. Iterate through primes where max exponent differs between arrays.
// 5. Greedily remove elements to balance exponents.
// 6. Output remaining elements (or "NO" if removal exhausts one array).

#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

template <typename T> ostream &operator+(ostream &out, const vector<T> &vec) {
  for (const auto &x : vec) {
    out << x << " ";
  }
  out << "\n";
  return out;
}
template <typename T> ostream &operator*(ostream &out, const vector<T> &vec) {
  for (const auto &x : vec) {
    out + x;
  }
  return out;
}
template <typename T> istream &operator>>(istream &in, vector<T> &vec) {
  for (auto &x : vec) {
    in >> x;
  }
  return in;
}
template <typename T> T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
// PrimeBasis<T>: maintains a set of coprime "basis" primes extracted from
// input numbers. Each new number is factorized over this basis. The solve_inner
// and add_element functions refine the basis when new prime factors appear.
template <typename T> struct PrimeBasis {
  void reduce_pair(T &x, T &y) {
    bool to_swap = 0;
    if (x > y) {
      to_swap ^= 1;
      swap(x, y);
    }
    while (x > 1 && y % x == 0) {
      y /= x;
      if (x > y) {
        to_swap ^= 1;
        swap(x, y);
      }
    }
    if (to_swap)
      swap(x, y);
  }
  vector<T> basis;
  void solve_inner(int pos, T &val) {
    vector<T> curr_basis = {basis[pos], val};
    int c_ptr = 1;
    while (c_ptr < curr_basis.size()) {
      for (int i = 0; i < c_ptr; i++) {
        reduce_pair(curr_basis[i], curr_basis[c_ptr]);
        if (curr_basis[c_ptr] == 1)
          break;
        if (curr_basis[i] == 1)
          continue;
        T g = gcd(curr_basis[c_ptr], curr_basis[i]);
        if (g > 1) {
          curr_basis[c_ptr] /= g;
          curr_basis[i] /= g;
          curr_basis.push_back(g);
        }
      }
      ++c_ptr;
    }
    basis[pos] = curr_basis[0];
    val = curr_basis[1];
    for (int i = 2; i < curr_basis.size(); i++)
      if (curr_basis[i] > 1)
        basis.push_back(curr_basis[i]);
    if (basis[pos] == 1) {
      swap(basis[pos], basis.back());
      basis.pop_back();
    }
  }
  void add_element(T val) {
    for (int i = 0; i < basis.size(); i++) {
      reduce_pair(val, basis[i]);
      if (basis[i] == 1) {
        swap(basis[i], basis.back());
        basis.pop_back();
        continue;
      }
      if (val == 1)
        return;
      if (gcd(basis[i], val) > 1)
        solve_inner(i, val);
    }
    if (val > 1)
      basis.push_back(val);
  }
  void verify_basis() {
    for (int i = 0; i < basis.size(); i++) {
      for (int j = i + 1; j < basis.size(); j++) {
        assert(gcd(basis[i], basis[j]) == 1);
      }
    }
  }
  void verify_element(T ele) {
    for (auto &x : basis) {
      while (ele % x == 0)
        ele /= x;
    }
    assert(ele == 1);
  }
  auto factorisation(T ele) {
    vector<int> factors(basis.size());
    for (int i = 0; i < basis.size(); i++) {
      while (ele % basis[i] == 0) {
        factors[i]++;
        ele /= basis[i];
      }
    }
    return factors;
  }
};
namespace Codeforces {
namespace MostSignificantBit {
const int SIZE = 1 << 16;
uint8_t table[SIZE];
bool WasInitialized() { return table[2]; }
bool Init() {
  for (int i = 1; i < SIZE; ++i) {
    for (uint8_t pow = 0; pow < 16; ++pow) {
      if ((i >> pow) & 1) {
        table[i] = pow;
      }
    }
  }
  return true;
}
int Get(int value) {
  return WasInitialized() || Init(), table[value & (SIZE - 1)];
}
} // namespace MostSignificantBit
struct uint128_t {
  uint64_t high, low;
  uint128_t(uint64_t high_, uint64_t low_) : high(high_), low(low_) {}
  uint128_t(uint64_t low_ = 0) : high(0), low(low_) {}
};
bool operator==(uint128_t lhs, uint128_t rhs) {
  return lhs.low == rhs.low && lhs.high == rhs.high;
}
bool operator<=(uint128_t lhs, uint128_t rhs) {
  return lhs.high < rhs.high || (lhs.high == rhs.high && lhs.low <= rhs.low);
}
bool operator>=(uint128_t lhs, uint128_t rhs) { return rhs <= lhs; }
bool operator!=(uint128_t lhs, uint128_t rhs) { return !(lhs == rhs); }
bool operator<(uint128_t lhs, uint128_t rhs) { return !(lhs >= rhs); }
bool operator>(uint128_t lhs, uint128_t rhs) { return !(lhs <= rhs); }
int mostSignificantBit32(uint32_t value) {
  return (value >> 16) ? MostSignificantBit::Get(value >> 16) + 16
                       : MostSignificantBit::Get(value);
}
int mostSignificantBit64(uint64_t value) {
  return (value >> 32) ? mostSignificantBit32(uint32_t(value >> 32)) + 32
                       : mostSignificantBit32(value & ~uint32_t(0));
}
int mostSignificantBit(uint128_t value) {
  return value.high ? mostSignificantBit64(value.high) + 64
                    : mostSignificantBit64(value.low);
}
uint128_t operator+(uint128_t lhs, uint128_t rhs) {
  uint128_t ret(lhs.high + rhs.high, lhs.low + rhs.low);
  ret.high += (ret.low < lhs.low);
  return ret;
}
uint128_t operator-(uint128_t lhs, uint128_t rhs) {
  uint128_t ret(lhs.high - rhs.high, lhs.low - rhs.low);
  ret.high -= (lhs.low < ret.low);
  return ret;
}
uint128_t &operator+=(uint128_t &lhs, uint128_t rhs) { return lhs = lhs + rhs; }
uint128_t &operator-=(uint128_t &lhs, uint128_t rhs) { return lhs = lhs - rhs; }
uint128_t operator<<(uint128_t lhs, int cnt) {
  if (cnt == 0) {
    return lhs;
  }
  if (cnt >= 64) {
    return uint128_t(lhs.low << (cnt - 64), 0);
  }
  return uint128_t((lhs.high << cnt) | (lhs.low >> (64 - cnt)), lhs.low << cnt);
}
uint128_t operator>>(uint128_t lhs, int cnt) {
  if (cnt == 0) {
    return lhs;
  }
  if (cnt >= 64) {
    return uint128_t(lhs.high >> (cnt - 64));
  }
  return uint128_t(lhs.high >> cnt,
                   (lhs.low >> cnt) | (lhs.high << (64 - cnt)));
}
uint128_t &operator>>=(uint128_t &lhs, int cnt) { return lhs = lhs >> cnt; }
uint128_t &operator<<=(uint128_t &lhs, int cnt) { return lhs = lhs << cnt; }
uint128_t operator*(uint128_t lhs, uint128_t rhs) {
  uint64_t a32 = lhs.low >> 32, a00 = lhs.low & 0xffffffff;
  uint64_t b32 = rhs.low >> 32, b00 = rhs.low & 0xffffffff;
  uint128_t ret(lhs.high * rhs.low + lhs.low * rhs.high + a32 * b32, a00 * b00);
  return ret + (uint128_t(a32 * b00) << 32) + (uint128_t(a00 * b32) << 32);
}
void DivMod(uint128_t a, uint128_t b, uint128_t &q, uint128_t &r) {
  assert(b.low | b.high);
  if (a < b) {
    q = 0, r = a;
    return;
  }
  if (a == b) {
    q = 1, r = 0;
    return;
  }
  const int shift = mostSignificantBit(a) - mostSignificantBit(b);
  q = 0, r = a, b <<= shift;
  for (int i = 0; i <= shift; ++i) {
    q <<= 1;
    if (r >= b) {
      r -= b;
      q.low |= 1;
    }
    b >>= 1;
  }
}
uint128_t operator/(uint128_t lhs, uint128_t rhs) {
  uint128_t div, rem;
  return DivMod(lhs, rhs, div, rem), div;
}
uint128_t operator%(uint128_t lhs, uint128_t rhs) {
  uint128_t div, rem;
  return DivMod(lhs, rhs, div, rem), rem;
}
uint128_t &operator/=(uint128_t &lhs, uint128_t rhs) { return lhs = lhs / rhs; }
uint128_t &operator%=(uint128_t &lhs, uint128_t rhs) { return lhs = lhs % rhs; }
} // namespace Codeforces
using bigint = Codeforces::uint128_t;
istream &operator>>(istream &in, bigint &v) {
  string s;
  in >> s;
  for (auto &c : s)
    v = v * 10 + (c - '0');
  return in;
}
ostream &operator<<(ostream &out, bigint v) {
  string s;
  while (v > 0) {
    s += '0' + (v % 10).low;
    v /= 10;
  }
  reverse(s.begin(), s.end());
  out << s;
  return out;
}
void solve() {
  // Main algorithm: read two arrays, build prime basis, and greedily remove
  // elements to equalize the LCMs of the remaining parts.
  int n, m;
  cin >> n >> m;
  vector<bigint> a(n), b(m);
  cin >> a >> b;
  // Build a common prime basis from both arrays
  PrimeBasis<bigint> pb;
  for (auto &x : a)
    pb.add_element(x);
  for (auto &x : b)
    pb.add_element(x);
  // Track which elements have been marked for removal
  vector<bool> a_deleted(n), b_deleted(m);
  // Compute exponent vectors for each element over the basis primes
  vector<vector<int>> a_factors;
  vector<vector<int>> b_factors;
  for (int i = 0; i < n; i++) {
    a_factors.push_back(pb.factorisation(a[i]));
  }
  for (int j = 0; j < m; j++) {
    b_factors.push_back(pb.factorisation(b[j]));
  }
  // For each prime, create sorted lists of indices by exponent (descending)
  int num_primes = pb.basis.size();
  vector<vector<int>> ord_a(num_primes, vector<int>(n, 0));
  vector<vector<int>> ord_b(num_primes, vector<int>(m, 0));
  for (int i = 0; i < num_primes; i++) {
    iota(ord_a[i].begin(), ord_a[i].end(), 0);
    iota(ord_b[i].begin(), ord_b[i].end(), 0);
    sort(ord_a[i].begin(), ord_a[i].end(),
         [&](int x, int y) { return a_factors[x][i] > a_factors[y][i]; });
    sort(ord_b[i].begin(), ord_b[i].end(),
         [&](int x, int y) { return b_factors[x][i] > b_factors[y][i]; });
  }
  // Maintain current pointer (next candidate) for each prime in each array
  vector<vector<int>::iterator> a_ptr(num_primes), b_ptr(num_primes);
  for (int i = 0; i < num_primes; i++) {
    a_ptr[i] = ord_a[i].begin();
    b_ptr[i] = ord_b[i].begin();
  }
  // Initialize: find primes where max exponent differs between arrays
  vector<int> upd;
  for (int i = 0; i < num_primes; i++) {
    if (a_factors[ord_a[i][0]][i] != b_factors[ord_b[i][0]][i]) {
      upd.push_back(i);
    }
  }
  // Greedy removal loop: process each prime with an imbalance
  auto add_to_upd_a = [&](int pos) {
    for (int i = 0; i < num_primes; i++) {
      if (a_factors[pos][i] > 0)
        upd.push_back(i);
    }
  };
  auto add_to_upd_b = [&](int pos) {
    for (int i = 0; i < num_primes; i++) {
      if (b_factors[pos][i] > 0)
        upd.push_back(i);
    }
  };
  while (upd.size() > 0) {
    int x = upd.back();
    upd.pop_back();
    // Skip already-deleted elements to find the next active candidate
    while (a_ptr[x] != ord_a[x].end() && a_deleted[*a_ptr[x]]) {
      a_ptr[x]++;
    }
    while (b_ptr[x] != ord_b[x].end() && b_deleted[*b_ptr[x]]) {
      b_ptr[x]++;
    }
    // If one array is exhausted, no valid solution exists
    if (a_ptr[x] == ord_a[x].end() || b_ptr[x] == ord_b[x].end()) {
      cout << "NO\n";
      return;
    }
    // Greedily remove the element with lower exponent of prime x
    if (a_factors[*a_ptr[x]][x] < b_factors[*b_ptr[x]][x]) {
      add_to_upd_b(*b_ptr[x]);
      b_deleted[*b_ptr[x]] = 1;
    }
    if (a_factors[*a_ptr[x]][x] > b_factors[*b_ptr[x]][x]) {
      add_to_upd_a(*a_ptr[x]);
      a_deleted[*a_ptr[x]] = 1;
    }
  }
  // Output the retained elements and their count
  cout << "YES\n";
  cout << n - accumulate(a_deleted.begin(), a_deleted.end(), 0) << " "
       << m - accumulate(b_deleted.begin(), b_deleted.end(), 0) << "\n";
  for (int i = 0; i < n; i++) {
    if (!a_deleted[i]) {
      cout << a[i] << " ";
    }
  }
  cout << "\n";
  for (int j = 0; j < m; j++) {
    if (!b_deleted[j]) {
      cout << b[j] << " ";
    }
  }
  cout << "\n";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}

// https://github.com/VaHiX/CodeForces/