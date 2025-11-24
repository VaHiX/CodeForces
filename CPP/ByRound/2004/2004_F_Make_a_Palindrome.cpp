// Problem: CF 2004 F - Make a Palindrome
// https://codeforces.com/contest/2004/problem/F

/*
F. Make a Palindrome
Algorithms/Techniques: Prefix sum, two pointers, hash map for frequency counting.
Time Complexity: O(n^2) per test case, where n is the size of the array.
Space Complexity: O(n^2) due to the hash map storing prefix sums and their frequencies.

This code computes the sum of minimum operations needed to make every subarray of
the given array into a palindrome. It uses a prefix sum approach combined with
a hash map to efficiently calculate how many previous occurrences of a prefix sum
exist, which helps determine the number of operations for each subarray.
*/

#include <iostream>
#include <unordered_map>

using namespace std;
const int maxn = 2e5 + 10;
int n, a[maxn];

void sol() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  
  // Hash map to store frequency of prefix sums
  unordered_map<int, int> cnt(n * n * 2); // Pre-allocate hash table size
  
  long long ans = 0;
  
  // Iterate over all starting points of subarrays
  for (int i = 1; i <= n; ++i) {
    int s = 0; // Running prefix sum
    // For each start point, iterate through ending points
    for (int j = i; j <= n; ++j) {
      s += a[j]; // Add current element to prefix sum
      
      // cnt[s] gives number of previous occurrences of this prefix sum
      // j - i - cnt[s] calculates how many operations needed for subarray [i..j]
      ans += j - i - cnt[s]++;
    }
  }
  
  cout << ans << '\n';
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    sol();
}


// https://github.com/VaHiX/codeForces/