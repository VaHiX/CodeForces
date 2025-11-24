// Problem: CF 2068 F - Mascot Naming
// https://codeforces.com/contest/2068/problem/F

/*
F. Mascot Naming
Algorithms/Techniques: Greedy approach with character buffering
Time Complexity: O(sum of lengths of all strings in s + length of t)
Space Complexity: O(sum of lengths of all strings in s + length of t)

When organizing a big event, organizers often handle side tasks outside their expertise. For example, the chief judge of EUC 2025 must find a name for the event's official mascot while satisfying certain constraints:
The name must include specific words as subsequences
s[0], s[1], ..., s[n-1]
such as the event name and location. You are given the list
s
1
,
s
2
,...,
s
n
of the
n
required words.
The name must not contain as a subsequence
*
*
the name
t
of last year's mascot.
Please help the chief judge find a valid mascot name or determine that none exists.
A string
x
is a subsequence of a string
y
if
x
can be obtained from
y
by erasing some characters (at any positions) while keeping the remaining characters in the same order. For example,
abc
is a subsequence of
axbycz
but not of
acbxyz
.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

vector<string> s; // List of required words that must appear as subsequences
vector<char> c[202020]; // Buffer to store characters that are not part of a subsequence match
int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  s.resize(n); // Resize the vector to hold n strings
  for (int i = 0; i < n; i++)
    cin >> s[i]; // Read each required word
  string t;
  cin >> t; // Read the forbidden subsequence name
  string ans = "";
  for (int i = 0; i < n; i++) { // For each required word
    int r = 0; // Pointer to track progress in matching t
    for (int j = 0; j < s[i].size(); j++) { // Iterate through characters of current word
      if (s[i][j] == t[r]) { // If character matches current target in t
        r++; // Move to next character in t
        if (r == t.size()) // If full t was matched, then a subsequence matching t exists
          return !(cout << "NO"); // Output NO because we are avoiding any subsequence of t
      } else // Otherwise add this character to buffer
        c[r].push_back(s[i][j]); // Store in appropriate position based on current target match level
    }
  }
  cout << "YES\n"; // If no full subsequence matching t found, we can construct a valid name
  for (int i = 0; i < t.size(); i++) { // For each character in target string t
    for (auto x : c[i]) // Output all buffered characters
      cout << x;
    if (i != t.size() - 1) // Add the target character only between the buffered parts
      cout << t[i];
  }
}


// https://github.com/VaHiX/codeForces/