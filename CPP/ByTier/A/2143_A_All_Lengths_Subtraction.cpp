// Problem: CF 2143 A - All Lengths Subtraction
// https://codeforces.com/contest/2143/problem/A

/*
 * Problem: Determine if a permutation can be reduced to all zeros by repeatedly subtracting 1 
 *          from a subarray of length k for each k from 1 to n.
 * 
 * Algorithm:
 *   - This problem involves checking whether the given permutation can be transformed into 
 *     all zeros by performing operations where we subtract 1 from a subarray of size k at step k.
 *   - We simulate the reverse process: instead of subtracting, we try to build up the original
 *     array from 0s by adding 1s in subarrays of increasing sizes.
 *   - For this simulation, we maintain pointers `l` and `r` to track valid positions and 
 *     ensure that elements match what would be expected at each step.
 * 
 * Time Complexity: O(n^2) due to nested loops in the worst case.
 * Space Complexity: O(n) for storing the array.
 */

#include <iostream>
using namespace std;

int t, n, a[110]; // t: number of test cases, n: size of permutation, a: array storing permutation

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i]; // Read the permutation

    int l = 1, r = n, b = 1; // l: left pointer, r: right pointer, b: flag to check validity
    
    for (int i = 1; i <= n; i++) {
      if (a[l] == i) { // If element at left matches expected value
        l++;           // Move left pointer
      } else if (a[r] == i) { // Else if element at right matches expected value
        r--;           // Move right pointer
      } else {
        b = 0;         // If neither matches, it's invalid
        break;
      }
    }

    if (b)
      cout << "Yes" << endl; // Valid sequence
    else
      cout << "No" << endl;  // Invalid sequence
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/