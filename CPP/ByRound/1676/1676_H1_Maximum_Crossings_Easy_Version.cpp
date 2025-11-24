// Problem: CF 1676 H1 - Maximum Crossings (Easy Version)
// https://codeforces.com/contest/1676/problem/H1

/*
 * Problem: Maximum Crossings (Easy Version)
 * 
 * Purpose: This code computes the maximum number of crossings between wires
 *          connecting segments of two terminals based on a given mapping array.
 * 
 * Algorithm:
 *   - For each wire (segment i), we count how many previous wires (segments j < i)
 *     cross with it.
 *   - A crossing occurs when a wire from segment i connects to a segment a[i],
 *     and a previous wire from segment j connects to a segment a[j] such that
 *     a[i] <= a[j]. This is because if a[i] <= a[j], then the wires will cross
 *     when drawn optimally.
 * 
 * Time Complexity: O(n^2) for each test case due to nested loops.
 * Space Complexity: O(n) for storing the array a.
 * 
 * Techniques:
 *   - Brute force pairwise comparison for counting crossings.
 */

#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, c = 0;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      for (int j = 0; j <= i - 1; j++) {
        // Count how many previous wires cross with current wire
        if (a[i] <= a[j]) {
          c++;
        }
      }
    }
    cout << c << endl;
  }
}


// https://github.com/VaHiX/CodeForces/