// Problem: CF 1368 B - Codeforces Subsequences
// https://codeforces.com/contest/1368/problem/B

/*
B. Codeforces Subsequences
Algorithm: Greedy allocation of characters to maximize subsequence count
Time Complexity: O(10 * log(k)) = O(log(k)) since the loop runs at most 10 * log(k) times
Space Complexity: O(1) - only using fixed size vector of 10 elements

The approach works by:
1. Starting with a base string "codeforces" (each character appears once)
2. Distributing additional characters greedily to maximize the number of subsequences
3. Each iteration, we increment one count in the vector and update product accordingly
4. The final result is built by repeating each character according to its count

This greedy method ensures the minimal length string that satisfies the subsequence requirement.
*/
#include <iostream>
#include <string>
#include <vector>
typedef long long ll;
int main() {
  const std::string t = "codeforces"; // Target string for subsequences
  std::vector<ll> v(t.size(), 1);     // Initialize count of each character to 1
  ll prod(1);                         // Product of all counts (represents total subsequences)
  ll idx(0);                          // Current index for greedy distribution
  ll k;                               // Target number of subsequences
  std::cin >> k;
  while (prod < k) {                  // While we don't have enough subsequences
    prod /= v[idx];                   // Remove contribution of current index
    ++v[idx];                         // Increase count at current index
    prod *= v[idx];                   // Add back updated contribution
    idx = (idx + 1) % t.size();       // Move to next index cyclically
  }
  for (long p = 0; p < t.size(); p++) { // Output final string by repeating characters
    std::cout << std::string(v[p], t[p]);
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/