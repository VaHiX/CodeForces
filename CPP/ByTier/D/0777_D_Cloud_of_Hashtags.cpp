// Problem: CF 777 D - Cloud of Hashtags
// https://codeforces.com/contest/777/problem/D

#include <iostream>
#include <vector>
#include <string>

/*
Algorithm: Greedy approach with suffix trimming
Time Complexity: O(L) where L is the total length of all hashtags
Space Complexity: O(L) for storing the hashtags

The algorithm processes hashtags from right to left. For each hashtag,
it determines the longest prefix that maintains lexicographical order
with the previous hashtag. It trims the current hashtag to this prefix.
This greedy approach ensures minimal deletions while maintaining order.
*/

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<std::string> a(n);
  for (long p = 0; p < n; p++) {
    std::cin >> a[p];
  }
  // Start with the last hashtag as the reference for comparison
  std::string prev = a[n - 1];
  // Process from second-to-last hashtag to the first
  for (long p = n - 2; p >= 0; p--) {
    long index(0);
    // Compare characters one by one
    while (index < a[p].size()) {
      // If we've reached the end of the previous hashtag, we can keep all chars of current
      if (index >= prev.size()) {
        break;
      }
      // If current character is smaller, we can keep all chars up to this point
      if (a[p][index] < prev[index]) {
        index = a[p].size();
        break;
      }
      // If current character is larger, we must stop here to maintain order
      if (a[p][index] > prev[index]) {
        break;
      }
      ++index;
    }
    // Trim the current hashtag to the valid prefix
    a[p] = a[p].substr(0, index);
    // Update the previous hashtag for next iteration
    prev = a[p];
  }
  for (long p = 0; p < n; p++) {
    std::cout << a[p] << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/