// Problem: CF 2167 B - Your Name
// https://codeforces.com/contest/2167/problem/B

/*
Code Purpose:
This program determines whether the letters of a given string 's' can be rearranged to form another string 't'.
The approach is to sort both strings and compare them. If the sorted versions are equal, then it's possible to rearrange 's' into 't'.

Algorithms/Techniques:
- Sorting: Both strings are sorted lexicographically.
- Comparison: After sorting, the strings are directly compared for equality.

Time Complexity:
- O(n log n) per test case, where n is the length of the strings.
  This is due to the sorting step; comparison takes O(n).

Space Complexity:
- O(n), where n is the length of the strings.
  This accounts for the space used by the two string variables and the sorting operation (in-place sorting).

*/
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
typedef long long int ll;
#define M 1000000007
#define sort(v) sort(v.begin(), v.end())
void solve() {
  ll n;
  cin >> n;
  string s, ss; // s is the initial string, ss is the target string
  cin >> s >> ss;
  sort(s); // Sort the characters in s
  sort(ss); // Sort the characters in ss
  if (s == ss) { // If sorted strings are equal, then s can be rearranged to form ss
    cout << "YES" << "\n";
    return;
  }
  cout << "NO" << "\n";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/