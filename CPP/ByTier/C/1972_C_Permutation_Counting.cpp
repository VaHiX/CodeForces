// Problem: CF 1972 C - Permutation Counting
// https://codeforces.com/contest/1972/problem/C

/*
Algorithm: Greedy + Sorting + Simulation
Time Complexity: O(n log n) - due to sorting
Space Complexity: O(n) - for storing array and stack

This problem involves maximizing the number of permutations of [1,2,...,n] 
in contiguous subarrays of length n, by optimally distributing k additional coins 
among n types of cards.

Approach:
1. Sort the given card counts in descending order.
2. Use a greedy method to determine how many cards of each type we can get
   by spending the available coins.
3. Simulate the process of distributing coins to maximize the number of
   valid permutations.

We maintain a stack to simulate the greedy process.
The key insight is to find the optimal balance of card types such that we
maximize the number of length-n contiguous subarrays that form a permutation.

*/
#include <stdio.h>
#include <algorithm>

using namespace std;
namespace Fread {
const int SIZE = 1 << 21;
char buf[SIZE], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SIZE, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 21;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void putchar(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
} // namespace Fwrite
#ifdef ONLINE_JUDGE
#define getchar Fread ::getchar
#define putchar Fwrite ::putchar
#endif
namespace Fastio {
struct Reader {
  template <typename T> Reader &operator>>(T &x) {
    char c = getchar();
    T f = 1;
    while (c < '0' || c > '9') {
      if (c == '-')
        f = -1;
      c = getchar();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
      x = x * 10 + (c - '0');
      c = getchar();
    }
    x *= f;
    return *this;
  }
  Reader &operator>>(char &c) {
    c = getchar();
    while (c == ' ' || c == '\n')
      c = getchar();
    return *this;
  }
  Reader &operator>>(char *str) {
    int len = 0;
    char c = getchar();
    while (c == ' ' || c == '\n')
      c = getchar();
    while (c != ' ' && c != '\n' && c != '\r') {
      str[len++] = c;
      c = getchar();
    }
    str[len] = '\0';
    return *this;
  }
  Reader() {}
} cin;
const char endl = '\n';
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    if (x == 0) {
      putchar('0');
      return *this;
    }
    if (x < 0) {
      putchar('-');
      x = -x;
    }
    static int sta[45];
    int top = 0;
    while (x) {
      sta[++top] = x % 10;
      x /= 10;
    }
    while (top) {
      putchar(sta[top] + '0');
      --top;
    }
    return *this;
  }
  Writer &operator<<(char c) {
    putchar(c);
    return *this;
  }
  Writer &operator<<(char *str) {
    int cur = 0;
    while (str[cur])
      putchar(str[cur++]);
    return *this;
  }
  Writer &operator<<(const char *str) {
    int cur = 0;
    while (str[cur])
      putchar(str[cur++]);
    return *this;
  }
  Writer() {}
} cout;
} // namespace Fastio
#define cin Fastio ::cin
#define cout Fastio ::cout
#define endl Fastio ::endl
#define int long long
const int N = 5e5 + 5;
const int mod = 998244353;
int n, k, a[N];
int stk[N], top;
void Solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  sort(a + 1, a + n + 1);
  top = 0;
  for (int i = n; i; i--)
    stk[++top] = a[i];
  int cnt = 0, lst = 0;
  while (top) {
    int d = stk[top] - lst;
    if (k < cnt * d)
      break; // if we can't afford this step, break
    k -= cnt * d, lst = stk[top]; // spend coins, update state
    while (top && stk[top] == lst) // count all cards of same type
      top--, cnt++;
  }
  lst += k / cnt, cnt -= k % cnt; // finalize the last distribution
  cout << lst * n - cnt + 1 << endl; // output result
}
signed main() {
  int Test = 1;
  cin >> Test;
  while (Test--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/