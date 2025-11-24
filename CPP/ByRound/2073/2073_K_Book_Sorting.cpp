// Problem: CF 2073 K - Book Sorting
// https://codeforces.com/contest/2073/problem/K

/*
Algorithm: Segment Tree with Lazy Propagation
Time Complexity: O(N * log N)
Space Complexity: O(N)

This problem involves finding the minimum number of operations to sort books on a shelf,
where each operation is either swapping adjacent books, moving a book to the leftmost,
or moving a book to the rightmost position.

The approach uses segment trees to efficiently track and update the positions of books.
We iterate through each position and try to minimize the number of moves needed to sort
the books, using the segment tree data structures to quickly find the minimum number of
steps required at each point.

The solution works by considering the current position of each book and computing the
minimum number of operations needed to place them correctly using segment trees for
efficient range queries and updates.
*/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <climits>

using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
#define all(p) p.begin(), p.end()
template <class T> bool chmin(T &a, const T b) {
  return a > b && (a = b, true);
}
const ll INF = LLONG_MAX / 4;
#include <limits.h>
#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
#include <iostream>
#ifdef _MSC_VER
#include <intrin.h>
#endif
#if __cplusplus >= 202002L
#include <bit>
#endif
namespace atcoder {
namespace internal {
#if __cplusplus >= 202002L
using std::bit_ceil;
#else
unsigned int bit_ceil(unsigned int n) {
  unsigned int x = 1;
  while (x < (unsigned int)(n))
    x *= 2;
  return x;
}
#endif
int countr_zero(unsigned int n) {
#ifdef _MSC_VER
  unsigned long index;
  _BitScanForward(&index, n);
  return index;
#else
  return __builtin_ctz(n);
#endif
}
constexpr int countr_zero_constexpr(unsigned int n) {
  int x = 0;
  while (!(n & (1 << x)))
    x++;
  return x;
}
} // namespace internal
} // namespace atcoder
namespace atcoder {
#if __cplusplus >= 201703L
template <class S, auto op, auto e> struct segtree {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");
#else
template <class S, S (*op)(S, S), S (*e)()> struct segtree {
#endif
public:
  segtree() : segtree(0) {}
  explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
  explicit segtree(const std::vector<S> &v) : _n(int(v.size())) {
    size = (int)internal::bit_ceil((unsigned int)(_n));
    log = internal::countr_zero((unsigned int)size);
    d = std::vector<S>(2 * size, e());
    for (int i = 0; i < _n; i++)
      d[size + i] = v[i];
    for (int i = size - 1; i >= 1; i--) {
      update(i);
    }
  }
  void set(int p, S x) {
    assert(0 <= p && p < _n);
    p += size;
    d[p] = x;
    for (int i = 1; i <= log; i++)
      update(p >> i);
  }
  S get(int p) const {
    assert(0 <= p && p < _n);
    return d[p + size];
  }
  S prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= _n);
    S sml = e(), smr = e();
    l += size;
    r += size;
    while (l < r) {
      if (l & 1)
        sml = op(sml, d[l++]);
      if (r & 1)
        smr = op(d[--r], smr);
      l >>= 1;
      r >>= 1;
    }
    return op(sml, smr);
  }
  S all_prod() const { return d[1]; }
  template <bool (*f)(S)> int max_right(int l) const {
    return max_right(l, [](S x) { return f(x); });
  }
  template <class F> int max_right(int l, F f) const {
    assert(0 <= l && l <= _n);
    assert(f(e()));
    if (l == _n)
      return _n;
    l += size;
    S sm = e();
    do {
      while (l % 2 == 0)
        l >>= 1;
      if (!f(op(sm, d[l]))) {
        while (l < size) {
          l = (2 * l);
          if (f(op(sm, d[l]))) {
            sm = op(sm, d[l]);
            l++;
          }
        }
        return l - size;
      }
      sm = op(sm, d[l]);
      l++;
    } while ((l & -l) != l);
    return _n;
  }
  template <bool (*f)(S)> int min_left(int r) const {
    return min_left(r, [](S x) { return f(x); });
  }
  template <class F> int min_left(int r, F f) const {
    assert(0 <= r && r <= _n);
    assert(f(e()));
    if (r == 0)
      return 0;
    r += size;
    S sm = e();
    do {
      r--;
      while (r > 1 && (r % 2))
        r >>= 1;
      if (!f(op(d[r], sm))) {
        while (r < size) {
          r = (2 * r + 1);
          if (f(op(d[r], sm))) {
            sm = op(d[r], sm);
            r--;
          }
        }
        return r + 1 - size;
      }
      sm = op(d[r], sm);
    } while ((r & -r) != r);
    return 0;
  }

private:
  int _n, size, log;
  std::vector<S> d;
  void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};
} // namespace atcoder
bool op(bool a, bool b) { return a | b; }
bool e() { return false; }
bool no(bool x) { return !x; }
int op2(int a, int b) { return max(a, b); }
int e2() { return -1; }
int target;
bool f(int a) { return a <= target; }
void solve();
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  rep(i, 0, t) solve();
}
void solve() {
  int N;
  cin >> N;
  vector<int> p(N);
  rep(i, 0, N) {
    int a;
    cin >> a;
    p[a - 1] = i; // p[i] stores the original position of book labeled (i+1)
  }
  int ans = N; // Initialize with maximum possible moves (each book needs to be moved)
  atcoder::segtree<bool, op, e> seg(N);  // Segment tree to track which positions are occupied
  atcoder::segtree<int, op2, e2> segp(p); // Segment tree to track positions efficiently
  int sum = N; // Current number of operations
  rep(i, 0, N) {
    seg.set(i, true); // Mark position i as occupied
    sum--; // Decrement count as we're using one move
    int r = i; // Current position being considered
    target = p[i]; // Target position for book at position i
    while (r) {
      r = segp.min_left<f>(r); // Find minimum position where condition f is satisfied
      int a = seg.min_left<no>(r); // Find minimum position where segment is false
      if (a == 0) // If we cannot move further left
        break;
      a--; // Adjust for 0 indexing
      r--; // Adjust for 0 indexing
      seg.set(a, false); // Mark position a as unoccupied
      sum++; // Increment count as we add a move
    }
    ans = min(ans, sum); // Update minimum moves
  }
  cout << ans << "\n";
}


// https://github.com/VaHiX/CodeForces/