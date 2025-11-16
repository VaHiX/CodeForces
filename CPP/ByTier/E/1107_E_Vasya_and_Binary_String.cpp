// Problem: CF 1107 E - Vasya and Binary String
// https://codeforces.com/contest/1107/problem/E

/*
E. Vasya and Binary String
Algorithms/Techniques: Dynamic Programming with Interval Decomposition
Time Complexity: O(n^3)
Space Complexity: O(n^3)

This problem uses dynamic programming to find the maximum points achievable 
by erasing consecutive substrings of equal characters from a binary string.
The solution considers all possible ways to split the current substring and 
recursively calculates the best score, memoizing results to avoid recomputation.

Key idea:
- For each interval [l, r], we try to decompose it into smaller intervals.
- If s[l] == s[i], we can erase s[l..i] together and recurse on the remaining parts.
- The DP state f[l][r][pre] stores the maximum points for interval [l,r] with prefix count 'pre'.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int n, a[200];
char s[200];
long long f[200][200][200];

long long solve(int l, int r, int pre) {
  if (l > r)
    return 0;
  if (l == r)
    return a[pre]; // Points for erasing single character with prefix count 'pre'
  long long &ans = f[l][r][pre];
  if (ans)
    return ans;
  ans = a[pre] + solve(l + 1, r, 1); // Erase s[l] alone and proceed
  for (int i = l + 1; i <= r; i++)
    if (s[l] == s[i])
      ans = max(ans, solve(l + 1, i - 1, 1) + solve(i, r, pre + 1)); // Split at i and recurse
  return ans;
}

int main() {
  cin >> n;
  cin >> s + 1; // 1-indexed string input
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  cout << solve(1, n, 1) << endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/