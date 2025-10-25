// Problem: CF 1505 C - Fibonacci Words
// https://codeforces.com/contest/1505/problem/C

#include <iostream>
#include <string>

using namespace std;
/*
C. Fibonacci Words
Algorithm: Checks if a string follows a Fibonacci-like pattern where each character 
represents the sum of the previous two characters in the alphabet (mod 26).
Time Complexity: O(1) - The string length is bounded by 10, so all operations are constant time.
Space Complexity: O(1) - Only using a fixed amount of extra space regardless of input size.

The pattern checks if s[2] = (s[0] + s[1]) mod 26 where characters are treated as 0-25 values.
For strings with length <= 2, the condition is automatically satisfied.
*/
int main() {
  string s;
  cin >> s;
  // Check if string length is <= 2 OR if the third character follows Fibonacci pattern
  if (s.size() <= 2 || ((s[0] + s[1]) % 26 == s[2] - 'A'))
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
}

// https://github.com/VaHiX/codeForces/