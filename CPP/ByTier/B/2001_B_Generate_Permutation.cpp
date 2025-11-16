// Problem: CF 2001 B - Generate Permutation
// https://codeforces.com/contest/2001/problem/B

#include <iostream>

using namespace std;
typedef long long ll;
#ifdef DEBUG
ifstream in("input.txt");
#define cin in
#endif
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    // If n is even, it's impossible to create a permutation that satisfies the condition
    if (!(n & 1)) {
      cout << -1 << "\n";
      continue;
    }
    // Output odd numbers in ascending order (1, 3, 5, ...)
    for (int i = 1; i <= n; i += 2)
      cout << i << ' ';
    // Output even numbers in descending order (n-1, n-3, n-5, ...)
    for (int i = n - 1; i > 0; i -= 2)
      cout << i << ' ';
    cout << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/