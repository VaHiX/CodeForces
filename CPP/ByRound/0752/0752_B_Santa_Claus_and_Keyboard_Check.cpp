// Problem: CF 752 B - Santa Claus and Keyboard Check
// https://codeforces.com/contest/752/problem/B

/*
Purpose: 
This program determines which pairs of keys on Santa's keyboard are swapped, 
such that typing the incorrect string 't' would produce the correct string 's' 
if the swapped keys were corrected. The solution identifies key mappings and 
verifies consistency to determine if a valid set of swaps exists.

Algorithm:
- For each character position, we check if characters in the two strings match.
- If they don't match and neither character has been mapped yet, create a new mapping.
- If one character is already mapped but to a different value, the mapping is inconsistent → output -1.
- Otherwise, store the pair of keys that need to be swapped.

Time Complexity: O(n), where n is the length of the strings. We iterate through each character once.

Space Complexity: O(1), since the map size is bounded by the number of unique lowercase letters (26), making it constant space.
*/

#include <iostream>
#include <map>
#include <string>

using namespace std;
map<int, int> mp; // Map to store character mappings
char s[66666], ss[666666]; // Arrays to store the key pairs
int main() {
  string a, b;
  cin >> a;
  cin >> b;
  int t = 0; // Counter for number of key pairs
  for (int i = 0; i < a.size(); i++) {
    // If neither character has been mapped yet
    if (mp[a[i]] == 0 && mp[b[i]] == 0) {
      mp[a[i]] = b[i]; // Map a[i] to b[i]
      mp[b[i]] = a[i]; // Map b[i] to a[i]
      if (a[i] != b[i]) // Only store if they are different characters
        s[++t] = a[i], ss[t] = b[i];
    } else if (mp[a[i]] != b[i]) { // If mapping is inconsistent
      cout << -1;
      return 0;
    }
  }
  cout << t << endl; // Print number of pairs
  for (int i = 1; i <= t; i++) // Print each pair
    cout << s[i] << " " << ss[i] << endl;
}


// https://github.com/VaHiX/CodeForces/