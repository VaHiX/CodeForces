// Problem: CF 1474 A - Puzzle From the Future
// https://codeforces.com/contest/1474/problem/A

/*
Problem: A. Puzzle From the Future
Purpose: Given a binary string b, find a binary string a such that when we compute c = a + b (bitwise sum without carry), 
         then after removing consecutive duplicates from c, the result d is lexicographically maximum.

Algorithms/Techniques:
- Greedy approach to construct string a character by character.
- For each position i, decide whether to place 0 or 1 in a such that we maximize the final result d.

Time Complexity: O(n) where n is the length of the string b. Each character is processed once.
Space Complexity: O(n) for storing the resulting string a.

*/
#include <iostream>
#include <string>

using namespace std;
typedef long long ll;
bool flag = false;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string a, b;
    cin >> b;
    a = "1"; // Start with '1' for the first character
    for (int i = 1; i < n; i++) {
      // If sum of current bits from b and previous bit of a is not equal to previous bit of b plus previous bit of a,
      // then choose '1' to maximize lexicographically; otherwise use '0'
      if (b[i] + '1' != b[i - 1] + a[i - 1])
        a += "1";
      else
        a += "0";
    }
    cout << a << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/