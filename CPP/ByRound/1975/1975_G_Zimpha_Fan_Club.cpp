// Problem: CF 1975 G - Zimpha Fan Club
// https://codeforces.com/contest/1975/problem/G

/*
 * Problem: G. Zimpha Fan Club
 *
 * Purpose: Determine if two strings with wildcards ('-' and '*') can be made equal
 *          by replacing wildcards appropriately.
 *
 * Algorithm:
 * - The approach is to use a greedy strategy with backtracking.
 * - First, we strip matching prefixes and suffixes from both strings.
 * - Then, we check if any of the strings has a '*' wildcard.
 * - If both have wildcards, they can match (return true).
 * - If only one string has wildcards, we try to match the other string against it.
 * - For matching strings with wildcards, we use a helper function FuzzyMatch and FuzzyFirstIndexOf.
 * - The key idea is using pattern matching with fuzzy equality for '-' and identical characters.
 *
 * Time Complexity: O(n * m) where n and m are lengths of the strings.
 * Space Complexity: O(n + m) for string views and recursion stack in worst case.
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;
#define int int64_t
#pragma GCC diagnostic ignored "-Wsign-compare"
int DivCeil(int x, int y) { return (x + y - 1) / y; }
vector<int> ReadVec(int n) {
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  return a;
}
inline bool FuzzyEquals(char c1, char c2) {
  return c1 == '-' || c2 == '-' || c1 == c2;
}
bool SkipBegin(string_view &s1, string_view &s2) {
  // Skip matching characters from the start of both strings
  while (!s1.empty() && !s2.empty() && s1[0] != '*' && s2[0] != '*') {
    if (!FuzzyEquals(s1[0], s2[0]))
      return false;
    s1 = s1.substr(1, s1.size() - 1);
    s2 = s2.substr(1, s2.size() - 1);
  }
  return true;
}
bool SkipEnd(string_view &s1, string_view &s2) {
  // Skip matching characters from the end of both strings
  while (!s1.empty() && !s2.empty() && s1[s1.size() - 1] != '*' &&
         s2[s2.size() - 1] != '*') {
    if (!FuzzyEquals(s1[s1.size() - 1], s2[s2.size() - 1]))
      return false;
    s1 = s1.substr(0, s1.size() - 1);
    s2 = s2.substr(0, s2.size() - 1);
  }
  return true;
}
int FuzzyFirstIndexOfFft(string_view t, string_view s) {
  int n = t.size();
  int m = s.size();
  for (int i = 0; i <= m - n; i++) {
    bool ok = true;
    for (int j = 0; j < n; j++)
      if (!FuzzyEquals(t[j], s[i + j])) {
        ok = false;
        break;
      }
    if (ok)
      return i;
  }
  return -1;
}
constexpr int Q = 5;
int LF = 0;
bool FuzzyMatch(string_view t, string_view s) {
  int n = t.size();
  assert(s.size() == n);
  // Check first Q characters
  for (int i = 0; i < min(n, Q); i++)
    if (!FuzzyEquals(t[i], s[i]))
      return false;
  // Check last Q characters
  for (int i = max((int)0, n - Q); i < n; i++)
    if (!FuzzyEquals(t[i], s[i]))
      return false;
  int l = clamp(LF, (int)0, n - 1);
  int r = l + 1;
  while (l >= Q || r < n - Q) {
    if (l >= Q) {
      if (!FuzzyEquals(t[l], s[l])) {
        LF = l;
        return false;
      }
      l--;
    }
    if (r < n - Q) {
      if (!FuzzyEquals(t[r], s[r])) {
        LF = r;
        return false;
      }
      r++;
    }
  }
  return true;
}
int FuzzyFirstIndexOf(string_view t, string_view s) {
  int n = t.size();
  int m = s.size();
  for (int i = 0; i <= m - n; i++) {
    if (FuzzyMatch(t, s.substr(i, n)))
      return i;
  }
  return -1;
}
bool MatchHard(string_view t, string_view s) {
  // Handle base case: empty string t
  if (s.empty()) {
    return (count(t.begin(), t.end(), '*') == t.size());
  }
  assert(!t.empty() && t[0] == '*' && t[t.size() - 1] == '*');
  if (t.size() == 1)
    return true;
  int next_star = t.find('*', 1);
  assert(next_star != string_view::npos);
  if (next_star == 1)
    return MatchHard(t.substr(1, t.size() - 1), s);
  int tl = next_star - 1;
  int fi = FuzzyFirstIndexOf(t.substr(1, tl), s);
  if (fi == -1)
    return false;
  return MatchHard(t.substr(next_star, t.size()), s.substr(fi + tl, s.size()));
}
bool Solve(string_view s1, string_view s2) {
  if (!SkipBegin(s1, s2))
    return false;
  if (!SkipEnd(s1, s2))
    return false;
  bool st1 = (s1.find('*') != string_view::npos);
  bool st2 = (s2.find('*') != string_view::npos);
  if (st1 && st2)
    return true;
  else if (!st1 && !st2)
    return s1.empty() && s2.empty();
  else if (st1 && !st2)
    return MatchHard(s1, s2);
  else
    return MatchHard(s2, s1);
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n1, n2;
  string s1, s2;
  cin >> n1 >> n2 >> s1 >> s2;
  cout << (Solve(s1, s2) ? "Yes" : "No") << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/