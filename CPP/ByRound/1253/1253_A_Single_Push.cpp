// Problem: CF 1253 A - Single Push
// https://codeforces.com/contest/1253/problem/A

/*
 * Problem: Single Push
 * 
 * Purpose: Determine if array 'a' can be transformed into array 'b' using at most one "push" operation.
 * A push operation adds a positive value k to a contiguous subarray of 'a'.
 * 
 * Algorithm:
 * - Compute the difference array 'c' where c[i] = b[i] - a[i].
 * - Traverse the difference array to count transitions from 0 to non-zero and vice versa.
 * - If there are more than one such transitions where the value becomes positive (indicating a push start),
 *   then at least two operations are needed, return "NO".
 * 
 * Time Complexity: O(n) - Single pass through the array
 * Space Complexity: O(n) - Extra space for the difference array
 */

#include <iostream>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    long int n;
    cin >> n;
    int i, k = 0;
    long a[n], b[n], c[n];
    for (i = 0; i < n; i++) {
      cin >> a[i];
    }
    for (i = 0; i < n; i++) {
      cin >> b[i];
      c[i] = b[i] - a[i];  // Compute difference array
      // Check for transitions from 0 to non-zero or vice versa
      if (c[i] != 0 && c[i] != c[i - 1])  
        if (c[i] > 0)  // If positive, it's a start of a push
          k++;
        else  // If negative, it's an end of a push
          k = 3;  // Mark that there's a conflict, indicating more than one operation needed
    }
    if (k > 1)  // If more than one start point, impossible with one operation
      cout << "No" << endl;
    else
      cout << "Yes" << endl;
  }
}


// https://github.com/VaHiX/CodeForces/