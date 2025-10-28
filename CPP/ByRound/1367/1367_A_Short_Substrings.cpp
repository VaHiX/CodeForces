// Problem: CF 1367 A - Short Substrings
// https://codeforces.com/contest/1367/problem/A

/*
Problem: Short Substrings
Algorithm: String Reconstruction from All Length-2 Substrings
Time Complexity: O(n) where n is the length of string b
Space Complexity: O(n) for storing the result string

Given a string b formed by concatenating all substrings of length 2 from some original string a,
reconstruct the original string a.

The approach:
- First character of a is same as first character of b
- For every even index i in b, that character belongs to a
- This works because substrings are formed as overlapping pairs
*/
#include <stdio.h>
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 5010
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
int cnt[210];
int main() {
  int i, j, k;
  int n, m, t;
  sf(t);
  while (t--) {
    string s;
    cin >> s;
    string ans; // Result string to be constructed
    ans.pb(s[0]); // First character of a is same as first of b
    n = s.length();
    for (i = 1; i < n; i += 2) // Take every second character from b starting at index 1
      ans.pb(s[i]);
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/