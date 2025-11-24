// Problem: CF 1698 E - PermutationForces II
// https://codeforces.com/contest/1698/problem/E

/*
 * Problem: E. PermutationForces II
 * 
 * Purpose:
 * This code determines the number of ways to fill in the missing elements (-1) in permutation b such that 
 * it's possible to transform permutation a into permutation b using a given strength s. 
 * 
 * Algorithms/Techniques:
 * - Preprocessing: Store positions of elements in both arrays to track mappings.
 * - Simulating constraints: Check if positions of elements in b can be achieved given the swap strength.
 * - Combinatorial counting: Count valid ways to assign -1 values using modular arithmetic.
 * 
 * Time Complexity: O(n), where n is the size of the permutation.
 * Space Complexity: O(n), for storing arrays and auxiliary data structures.
 */

#include <stdio.h>
#include <iostream>

using namespace std;
const int N = 200010, mod = 998244353;
int t, n, k, a[N], b[N], c[N], d[N]; // c: position of element in a, d: position of element in b

void solve() {
  scanf("%d%d", &n, &k); // Read n (size) and k (strength)
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i); // Read permutation a
    c[a[i]] = i;       // c[a[i]] = position of a[i] in a
    d[i] = 0;          // Initialize d array
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i); // Read permutation b
    if (b[i] > 0)
      d[b[i]] = i;     // d[b[i]] = position of b[i] in b
  }
  
  long long ans = 1, free = 0; // ans: result, free: number of positions that can be assigned freely
  
  // Count initial free positions among first k elements
  for (int i = 1; i <= k; i++) {
    free += (b[c[i]] == -1); // If element i can be placed anywhere in first k positions
  }
  
  // Process each element from 1 to n
  for (int i = 1; i <= n; i++) {
    // Add free positions for elements in range [i + k, i + k]
    free += (i + k <= n && b[c[i + k]] == -1); 
    // Check validity of swaps
    if (d[i] && a[d[i]] - i > k) 
      ans = 0; // If element i is already in b but cannot be moved to i with strength k, impossible
    
    // If element i doesn't exist in b yet, we can assign it here
    if (!d[i]) {
      ans = ans * free % mod; // Multiply result by number of choices
      free--;                 // Reduce free choices
    }
  }
  
  cout << ans << endl; // Output result
}

int main() {
  scanf("%d", &t); // Read number of test cases
  while (t) {
    t--;
    solve(); // Solve each test case
  }
}


// https://github.com/VaHiX/CodeForces/