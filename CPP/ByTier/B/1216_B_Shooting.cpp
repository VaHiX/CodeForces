// Problem: CF 1216 B - Shooting
// https://codeforces.com/contest/1216/problem/B

/*
Algorithm: Greedy
Sort the cans in decreasing order of their durability.
The reason is that if we have to shoot a can with higher durability later,
we will have already shot more cans, so the cost (a_i * x + 1) will be higher.
By shooting the cans with higher durability first, we minimize the total cost.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the cans
*/

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <utility>

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
  int n, m;
  sf(n);
  pp a[n]; // Store {durability, index} pairs
  for (i = 0; i < n; i++)
    sf(m), a[i] = {m, i}; // Read durability and store with index
  sort(a, a + n, greater<pp>()); // Sort in decreasing order of durability
  int cnt = 0; // Total shots needed
  m = 0; // Number of cans already shot
  for (i = 0; i < n; i++)
    cnt += (a[i].first * m + 1), m++; // Add shots needed for current can
  pf(cnt); // Print total shots
  nl;
  for (i = 0; i < n; i++)
    pf(a[i].second + 1), pfs(" "); // Print indices in order (1-indexed)
  return 0;
}


// https://github.com/VaHiX/CodeForces/