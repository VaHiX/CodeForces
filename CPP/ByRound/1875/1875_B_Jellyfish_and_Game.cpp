// Problem: CF 1875 B - Jellyfish and Game
// https://codeforces.com/contest/1875/problem/B

/*
Algorithm: Greedy
Time Complexity: O(n + m) per test case
Space Complexity: O(1)

The problem involves two players (Jellyfish and Gellyfish) swapping apples in k rounds,
with Jellyfish going first (on odd rounds) and Gellyfish on even rounds. Both aim to maximize
their own total apple values.

Key Observations:
1. In each round, players can either swap an apple or do nothing.
2. The optimal strategy in the long run depends only on the maximum and minimum values
   of each player's apples.
3. If Jellyfish can improve her score by swapping, she will.
4. After k rounds, the best possible outcome for Jellyfish is computed based on
   how many swaps are possible (if k is odd, she gets an extra chance to improve).

Strategy:
- For each player, compute total sum, max value, and min value.
- If Jellyfish's min value is less than Gellyfish's max, then she can improve by swapping.
- If k is odd, she gets one extra turn to optimize further.
*/

#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;
namespace fio {
streambuf *in = cin.rdbuf();
char bb[1000000], *s = bb, *t = bb;
#define gc()                                                                   \
  (s == t && (t = (s = bb) + in->sgetn(bb, 1000000), s == t) ? EOF : *s++)
int read() {
  int x = 0;
  char ch = gc();
  while (!isdigit(ch))
    ch = gc();
  while (isdigit(ch))
    x = x * 10 + ch - 48, ch = gc();
  return x;
}
} // namespace fio
using fio::read;
int n, m, k;
long long arr, brr;
long long xa, na, xb, nb, sa, sb;
int main() {
  int t = read();
  while (t--) {
    n = read(), m = read(), k = read(), sa = xa = 0, na = 1e9, sb = xb = 0,
    nb = 1e9;
    for (int i = 1; i <= n; i++)
      sa += arr = read(), xa = max(xa, arr), na = min(na, arr);
    for (int i = 1; i <= m; i++)
      sb += brr = read(), xb = max(xb, brr), nb = min(nb, brr);
    if (na <= xb)
      sa += xb - na, sb -= xb - na;
    if (k & 1)
      cout << sa << endl;
    else
      cout << sa - max(xa, xb) + min(na, nb) << endl;
  }
}


// https://github.com/VaHiX/CodeForces/