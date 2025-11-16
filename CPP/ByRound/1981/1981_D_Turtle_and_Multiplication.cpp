// Problem: CF 1981 D - Turtle and Multiplication
// https://codeforces.com/contest/1981/problem/D

/*
    Problem: Turtle and Multiplication
    Algorithm: Construct a sequence with minimum distinct elements such that all adjacent products are unique.
    Approach:
        1. Generate primes up to 1e6 using Sieve of Eratosthenes.
        2. For a sequence of length n, determine the minimum number of distinct primes needed.
        3. Use a greedy strategy to assign primes such that no two consecutive products are equal.
        4. Maintain a graph-like structure to track used pairs and avoid duplicate products.

    Time Complexity: O(n * sqrt(max_n)) due to prime sieve + O(n) for construction
    Space Complexity: O(n^2) for the mp array to track product pairs
*/

#include <stdio.h>
#include <bitset>

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
const int N = 1e6 + 5;
const int mod = 998244353;
int pr[N], cnt;
bitset<N> isp;
void init(int n) {
  isp[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isp[i])
      pr[++cnt] = i;
    for (int j = 1; j <= cnt && i * pr[j] <= n; j++) {
      isp[i * pr[j]] = 1;
      if (i % pr[j] == 0)
        break;
    }
  }
}
int calc(int x) {
  if (x & 1)
    return x * (x + 1) / 2;
  return x * x / 2 + 1;
}
int mp[2005][2005], head[N];
void Solve() {
  int n;
  cin >> n;
  int m = 1;
  while (calc(m) < n - 1)
    m++;
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= m; j++)
      mp[i][j] = 0;
  for (int i = 1; i <= m; i++)
    head[i] = i;
  cout << 2 << ' ';
  int pos = 1;
  for (int i = 2; i <= n; i++) {
    while (head[pos] <= m && mp[pos][head[pos]])
      head[pos]++;
    if (head[pos] > m)
      head[pos] = 1;
    while (head[pos] <= m && mp[pos][head[pos]])
      head[pos]++;
    mp[pos][head[pos]] = mp[head[pos]][pos] = 1;
    cout << pr[pos = head[pos]] << ' ';
  }
  cout << endl;
}
signed main() {
  init(1e6);
  int Test = 1;
  cin >> Test;
  while (Test--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/