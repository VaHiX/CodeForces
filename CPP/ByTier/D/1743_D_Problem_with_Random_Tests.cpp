// Problem: CF 1743 D - Problem with Random Tests
// https://codeforces.com/contest/1743/problem/D

/*
Purpose: This program finds the maximum possible bitwise OR value of two substrings of a binary string.
         It does so by iteratively building a string that maximizes the OR result.
Algorithms/Techniques: 
    - Greedy approach to construct a string that maximizes OR value.
    - For each length i from 1 to 30, we try to extend the current best answer by setting bits in positions 
      such that OR with the prefix gives maximum result.
Time Complexity: O(n * 30) = O(n), where n is the length of the input string.
Space Complexity: O(n) for storing the string and temporary variables.
*/
#include <iostream>
#include <string>

using namespace std;
int n;
string s, t, ans;
int main() {
  cin >> n >> s;
  ans = s; // Initialize answer with the original string
  for (int i = 1; i <= 30; i++) { // Try lengths from 1 to 30 (sufficient for 2^30)
    t = s; // Copy current string to t
    for (int j = i; j < n; j++)
      if (s[j - i] == '1') // If the bit at position j-i is 1
        t[j] = '1'; // Set the bit at position j to 1 to maximize OR
    if (t > ans) // If new string is lexicographically greater (better)
      ans = t; // Update the answer
  }
  int cnt = 0;
  while (ans[cnt] == '0' && cnt < n - 1) // Skip leading zeros
    cnt++;
  cout << ans.substr(cnt) << endl; // Print result without leading zeros
  return 0;
}


// https://github.com/VaHiX/CodeForces/