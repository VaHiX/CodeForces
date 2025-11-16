// Problem: CF 1508 A - Binary Literature
// https://codeforces.com/contest/1508/problem/A

/*
Purpose: 
This code solves the Binary Literature problem where the goal is to construct a bitstring of length at most 3n
that contains at least two of the three given bitstrings of length 2n as subsequences.

Algorithm:
1. For each character position, we decide which bit ('0' or '1') to place in the result string.
2. We use a greedy method where for each position, we count how many of the three input strings have '1' at that position.
   If at least two of them have '1', we place '1' in the result; otherwise we place '0'.
3. We advance pointers in all three input strings as needed to maintain subsequence property.
4. After processing the common prefix, we append the remaining characters from any of the strings.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the result string and input storage

Techniques:
- Greedy algorithm to merge three bitstrings into one
- Subsequence checking via pointer advancement
- Bit manipulation for determining character frequencies

*/

#include <stddef.h>
#include <iostream>
#include <string>

using namespace std;
int t, n;
string s1, s2, s3;
void Process() {
  cin >> n >> s1 >> s2 >> s3;
  string ans = "";
  int i = 0, j = 0, w = 0;
  // Loop through the strings and greedily build the result
  while (i < n * 2 && j < n * 2 && w < n * 2) {
    // Determine the character based on majority rule
    char c = (s1[i] + s2[j] + s3[w] - '0' * 3 >= 2) + '0';
    // Advance pointers if current character matches
    if (s1[i] == c)
      ++i;
    if (s2[j] == c)
      ++j;
    if (s3[w] == c)
      ++w;
    ans += c;
  }
  // Append remaining characters from first string
  if (i >= j || i >= w)
    while (i < n * 2)
      ans += s1[i++];
  // Append remaining characters from second string
  if (j > i || j >= w)
    while (j < n * 2)
      ans += s2[j++];
  // Append remaining characters from third string
  if (w > i || w > j)
    while (w < n * 2)
      ans += s3[w++];
  cout << ans << '\n';
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin >> t;
  while (t--) {
    Process();
  }
}


// https://github.com/VaHiX/CodeForces/