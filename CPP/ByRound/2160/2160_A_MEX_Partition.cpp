// Problem: CF 2160 A - MEX Partition
// https://codeforces.com/contest/2160/problem/A

/* 
 * Problem: A. MEX Partition
 * Algorithms/Techniques: Counting, Greedy, MEX calculation
 * 
 * Time Complexity: O(n) per test case, where n is the size of input multiset.
 * Space Complexity: O(1), since we use a fixed-size array of size 102.
 *
 * The solution works by counting occurrences of each number in the range [0, 101].
 * Then, it finds the smallest non-negative integer (MEX) that is missing from the counts.
 * This corresponds to the minimum possible score for any valid partition.
 */

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define int long long

void solve() {
  int n;
  cin >> n;
  vector<int> cnt(102, 0); // Count array for numbers in range [0, 101]
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (x <= 101) { // Only process numbers up to 101
      cnt[x]++;
    }
  }
  for (int i = 0; i <= 101; i++) {
    if (cnt[i] == 0) { // Find the first missing number (MEX)
      cout << i << endl;
      return;
    }
  }
}

int32_t main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/