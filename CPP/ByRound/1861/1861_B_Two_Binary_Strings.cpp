// Problem: CF 1861 B - Two Binary Strings
// https://codeforces.com/contest/1861/problem/B

/*
B. Two Binary Strings

Algorithm/Technique: Direct comparison of adjacent character pairs in both strings.

Time Complexity: O(n) where n is the length of the string (for each test case).
Space Complexity: O(1) (only using a few variables, no extra space proportional to input size).

The problem allows merging equal characters in a string to make it uniform between them.
We can only perform operations that merge segments of identical characters.
The key insight is that we just need to check whether there exists a pair of adjacent characters
in both strings such that one is '0' and the other is '1', or vice versa, because:
- If at any point both strings have same character pattern, then all transitions can be made equal.
- So, if we find even one place where both strings match in '0' followed by '1', or '1' followed by '0',
  it's possible to make strings equal with operations.

However, the current implementation checks for a specific case:
- A transition from '0' to '1' in both strings at some index p (i.e., a[p] = '1' && b[p] = '1' && a[p-1] = '0' && b[p-1] = '0')
  This condition ensures there's an opportunity to align parts of the strings.

If such a pair is found, it means we can possibly merge or adjust parts to make strings equal.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t;
  
  while (t--) {
    std::string a, b;
    std::cin >> a >> b;
    
    bool possible(false); // Flag to determine if it's possible to make strings equal
    
    // Loop through all positions except the first and last ones
    for (long p = 1; !possible && p < a.size(); p++) {
      // Check if both strings have '1' at position p, and '0' at position p-1
      // This condition implies there's a potential to align both strings
      if (a[p] == '1' && b[p] == '1' && a[p - 1] == '0' && b[p - 1] == '0') {
        possible = true;
      }
    }
    
    // Output result based on flag
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}



// https://github.com/VaHiX/codeForces/