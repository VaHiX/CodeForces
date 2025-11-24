// Problem: CF 1974 F - Cutting Game
// https://codeforces.com/contest/1974/problem/F

/*
 * Purpose: Solve the Cutting Game problem where Alice and Bob take turns cutting rows/columns from a grid,
 *          scoring points based on chips in the cut portion. The game involves maintaining chip positions
 *          and efficiently tracking how many chips each player scores.
 *
 * Algorithms/Techniques:
 * - Sort chips by rows and columns for efficient lookup
 * - Use two pointers to track which chips are still in play in current grid
 * - For each move, determine how many new chips are cut and add to appropriate player's score
 * - Efficiently update pointer positions and avoid reprocessing chips
 *
 * Time Complexity: O(n log n + m), where n is the number of chips and m is the number of moves.
 *                  The n log n factor comes from sorting chips initially, and each move is O(1) amortized.
 * Space Complexity: O(n), for storing chip positions and auxiliary arrays.
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
namespace Fread {
const int SZ = 1 << 17;
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
const int SZ = 1 << 12;
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
    while (isdigit(c)) {
      x = x * 10 + (c - '0');
      c = getchar();
    }
    return *this;
  }
  Reader &operator>>(char &c) {
    c = getchar();
    while (c == '\n' || c == ' ')
      c = getchar();
    return *this;
  }
} cin;
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    if (x == 0) {
      putchar('0');
      return *this;
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
} cout;
} // namespace Fast
#define cin Fast ::cin
#define cout Fast ::cout
#define f first
#define s second
#define pi pair<int, int>
#define all(v) v.begin() + 1, v.end()
int main() {
  int t;
  cin >> t;
  while (t--) {
    int gxr, gyr, n, m;
    cin >> gxr >> gyr >> n >> m;
    vector<pi> sbx(n + 1), sby(n + 1);
    for (int i = 1; i <= n; i++)
      cin >> sbx[i].f >> sby[i].f, sbx[i].s = sby[i].s = i;
    sort(all(sbx));
    sort(all(sby));
    auto *p1 = &sbx[1], *p2 = &sbx[n], *p3 = &sby[1], *p4 = &sby[n];
    int gxl = 1, gyl = 1, ans[2]{};
    bool p = 0;
    vector<bool> c(n + 1);
    while (m--) {
      int cnt = 0, k;
      char ch;
      cin >> ch >> k;
      switch (ch) {
      case 'U': {
        gxl += k;
        while (p1 <= p2 && p1->f < gxl) {
          if (!c[p1->s])
            c[p1->s] = 1, cnt++;
          p1++;
        }
      } break;
      case 'D': {
        gxr -= k;
        while (p1 <= p2 && p2->f > gxr) {
          if (!c[p2->s])
            c[p2->s] = 1, cnt++;
          p2--;
        }
      } break;
      case 'L': {
        gyl += k;
        while (p3 <= p4 && p3->f < gyl) {
          if (!c[p3->s])
            c[p3->s] = 1, cnt++;
          p3++;
        }
      } break;
      case 'R': {
        gyr -= k;
        while (p3 <= p4 && p4->f > gyr) {
          if (!c[p4->s])
            c[p4->s] = 1, cnt++;
          p4--;
        }
      }
      }
      ans[p] += cnt, p ^= 1;
    }
    cout << ans[0] << ' ' << ans[1] << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/