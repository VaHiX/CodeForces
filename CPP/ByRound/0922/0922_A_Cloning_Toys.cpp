// Problem: CF 922 A - Cloning Toys
// https://codeforces.com/contest/922/problem/A

/*
 * Problem: Cloning Toys
 * 
 * Algorithm:
 * - The problem simulates a cloning process where:
 *   - Applying the machine to an original toy produces 1 new original and 1 copy.
 *   - Applying the machine to a copy produces 2 new copies.
 * - Initially, there is 1 original toy and 0 copies.
 * - Goal: Determine if it's possible to get exactly x copies and y original toys.
 * 
 * Key Insight:
 * - To get y original toys, we must have applied the machine (y - 1) times to original toys,
 *   since each such operation gives one new original toy.
 * - Let's say we've applied the machine to original toys (y - 1) times.
 *   This gives us 1 initial original + (y - 1) new originals = y originals.
 * - For the copies, after applying to y - 1 original toys, we have (y - 1) copies.
 *   Applying the machine to a copy produces 2 new copies.
 * - To get exactly x copies total:
 *   - We already have (y - 1) copies from applying to originals.
 *   - We need (x - (y - 1)) more copies.
 *   - Each application to copies produces 2 new copies.
 * - So if (x - (y - 1)) is positive, and if it's divisible by 2, we can achieve it.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 15
#define inf 100000000
#define pp pair<char, char>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  ll x, y;
  ll a, b;
  cin >> a >> b; // a = x (copies), b = y (originals)
  if (b == 0) {
    printf("No");
    return 0;
  }
  if (b == 1) {
    if (a == 0)
      printf("Yes");
    else
      printf("No");
    return 0;
  }
  x = b - 1; // number of times machines was applied to original toys
  a -= x; // Remaining copies needed after applying to originals
  if (a == 0) {
    printf("Yes");
    return 0;
  }
  if (a < 0) {
    printf("No");
    return 0;
  }
  a++; // Adjusting to see how many operations to apply on copies
  y = a - 1; // Number of operations that must be applied to copies
  if (y % 2 == 0)
    printf("Yes");
  else
    printf("No");
  return 0;
}


// https://github.com/VaHiX/CodeForces/