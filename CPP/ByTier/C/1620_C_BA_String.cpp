// Problem: CF 1620 C - BA-String
// https://codeforces.com/contest/1620/problem/C

/*
Algorithm: Digit DP / Enumeration with Prefix Sum
Purpose: Given a string with 'a' and '*' characters, replace '*' with 0 to k 'b's,
         and find the x-th lexicographically smallest resulting string.

Time Complexity: O(n^2) for each test case, where n is the length of the string.
Space Complexity: O(n), for storing the result string.

Approach:
1. Process the string from right to left.
2. For each '*', we calculate how many combinations exist to the right (including this '*').
3. When we reach a 'a' or the beginning of the string, we determine how many 'b's should be placed
   at this position by taking x modulo the number of ways to arrange the suffix.
4. This simulates a base-(k+1) number system where we are computing the x-th number.

Key variables:
- x: the 0-indexed position of the desired string in sorted order.
- t: cumulative number of combinations to the right of current position.
- a: result string built in reverse.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>

#define ll long long
using namespace std;

int main() {
  ll T, n, k, x, t;
  string s, a;
  for (scanf("%lld", &T), t = 0; T; T--) {
    cin >> n >> k >> x >> s;
    x--; // Convert to 0-indexed
    a = "";
    for (ll i = n - 1; i + 1; i--) {
      if (s[i] == 'a') {
        a += "a"; // 'a' remains unchanged
        continue;
      }
      t += k; // Add possible 'b' counts for current '*'
      if (i == 0 || s[i - 1] == 'a') { // If this is last '*' or preceded by 'a'
        a += string(x % (t + 1), 'b'); // Append 'b's based on x mod (t+1)
        x /= (t + 1); // Move to next level in our number system
        t = 0; // Reset for next '*'
      }
    }
    reverse(a.begin(), a.end()); // Reverse to get final correct order
    cout << a << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/