// Problem: CF 1736 D - Equal Binary Subsequences
// https://codeforces.com/contest/1736/problem/D

/*
Purpose: 
This code solves the problem of partitioning a binary string of length 2n into two disjoint equal subsequences after performing exactly one right rotation operation on a chosen subsequence.

The algorithm uses a greedy approach to identify positions that need to be rotated to make the string have a structure where equal subsequences can be formed.

Time Complexity: O(n) - The algorithm makes a single pass through the input string.
Space Complexity: O(n) - The array t stores indices for rotation operation.
*/
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
int T, n, sum, tot, t[100001]; // t stores indices of elements to be rotated
string s;
void solve() {
  cin >> n >> s, sum = tot = 0;
  // Count number of '1's in the string
  for (int i = 0; i < (n << 1); i++)
    sum += s[i] & 1;
  // Check if total number of 1s is odd, if so, impossible to split into two equal subsequences
  if (sum & 1) {
    puts("-1");
    return;
  }
  // Loop through pairs of consecutive characters to find mismatches
  for (int i = 0; i < (n << 1); i += 2)
    if (s[i] != s[i + 1]) {
      // If s[i] is '1' and we are at an odd parity position, schedule s[i] for rotation
      if ((s[i] & 1) == (tot & 1))
        t[++tot] = i + 1;
      else
        // Else schedule s[i+1] for rotation
        t[++tot] = i + 2;
    }
  // Output indices to be rotated
  cout << tot << ' ';
  for (int i = 1; i <= tot; i++)
    cout << t[i] << ' ';
  putchar('\n');
  // Output indices for first subsequence
  for (int i = 1; i <= n; i++)
    cout << 2 * i << ' ';
  putchar('\n');
}
int main() {
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/