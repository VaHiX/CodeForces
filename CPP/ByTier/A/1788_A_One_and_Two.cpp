// Problem: CF 1788 A - One and Two
// https://codeforces.com/contest/1788/problem/A

/*
Problem: A. One and Two
Task: Given a sequence of 1s and 2s, find the smallest k such that the product of first k elements equals the product of the remaining elements.
Algorithms/Techniques: 
  - Simulation with counting
  - Greedy approach for finding valid splitting point

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(n) for storing indices of 2s.

Approach:
- Count total occurrences of 1s and 2s in the array.
- If all elements are 1s, return 1 (as product of first 1 element equals the rest).
- If number of 2s is odd, no valid k exists → return -1.
- If even number of 2s, find the middle 2 and return its index + 1.

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define endl "\n"
#define input cin >>
#define output cout <<
#define pb push_back

void fastIO() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int lcm(int a, int b) { return (a * (b / gcd(a, b))); }

bool isPrime(int n) {
  if (n < 2)
    return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0)
      return false;
  }
  return true;
}

int factorial(int n) { return n * factorial(n - 1); }

void solve() {
  ll n;
  cin >> n;
  ll cnt_2 = 0, cnt_1 = 0; // Count of 2s and 1s
  vector<int> ans;         // Store indices where element is 2
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (x == 2) {
      cnt_2++;
      ans.push_back(i + 1); // Store index (1-based)
    } else
      cnt_1++;
  }

  if (cnt_1 == n)
    cout << 1 << endl; // All elements are 1s, k=1 is valid
  else if (cnt_2 % 2)
    cout << -1 << endl; // Odd number of 2s means impossible split
  else {
    // Return the index of the last 2 in the first half
    cout << ans[cnt_2 / 2 - 1] << endl;
  }
}

int main() {
  fastIO();
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/