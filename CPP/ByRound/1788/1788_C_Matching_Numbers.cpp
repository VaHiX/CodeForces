// Problem: CF 1788 C - Matching Numbers
// https://codeforces.com/contest/1788/problem/C

/*
 * Problem: C. Matching Numbers
 * 
 * Algorithm/Technique: Greedy pairing approach
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) (excluding input/output)
 * 
 * The task is to pair integers from 1 to 2n such that the sums of each pair are
 * consecutive and distinct. This is possible only when n is odd.
 * 
 * For odd n, we can construct a valid pairing by:
 * - Pairing 1 with 2n, 2 with 2n-2, ..., (n-1) with n+2
 * - Then pair n with n+1
 * 
 * This ensures all sums are consecutive and distinct.
 */

#include <iostream>

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
  int n;
  cin >> n;
  if (n % 2) { // Only odd n allows a valid solution
    int temp = n * 2; // Start pairing from 2n
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
      cout << i << " " << temp << endl;
      temp = temp - 2; // Decrease temp by 2 to get next pair
      if (temp == n - 1) // When we reach a specific condition, adjust temp
        temp = 2 * n - 1;
    }
  } else {
    cout << "NO" << endl; // Even n has no valid solution
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


// https://github.com/VaHiX/CodeForces/