// Problem: CF 2115 D - Gellyfish and Forget-Me-Not
// https://codeforces.com/contest/2115/problem/D

/*
 * Problem: D. Gellyfish and Forget-Me-Not
 * Algorithm: Gaussian Elimination with Optimization for XOR Game
 * Time Complexity: O(60 * n) = O(n) per test case
 * Space Complexity: O(n)
 *
 * This solution uses a variant of Gaussian elimination to find the optimal XOR value
 * that can be achieved based on the choices available in a two-player game.
 * Each bit is processed from most significant to least significant.
 * For each bit, we try to form a basis vector and decide whether to use it
 * to minimize or maximize the result depending on the player's turn.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  int t;
  cin >> t;
  while (t--) {
    int n;
    vector<ll> a;
    ll Bas = 0; // Base value initialized to 0
    string s;
    cin >> n;
    a.resize(n);
    
    // Read array `a`, compute initial XOR of all elements into Bas
    for (auto &k : a)
      cin >> k, Bas ^= k;
    
    // Read array `b` and update `a[i] = a[i] ^ b[i]`
    for (auto &k : a) {
      ll x;
      cin >> x;
      k ^= x;
    }
    
    cin >> s; // Read string that determines player turns
    
    // Process each bit from MSB to LSB
    for (int z = 59; z >= 0; z--) {
      int p = -1; // Index of pivot element for current bit
      
      // Find a non-zero entry in column `z` from bottom to top
      for (int i = n - 1; i >= 0; i--)
        if (a[i] >> z & 1) {
          if (p == -1)
            p = i; // First valid index becomes pivot
          else
            a[i] ^= a[p]; // Eliminate using Gaussian elimination
        }
      
      if (p == -1)
        continue; // No pivot in this column, skip
      
      // If current player is Gellyfish (c[p]='0'), minimize result
      // If current player is Flower (c[p]='1'), maximize result
      if (s[p] == '0')
        Bas = min(Bas, Bas ^ a[p]);
      else
        Bas = max(Bas, Bas ^ a[p]);
      
      a[p] = 0; // Clear the pivot row for future processing
    }
    
    cout << Bas << '\n';
  }
}


// https://github.com/VaHiX/codeForces/