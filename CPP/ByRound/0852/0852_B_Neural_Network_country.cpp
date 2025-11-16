// Problem: CF 852 B - Neural Network country
// https://codeforces.com/contest/852/problem/B

/*
 * Problem: Count paths from entry to exit in a layered country (Neural Network) 
 * where total travel cost is divisible by M.
 * 
 * Approach:
 * - The country has L layers, each with N cities.
 * - Each layer is connected to the next with the same N×N cost matrix (md).
 * - Entry connects to first layer (st), last layer connects to exit (ed).
 * - Path cost is sum of costs along path.
 * - Goal: count paths with total cost ≡ 0 (mod M).
 * 
 * Technique:
 * - Matrix exponentiation to compute (md)^(L-2) efficiently.
 * - Use dynamic programming with modular arithmetic.
 * 
 * Time Complexity: O(M^2 * log L), due to matrix exponentiation and M^2 multiplication steps.
 * Space Complexity: O(M^2), for storing the transition matrix and intermediate results.
 */
#include <stdio.h>
#include <string.h>
#include <iosfwd>

using namespace std;
#define maxn 110
typedef long long ll;
const ll mod = (1e9) + 7;
int m;

// Structure to represent a matrix of size M x M
struct mxt {
  ll M[maxn];
  mxt() { memset(M, 0, sizeof(mxt)); }
  void init() { M[0] = 1; } // Initialize identity element for multiplication
};

// Multiply two matrices (modular)
mxt mutil(mxt x1, mxt x2) {
  mxt x3;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int cnt = (i + j) % m;
      x3.M[cnt] += x1.M[i] * x2.M[j];
      x3.M[cnt] %= mod;
    }
  }
  return x3;
}

// Fast matrix exponentiation
mxt mxt_fpow(mxt x, ll p) {
  mxt ans;
  ans.init();
  while (p) {
    if (p % 2 == 1) {
      ans = mutil(ans, x);
    }
    x = mutil(x, x);
    p /= 2;
  }
  return ans;
}

int a[1000010]; // For storing the middle layer costs

int main() {
  int n, l;
  scanf("%d%d%d", &n, &l, &m);
  
  mxt st, md, ed; // st: entry to first layer, md: cost between layers, ed: last layer to exit

  // Read cost from entry point to first layer
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    st.M[(x % m)]++; // Count number of paths with specific mod value
  }

  // Read cost between layers (same for all pairs)
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    md.M[(x % m)]++; // All connections have same cost pattern
    a[i] = x; // Store for later use
  }

  // Read cost from last layer to exit (with precomputed cost from earlier layer)
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    ed.M[(a[i] + x) % m]++; // Combine cost from layer and final cost
  }

  mxt ans;

  // If there are more than 2 layers, use matrix exponentiation
  if (l > 2) {
    ans = mxt_fpow(md, l - 2); // Raise the transition matrix to (L-2)th power
    ans = mutil(ans, st);      // Multiply by entry cost
    ans = mutil(ans, ed);      // Multiply by exit cost  
  } else {
    // Case when L = 2, no need for exponentiation
    ans = mutil(st, ed);
  }

  ll Ans = ans.M[0]; // Total number of paths with cost divisible by M
  printf("%lld\n", Ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/