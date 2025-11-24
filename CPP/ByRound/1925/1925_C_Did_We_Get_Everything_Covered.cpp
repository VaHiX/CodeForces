// Problem: CF 1925 C - Did We Get Everything Covered?
// https://codeforces.com/contest/1925/problem/C

/*
Algorithm: Greedy approach to check if all subsequences of length n from first k
letters are present Time Complexity: O(n * m) where n is length of string to
form, m is length of input string s Space Complexity: O(k) for tracking which
characters are seen

The algorithm works by scanning the input string s and trying to form a string
of length n by taking one character from each group of k consecutive characters
that contain all k letters. If we cannot form such a string, we construct the
lexicographically smallest missing string.

Approach:
1. For each group of k characters that form a complete set of first k letters,
we take one character
2. If we complete n such groups, the answer is YES
3. Otherwise, we build the lexicographically smallest string not seen (missing
first character not yet included)
*/

#include <algorithm>
#include <array>
#include <ctype.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <math.h>
#include <random>
#include <set>
#include <shared_mutex>
#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

using namespace std;
using ll = long long;

char buf[100000], *bufs, *buft;
#define gc()                                                                   \
  ((bufs == buft && (buft = (bufs = buf) + fread(buf, 1, 100000, stdin))),     \
   bufs == buft ? -1 : *bufs++)
template <typename T> inline void read(T &x) {
  x = 0;
  bool f = 0;
  char ch = gc();
  while (!isdigit(ch))
    f = ch == '-', ch = gc();
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = gc();
  if (f)
    x = -x;
}
inline void reads(char *s) {
  char ch = gc();
  while (isspace(ch))
    ch = gc();
  while (!isspace(ch) && ch != EOF)
    *(s++) = ch, ch = gc();
  *s = 0;
  return;
}
template <typename T, typename... Arg> inline void read(T &x, Arg &...y) {
  read(x);
  read(y...);
}
#define O(x) cerr << #x << " : " << x << '\n'
const double Pi = acos(-1);
const int MAXN = 1 << 18, MOD = 998244353, inv2 = (MOD + 1) / 2,
          I32_INF = 0x3f3f3f3f;
const long long I64_INF = 0x3f3f3f3f3f3f3f3f;
inline int Ksm(int x, int y) {
  if (y < 0) {
    y %= MOD - 1;
    y += MOD - 1;
  }
  int ret = 1;
  for (; y; y /= 2, x = (long long)x * x % MOD)
    if (y & 1)
      ret = (long long)ret * x % MOD;
  return ret;
}
inline int Mod(int x) {
  if (x >= MOD)
    return x - MOD;
  else if (x < 0)
    return x + MOD;
  else
    return x;
}
template <const int N_num, const int M_num> struct no_w_Graph {
  int H[N_num];
  struct Edge {
    int to, lac;
  } e[M_num];
  inline void add_edge(int x, int y) {
    e[*H] = {y, H[x]};
    H[x] = (*H)++;
  }
  inline void init() {
    memset(H, -1, sizeof H);
    *H = 0;
  }
};
template <const int N_num, const int M_num> struct w_Graph {
  int H[N_num];
  struct Edge {
    int to, lac, w;
  } e[M_num];
  inline void add_edge(int x, int y, int z) {
    e[*H] = {y, H[x], z};
    H[x] = (*H)++;
  }
  inline void init() {
    memset(H, -1, sizeof H);
    *H = 0;
  }
};
#define go(x, y) for (int i = x.H[y], v; (v = x.e[i].to) && ~i; i = x.e[i].lac)
inline int ls(int k) { return k << 1; }
inline int rs(int k) { return k << 1 | 1; }
using ull = unsigned long long;
void add(int &x, int y) {
  if ((x += y) >= MOD)
    x -= MOD;
}
int T;
char s[MAXN], ans[MAXN];
int main() {
  read(T);
  auto sol = [&]() -> void {
    int N, K, M, ct = 0;
    read(N, K, M);
    reads(s);
    std::string res;
    vector<int> flg(
        K, 0); // Track which characters from first K letters we've seen
    for (int i = 0; i < M && res.size() < N; ++i)
      if (!flg[s[i] - 'a']) {
        flg[s[i] - 'a'] = 1;
        if (++ct == K) { // Found a complete set of K characters
          ct = 0;
          for (auto &j : flg)
            j = 0;     // Reset for next group
          res += s[i]; // Add one char to final result
        }
      }
    if (res.size() == N) // If we could form complete string of length N
      puts("YES");
    else { // If we couldn't, construct the answer
      for (int i = 0; i < K; ++i)
        if (!flg[i]) { // Find first missing character
          while (res.size() < N)
            res +=
                i + 'a'; // Fill with this character to make string of length N
          break;
        }
      printf("NO\n%s\n", res.data()); // Print result
    }
  };
  while (T--)
    sol();
  cerr << ((double)clock() / CLOCKS_PER_SEC) << '\n';
  return (0 - 0);
}

// https://github.com/VaHiX/CodeForces/