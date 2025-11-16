// Problem: CF 825 A - Binary Protocol
// https://codeforces.com/contest/825/problem/A

/*
 * Purpose: Decode a binary encoded string back to the original number.
 *          The encoding rule is: each digit is represented by a sequence of '1's 
 *          equal to the digit's value, and digits are separated by a single '0'.
 *          
 * Algorithm:
 *   - Traverse the string character by character.
 *   - Count consecutive '1's until a '0' is encountered.
 *   - When a '0' is found, output the count of '1's (which represents the digit),
 *     and reset the counter.
 *   - At the end of the string, output the remaining count of '1's.
 *          
 * Time Complexity: O(n), where n is the length of the input string.
 * Space Complexity: O(1), excluding the input string storage.
 */

#include <iostream>
#include <string>

typedef long long int ll;
#define pp pair<int, int>
#define dbg printf("in\n");
#define NL printf("\n");
#define inf 1000000000000
using namespace std;

int main() {
  ll i, j, k;
  ll n, m;
  string s;
  cin >> n >> s; // Read the length and the encoded string
  k = 0; // Initialize counter for consecutive '1's
  for (i = 0; i < n; i++) {
    if (s[i] == '1')
      k++; // Increment counter if current character is '1'
    else {
      cout << k; // Output the count of '1's which represents the digit
      k = 0; // Reset counter for the next digit
    }
  }
  cout << k; // Output the last digit (since string ends with '1's)
  return 0;
}


// https://github.com/VaHiX/CodeForces/