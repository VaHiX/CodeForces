// Problem: CF 1622 B - Berland Music
// https://codeforces.com/contest/1622/problem/B

/*
B. Berland Music
Purpose: Re-evaluate song ratings such that liked songs have higher ratings than disliked ones,
         and the total absolute difference between original and new ratings is minimized.

Algorithms/Techniques:
- Sorting with custom key to assign ranks
- Greedy assignment of new ratings based on like/dislike votes

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing vectors and pairs

Input:
- t: number of test cases
- n: number of songs
- p: predicted ratings (permutation)
- s: vote string ('1' = like, '0' = dislike)

Output:
- Re-evaluated permutation q minimizing sum of |p_i - q_i|
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  const long M = 1e7; // Large value to encode vote into rating for sorting
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<std::pair<long, long>> v(n); // Store (rating * M + vote, index)
    for (long p = 0; p < n; p++) {
      std::cin >> v[p].first;
      v[p].second = p; // Store original index
    }
    std::string s;
    std::cin >> s;
    for (long p = 0; p < n; p++) {
      v[p].first += M * (s[p] - '0'); // Encode vote into rating for sorting
    }
    sort(v.begin(), v.end()); // Sort by encoded value (rating first, then vote)
    std::vector<long> w(n, 0); // Result array to store new ratings
    for (long p = 0; p < n; p++) {
      w[v[p].second] = p + 1; // Assign ranks based on sorted order
    }
    for (long p = 0; p < n; p++) {
      std::cout << w[p] << " "; // Output the new permutation
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/