// Problem: CF 1195 A - Drinks Choosing
// https://codeforces.com/contest/1195/problem/A

/*
Problem: Drinks Choosing
Algorithm: Greedy + Map
Time Complexity: O(n log n) due to map operations
Space Complexity: O(n) for storing the map and input

The problem is about selecting minimum number of drink sets (each set has exactly 2 portions of same drink type)
to maximize the number of students getting their favorite drink.
We use a greedy approach:
1. Count frequency of each drink type
2. For each drink type, we can form floor(count/2) pairs (sets)
3. We prioritize forming pairs from drinks that appear more frequently
4. Then we try to match the remaining odd-count items to students having those favorite drinks

Key idea:
- We want to use minimum sets = ceil(n/2)
- We sort drink types by their count in descending order to maximize pair formation
- We try to assign odd counts first for maximum student satisfaction
*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include <utility>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 200100
#define inf 1e18
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
  sff(n, k);                        // Read number of students and drink types
  map<int, int> mp;                 // Map to store count of each drink type
  for (i = 0; i < n; i++) {
    sf(m);                          // Read favorite drink of student i
    mp[m]++;                        // Increment count of that drink type
  }
  m = n / 2;                        // Required number of sets = ceil(n/2)
  if (n % 2)
    m++;                            // If odd, we need one more set  
  auto itr = mp.begin();            // Iterator for map
  int even = 0, odd = 0;            // Count how many pairs and singles we have
  while (itr != mp.end()) {
    even += (itr->second / 2) * 2;  // Add number of students satisfied by forming pairs (even count)
    odd += itr->second % 2;         // Add leftover students who want this drink type (odd count)
    itr++;
  }
  int ans = 0;                      // Final answer - max students getting favorite drinks
  if (even / 2 <= m)                // If we can use all the pairs we formed
    ans += even, m -= even / 2;     // Use them and update remaining sets needed
  else                              // Otherwise, use only required number of pairs
    ans += m * 2, m = 0;            // Add them to answer and set remaining to zero
  if (m)                            // If there are still unused sets
    ans += min(m, odd);             // Assign leftover students optimally
  pf(ans);                          // Print result
  return 0;
}


// https://github.com/VaHiX/codeForces/