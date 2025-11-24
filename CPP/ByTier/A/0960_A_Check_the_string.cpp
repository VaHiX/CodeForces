// Problem: CF 960 A - Check the string
// https://codeforces.com/contest/960/problem/A

/*
Purpose: Determine if a given string can be formed by appending 'c's equal to either the count of 'a's or 'b's,
         after the sequence 'a's followed by 'b's followed by 'c's.
Algorithm: 
    1. Validate that the string is in the correct order (all 'a's, then all 'b's, then all 'c's).
    2. Count the number of 'a's, 'b's, and 'c's.
    3. Check that there is at least one 'a' and one 'b'.
    4. Check if the number of 'c's equals the count of 'a's or 'b's.
Time Complexity: O(n log n) due to sorting, where n is the length of the string.
Space Complexity: O(n) for storing the character vector.
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 150
#define inf 1000000
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d\n", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s\n", s)
#define pb(n) push_back(n)
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  int x, y, z;
  string s;
  cin >> s;
  n = s.length();
  x = 0;
  y = 0;
  z = 0;
  vector<char> ch;
  for (i = 0; i < n; i++)
    ch.pb(s[i]);
  sort(ch.begin(), ch.end());
  // Check if the original string is already sorted (i.e. 'a's, then 'b's, then 'c's)
  for (i = 0; i < n; i++) {
    if (ch[i] != s[i]) {
      cout << "NO";
      return 0;
    }
  }
  // Count occurrences of each character
  for (i = 0; i < n; i++) {
    if (s[i] == 'a')
      x++;
    else if (s[i] == 'b')
      y++;
    else if (s[i] == 'c')
      z++;
  }
  // Ensure at least one 'a' and one 'b' exist
  if (x == 0 || y == 0) {
    cout << "NO";
    return 0;
  }
  // Check if number of 'c's matches the count of 'a's or 'b's
  if (z == x || z == y)
    cout << "YES";
  else
    cout << "NO";
  return 0;
}


// https://github.com/VaHiX/CodeForces/