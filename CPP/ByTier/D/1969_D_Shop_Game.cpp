// Problem: CF 1969 D - Shop Game
// https://codeforces.com/contest/1969/problem/D

/*
 * Problem: D. Shop Game
 * 
 * Purpose: Alice and Bob play a game where Alice chooses items to buy and Bob decides which items
 *          he takes for free and which he pays for. Alice wants to maximize her profit while Bob
 *          wants to minimize it.
 * 
 * Algorithm: 
 * 1. For each item, compute the difference (b_i - a_i) which represents Alice's gain if she sells it.
 * 2. Filter items where b_i > a_i (Alice gains from selling).
 * 3. Sort these items by b_i in ascending order using a greedy approach.
 * 4. Use a multiset to maintain the current set of items Alice has bought.
 * 5. Try all possible subsets by greedily removing the least beneficial item and adding a new one.
 * 
 * Time Complexity: O(n log n) for each test case due to sorting and multiset operations.
 * Space Complexity: O(n) for storing the items and the multiset.
 */

#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <set>
#include <utility>

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
int n, k, cb, cc;
struct node {
  int x, y;
} a[N], c[N];
multiset<pair<int, int>> s;
bool cmpx(node a, node b) { return a.x < b.x; }
bool cmpy(node a, node b) { return a.y < b.y; }
void Solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++)
    cin >> a[i].x;
  for (int i = 1; i <= n; i++)
    cin >> a[i].y;
  s.clear();
  cb = cc = 0;
  for (int i = 1; i <= n; i++)
    if (a[i].y > a[i].x)
      c[++cc] = a[i];
  sort(c + 1, c + cc + 1, cmpy);
  int ans = 0;
  while (k && cc)
    s.insert(make_pair(c[cc].x, c[cc].y)), ans -= c[cc--].x, k--;
  for (int i = 1; i <= cc; i++)
    ans += c[i].y - c[i].x;
  int res = ans;
  while (s.size()) {
    pair<int, int> bg = *s.rbegin();
    node nwb = (node){bg.first, bg.second};
    node nwc = (cc > 0 ? c[cc] : (node){0, 0});
    res += nwb.x, res -= nwc.y;
    ans = max(res, ans);
    cc--, s.erase(--s.end());
    if (nwc.x != 0)
      s.insert(make_pair(nwc.x, nwc.y));
  }
  cout << ans << endl;
}
signed main() {
  int Test = 1;
  cin >> Test;
  while (Test--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/