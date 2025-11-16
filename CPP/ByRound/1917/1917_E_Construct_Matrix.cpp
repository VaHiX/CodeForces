// Problem: CF 1917 E - Construct Matrix
// https://codeforces.com/contest/1917/problem/E

/*
Problem: Construct Matrix
Algorithm/Technique: Greedy construction with bit manipulation and symmetry
Time Complexity: O(n^2) per test case
Space Complexity: O(n^2) for the matrix storage

This solution constructs a binary matrix of size n x n such that:
1. The total sum of matrix elements equals k
2. Each row has the same XOR value
3. Each column has the same XOR value

The key insight is that for a valid construction:
- If k is odd, it's impossible (since each row/column XOR must be 0 or 1, and their sum is even due to symmetry)
- We can greedily place 1s in blocks of 4 to maintain equal row/column XORs
- Special handling for edge cases (e.g., n=2, k=2, k=n*n-2)
- If k > n*n/2, we can mirror the solution by flipping all bits
*/

#include <ctype.h>
#include <stdio.h>
#include <bitset>

#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
namespace Fread {
const int SZ = 1 << 8;
char buf[SZ], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SZ, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SZ = 1 << 18;
char buf[SZ], *S = buf, *T = buf + SZ;
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
#define getchar Fread ::getchar
#define putchar Fwrite ::putchar
namespace Fast {
struct Reader {
  template <typename T> Reader &operator>>(T &x) {
    char c = getchar();
    while (!isdigit(c))
      c = getchar();
    x = 0;
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = getchar();
    return *this;
  }
} cin;
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    x ? putchar('1') : putchar('0');
    return *this;
  }
  Writer &operator<<(const char *str) {
    int cur = 0;
    while (str[cur])
      putchar(str[cur++]);
    return *this;
  }
} cout;
} // namespace Fast
#define cin Fast ::cin
#define cout Fast ::cout
#define fore(i, a, b) for (int i = a; i <= b; i++)
const int N = 1e3 + 1;
int t;
bitset<N> a[N];
void ok() {
  int n, k, f = 0;
  cin >> n >> k;
  if (k & 1 || (k == 2 || k == n * n - 2) && n > 2) {
    cout << "No\n";
    return;
  }
  if (k > n * n / 2)
    f = 1, k = n * n - k;
  if (k == 2 && n == 2)
    fore(i, 1, 2) a[i][i] = 1;
  else {
    if ((k >> 1) & 1)
      a[n - 2][n - 2] = 1, a[n - 2][n - 1] = 1, a[n - 1][n - 2] = 1,
                   a[n - 1][n] = 1, a[n][n - 1] = 1, a[n][n] = 1, k -= 6;
    for (int i = 1; i <= n - 1 && k; i += 2)
      for (int j = 1; j <= n - 1 && k; j += 2)
        fore(i2, 0, 1) fore(j2, 0, 1) a[i + i2][j + j2] = 1, k--;
  }
  cout << "Yes\n";
  if (f)
    fore(i, 1, n) {
      fore(j, 1, n) cout << (a[i][j] ^ 1) << " ";
      cout << "\n";
    }
  else
    fore(i, 1, n) {
      fore(j, 1, n) cout << a[i][j] << " ";
      cout << "\n";
    }
  if (t)
    fore(i, 1, n) fore(j, 1, n) a[i].reset(j);
}
int main() {
  cin >> t;
  while (t--)
    ok();
}


// https://github.com/VaHiX/CodeForces/