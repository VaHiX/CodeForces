// Problem: CF 1076 A - Minimizing the String
// https://codeforces.com/contest/1076/problem/A

#include <iostream>
#include <string>

using namespace std;
int n, i;
string s;
int main() {
  cin >> n >> s;
  // Find the first position where s[i] > s[i+1], which is the point to remove
  // to make the string lexicographically smallest
  while (i < n && s[i++] <= s[i])
    ;
  // Remove the character at index (i-1) to minimize lexicographically
  s.erase(s.begin() + i - 1);
  cout << s;
}
/*
Purpose: This code removes at most one character from a string to make it
         lexicographically smallest.
Algorithm: Greedy approach - find the first position where s[i] > s[i+1]
           and remove that character. If no such position exists, remove the
           last character.
Time Complexity: O(n) - single pass through the string
Space Complexity: O(1) - uses only a constant amount of extra space (excluding input)
*/

// https://github.com/VaHiX/codeForces/