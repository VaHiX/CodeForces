// Problem: CF 2108 D - Needle in a Numstack
// https://codeforces.com/contest/2108/problem/D

/*
 * Problem: D. Needle in a Numstack
 *
 * Purpose: Given a concatenated array C of two arrays A and B, each of length at least k,
 * where each array has the property that no k consecutive elements are the same,
 * determine the lengths of arrays A and B by querying elements.
 *
 * Algorithms/Techniques:
 * - Binary search to find position of transition between arrays A and B
 * - Interactive guessing using queries based on constraints of k-consecutive distinct elements
 *
 * Time Complexity: O(n * log(n)) in worst case due to binary search and query limits.
 * Space Complexity: O(1) - only a few variables used, no extra space proportional to input.
 */

#include <algorithm>
#include <iostream>

using namespace std;
int n, k;

// Function to ask for element at index t (1-based)
int ask(int t) {
  int ans;
  cout << "? " << t + 1 << endl; // Query the element at index t+1 (1-based indexing)
  cin >> ans;
  return ans;
}

// Binary search to find position where the pattern changes
int find(int p, int ans) {
  int l = 1, r = (n - p - 1) / k + 1, mid;
  while (l <= r) {
    mid = (l + r) / 2; // Midpoint for binary search
    if (ask(k * (mid - 1) + p) == ans) { // Query element at position k*(mid-1)+p
      l = mid + 1;
    } else
      r = mid - 1;
  }
  return r; // Return the valid right boundary found by binary search
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> k;
    if (n == 2 * k) { // Edge case: if total length equals sum of two array lengths
      cout << "! " << k << " " << k << endl;
      continue;
    }
    int p, ans1, ans2;
    for (p = 0; p < k; p++) { // Try to find mismatch in first k elements
      ans1 = ask(p); // Query element at position p
      ans2 = ask(k * ((n - p - 1) / k) + p); // Query symmetric element from end
      if (ans1 != ans2) {
        break;
      }
    }
    if (p == k) { // If all first k elements are same, it's impossible to tell
      cout << "! -1" << endl;
      continue;
    }
    int t = find(p, ans1); // Find transition point with binary search
    int r = min(k * t + p - 1, n - k - 1); // Right boundary for current segment
    p += max(0, k - 1 - (k * (t - 1) + p)); // Adjust starting index
    int l = k * (t - 1) + p; // Left boundary of valid segment
    int sta = l; // Store start of this range
    for (int i = 1; i < k - p && l < r && sta + i <= r; i++) { // Iterate in current range
      ans1 = ask(p + i); // Query left element
      ans2 = ask(k * ((n - (p + i) - 1) / k) + (p + i)); // Query symmetric right element
      if (ans1 != ans2) { // If they are different, check if it's part of the solution
        ans2 = ask(sta + i); // Re-query to validate
        if (ans1 == ans2) { // Confirm left side
          l = sta + i;
        } else { // Otherwise, adjust right boundary
          r = sta + i - 1;
        }
      }
    }
    if (l == r) {
      cout << "! " << l + 1 << " " << n - l - 1 << endl; // Output solution
    } else {
      cout << "! -1" << endl; // Impossible to determine uniquely
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/