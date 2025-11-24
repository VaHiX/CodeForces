// Problem: CF 798 B - Mike and strings
// https://codeforces.com/contest/798/problem/B

/*
Code Purpose:
This code solves the problem of finding the minimum number of moves to make all strings equal,
where a move consists of taking the first character of a string and appending it to the end.
The approach is to try each string as a target and compute the minimum rotations needed
to transform all strings into that target.

Algorithms/Techniques:
1. Brute-force approach: try each string as the target string.
2. For each target, calculate number of rotations required for all other strings.
3. If any string cannot be transformed into the target, return -1.
4. Use rotation technique to simulate moves (remove first char, append to end).

Time Complexity: O(n * L * n * L) = O(n^2 * L^2)
where n is number of strings and L is the length of each string.
Space Complexity: O(n * L) for storing the strings.
*/

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <string>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
#define inf INT_MAX
using namespace std;
int main() {
  int i, j, k;
  int n, sum, m;
  cin >> n;
  char ch;
  string s[n], t, z;
  for (i = 0; i < n; i++)
    cin >> s[i];
  m = inf;
  for (i = 0; i < n; i++) {
    sum = 0;
    for (j = 0; j < n; j++) {
      t = s[j];
      k = 0;
      // Try to rotate string s[j] to match s[i]
      while (t != s[i]) {
        if (k == s[j].length()) {
          cout << "-1";
          return 0;
        }
        ch = t.front(); // Get first character
        z = t;
        reverse(z.begin(), z.end());
        z.pop_back();   // Remove last character (which was originally first)
        reverse(z.begin(), z.end());
        z.push_back(ch); // Append the first character to end
        t = z;
        sum++;
        k++;
      }
    }
    m = min(m, sum);
  }
  cout << m;
  return 0;
}


// https://github.com/VaHiX/CodeForces/