// Problem: CF 1102 C - Doors Breaking and Repairing
// https://codeforces.com/contest/1102/problem/C

/*
C. Doors Breaking and Repairing
Algorithms/Techniques: Greedy approach, game theory
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves a game between two players (you and Slavik) where:
- You break doors (reduce durability by x)
- Slavik repairs doors (increase durability by y)
- The goal is to maximize doors at 0 durability for you, minimize for Slavik
- Strategy: If x > y, you can always break all doors in one move. Otherwise,
  count how many doors can be broken to 0 or below by you, then determine
  optimal pairing strategy.

Input:
n - number of doors
x - your breaking power
y - Slavik's repair power
a[] - initial durability of doors

Output:
Number of doors at 0 durability after optimal play.
*/

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 100100
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
  int n, m;
  int x, y, cnt = 0;
  sf(n);
  sff(x, y);
  int a[n];
  for (i = 0; i < n; i++)
    sf(a[i]);
  if (x > y) { // If your breaking power is greater than Slavik's repair power
    pf(n); // You can break all doors in one turn
    return 0;
  }
  k = 0;
  for (i = 0; i < n; i++) {
    if (a[i] <= x) // Count doors that you can break to zero in one turn
      k++;
  }
  if (k % 2 == 0) // If even number of such doors, divide by 2
    pf(k / 2);
  else // If odd, one extra door remains unpaired, so +1
    pf(k / 2 + 1);
  return 0;
}


// https://github.com/VaHiX/codeForces/