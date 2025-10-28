// Problem: CF 1027 A - Palindromic Twist
// https://codeforces.com/contest/1027/problem/A

/*
Problem: A. Palindromic Twist
Algorithms/Techniques: Two pointers, character comparison
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables

The problem asks to determine if we can transform a given string into a palindrome 
by changing each character to either its previous or next letter in the alphabet.
For a string to become a palindrome after transformation, characters at symmetric positions
must be such that one can be transformed to match the other.

Approach:
1. For each test case, iterate through the first half of the string.
2. Compare characters at symmetric positions (i and n-1-i).
3. Check if the absolute difference between their ASCII values is 0 or 2.
   - If difference is 0, they can be made equal by changing both to same character.
   - If difference is 2, one can be changed to match the other.
   - Otherwise, impossible to make them match via allowed transformations.
4. If any pair fails the condition, answer is "NO", otherwise "YES".

*/
#include <iostream>
#include <string>

using namespace std;
int t, n, i, j, x, r;
string s;
int main() {
  for (cin >> t; t--;) {           // Read number of test cases
    for (cin >> n >> s, r = j = 0; j < n / 2; j++) {  // Iterate through first half
      x = s[j] - s[n - j - 1];       // Calculate difference between symmetric characters
      r |= x != 0 && x * x != 4;     // If difference is not 0 and square is not 4, set r=1 (impossible)
    }
    cout << (r ? "NO" : "YES") << endl;  // Output result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/