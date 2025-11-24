// Problem: CF 474 B - Worms
// https://codeforces.com/contest/474/problem/B

/*
 * Problem: Worms
 * 
 * Purpose: 
 *   Given n piles of worms with specific numbers of worms in each pile, 
 *   determine which pile a worm with a given label belongs to.
 * 
 * Approach:
 *   Preprocess the worm labels by assigning each label to its corresponding pile.
 *   This is done by iterating through the piles and filling an array `arr` such that 
 *   `arr[label]` contains the pile number where that label belongs.
 * 
 * Time Complexity: O(sum of all a_i) where sum is total number of worms.
 * Space Complexity: O(sum of all a_i) for the array `arr`.
 * 
 * Algorithms/Techniques:
 *   - Preprocessing with direct indexing
 *   - Linear traversal of input data
 */

#include <iostream>
using namespace std;
int n, arr[1000003], i, x = 1, m, t;
int main() {
  cin >> n;
  for (i = 1; i <= n; i++) {
    cin >> t;
    while (t--)  // For each worm in the current pile
      arr[x] = i, x++;  // Assign pile number 'i' to label 'x', then increment x
  }
  cin >> m;
  while (m--)  // For each query worm label
    cin >> t, cout << arr[t] << endl;  // Output the pile number for label 't'
}


// https://github.com/VaHiX/CodeForces/