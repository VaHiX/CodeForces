// Problem: CF 672 B - Different is Good
// https://codeforces.com/contest/672/problem/B

/*
B. Different is Good
Problem: Make all substrings of a string distinct with minimum changes, or return -1 if impossible.

Algorithms/Techniques: 
- Use a set to count unique characters in the string.
- If the string length exceeds 26 (number of lowercase letters), it's impossible to make all substrings distinct.
- The minimum number of changes needed equals the difference between total length and unique character count.

Time Complexity: O(n), where n is the length of the string (due to one pass through the string and set operations).
Space Complexity: O(1), since the set stores at most 26 characters (constant space).

Input:
- First line: n (length of string)
- Second line: string s of length n
Output:
- Minimum changes needed, or -1 if impossible.
*/

#include <cstdio>
#include <iostream>
#include <set>
#include <string>

const int N = 26;
int main() {
  long n;
  std::string s;
  std::cin >> n >> s;
  if (s.size() > N) {  // If string length exceeds number of lowercase letters, impossible
    puts("-1");
    return 0;
  }
  std::set<char> c;  // Set to store unique characters
  for (int p = 0; p < s.size(); p++) {
    c.insert(s[p]);  // Insert each character into the set
  }
  printf("%ld\n", s.size() - c.size());  // Difference gives minimum changes needed
  return 0;
}


// https://github.com/VaHiX/codeForces/