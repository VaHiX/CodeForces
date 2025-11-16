// Problem: CF 1934 D2 - XOR Break --- Game Version
// https://codeforces.com/contest/1934/problem/D2

/*
Purpose: This code solves the interactive game problem where Alice and Bob take turns breaking a number into two parts such that their XOR equals the original number. The goal is to determine whether Alice should play first or second to ensure a win, based on the binary representation of the starting number n.

Algorithms/Techniques:
- Bit manipulation using popcount (count of set bits) and __lg (floor of log base 2)
- Game theory logic: if the number of set bits in the initial number is odd, Alice should play second; otherwise, she plays first
- For each move, we decompose the current number n into two numbers p1 and p2 such that p1 XOR p2 = n
  - We use p1 = n - (1 << __lg(n)) and p2 = (1 << __lg(n)) to ensure the XOR property

Time Complexity: O(1) per test case (since we only do constant time operations)
Space Complexity: O(1) (uses only a few variables regardless of input size)
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>

#define ull unsigned long long
#define int long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int, int>
#define fi first
#define se second
#define ls k << 1
#define rs k << 1 | 1
#define mid ((l + r) >> 1)
#define gcd __gcd
#define lowbit(x) (x & (-x))
#define popcount __builtin_popcountll
using namespace std;

int rd() {
  int x = 0, f = 1;
  char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar())
    if (ch == '-')
      f = -1;
  for (; ch >= '0' && ch <= '9'; ch = getchar())
    x = (x << 1) + (x << 3) + (ch ^ 48);
  return x * f;
}

void write(int x) {
  if (x > 9)
    write(x / 10);
  putchar('0' + x % 10);
}

void solve() {
  int x = rd(), p = popcount(x);
  // If number of set bits is odd, Alice plays second
  if (p & 1) {
    puts("second");
    fflush(stdout);
    x = rd();
    int y = rd();
    if (x == -1 && y == -1)
      return;
    // If current number has odd set bits, swap x and y to ensure odd number comes first (since we want to always have odd set bits to lose)
    if (popcount(x) & 1)
      swap(x, y);
  } else
    // If number of set bits is even, Alice plays first
    puts("first"), fflush(stdout);
  
  // While loop continues until x becomes 0
  while (x) {
    // Get the highest power of 2 less than or equal to x
    int y = 1ll << (__lg(x));
    // Subtract highest power of 2 from x to get a new number
    x -= y;
    cout << x << ' ' << y << endl;
    fflush(stdout);
    // Read next numbers from Bob
    x = rd(), y = rd();
    if (x == -1 && y == -1)
      return;
    // If x now has odd number of set bits, swap x and y
    if (popcount(x) & 1)
      swap(x, y);
  }
}

signed main() {
  int T = rd();
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/