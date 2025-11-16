// Problem: CF 920 A - Water The Garden
// https://codeforces.com/contest/920/problem/A

/*
Code Purpose:
This code solves the problem of finding the minimum number of seconds required to water an entire garden using taps placed at specific positions.
Each tap, when turned on, waters a range that expands over time. The solution uses dynamic programming to compute the minimum time needed for each garden bed to be watered.

Algorithms/Techniques:
- Dynamic Programming
- Two-pass approach to calculate minimum distances from left and right taps
- Preprocessing each position's minimum tap distance from either direction

Time Complexity: O(n) per test case, where n is the number of garden beds
Space Complexity: O(n) for storing the arrays l[], r[], and ase[]

*/
#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 220
#define inf 100000
#define pp pair<char, char>
using namespace std;
int l[N], r[N], ase[N]; // l[]: min steps from left, r[]: min steps from right, ase[]: tap positions

int main() {
  int i, j, k;
  int n, m, t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k);
    memset(ase, 0, sizeof(ase)); // Initialize all beds as not having taps
    memset(l, 0, sizeof(l));     // Reset left array
    memset(r, 0, sizeof(r));     // Reset right array
    for (i = 0; i < k; i++) {    // Read tap positions
      scanf("%d", &m);
      ase[m] = 1;                // Mark positions with taps
    }
    
    // Fill left array: for each position, compute minimum distance to a tap on the left
    if (ase[1])
      l[1] = 1; // If tap is at position 1, distance is 1
    else
      l[1] = inf; // Otherwise, impossible to reach from left (set to infinity)
    
    for (i = 2; i <= n; i++) {
      if (ase[i])
        l[i] = 1; // If current position has a tap, distance is 1
      else {
        if (l[i - 1] == inf)
          l[i] = inf; // No previous tap, so no way to reach from left
        else
          l[i] = l[i - 1] + 1; // Distance is one more than previous
      }
    }
    
    // Fill right array: for each position, compute minimum distance to a tap on the right
    if (ase[n])
      r[n] = 1; // If tap is at last position, distance is 1
    else
      r[n] = inf; // Otherwise, impossible to reach from right
    
    for (i = n - 1; i >= 0; i--) {
      if (ase[i])
        r[i] = 1; // If current position has a tap, distance is 1
      else {
        if (r[i + 1] == inf)
          r[i] = inf; // No next tap, so no way to reach from right
        else
          r[i] = r[i + 1] + 1; // Distance is one more than next
      }
    }
    
    // Find the maximum of minimum distances. This will give the minimum seconds needed
    m = 1;
    for (i = 1; i <= n; i++)
      m = max(m, min(r[i], l[i])); // For each position, take min of left and right distances
    
    printf("%d\n", m); // Output result
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/