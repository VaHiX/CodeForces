// Problem: CF 1234 A - Equalize Prices Again
// https://codeforces.com/contest/1234/problem/A

/*
Problem: Equalize Prices Again
Purpose: Given n goods with individual prices, find the minimum equal price to set for all goods such that total revenue is at least the sum of initial prices.
Algorithm/Techniques: Greedy approach
Time Complexity: O(n) per query
Space Complexity: O(1)

Input:
- q: number of queries
- For each query:
  - n: number of goods
  - Array of n prices

Output:
- Minimum equal price for all goods such that sum of new prices >= sum of original prices

Approach:
1. Calculate total sum of original prices
2. To minimize the equal price, we need to find minimum value 'x' such that n*x >= sum
3. This is equivalent to x >= sum/n, so x = ceil(sum/n)
4. Since we're dealing with integers, if sum%n == 0, result is sum/n, else it's sum/n + 1
*/

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 1010101
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
  sf(q); // Read number of queries
  while (q--) { // Process each query
    sf(n); // Read number of goods
    ll sum = 0; // Initialize sum of prices
    for (i = 0; i < n; i++)
      sf(m), sum += m; // Read each price and add to sum
    if (sum % n == 0) // If sum is divisible by n
      pfl(sum / n); // Print quotient as minimum equal price
    else
      pfl(sum / n + 1); // Otherwise, add 1 to get ceiling value
    nl; // Print newline
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/