// Problem: CF 1951 E - No Palindromes
// https://codeforces.com/contest/1951/problem/E

/*
 * Problem: E. No Palindromes
 * Algorithm: Greedy approach with palindrome checking
 * Time Complexity: O(n^2) where n is the length of the string
 * Space Complexity: O(n) for storing the string and temporary substrings
 *
 * The solution works as follows:
 * 1. First, check if the entire string is not a palindrome - if so, return it as a single part.
 * 2. If the string is all the same character, we cannot partition it into non-palindromes.
 * 3. Try to find a valid partition by examining prefixes.
 * 4. If a palindrome is found later in the string, we can potentially split at a specific point
 *    to ensure both parts are non-palindromes.
 * 5. Special edge cases are handled based on where the first differing character occurs.
 */

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#define endl '\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
};
typedef pair<string, string> pss;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<string, int> psi;
typedef pair<int, string> pis;
typedef map<char, char> mcc;
typedef map<string, string> mss;
typedef map<int, int> mii;
typedef map<ll, int> mli;
typedef map<string, int> msi;
typedef map<int, string> mis;
typedef unordered_map<char, char> umcc;
typedef unordered_map<string, string> umss;
typedef unordered_map<int, int, custom_hash> umii;
typedef unordered_map<ll, int, custom_hash> umli;
typedef unordered_map<int, string, custom_hash> umis;
typedef unordered_map<ll, ll, custom_hash> umll;
typedef unordered_map<string, int> umsi;
typedef unordered_map<char, int> umci;
typedef unordered_map<string, ll> umsl;
typedef unordered_map<int, ll, custom_hash> umil;
typedef unordered_map<ll, string, custom_hash> umls;
typedef unordered_map<int, char, custom_hash> umic;
typedef set<int> si;
typedef set<ll> sl;
typedef set<string> ss;
typedef set<char> sc;
typedef unordered_set<int, custom_hash> usi;
typedef unordered_set<ll, custom_hash> usl;
typedef unordered_set<string> uss;
typedef multiset<int> mulsi;
typedef multiset<ll> mulsl;
const double pi = 3.14159265358979323846;
typedef stack<int> stai;
typedef stack<char> stac;
typedef stack<ll> stal;
typedef queue<int> quei;
typedef queue<char> quec;
typedef queue<ll> quel;
typedef deque<int> deqi;
typedef deque<char> deqc;
typedef deque<ll> deql;
typedef priority_queue<int> pqi;
typedef priority_queue<ll> pql;
typedef priority_queue<string> pqs;
template <class T> void read(T &x) {
  x = 0;
  bool f = 0;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + (ch ^ 48);
    ch = getchar();
  }
  if (f)
    x = -x;
}
template <class T> void write(T x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x > 9)
    write(x / 10);
  putchar(x % 10 + '0');
  return;
}
bool check(string s) {
  // Check if string is palindrome by comparing characters from both ends
  for (int i = 0; i < s.size() / 2; ++i)
    if (s[i] != s[s.size() - 1 - i])
      return true;
  return false;
}
const int mod = 998244353;
void solve() {
  string s;
  cin >> s;
  int n = s.size();
  if (check(s)) {
    // If entire string is not palindrome, return it as single part
    cout << "YES\n";
    cout << 1 << "\n";
    cout << s << "\n";
    return;
  }
  // If all characters are same
  if (count(s.begin(), s.end(), s[0]) == s.size()) {
    cout << "NO\n";
    return;
  }
  // Find first character different from s[0]
  int i = 0;
  string st = "";
  while (s[i] == s[0])
    st += s[i++];
  // Try to split after first non-matching character
  if (check(s.substr(i + 1))) {
    cout << "YES\n";
    cout << 2 << "\n";
    cout << st << s[i] << " " << s.substr(i + 1) << "\n";
    return;
  }
  // Handle edge cases based on the length of prefix
  if (i == 1 || i + 1 == (n + 1) / 2)
    cout << "NO\n";
  else {
    cout << "YES\n";
    cout << 2 << "\n";
    cout << st << s[i] << st[0] << " " << s.substr(i + 2) << "\n";
    return;
  }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int z;
  cin >> z;
  for (; z; --z)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/