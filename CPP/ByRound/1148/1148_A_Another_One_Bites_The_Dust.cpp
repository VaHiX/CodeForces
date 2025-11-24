// Problem: CF 1148 A - Another One Bites The Dust
// https://codeforces.com/contest/1148/problem/A

#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  long long a, b, c;
  cin >> a >> b >> c;
  cout << (2 * min(a, b) + 2 * c + (a != b)); // Calculate maximum length of good string
}

/*
Problem: A. Another One Bites The Dust
Purpose: Given counts of strings "a", "b", and "ab", find the maximum length of a good string formed by concatenating some subset of these strings.
A good string consists only of 'a' and 'b', with no two consecutive characters being the same.

Approach:
- We can use at most min(a, b) pairs of "a" and "b" to form alternating sequences like "abab..." or "baba..."
- Each such pair contributes 2 to the total length.
- All "ab" strings can be used directly, each contributing 2 characters.
- If a != b, we need an extra character to connect the sequence, hence + (a != b).

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - only using a few variables
*/

// https://github.com/VaHiX/codeForces/