// Problem: CF 2025 A - Two Screens
// https://codeforces.com/contest/2025/problem/A

/*
 * Problem: A. Two Screens
 * Algorithms/Techniques: Greedy, String Matching
 *
 * Time Complexity: O(min(|s|, |t|)) per test case
 * Space Complexity: O(|s| + |t|) per test case
 *
 * The solution computes the minimal time to display strings s and t on two screens.
 * It uses the idea that if the strings share a common prefix, we can copy that part,
 * minimizing the total operations. Each character must be written at least once,
 * but shared prefix can be copied instead of re-typed.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string a, b;
    std::cin >> a >> b;
    
    // Initial estimate: all characters of both strings need to be typed
    long ans = a.size() + b.size() + (a[0] == b[0]);
    
    // Reduce the count by 2 for each matching character in prefix (once for typing, once for copying)
    for (long p = 0; p < a.size() && p < b.size() && a[p] == b[p]; p++) {
      --ans;
    }
    
    std::cout << ans << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/