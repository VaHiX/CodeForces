// Problem: CF 1675 E - Replace With the Previous, Minimize
// https://codeforces.com/contest/1675/problem/E
 
/*
Algorithm: Greedy approach
- For each character in the string from left to right, we try to decrease it to the previous letter (in alphabetical order, looping from 'a' to 'z')
- We use a map to track which characters have been processed (i.e., used in an operation)
- If we have operations available (k > 0) and the current character is not 'a', we decrease it and decrement k
- If we already processed a character with the same value before, we simply decrease it without decrementing k
 
Time Complexity: O(n) where n is the length of the string. Each character is processed at most once.
Space Complexity: O(1) since we use a map with at most 26 entries (one for each lowercase letter), which is constant.
*/
 
#include <iostream>
#include <map>
#include <string>
 
using namespace std;
int t, n, k;
string s;
int main() {
  cin >> t;
  while (t--) {
    cin >> n >> k;
    cin >> s;
    map<char, int> mp;  // Track characters that have been used in operations
    for (int i = 0; i < n; i++) {
      while (s[i] > 'a') {  // While current character is not 'a'
        if (mp[s[i]])  // If we already decreased this character before
          s[i]--;  // Just decrease it
        else if (k) {  // If we still have operations left
          mp[s[i]] = 1;  // Mark this character as used
          k--;  // Use one operation
          s[i]--;  // Decrease the character
        } else {
          break;  // No more operations, stop
        }
      }
    }
    cout << s << endl;
  }
}
 
 
// https://github.com/VaHiX/CodeForces/