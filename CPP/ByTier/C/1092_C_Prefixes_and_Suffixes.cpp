// Problem: CF 1092 C - Prefixes and Suffixes
// https://codeforces.com/contest/1092/problem/C

/*
C. Prefixes and Suffixes
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Ivan wants to play a game with you. He picked some string s of length n consisting only of lowercase Latin letters. 
You don't know this string. Ivan has informed you about all its improper prefixes and suffixes (i.e. prefixes and suffixes of lengths from 1 to n-1), but he didn't tell you which strings are prefixes and which are suffixes.
Ivan wants you to guess which of the given 2n-2 strings are prefixes of the given string and which are suffixes. It may be impossible to guess the string Ivan picked (since multiple strings may give the same set of suffixes and prefixes), but Ivan will accept your answer if there is at least one string that is consistent with it. Let the game begin!

Algorithm:
- Sort all input strings by length
- Match pairs of strings of same length (first string should be prefix, second suffix or vice versa)
- When unmatched single pair remains, try to assign them as prefix/suffix optimally based on their substructure
- Use greedy assignment for remaining strings

Time Complexity: O(n^2 * log n) where n is the length of the string due to sorting and nested loops
Space Complexity: O(n^2) for storing strings and tracking assignments
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 100100
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
#define pp pair<string, int>
using namespace std;

bool cmp(pp a, pp b) { return a.first.length() < b.first.length(); }

int main() {
  int i, j, k;
  int n, m, t;
  sf(n);
  if (n == 2) {
    pfs("PS\n");
    return 0;
  }
  n = 2 * n - 2; // total number of prefixes and suffixes
  pp a[n];
  string x, y;
  for (i = 0; i < n; i++)
    cin >> x, a[i] = {x, i}; // store each string with its original index

  sort(a, a + n, cmp); // sort strings based on their lengths

  map<int, int> mp; // to track which indices are already assigned
  int ans[n];
  memset(ans, 0, sizeof(ans)); // initialize all answers as 0 (unassigned)

  k = -1; // index of unmatched pair if exists
  m = 0;  // count of matched strings

  // iterate from longest to shortest (reverse order) and match pairs
  for (i = n - 1; i >= 0; i -= 2) {
    x = a[i].first;
    y = a[i - 1].first;
    if (x == y) { // if matched pair found
      ans[a[i].second] = 1;  // assign first as prefix (P)
      ans[a[i - 1].second] = 2; // assign second as suffix (S)
      m += 2; // increment match count
    } else {
      k = i; // if no match, store index of last unmatched string
      break;
    }
  }

  // Process unmatched pair (if exists)
  if (k != -1) {
    x = a[k].first;
    y = a[k - 1].first;
    string pref = x, suff = y; // start with given candidate prefix/suffix
    int cnt1 = 0, cnt2 = 0;

    // Try to count number of distinct substrings in pref that can be matched
    while (x.length() >= 1) {
      for (i = 0; i < n; i++) {
        if (!ans[a[i].second] && !mp[a[i].second] && a[i].first == x) {
          mp[a[i].second] = 1;
          cnt1++;
          break;
        }
      }
      x.pop_back(); // remove last character from prefix (i.e., suffix of the string)
    }

    // Try to count number of distinct substrings in suff that can be matched
    while (y.length() >= 1) {
      for (i = 0; i < n; i++) {
        if (!ans[a[i].second] && !mp[a[i].second] && a[i].first == y) {
          mp[a[i].second] = 1;
          cnt2++;
          break;
        }
      }
      y = y.substr(1, y.length() - 1); // remove first character from suffix (i.e., prefix of the string)
    }

    if (cnt1 != cnt2 || (n - m) / 2 != cnt1 || (n - m) / 2 != cnt2)
      swap(pref, suff); // swap if mismatch found

    // Assign prefix
    while (pref.length() >= 1) {
      for (i = 0; i < n; i++) {
        if (!ans[a[i].second] && a[i].first == pref) {
          ans[a[i].second] = 1;
          break;
        }
      }
      pref.pop_back(); // reduce prefix size
    }

  }

  // Output final result
  for (i = 0; i < n; i++) {
    if (ans[i] == 1)
      pfs("P");
    else
      pfs("S");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/