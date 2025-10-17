// Problem: CF 1888 A - Chemistry
// https://codeforces.com/contest/1888/problem/A

/*
 * Problem: Chemistry
 * 
 * Purpose:
 *   Given a string s of length n and an integer k, check whether it's possible to remove exactly k characters
 *   such that the remaining characters can be rearranged into a palindrome.
 * 
 * Algorithm:
 *   1. Count frequency of each character in the string.
 *   2. Count how many characters have odd frequencies.
 *   3. To form a palindrome from rearranged characters:
 *      - If the final length is odd, at most one character may have an odd count (for center).
 *      - If the final length is even, all characters must have even counts.
 *   - After removing k characters, new length = n - k.
 *   - Number of characters with odd frequencies in remaining string:
 *     - At most 1 for odd-length palindrome.
 *     - 0 for even-length palindrome.
 *   - So we need at most (n - k) % 2 + 1 characters with odd counts.
 *   - But since we are allowed to remove k characters, effectively, it's possible
 *     if number of characters with odd frequency is <= ((n - k) % 2 + 1).
 * 
 * Time Complexity: O(n) per test case due to character counting and iteration through map.
 * Space Complexity: O(1) since there are at most 26 distinct lowercase letters, so map size is bounded.
 */

#include <iostream>
#include <map>
#include <string>
#include <utility>
using namespace std;
using ll = long long;

int main() {
  int k;
  cin >> k;
  while (k--) {
    int n, q;
    cin >> n >> q; // q is used as k in the logic below
    string a;
    cin >> a;
    int cnt = 0;
    
    // Special case: if after removal only one character remains, it's always a palindrome
    if (n - q == 1) {
      cout << "YES" << endl;
      continue;
    }
    
    // Count frequency of each character
    map<char, int> mp;
    for (int i = 0; i < n; i++)
      mp[a[i]]++;
    
    // Count how many characters have odd frequencies
    for (auto it : mp) {
      if (it.second % 2 != 0)
        cnt++;
    }
    
    // For a palindrome:
    // - If remaining length is even, at most 0 characters with odd count allowed
    // - If remaining length is odd, at most 1 character with odd count allowed
    // So we allow up to (n - q) % 2 + 1 odd counts.
    if (cnt <= q + 1)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/