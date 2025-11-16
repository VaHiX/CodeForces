// Problem: CF 959 A - Mahmoud and Ehab and the even-odd game
// https://codeforces.com/contest/959/problem/A

/*
Purpose: Determine the winner of the even-odd game where Mahmoud and Ehab take turns subtracting numbers from n.
         Mahmoud can only subtract even numbers, Ehab can only subtract odd numbers.
         The player who cannot make a move loses.
Algorithm: Game Theory
Time Complexity: O(1)
Space Complexity: O(1)

Approach:
- If n is even, Mahmoud can subtract 2 (an even number) and leave an even number for Ehab.
  Since Ehab can only subtract odd numbers, he will always subtract an odd number, leaving an odd number for Mahmoud.
  Eventually, Mahmoud will be left with 1 and cannot make a move, so Ehab wins.
- If n is odd, Mahmoud will subtract an even number, leaving an odd number for Ehab.
  Ehab can then subtract 1 (odd), leaving 0 for Mahmoud, who cannot move.
  So Mahmoud wins.
*/

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 150
#define inf 1000000
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d\n", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s\n", s)
#define pb(n) push_back(n)
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  sf(n);
  if (n % 2 == 0) // If n is even, Mahmoud wins
    pfs("Mahmoud");
  else // If n is odd, Ehab wins
    pfs("Ehab");
  return 0;
}


// https://github.com/VaHiX/CodeForces/