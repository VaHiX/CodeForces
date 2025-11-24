// Problem: CF 1863 A - Channel
// https://codeforces.com/contest/1863/problem/A

/*
 * Problem: Channel
 * Algorithms/Techniques: Simulation, Greedy
 *
 * Time Complexity: O(q) per test case, where q is the length of the string s.
 * Space Complexity: O(1), only using a constant amount of extra space.
 *
 * Description:
 * Petya's channel has n subscribers. Initially, 'a' are online.
 * Over time, a sequence of notifications (s) is received indicating
 * when subscribers go online ('+') or offline ('-').
 * Determine if all n subscribers have read the post:
 * - "YES" if it's guaranteed,
 * - "NO" if impossible,
 * - "MAYBE" if uncertain.
 *
 * Key idea: Track current online count and maximum possible online count.
 * If at any point online count reaches n, we know all have read.
 * At end, if max possible is >= n, return MAYBE, else NO.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, a, q;
    std::cin >> n >> a >> q;
    std::string s;
    std::cin >> s;
    
    long cnt(a), plus(a); // cnt is current online, plus tracks max possible online
    bool all(cnt >= n);   // Flag to see if at any time all are online
    
    for (long p = 0; p < s.size(); p++) {
      plus += (s[p] == '+');     // Update max possible online count
      cnt += (s[p] == '+') - (s[p] == '-'); // Update current online count
      
      if (cnt >= n) {            // If at any time all are online, set flag
        all = true;
      }
    }
    
    if (all) {
      std::cout << "YES" << std::endl;  // Guaranteed all read
    } else {
      std::cout << (plus >= n ? "MAYBE" : "NO") << std::endl; // Maybe or impossible
    }
  }
}


// https://github.com/VaHiX/codeForces/