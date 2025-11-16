// Problem: CF 1997 A - Strong Password
// https://codeforces.com/contest/1997/problem/A

/*
 * Problem: Strong Password
 * 
 * Purpose: To insert exactly one lowercase letter into the given password to maximize the typing time.
 * 
 * Algorithm:
 * - For each test case, analyze the string to determine where to insert a character.
 * - Identify the first position where two consecutive characters are the same, to maximize the number of different character transitions.
 * - Insert a character that is different from the character at the identified position to increase the typing time.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1) additional space (excluding input/output strings).
 */

#include <stddef.h>
#include <iostream>
#include <string>

#define endl '\n'
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 3;
ll i, j, p, q, n, m, k, a[maxn], t;

void solve() {
  string s;
  cin >> s;
  p = 0;
  // Find the first position where two adjacent characters are equal
  for (i = 0; i < s.size() - 1; i++) {
    if (s[i] == s[i + 1]) {
      p = i + 1;
      break;
    }
  }
  string f = "a"; // default character to insert
  if (s[p] == 'a') // if the character at p is 'a', use 'b' to make it different
    f = "b";
  // Insert the chosen character at position p
  s.insert(p, f);
  cout << s << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/