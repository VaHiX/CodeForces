// Problem: CF 1247 A - Forgetting Things
// https://codeforces.com/contest/1247/problem/A

/*
Code Purpose:
This program determines whether there exist positive integers a and b such that a + 1 = b,
where the first digit of a is d_a and the first digit of b is d_b. It outputs any such pair
if it exists, otherwise outputs -1.

Algorithm:
The problem is based on simple digit analysis:
1. If d_a == d_b, then we can construct a = d_a * 10^k + x where x is some number such that
   adding 1 results in b = d_b * 10^k + y. This works for certain cases, for example
   412 + 1 = 413.
2. If d_a + 1 == d_b, then a could end in 9 and b would start with d_b, like 199 + 1 = 200.
3. If d_a == 9 and d_b == 1, the case is special: 9 + 1 = 10.
4. In all other cases, no valid pair exists.

Time Complexity: O(1) - All operations are constant time.
Space Complexity: O(1) - Only a fixed number of variables are used.
*/

#include <stdio.h>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 10000100
#define inf 1e9
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m, t;
  int a, b;
  sff(a, b);
  
  // Case 1: Same first digit - check for pattern like 412 -> 413
  if (a == b) {
    // Construct a number starting with a and ending with 1, and b with 2
    cout << a << "1 " << b << "2";
  }
  // Case 2: First digit of b is one more than a's first digit - like 199 -> 200
  else if (b - a == 1) {
    cout << a << "9 " << b << "0";
  }
  // Special case: 9 -> 10
  else if (a == 9 && b == 1) {
    cout << "9 10";
  }
  // No valid case found
  else {
    cout << "-1";
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/