// Problem: CF 1187 A - Stickers and Toys
// https://codeforces.com/contest/1187/problem/A

#include <algorithm>
#include <iostream>

using namespace std;
long long q, n, s, t;
int main() {
  // Flowerbox: 
  // Problem: A. Stickers and Toys
  // Purpose: Find the minimum number of Kinder Surprise eggs to buy to guarantee at least one sticker and one toy.
  // Algorithm: Mathematical approach based on worst-case analysis.
  // Time Complexity: O(1) per query
  // Space Complexity: O(1)
  
  for (cin >> q; q--; cout << max(n - s, n - t) + 1 << endl)
    cin >> n >> s >> t;
}

// https://github.com/VaHiX/codeForces/