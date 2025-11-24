// Problem: CF 1994 B - Fun Game
// https://codeforces.com/contest/1994/problem/B

/*
B. Fun Game

Purpose:
This code determines whether it's possible to transform a binary sequence s into another binary sequence t using a specific operation. The allowed operation is to choose a range [l, r] and for each i in that range, update s[i] = s[i] XOR s[i-l+1]. 

Algorithm:
The key insight is that we can only change a position if the corresponding prefix of s has a '0' before it. If all elements of s up to any position are '0', then the operation cannot make changes, hence if t differs from s at any such position, it's impossible to transform.

Time Complexity: O(n) per test case, where n is the length of the sequences.
Space Complexity: O(1) excluding input storage.

Techniques:
- Linear scanning with early termination for efficiency.
- Bitwise XOR operations on binary strings.

*/

#include <iostream>
#include <string>

int main() {
  long q;
  std::cin >> q;
  while (q--) {
    long n;
    std::cin >> n;
    std::string s, t;
    std::cin >> s >> t;
    bool possible(true);
    for (long p = 0; possible && p < s.size(); p++) {
      if (s[p] == '1') { // If current element in s is '1', we can potentially make changes
        break;
      } else if (t[p] == '1') { // If t has a '1' at this position but s does not, it's impossible to reach t
        possible = false;
      }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/