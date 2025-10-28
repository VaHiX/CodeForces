// Problem: CF 2059 E2 - Stop Gaming (Hard Version)
// https://codeforces.com/contest/2059/problem/E2

/*
 * Problem: E2. Stop Gaming (Hard Version)
 * Purpose: Given n arrays of size m each, transform the original arrays a into final arrays b using minimum operations.
 *          Each operation inserts an element at the beginning of an array and shifts all elements in that and subsequent arrays.
 *
 * Algorithms/Techniques:
 *   - Greedy simulation with deque to track operations
 *   - For each row, compare a[i] and b[i], and simulate what needs to be done
 *   - Simulate the shift operations backwards by maintaining insertion order

 * Time Complexity: O(n * m)
 * Space Complexity: O(n * m)

 * Each test case processes n*m elements linearly in time.
 * The deque operations are amortized O(1) per element, leading to overall linear complexity.
 */

#include <algorithm>
#include <array>
#include <ctype.h>
#include <deque>
#include <iterator>
#include <stdio.h>
#include <vector>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
namespace qGet {
const int sz = 1 << 18;
char buf[sz], *S, *T;
inline char gc() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, sz, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
struct Rd {
  Rd &operator>>(int &x) {
    x = 0;
    char c = gc();
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = gc();
    return *this;
  }
} cin;
} // namespace qGet
namespace qPut {
const int sz = 1 << 18;
char buf[sz], *S = buf, *T = buf + sz;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void pc(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct Exi {
  ~Exi() { flush(); }
} exi;
struct Wt {
  Wt &operator<<(int x) {
    if (!x) {
      pc('0');
      return *this;
    }
    static int sta[6];
    int top = 0;
    while (x) {
      sta[top++] = x % 10;
      x /= 10;
    }
    while (top)
      pc('0' + sta[--top]);
    return *this;
  }
  Wt &operator<<(char c) {
    pc(c);
    return *this;
  }
} cout;
} // namespace qPut
#define cin qGet::cin
#define cout qPut::cout
#define rsz resize
#define pb push_back
#define vi vector<int>
#define mmi make_move_iterator
int main() {
  int t;
  cin >> t;
  vi a, b;
  while (t--) {
    int n, m;
    cin >> n >> m;
    a.rsz(n * m);
    for (int &x : a)
      cin >> x;
    b.rsz(n * m);
    for (int &x : b)
      cin >> x;
    int res = 0;
    deque<array<int, 2>> ord; // stores operations: {array_index, element_value}
    for (int r = 0; r < n; r++) {
      int rm = r * m, r1m = rm + m, j = rm, i = j - res, pos = 0;
      deque<array<int, 2>> tmp; // temporary deque to collect operations for this row
      while (i < rm && j < r1m) {
        if (a[i] != b[j]) {
          tmp.pb({r + 1, b[j++]});
          res++;
        } else {
          tmp.pb(ord.front());
          ord.pop_front();
          j++;
          i++;
        }
      }
      while (j < r1m && a[i] != b[j]) {
        tmp.pb({r + 1, b[j++]});
        res++;
      }
      int cnt = 0;
      while (j < r1m && a[i] == b[j]) {
        j++;
        i++;
        cnt++;
      }
      if (j < r1m) {
        j -= cnt;
        while (j < r1m) {
          tmp.pb({r + 1, b[j++]});
          res++;
        }
      }
      if (!tmp.empty())
        ord.insert(ord.begin(), mmi(tmp.begin()), mmi(tmp.end())); // update operations in reverse order
    }
    cout << res << '\n';
    for (int i = --res; i >= 0; i--) // output results in reverse to get correct chronological order
      cout << ord[i][0] << ' ' << ord[i][1] << '\n';
  }
}


// https://github.com/VaHiX/codeForces/