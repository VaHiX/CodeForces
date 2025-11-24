// Problem: CF 1119 B - Alyona and a Narrow Fridge
// https://codeforces.com/contest/1119/problem/B

/*
B. Alyona and a Narrow Fridge
Purpose: Determine the maximum number of bottles (1 to k) that can be placed in a fridge of height h,
         considering that bottles are placed from bottom to top, and each shelf can support bottles
         up to a certain height. Shelves divide the fridge into parts, and only one bottle can be placed per cell.
         We use a greedy approach with sorting to maximize the number of bottles placed.

Algorithms:
  - Greedy algorithm
  - Sorting

Time Complexity: O(n^2 log n) 
Space Complexity: O(n)

*/
#include <algorithm>
#include <iostream>

using namespace std;
int i, n, k, r, j, a[300000];
int main() {
  for (cin >> n >> k; i < n; i++) {      // Read number of bottles and fridge height, iterate through each bottle
    cin >> a[i];                        // Read the height of current bottle
    sort(a, a + i + 1);                 // Sort bottles in ascending order so far (greedy choice)
    r = 0;                              // Reset sum for current iteration
    j = i;                              // Start from last index
    while (j > -1) {                    // Traverse backwards selecting every other bottle (greedy)
      r += a[j];                        // Add height of bottle at index j to total required height
      j -= 2;                           // Move two positions back (take every second bottle from the sorted array)
    }
    if (r > k) {                        // If total required height exceeds fridge height
      cout << i;                        // Output current count of bottles placed
      return 0;                         // Exit program
    }
  }
  cout << i;                            // If all bottles fit, output n
}


// https://github.com/VaHiX/codeForces/