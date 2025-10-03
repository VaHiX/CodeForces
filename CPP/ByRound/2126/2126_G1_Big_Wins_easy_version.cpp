// Problem: CF 2126 G1 - Big Wins! (easy version)
// https://codeforces.com/contest/2126/problem/G1

/*
G1. Big Wins! (easy version)
Algorithm: Brute force over all possible medians (up to 100), for each median compute maximum difference between it and minimum element in subarrays where that median is valid.
Time Complexity: O(100 * n) = O(n) per test case since 100 is a constant.
Space Complexity: O(n)

This problem asks us to find the maximum value of (median - minimum) over all possible subarrays.
Since a[i] <= min(n, 100), we can enumerate each possible median value from 1 to 100 and check for valid subarrays where this value is indeed the median.
For a fixed median i:
- We convert array elements into +1 (if >= i) or -1 (if < i)
- Compute prefix sums to quickly evaluate how many elements are >= i in any interval
- Then, for every position j, we can determine if there exists a valid subarray ending at j with median >= i
- The key insight is that if Pre[j-1] <= Pre[j], then we can include the current element into such subarray
*/

#include <iostream>
#include <algorithm>

using namespace std;
const int N = 200001;
int A[N], Pre[N], Max[N], Min[N];

int Solve() {
  int n, Ans = 0;
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  
  // Enumerate all possible medians (since a[i] <= 100)
  for (int i = 1; i <= 100; i++) {
    // Pre[j] represents the number of elements >= i from start to j
    for (int j = 1; j <= n; j++)
      Pre[j] = Pre[j - 1] + (A[j] >= i ? 1 : -1);
    
    // Compute minimum prefix sum up to index j
    Min[0] = 0;
    for (int j = 1; j <= n; j++)
      Min[j] = min(Min[j - 1], Pre[j]);
    
    // Compute maximum suffix sum from index j onwards
    Max[n] = Pre[n];
    for (int j = n - 1; j >= 1; j--)
      Max[j] = max(Max[j + 1], Pre[j]);
    
    // Check every position to see if we can form a valid subarray with median exactly i
    for (int j = 1; j <= n; j++) {
      // If either:
      // - there's some previous prefix sum <= current sum --> subarray before j has enough elements >= i
      // - or current prefix sum <= later suffix max --> we can make subarray after j valid
      if (Min[j - 1] <= Pre[j] || Pre[j - 1] <= Max[j])
        Ans = max(Ans, i - A[j]); // Calculate diff between median and minimum so far
    }
  }
  
  return Ans;
}

int main() {
  int T;
  cin >> T;
  while (T--)
    cout << Solve() << endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/