// Problem: CF 2145 A - Candies for Nephews
// https://codeforces.com/contest/2145/problem/A

/*
Problem: A. Candies for Nephews
Algorithms/Techniques: Modular arithmetic
Time Complexity: O(1) per test case
Space Complexity: O(1)

Monocarp has three nephews and wants to distribute n candies equally among them.
The goal is to find the minimum number of additional candies needed so that n + x is divisible by 3.
This can be computed as (3 - (n % 3)) % 3.

Input:
- Integer t (number of test cases)
- For each test case, integer n (initial number of candies)

Output:
- Minimum additional candies needed for equal distribution among 3 nephews

Example:
Input: 7 -> Output: 2 (7 + 2 = 9, divisible by 3)
Input: 24 -> Output: 0 (24 already divisible by 3)
*/
#include <cstring>
#include <iostream>

#define int long long
#define F first
#define S second
#define pb push_back
using namespace std;
const int N = (int)3e6 + 1000;
void solve() {
  int n;
  cin >> n;
  cout << (3 - (n % 3)) % 3 << endl;  // Calculate minimum candies to buy
  return;
}
signed main() {
#ifdef Maga
  freopen("input.txt", "r", stdin);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/