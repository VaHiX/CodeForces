// Problem: CF 2027 E1 - Bit Game (Easy Version)
// https://codeforces.com/contest/2027/problem/E1

/*
 * Problem: E1. Bit Game (Easy Version)
 * 
 * Purpose:
 *   This code determines the winner of a two-player game involving piles of stones,
 *   where players can only take a certain number of stones based on bitwise AND conditions.
 *   The game is modeled as a Nim-like game using Sprague-Grundy theorem and XOR of Grundy numbers.
 * 
 * Algorithms:
 *   - Sprague-Grundy theorem for game theory
 *   - Bit manipulation to preprocess pile states
 *   - XOR of Grundy numbers to determine overall game state
 * 
 * Time Complexity: O(n * H) where H = 29 (fixed bit length) and n is the total number of piles
 * Space Complexity: O(n) for storing pile information and intermediate results
 */

#include <stdio.h>
#include <iosfwd>

#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
int read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch - '0');
    ch = getchar();
  }
  return x;
}
void print(cint x) {
  if (x < 10) {
    putchar(x + '0');
    return;
  }
  print(x / 10);
  putchar(x % 10 + '0');
}
void princh(cint x, const char ch) {
  print(x);
  putchar(ch);
}
cint H = 29;
int n, a[10001], b[10001];
void del(int &x, cint y) { x = (x & ((1 << y) - 1)) | (x >> y + 1 << y); }
bool check(cint x) { return (x == (x & -x)); }
int hb(cint x) {
  for (int i = 0;; ++i) {
    if (!(x >> i + 1))
      return i;
  }
}
int SG(cint x) {
  if (check(x + 2))
    return 0;
  if (check(x + 1))
    return hb(x + 1);
  if (check(x))
    return hb(x) ^ 1;
  return hb(x) + 1;
}
int ans;
void solve() {
  n = read();
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
  }
  for (int i = 1; i <= n; ++i) {
    b[i] = read();
  }
  ans = 0;
  for (int i = 1; i <= n; ++i) {
    bool flag = 0;
    for (int h = H; h >= 0; --h) {
      const bool ca = ((a[i] >> h) & 1), cb = ((b[i] >> h) & 1);
      flag |= ca;
      if ((!cb && !ca) || !flag) {
        // Clear bits up to h-th bit if the constraints are not satisfied
        del(a[i], h);
        del(b[i], h);
      } else if (!cb) {
        // Process case where b[i] bit is 0 but a[i] bit is 1
        a[i] |= (1 << h) - 1;  // Set low bits
        del(a[i], h);  // Clear h-th bit
        del(b[i], h);  // Clear h-th bit
      }
    }
    // Calculate Grundy number for modified a[i] and XOR it to overall result
    ans ^= SG(a[i]);
  }
  puts((ans ? "Alice" : "Bob"));
}
int main() {
  int T = read();
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/