// Problem: CF 1673 C - Palindrome Basis
// https://codeforces.com/contest/1673/problem/C

/*
Algorithm: Dynamic Programming with Palindrome Generation
Time Complexity: O(n * log(n) + T * n) where n is up to 4*10^4, T is number of test cases
Space Complexity: O(n) for the dp array f

This solution uses dynamic programming to count the number of ways to express a number n as a sum of palindromic numbers.
It precomputes all palindromes up to 4*10^4, then builds a DP table where f[i] represents the number of ways to form sum i
using palindromic integers. For each palindrome p, it updates the DP table by adding the number of ways to form (i - p)
to the current number of ways to form i.
*/
#include <iostream>
#include <string>

using namespace std;
typedef long long ll;
ll f[400001], ans = 0, mod = 1e9 + 7;
int main() {
  f[0] = 1; // Base case: one way to form sum 0 (using no elements)
  for (int i = 1; i <= 4e4; i++) {
    string a = to_string(i); // Convert number to string to check palindrome
    if (string(a.rbegin(), a.rend()) == a) { // Check if number is palindrome
      for (int j = i; j <= 4e4; j++)
        f[j] = (f[j] + f[j - i]) % mod; // Update DP table for all sums >= i
    }
  }
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cout << f[n] << endl; // Output result for current test case
  }
}


// https://github.com/VaHiX/CodeForces/