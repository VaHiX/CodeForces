// Problem: CF 1263 B - PIN Codes
// https://codeforces.com/contest/1263/problem/B

/*
 * Problem: PIN Codes
 * Purpose: Given n bank card PIN codes, make all codes unique by changing the minimum number of digits.
 * Algorithm: 
 *   1. Count occurrences of each PIN code.
 *   2. For each PIN code that appears more than once, try to modify it by changing one digit
 *      to make it unique, prioritizing minimal changes.
 *   3. Use a greedy approach to modify the first conflicting PIN code encountered.
 * 
 * Time Complexity: O(n * 4 * 10) = O(n) where n is number of PINs (since 4 digits and 10 possible values)
 * Space Complexity: O(n) for storing the PINs and map
 */

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    string s[10];       // Array to store the PIN codes
    map<string, int> mp; // Map to count occurrences of each PIN
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> s[i];
      mp[s[i]]++;  // Count each PIN's occurrence
    }
    int ans = 0;  // Counter for minimum changes needed
    
    // Iterate through each PIN code
    for (int i = 0; i < n; i++) {
      if (mp[s[i]] > 1) {  // If this PIN is not unique
        ans++;
        mp[s[i]]--;  // Decrement count as we're modifying this PIN
        
        // Try changing first digit to make it unique
        for (int j = 0; j < 10; j++) {
          s[i][0] = j + '0';  // Change first digit to 0-9
          if (mp[s[i]] == 0)  // If the new PIN is not in map, we're done
            break;
        }
        mp[s[i]]++;  // Add modified PIN back to map
      }
    }
    
    cout << ans << "\n";  // Print minimum changes
    for (int i = 0; i < n; i++)
      cout << s[i] << "\n";  // Print all modified PINs
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/