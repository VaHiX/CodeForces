// Problem: CF 2116 F - Gellyfish and Forget-Me-Not
// https://codeforces.com/contest/2116/problem/F

/*
F. Gellyfish and Forget-Me-Not

This problem involves a two-player game where players take turns choosing between two XOR operations on elements from arrays 'a' and 'b', depending on a binary string 'c'. The first player (Gellyfish) minimizes the final value of x, while the second player (Flower) maximizes it. Both play optimally.

The solution uses the concept of a basis vector space over GF(2) to represent all possible XOR values that can be achieved. At each step:
- We compute v = a[i] ^ b[i], which represents all valid XOR differences we can generate with this round.
- Then, for each existing basis vector, we attempt to reduce v using XOR operations to find the minimal vector that can still affect future states.
- If v is non-zero and not already in our basis, we consider adding it based on player's type ('0' = Gellyfish, '1' = Flower):
  - For Gellyfish ('0'): minimize final x by possibly reducing base.
  - For Flower ('1'): maximize final x by possibly increasing base.

Time complexity: O(n * log(max(a[i], b[i]))) where log factor arises from operations on basis vectors (at most 60 bits).
Space complexity: O(n) for storing basis and vectors.

Algorithms/Techniques: 
    - Basis representation of XOR space
    - Minimax decision-making with optimization using bitwise operations

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solve_one_case(int n, const vector<long long> &a,
                         const vector<long long> &b, const string &c) {
  long long base = 0;
  for (long long x : a) {
    base ^= x; // Initialize base with XOR of all elements in array 'a'
  }
  vector<long long> basis;
  for (int i = n - 1; i >= 0; i--) {
    long long v = a[i] ^ b[i]; // Compute difference between a[i] and b[i]
    for (long long bv : basis) { // Try to reduce v using existing basis vectors
      if (v == 0)
        break;
      v = min(v, v ^ bv);
    }
    if (v != 0) { // If v has non-zero bits, add it to basis
      if (c[i] == '0') {
        base = min(base, base ^ v); // Gellyfish (minimize): consider reducing base
      } else {
        base = max(base, base ^ v); // Flower (maximize): consider increasing base
      }
      basis.push_back(v); // Add new basis vector
    }
  }
  return base;
}

void solve() {
  int n;
  cin >> n;
  vector<long long> a(n), b(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  string c;
  cin >> c;
  long long ans = solve_one_case(n, a, b, c);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/