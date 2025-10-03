// Problem: CF 2089 C1 - Key of Like (Easy Version)
// https://codeforces.com/contest/2089/problem/C1

/*
 * Problem: C1. Key of Like (Easy Version)
 * Algorithm: Dynamic Programming with Probability Calculation
 * Time Complexity: O(l * n) per test case
 * Space Complexity: O(n) 
 * 
 * This problem computes the expected number of successful matches for each member
 * in a game where n members take turns trying to unlock l locks using l keys.
 * Each key opens exactly one lock, and the probability is initially uniform.
 * The solution uses dynamic programming with probabilities stored modulo 10^9 + 7.
 * 
 * For each step, based on prior choices, we calculate how many matches are expected 
 * for each member. The code precomputes some base probabilities and then iteratively
 * adjusts them according to what's left after previous picks.
 */

#include "iostream"
#include <istream>
using namespace std;
typedef long long int lli;
#define fori(x) for (int i = 0; i < (x); i++)
#define MOD (1000000000 + 7)
#define N 100
#define L 5000

int p[2][N]; // Stores probabilities at different stages
int e[N];    // Final expected values for each member

// Compute modular multiplicative inverse
int invMod(int a) {
  return a <= 1 ? a : MOD - (long long)(MOD / a) * invMod(MOD % a) % MOD;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, l, k;
    cin >> n >> l >> k;
    
    int prv = 0;   // Previous stage index
    int crt = 1;   // Current stage index
    
    // Initialize arrays to zero
    fori(n) {
      p[prv][i] = 0;
      p[crt][i] = 0;
      e[i] = 0;
    }
    
    // Precompute inverse of l modulo MOD
    int inv_l = invMod(l);
    // Base probability for first round
    int acc = ((l / n) * (lli)inv_l) % MOD;
    fori(n) {
      p[prv][i] = acc;
      if (i < (l % n))
        p[prv][i] = (p[prv][i] + inv_l) % MOD;
    }
    
    // Copy initial probabilities into e
    fori(n) e[i] = p[prv][i];
    
    // Iteratively compute for remaining steps
    for (int j = l - 1; j >= 1; j--) {
      inv_l = invMod(j);  // New inverse of current lock count
      
      // Update probabilities by multiplying with inverse
      fori(n) p[prv][i] = (p[prv][i] * (lli)inv_l) % MOD;
      
      // Compute accumulated value
      acc = ((j / n) * (lli)inv_l) % MOD;
      
      // Adjust acc with last few elements of previous array
      fori(j % n) acc = (acc + p[prv][n - 1 - i]) % MOD;
      
      int accl = (n - (j % n)) % n;   // Index offset for sliding window
      
      // Update current stage probabilities using running sum approach
      fori(n) {
        p[crt][i] = acc;
        acc = (((lli)acc - p[prv][accl] + MOD) + p[prv][i]) % MOD;
        accl = (accl + 1) % n;
      }
      
      // Update final expectations by adding current stage values
      fori(n) e[i] = (e[i] + p[crt][i]) % MOD;
      
      // Swap pointers for next iteration
      crt = (crt + 1) % 2;
      prv = (prv + 1) % 2;
    }
    
    // Output result modulo MOD
    fori(n) cout << e[i] << " ";
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/