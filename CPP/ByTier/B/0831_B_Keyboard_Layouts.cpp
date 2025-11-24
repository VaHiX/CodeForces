// Problem: CF 831 B - Keyboard Layouts
// https://codeforces.com/contest/831/problem/B

/*
Purpose: This code translates a text from one keyboard layout to another.
         It maps characters from the first layout to the second layout,
         preserving case for letters and leaving digits unchanged.

Algorithms/Techniques: 
- Character mapping using a hash map (std::map)
- Case handling using ASCII value manipulation (isupper, isdigit)
- Linear traversal of the input string

Time Complexity: O(n) where n is the length of the input string s.
Space Complexity: O(1) for the map (since it's bounded by 26 letters),
                  and O(n) for the input string storage.

*/

#include <ctype.h>
#include <iostream>
#include <map>
#include <string>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in\n");
#define NL printf("\n");
#define inf 1000000000000
using namespace std;

int main() {
  ll i, j, k;
  ll n;
  string s, t;
  map<char, char> mp; // Map to store character translations between layouts
  cin >> s >> t;
  for (i = 0; i < s.length(); i++)
    mp[s[i]] = t[i]; // Build the mapping from first layout to second
  cin >> s;
  char ch;
  for (i = 0; i < s.length(); i++) {
    if (isdigit(s[i])) { // If the character is a digit, output it as is
      cout << s[i];
      continue;
    }
    if (mp[s[i]]) // If the character exists in the mapping, use the mapped character
      cout << mp[s[i]];
    else { // For characters not in the mapping, handle case conversion
      if (isupper(s[i])) { // If uppercase, convert to lowercase, map, then uppercase again
        ch = mp[s[i] + 32] - 32;
        cout << (ch);
      } else { // If lowercase, map and keep as lowercase
        ch = mp[s[i] - 32] + 32;
        cout << ch;
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/