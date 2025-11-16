// Problem: CF 2126 G1 - Big Wins! (easy version)
// https://codeforces.com/contest/2126/problem/G1

/*
 * Problem: G1. Big Wins! (easy version)
 * Algorithm: Brute force over all possible medians up to 100, using prefix sums to efficiently calculate subarray properties.
 * Time Complexity: O(100 * n) = O(n), since max value of array elements is 100.
 * Space Complexity: O(n)
 *
 * For each possible median value i from 1 to 100:
 *   - Create a binary prefix sum array (Pre), where +1 if A[j] >= i, else -1
 *   - Compute Min and Max arrays to track minimum and maximum prefix sums
 *   - For each subarray ending at j, check if it's valid based on prefix sums,
 *     and update answer with max(i - A[j]) for valid cases
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
  
  // Loop over all possible values of median (since max element is at most 100)
  for (int i = 1; i <= 100; i++) {
    
    // Build prefix sum array where Pre[j] = #elements >= i - #elements < i
    for (int j = 1; j <= n; j++)
      Pre[j] = Pre[j - 1] + (A[j] >= i ? 1 : -1);
    
    // Initialize Min and Max arrays to store min prefix sum up to index j and max suffix up to index j
    Min[0] = 0, Max[n] = Pre[n];
    for (int j = 1; j <= n; j++)
      Min[j] = min(Min[j - 1], Pre[j]);
    for (int j = n - 1; j >= 1; j--)
      Max[j] = max(Max[j + 1], Pre[j]);

    // Check every ending position of subarray to see if we can form valid median
    for (int j = 1; j <= n; j++)
      if (Min[j - 1] <= Pre[j] || Pre[j - 1] <= Max[j])
        Ans = max(Ans, i - A[j]);
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


// https://github.com/VaHiX/CodeForces/