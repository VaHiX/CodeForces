// Problem: CF 1189 A - Keanu Reeves
// https://codeforces.com/contest/1189/problem/A

/*
Problem: Cut a binary string into minimum number of "good" substrings.
A good string has different counts of 0s and 1s.

Algorithm:
- Count total number of 0s and 1s in the string.
- If counts are different, whole string is good -> return 1 part.
- If counts are equal, we must split into at least 2 parts.
  - The strategy is to find the earliest prefix that is good,
    then process the rest recursively (greedy).
  - However, this specific code uses a simpler approach:
    - If counts equal, output 2 parts: first n-1 chars + last char.

Time Complexity: O(n) - single pass through string.
Space Complexity: O(1) - just using fixed size arrays and variables.

*/
#include <stdio.h>
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 310
#define inf 1e9
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;
int main() {
  int i, j, k;
  int n, m, t;
  string s;
  cin >> n >> s;
  int cnt[2] = {0}; // Count of 0s and 1s
  for (i = 0; i < n; i++)
    cnt[s[i] - '0']++; // Increment count based on character
  if (cnt[0] != cnt[1]) // If counts differ, string is already good
    cout << "1\n" << s;
  else { // If counts equal, must split into at least 2 parts
    cout << "2\n";
    for (i = 0; i < n - 1; i++) // Print all but last character
      cout << s[i];
    pfs(" "); // Space between parts
    cout << s[n - 1]; // Last character
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/