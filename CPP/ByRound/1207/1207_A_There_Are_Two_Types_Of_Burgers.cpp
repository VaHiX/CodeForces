// Problem: CF 1207 A - There Are Two Types Of Burgers
// https://codeforces.com/contest/1207/problem/A

/*
Problem: A. There Are Two Types Of Burgers
Purpose: Given buns, beef patties, and chicken cutlets, determine the maximum profit 
         by selling hamburgers (2 buns + 1 beef) or chicken burgers (2 buns + 1 chicken).
         Each hamburger sells for 'h' dollars, each chicken burger for 'c' dollars.
Algorithms/Techniques: Greedy approach - try all possible numbers of hamburgers 
                       and calculate maximum profit by adjusting chicken burgers.
Time Complexity: O(b) per query, since we iterate up to b/2 hamburgers.
Space Complexity: O(1), only using a constant amount of extra space.
*/

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 35
#define inf 1e18
#define mod 100000007
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
  int n, m, q;
  int b, p, f;
  int h, c;
  
  sf(q); // Read number of queries
  
  while (q--) {
    sff(b, p); // Read buns and beef patties
    sf(f);     // Read chicken cutlets
    sff(h, c); // Read hamburger and chicken burger prices
    
    int ans = 0; // Initialize maximum profit
    m = b / 2;   // Maximum possible hamburgers (each needs 2 buns)
    
    // Iterate through all possible numbers of hamburgers (0 to m)
    while (p + f > 0 && m > 0) {
      if (p > 0 && f > 0) { 
        // Both ingredients available: choose more profitable one
        if (h > c)
          p--, ans += h, m--; // Make hamburger if it's more profitable
        else
          f--, ans += c, m--; // Make chicken burger if it's more profitable
      } else if (p > 0) {
        // Only beef available: make hamburgers
        p--, ans += h, m--;
      } else if (f > 0) {
        // Only chicken available: make chicken burgers
        f--, ans += c, m--;
      }
    }
    
    pf(ans); // Print maximum profit
    nl;      // New line
  }
  
  return 0;
}


// https://github.com/VaHiX/codeForces/