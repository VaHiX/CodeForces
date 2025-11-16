// Problem: CF 1216 A - Prefixes
// https://codeforces.com/contest/1216/problem/A

/*
Purpose: 
This code solves the problem of making every prefix of even length in a string 's' 
have an equal number of 'a' and 'b'. It does so by iterating through the string 
in pairs of characters and ensuring that each pair contains one 'a' and one 'b'.
If a pair has two identical characters, it changes one of them to the opposite 
character to balance the prefix.

Algorithm:
- Iterate over the string in steps of 2 (processing pairs of characters).
- For each pair, if the characters are the same, change one of them to make 
  the pair balanced (one 'a', one 'b').
- Count the number of such changes needed.

Time Complexity: O(n), where n is the length of the string. We process each 
                 pair of characters once.

Space Complexity: O(1), excluding the input string, as we only use a constant 
                  amount of additional space.
*/

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long cnt(0);
  for (long p = 1; p < s.size(); p += 2) {
    // Check if the pair of characters at positions p-1 and p are equal
    if (s[p] != s[p - 1]) {
      continue; // If they are different, no operation needed
    }
    // If they are the same, change the character at position p to make the pair balanced
    s[p] = (s[p - 1] == 'a' ? 'b' : 'a');
    ++cnt;
  }
  std::cout << cnt << std::endl;
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/