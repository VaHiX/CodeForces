// Problem: CF 1923 D - Slimes
// https://codeforces.com/contest/1923/problem/D

/*
Algorithm: Slimes
Purpose: For each slime, compute the minimum number of seconds it takes to be eaten by another slime.
Techniques: 
- Preprocessing with prefix sums for efficient range sum queries.
- Binary search to find the nearest slime that can eat the current slime from left or right.
- Grouping same-sized slimes for optimization.

Time Complexity: O(n log n) per test case due to binary search for each slime.
Space Complexity: O(n) for storing health, prefix sums, and left/right boundaries.
*/

#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

// Function to compute minimum steps for slime at 'pos' to be eaten from the left
int computeLeftSteps(int pos, int *health, long long *sum, int *left, int n) {
  int leftPos = left[pos - 1];  // Position of the leftmost slime in the group
  int low = 1, high = leftPos;  // Binary search bounds
  while (low <= high) {
    int mid = (low + high) >> 1;  // Midpoint calculation
    if (sum[pos - 1] - sum[mid - 1] > health[pos]) {  // If sum of slimes between mid and pos is greater than current slime
      low = mid + 1;  // Move right to find smaller sum
    } else {
      high = mid - 1;  // Move left to find larger sum
    }
  }
  if (high == 0) {
    return n + 1;  // Impossible to be eaten from left
  }
  return pos - high;  // Steps needed
}

// Function to compute minimum steps for slime at 'pos' to be eaten from the right
int computeRightSteps(int pos, int *health, long long *sum, int *right, int n) {
  int rightPos = right[pos + 1];  // Position of the rightmost slime in the group
  int low = rightPos, high = n;  // Binary search bounds
  while (low <= high) {
    int mid = (low + high) >> 1;  // Midpoint calculation
    if (sum[mid] - sum[pos] > health[pos]) {  // If sum of slimes between pos and mid is greater than current slime
      high = mid - 1;  // Move left to find smaller sum
    } else {
      low = mid + 1;  // Move right to find larger sum
    }
  }
  if (low == n + 1) {
    return n + 1;  // Impossible to be eaten from right
  }
  return low - pos;  // Steps needed
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int t;
  cin >> t;
  while (t-- > 00) {
    int n;
    cin >> n;
    int health[n + 1], left[n + 1], right[n + 1];
    long long sum[n + 1];
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= n; ++i) {
      cin >> health[i];
      sum[i] = sum[i - 1] + health[i];  // Prefix sum calculation
    }
    int i = 1;
    while (i <= n) {
      int j = i;
      while (j <= n and health[i] == health[j]) {  // Group consecutive same-sized slimes
        j++;
      }
      for (int k = i; k < j; ++k) {
        right[k] = j;  // Right boundary for all slimes in the group
        left[k] = i - 1;  // Left boundary for all slimes in the group
      }
      i = j;
    }
    for (int i = 1; i <= n; ++i) {
      int steps = n + 1;  // Initially impossible
      if (i - 1 >= 1) {
        if (health[i - 1] > health[i]) {  // If immediate neighbor can eat
          steps = 1;
        } else {
          steps = min(steps, computeLeftSteps(i, health, sum, left, n));  // Binary search for possible left eater
        }
      }
      if (i + 1 <= n) {
        if (health[i + 1] > health[i]) {  // If immediate neighbor can eat
          steps = 1;
        } else {
          steps = min(steps, computeRightSteps(i, health, sum, right, n));  // Binary search for possible right eater
        }
      }
      if (steps == n + 1) {
        steps = -1;  // No valid eater found
      }
      cout << steps << " ";
    }
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/