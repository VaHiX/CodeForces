// Problem: CF 1677 D - Tokitsukaze and Permutations
// https://codeforces.com/contest/1677/problem/D

/*
Algorithm: 
This problem involves determining the number of permutations that, after exactly k bubble sort-like operations, result in a specific value sequence v. 
The key insight is:
1. The last k elements of the permutation will always have a value of 0 in the value sequence after k operations.
2. For the first n-k elements, we analyze how many valid choices there are for each position. 
   - If v[i] is -1 (unknown), it can be any of (i+k) values.
   - If v[i] is 0, then value of the element in that position can be chosen in (k+1) ways.
3. Multiply the number of choices for all positions, and also multiply by k! to account for arrangements of the last k elements.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the value sequence and constants
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
int t, n, k, v[1000001];
const int mod = 998244353;
int main() {
  scanf("%d", &t);
  while (t--) {
    long long ans = 1;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
      scanf("%d", &v[i]);
    // Check if last k elements have value 0 after k operations
    for (int i = n - k + 1; i <= n; i++)
      ans &= v[i] <= 0; // This line ensures that the condition is met; bitwise AND is likely a typo and should be ans = (ans && (v[i] <= 0)) or similar logic
    
    // Calculate possibilities for first n-k elements
    for (int i = 1; i <= n - k; i++) {
      if (v[i] == -1)
        ans = ans * (i + k) % mod; // If unknown, number of options is (i+k)
      else if (!v[i])
        ans = ans * (k + 1) % mod; // If v[i] = 0, number of options is (k+1)
    }
    
    // Multiply by k! for the last k elements' arrangements
    for (int i = 1; i <= k; i++)
      ans = ans * i % mod;
    
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/