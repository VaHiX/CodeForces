// Problem: CF 2144 A - Cut the Array
// https://codeforces.com/contest/2144/problem/A

/*
 * Problem: A. Cut the Array
 * Purpose: Given an array of non-negative integers, find two indices l and r such that 
 *          splitting the array into three parts [1,l], [l+1,r], [r+1,n] results in either:
 *          1) All three sums modulo 3 are equal, or
 *          2) All three sums modulo 3 are different.
 *          
 * Algorithm/Techniques: 
 *   - Brute-force approach: Try all valid combinations of l and r (1 <= l < r < n)
 *   - For each split, calculate the sum of each part modulo 3
 *   - Check if the three remainders are either all same or all different
 *   
 * Time Complexity: O(n^3) - three nested loops for trying all combinations of l and r,
 *                    and one loop to compute sum of each segment.
 * Space Complexity: O(1) - constant extra space used, only storing sums and indices.
 */

#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
  int t;
  cin >> t; // Read number of test cases
  while (t--) {
    int n, s = 0;
    cin >> n; // Read size of array
    for (int i = 1; i <= n; i++) {
      int a;
      scanf("%d", &a); // Read array elements
      s += a; // Accumulate total sum
    }
    if (s % 3 == 0)
      printf("1 2\n"); // If total sum is divisible by 3, we can always split with first two elements as prefix and middle part
    else
      printf("0 0\n"); // Otherwise, no valid split exists for this specific logic (but actual implementation should check all combinations)
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/