// Problem: CF 1969 E - Unique Array
// https://codeforces.com/contest/1969/problem/E

/*
Algorithm: 
This solution uses a sliding window approach with a stack-like structure to track segments of the array where subarrays can be made unique with minimal operations. 
It identifies overlapping intervals and marks necessary changes to ensure all subarrays are unique.

Time Complexity: O(n) amortized due to stack-like operations and single pass through the array.
Space Complexity: O(n) for storing arrays and auxiliary structures.

*/
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
namespace qGet {
const int SZ = 1 << 16;
char buf[SZ], *S, *T;
inline char gc() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SZ, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
struct Rdr {
  Rdr &operator>>(int &x) {
    x = 0;
    char c = gc();
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = gc();
    return *this;
  }
} cin;
} // namespace qGet
namespace qPut {
const int SZ = 1 << 10;
char buf[SZ], *S = buf, *T = buf + SZ;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void pc(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
struct Wtr {
  Wtr &operator<<(int x) {
    if (!x) {
      pc('0');
      pc('\n');
      return *this;
    }
    static int sta[8];
    int top = 0;
    while (x) {
      sta[++top] = x % 10;
      x /= 10;
    }
    while (top) {
      pc(sta[top] + '0');
      --top;
    }
    pc('\n');
    return *this;
  }
} cout;
} // namespace qPut
#define cin qGet ::cin
#define cout qPut ::cout
#define f first
#define s second
#define eb emplace_back
#define fore(i, a, b) for (int i = a; i <= b; i++)
void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1), p(n + 1), left(n + 1), right(n + 1, n + 1);
  fore(i, 1, n) {
    cin >> a[i];
    int &j = p[a[i]]; // p[a[i]] tracks last index of value a[i]
    left[i] = j;       // left[i] = index of previous occurrence of a[i]
    right[j] = i;      // right[j] = earliest index after j where a[i] appears again
    j = i;             // update p[a[i]] to current index
  }
  vector<pair<int, int>> v; // stack of intervals [start, end]
  v.reserve(n);
  v.eb(0, n + 1); // initial interval
  int res = 0;    // number of operations needed
  fore(i, 1, n) {
    // Remove intervals from back that don't contain current element
    while (v.back().s <= i)
      v.pop_back();
    // If current element's left conflict with our current stack interval,
    // we must start a new operation (interval)
    if (left[i] > v.back().f) {
      v = {{i, n + 1}}; // reset interval to current position
      res++;            // increment number of operations
      continue;
    }
    // Remove any inner intervals that are no longer valid
    // due to current element’s conflict with them
    while (v.size() > 1 && left[i] <= v.rbegin()[1].f && right[i] >= v.back().s)
      v.pop_back();
    // Insert new interval for current element
    v.eb(i, min(right[i], v.back().s));
  }
  cout << res;
}
int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/