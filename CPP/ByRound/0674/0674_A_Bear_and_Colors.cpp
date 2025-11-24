// Problem: CF 674 A - Bear and Colors
// https://codeforces.com/contest/674/problem/A

/*
 * Problem: Bear and Colors
 * Algorithm: Brute Force with Frequency Counting
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 * 
 * Approach:
 * For each starting index i, we iterate through all intervals [i, j] ending at j.
 * We maintain a frequency array to count occurrences of each color in the current interval.
 * We track the dominant color (with highest frequency, smallest index in case of tie).
 * For every interval, we increment the count for the dominant color.
 * Finally, we output the count for each color.
 */

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
const int N = 5005;
int frq[N], n, arr[N], mx, ans[N], best;
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
  for (int i = 0; i < n; i++) {
    memset(frq, 0, sizeof(frq)); // Reset frequency array for new starting point
    mx = best = -1;              // Reset max frequency and best color
    for (int j = i; j < n; j++) {
      frq[arr[j]]++;                             // Increment frequency of current color
      if (frq[arr[j]] > mx || (frq[arr[j]] == mx && arr[j] < best)) {
        mx = frq[arr[j]];                        // Update max frequency
        best = arr[j];                           // Update best (dominant) color
      }
      ans[best]++;                               // Increment count for dominant color
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " ";                     // Output result for each color
  }
  cout << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/