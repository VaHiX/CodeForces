// Problem: CF 1878 E - Iva & Pav
// https://codeforces.com/contest/1878/problem/E

/*
Algorithm: Sparse Table + Binary Search
Purpose: For each query (l, k), find the largest index r such that bitwise AND of elements from l to r is >= k.
Time Complexity: O((n + q) * log n) per test case
Space Complexity: O(n * log n) per test case

Sparse Table is used to preprocess the array to answer range AND queries efficiently in O(1).
Then for each query, binary search is performed on the possible values of r to find the maximum valid r.
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>

namespace fastio {
class input;
class output;
}  // namespace fastio

#define cin in
#define cout out
using namespace std;
namespace fastio {
class input {
public:
  enum states { eof = 0, good = 1 } state;
  char buf[1 << 20], *p, *q;
  const int mxsz = 1 << 20;
  input() : p(buf), q(buf), state(good) {}
  inline char getc() {
    if (p == q) {
      p = buf;
      q = buf + fread(buf, 1, mxsz, stdin);
      if (p == q)
        return -1;
    }
    return *p++;
  }
  inline void readchar(char &c) { c = getc(); }
  template <class T> inline input &read(T &x) {
    static char c;
    for (readchar(c); (!isdigit(c)) && c != '-' && c != EOF; readchar(c)) {
    }
    if (c == '-') {
      x = 0;
      for (readchar(c); isdigit(c); readchar(c)) {
        x += x + (x << 3);
        x -= (c ^ 48);
      }
    } else if (c != EOF) {
      x = 0;
      for (; isdigit(c); readchar(c)) {
        x += x + (x << 3);
        x += (c ^ 48);
      }
    } else if (c == EOF) {
      (this)->state = eof;
    }
    return (*this);
  }
  inline input &operator>>(char &c) {
    for (readchar(c); isspace(c); readchar(c)) {
    }
    if (c == EOF) {
      (this)->state = eof;
    }
    return (*this);
  }
  inline input &operator>>(string &str) {
    static char c;
    static char buff[1 << 8];
    static int bsz;
    bsz = 0;
    const int mx = 1 << 8;
    for (readchar(c); c == ' ' || c == '\n'; readchar(c)) {
    }
    for (str.erase(); (!isspace(c)) && c != EOF; readchar(c)) {
      if (bsz == mx) {
        str.append(buff, mx);
        bsz = 0;
      }
      buff[bsz++] = c;
    }
    str.append(buff, bsz);
    if (c == EOF) {
      (this)->state = eof;
    }
    return (*this);
  }
  inline input &operator>>(unsigned long long &x) { return read(x); }
  inline input &operator>>(long long &x) { return read(x); }
  inline input &operator>>(unsigned int &x) { return read(x); }
  inline input &operator>>(int &x) { return read(x); }
  inline input &operator>>(unsigned short &x) { return read(x); }
  inline input &operator>>(short &x) { return read(x); }
  explicit inline operator bool() const { return state; }
};
class output {
public:
  char buf[1 << 20], numbuf[32];
  const int mxsz = 1 << 20;
  int size;
  output() : size(0) {}
  ~output() { flush(); }
  inline void flush() {
    if (!size)
      return;
    fwrite(buf, 1, size, stdout);
    size = 0;
  }
  inline void writechar(const char &c) {
    if (size == mxsz)
      flush();
    buf[size++] = c;
  }
  template <class T> inline output &write(T x) {
    static int sz;
    static bool neg;
    neg = false;
    sz = 0;
    if (x <= 0) {
      numbuf[sz++] = (-(x % 10)) ^ 48;
      if (x)
        neg = true;
      x = -(x / 10);
    }
    for (; x; x /= 10) {
      numbuf[sz++] = (x % 10) ^ 48;
    }
    if (neg)
      writechar('-');
    for (; sz--;) {
      writechar(numbuf[sz]);
    }
    return (*this);
  }
  inline output &operator<<(const unsigned long long &x) { return write(x); }
  inline output &operator<<(const long long &x) { return write(x); }
  inline output &operator<<(const unsigned int &x) { return write(x); }
  inline output &operator<<(const int &x) { return write(x); }
  inline output &operator<<(const unsigned short &x) { return write(x); }
  inline output &operator<<(const short &x) { return write(x); }
  inline output &operator<<(const char &c) {
    writechar(c);
    return (*this);
  }
  inline output &operator<<(const string &s) {
    if (mxsz - size <= s.length())
      flush();
    copy(s.begin(), s.end(), buf + size);
    size += s.length();
    return (*this);
  }
  inline output &operator<<(const char *s) { return (*this) << string(s); }
};
}; // namespace fastio
using namespace fastio;
input in;
output out;
template <typename T> struct sparse_table {
  int n, lgn;
  vector<vector<T>> table;
  sparse_table() : n(0), lgn(-1) {}
  ~sparse_table() {}
  inline int &operator[](const int &pos) { return table[0][pos]; }
  inline void resize(const int &_n) {
    n = _n;
    lgn = __lg(_n);
    table.assign(__lg(_n) + 1, vector<T>(_n, 0));
  }
  inline void build() {
    for (int i = 0; i < n; i++) {
      cin >> table[0][i];
    }
    for (int i = 1; i <= lgn; i++) {
      for (int j = 0; j + (1 << (i - 1)) < n; j++) {
        table[i][j] = table[i - 1][j] & table[i - 1][j + (1 << (i - 1))];
      }
    }
  }
  inline T query(const int &l, const int &r) {
    int lglen = __lg(r - l);
    return table[lglen][l] & table[lglen][r - (1 << lglen)];
  }
};
sparse_table<int> ST;
inline void solve() {
  static int n, q, l, ll, k, rr, mid;
  cin >> n;
  ST.resize(n);
  ST.build();
  cin >> q;
  while (q--) {
    cin >> l >> k;
    --l;
    if (ST[l] < k) {
      cout << -1 << " \n"[q == 0];
      continue;
    } else {
      ll = l, rr = n;
      while (ll < rr - 1) {
        mid = (ll + rr) >> 1;
        if (ST.query(l, mid + 1) >= k)
          ll = mid;
        else
          rr = mid;
      }
      cout << ++ll << " \n"[q == 0];
    }
  }
}
int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/