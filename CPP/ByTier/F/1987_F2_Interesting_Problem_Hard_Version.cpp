// Problem: CF 1987 F2 - Interesting Problem (Hard Version)
// https://codeforces.com/contest/1987/problem/F2

/*
 * Problem: F2. Interesting Problem (Hard Version)
 * 
 * Algorithm: Dynamic Programming with Memoization
 * 
 * Time Complexity: O(n^3), where n is the size of the array
 * Space Complexity: O(n^2), for the 2D DP table
 * 
 * Approach:
 * - The problem involves removing elements from an array under specific conditions.
 * - A dynamic programming approach is used to store the maximum number of operations
 *   that can be performed for subarrays.
 * - The state dp[i][j] represents the maximum operations possible for a window
 *   starting at index i and ending at index j.
 * - The transitions consider valid pairs of indices that satisfy the condition a[i] = i+1
 *   (adjusted for 0-based indexing).
 * 
 * Key observations:
 * - For a subarray, we check if we can perform operations by matching values to indices.
 * - The algorithm uses a 2D table to compute optimal substructure.
 * - The helper function `update_max` ensures we maintain the maximum number of operations.
 */

#include <iostream>
using namespace std;

// Helper function to update maximum value
void update_max(int a, int *b);
int main() {
  int t;
  cin >> t;
  while (t-- > 0) {
    int n;
    cin >> n;
    int *a = new int[n];
    int b;
    for (int i = 0; i < n; i++) {
      cin >> b;
      a[i] = b - 1;  // Adjust for 0-based indexing
    }
    int *s = new int[n * n];  // DP table for storing results
    
    if (n == 1) {
      cout << 0 << endl;
      delete[] a;
      delete[] s;
      continue;
    }
    
    // Initialize DP table
    for (int i = 0; i < n; i++) {
      s[i * n] = 0;
      s[i] = 0;
    }
    
    int diff;
    // Set base values for the last column
    for (int i = 0; i <= (n - 1) / 2; i++) {
      s[n * i + n - 1] = 0;
    }
    
    // Process from right to left
    for (int j = n - 2; j >= 0; j--) {
      diff = j - a[j];  // Compute the difference between index and value
      for (int i = 0; i <= j / 2; i++) {
        // Copy value from right neighbor in DP table
        s[n * i + j] = s[n * i + j + 1];
        
        // Check if the diff is even and within bounds
        if ((diff % 2 == 0) && (diff <= i * 2) && (diff >= 0)) {
          int k0 = 0;
          // Check if there are elements beyond current position
          if (j + 2 < n) {
            k0 = s[(i + 1) * n + j + 2];
          }
          
          // Update if new solution is better
          update_max(k0 + 1, s + i * n + j);
          
          // Additional logic based on lower value
          int lower = s[(diff / 2) * n + j + 1];
          if (n - j - 1 - 2 * lower > 1) {
            // Iterate through possible combinations
            for (int k = 1; 2 * k + 1 <= n - j - 1; k++) {
              int new_val = 0;
              int upper = 0;
              upper = s[(diff / 2 + k) * n + j + 2 * k];
              if (j + 2 * k + 2 < n) {
                new_val = s[(i + k + 1) * n + j + 2 * k + 2];
              }
              
              // Decide if the condition allows updating
              if (lower - upper >= k) {
                update_max(new_val + k + 1, s + n * i + j);
              } else {
                break;  // Break if condition no longer holds
              }
            }
          } else if (n - j - 1 - 2 * lower == 1) {
            // Single element case
            update_max(s[n * i + j + 1] + 1, s + n * i + j);
          }
        }
      }
    }
    
    cout << s[0] << endl;  // Output result for the full array
    delete[] s;
    delete[] a;
  }
}

// Update maximum value in place
void update_max(int a, int *b) {
  if (*b < a) {
    *b = a;
  }
  return;
}


// https://github.com/VaHiX/CodeForces/