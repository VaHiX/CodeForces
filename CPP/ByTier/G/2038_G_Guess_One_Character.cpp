// Problem: CF 2038 G - Guess One Character
// https://codeforces.com/contest/2038/problem/G

/*
Purpose: This code solves the interactive problem "Guess One Character" where
the goal is to guess at least one character of a hidden binary string s of
length n using at most 3 queries.

Algorithms/Techniques:
- Use three specific queries to determine the pattern:
    1. Query "1" (count of occurrences of '1')
    2. Query "10" (count of occurrences of "10")
    3. Query "11" (count of occurrences of "11")
- Based on these counts, we can deduce information about the structure of the
string and determine the value of at least one character.
- The logic to infer the result is based on:
    - If the count of "11" is 0, then there are no consecutive '1's.
    - If the count of "10" is greater than or equal to the count of "11", then
the last character must be '0' if the last two characters are "10".
    - The final guess is made by analyzing how many '1's are present compared to
the count of "10" and "11".

Time Complexity: O(1) - Fixed number of operations regardless of input size.
Space Complexity: O(1) - Only a constant amount of space is used.
*/

#include <cstdio>
#include <iostream>

#define inf 0x3f3f3f3f
using namespace std;
int n, p;
void work() {
  cin >> n;
  // Query for count of "1", "10", and "11"
  cout << "1 1\n1 10\n1 11\n";
  fflush(stdout);
  int a, b, c;
  cin >> a >> b >> c; // Read the responses to queries
  // The logic to determine the value of the last character
  cout << "0 " << n << ' ' << (a != b + c) << '\n';
  fflush(stdout);
  cin >> p;
}
signed main() {
  int _ = 1;
  cin >> _;
  while (_--)
    work();
}

// https://github.com/VaHiX/CodeForces/