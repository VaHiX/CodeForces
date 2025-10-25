// Problem: CF 1398 C - Good Subarrays
// https://codeforces.com/contest/1398/problem/C

/*
C. Good Subarrays
Algorithm: Prefix Sum with HashMap
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem asks to count the number of "good" subarrays where the sum of elements equals the length of the subarray.
We use a prefix sum approach:
- For each position i, we compute the prefix sum up to that point.
- A subarray from index l to r is good if sum[l..r] = r - l + 1.
- Rearranging: sum[l..r] = r - l + 1 => sum[0..r] - sum[0..l-1] = r - l + 1
- Let prefix_sum = sum[0..r], and prev_prefix = sum[0..l-1]
- This becomes: prefix_sum - prev_prefix = r - l + 1
- Or rearranged: prefix_sum - r = prev_prefix - l + 1
- Define "key" = prefix_sum - i - 1, for index i.
- When we see the same key again, it means there are previous indices that form valid subarrays with current index.

We maintain a map to count occurrences of each key and accumulate results accordingly.
*/

#include <iostream>
#include <map>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::map<long, long> m; // Map to store count of each prefix sum key
    m[0] = 1; // Initialize with 0 to handle subarrays starting from index 0
    long cs(0); // Current prefix sum
    long long ans(0); // Result counter
    for (long p = 0; p < s.size(); p++) {
      cs += s[p] - '0'; // Add current digit to prefix sum
      long cur = cs - p - 1; // Calculate the key for current position
      ++m[cur]; // Increment count of this key
      ans += m[cur] - 1; // Add number of previous occurrences (valid subarrays ending here)
    }
    std::cout << ans << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/