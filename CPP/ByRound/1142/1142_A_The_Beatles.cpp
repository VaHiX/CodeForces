// Problem: CF 1142 A - The Beatles
// https://codeforces.com/contest/1142/problem/A

/*
 * Problem: A. The Beatles
 * Purpose: Determine the minimum and maximum number of stops Sergey could have made 
 *          before returning to his starting city, given constraints on distances to 
 *          fast food restaurants at specific intervals.
 *
 * Algorithm:
 *   - For each combination of initial stop position (a) and first move (l), we compute
 *     the least common multiple with k to find valid stopping points that align with
 *     the circular route and the positions of fast food restaurants.
 *   - Use mathematical properties related to GCD and LCM, particularly simplifying
 *     fractions to avoid redundant computations.
 *
 * Time Complexity: O(log(k) + √k)
 * Space Complexity: O(1)
 *
 * Techniques:
 *   - Mathematical optimization using GCD and LCM
 *   - Circular arithmetic with modular arithmetic
 *   - Iteration over all valid combinations of position and step sizes
 */

#include <algorithm>
#include <initializer_list>
#include <iostream>

using namespace std;
typedef long long int ll;

// Function to compute min and max stops based on given parameters
void solve(int n, int k, int l, ll &min, ll &max) {
  l = ((l % k) + k) % k; // Normalize l to [0, k)
  int h = __gcd(k, l);   // Find GCD of k and l
  k /= h;                // Simplify k
  l /= h;                // Simplify l
  int m = n;
  while (__gcd(m, k) > 1) // Reduce m by removing common factors with k
    m /= __gcd(m, k);
  min = std::min(min, (ll)n * k / m); // Update minimum stops needed
  max = std::max(max, (ll)n * k);     // Update maximum stops possible
}

int main() {
  int n, k;
  cin >> n >> k;
  int a0, b0;
  cin >> a0 >> b0;
  ll min = (ll)1 << 60, max = 0; // Initialize min to large value and max to 0
  
  // Iterate through all possible starting positions and first moves
  for (int a : {a0, k - a0})    // Try both a and k-a (symmetric cases)
    for (int b : {b0, k - b0})  // Try both b and k-b (symmetric cases)
      solve(n, k, a - b, min, max); // Compute result for each pair
  std::cout << min << ' ' << max << '\n'; // Output the final answer
}


// https://github.com/VaHiX/codeForces/