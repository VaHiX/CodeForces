// Problem: CF 1998 B - Minimize Equal Sum Subarrays
// https://codeforces.com/contest/1998/problem/B

/*
 * Purpose: To minimize the number of equal sum subarrays between two permutations.
 * Algorithm: The approach is to reverse the given permutation to create a new permutation q.
 *            This minimizes the chances of having equal subarray sums because it disrupts
 *            the cumulative sum patterns from the original array.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the permutation.
 * Space Complexity: O(n) for storing the input and output arrays.
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
      cin >> p[i];
    }
    // Output the last element of p, followed by all elements of p except the last
    cout << p[n - 1];  // Print the last element first
    for (int i = 0; i < n - 1; i++) {
      cout << " " << p[i];  // Then print the rest in order
    }
    cout << "\n";  // New line after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/