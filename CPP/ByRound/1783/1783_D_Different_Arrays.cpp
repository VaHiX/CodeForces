// Problem: CF 1783 D - Different Arrays
// https://codeforces.com/contest/1783/problem/D

/*
 * Problem: D. Different Arrays
 * Purpose: Count the number of reachable arrays after performing a sequence of operations
 *          on the input array, where each operation adds a[i+1] to one neighbor and 
 *          subtracts it from the other.
 * 
 * Algorithms/Techniques: Dynamic Programming with memoization
 * 
 * Time Complexity: O(n * M) where M is the range of possible values (180000)
 * Space Complexity: O(n * M) for the DP table
 * 
 * The solution uses a backward DP approach, starting from the last element and working 
 * backwards to compute the number of ways to reach each state at each step.
 */

#include <iostream>

#define int long long
using namespace std;
int n, a[320], f[320][180020];
const int p = 998244353;

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  
  // Initialize the base case: for the last element, all values are reachable in 1 way
  for (int i = -90000; i <= 90000; i++)
    f[n][i] = 1;
  
  // Process the array from right to left (excluding first two elements)
  for (int i = n - 1; i > 1; i--)
    for (int j = -90000; j <= 90000; j++)
      // f[i][j] = number of ways to reach state j at position i
      // Two transitions: add a[i+1] to left neighbor or right neighbor
      f[i][j] =
          (f[i + 1][a[i + 1] + j] + (j != 0) * f[i + 1][a[i + 1] - j]) % p;
  
  // The answer is the number of ways to reach the value a[2] at position 2
  cout << f[2][a[2]] << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/