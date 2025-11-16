// Problem: CF 2048 G - Kevin and Matrices
// https://codeforces.com/contest/2048/problem/G

/*
G. Kevin and Matrices
time limit per test6 seconds
memory limit per test256 megabytes

Task:
Count how many n×m matrices with values in [1,v] satisfy:
min_i(max_j a[i][j]) <= max_j(min_i a[i][j])

Algorithm:
- Uses inclusion-exclusion principle to count valid matrices.
- For each possible value of min_i(max_j a[i][j]), we compute number of matrices satisfying that,
  then use inclusion-exclusion to avoid overcounting.
- Uses combinatorics and modular arithmetic for efficient computation.

Time Complexity: O(N * V + N * log(MOD)) per test case
Space Complexity: O(V + N) 

*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
const int MAX = 1e6 + 5;
const int MOD = 998244353;

// Modular addition
inline int add(int x, int y) {
  x += y;
  if (x >= MOD)
    return x - MOD;
  if (x < 0)
    return x + MOD;
  return x;
}

// Modular multiplication
inline int mul(int x, int y) { return (long long)x * y % MOD; }

// Fast exponentiation
int pot(int x, int y) {
  int res = 1;
  for (; y; y /= 2) {
    if (y % 2)
      res = mul(res, x);
    x = mul(x, x);
  }
  return res;
}

// Precompute modular inverses
int inv[MAX];

int solve() {
  int N, M, V;
  scanf("%d%d%d", &N, &M, &V);
  
  // Precompute combinations C(N, k)
  vector<int> choose(N + 1);
  choose[0] = 1;
  for (int k = 1; k <= N; k++)
    choose[k] = mul(choose[k - 1], mul(N - k + 1, inv[k]));

  int sol = 0;
  
  // Iterate over each possible value of min_i(max_j a[i][j]) 
  for (int x = 1; x <= V; x++) {
    // a is the number of matrices where all elements are <= x
    int a = pot(V, N);
    
    // b is the number of matrices where all elements are < x 
    int b = pot(V - x + 1, N);
    
    for (int k = 1; k <= N; k++) {
      // Update a and b to represent number of valid arrangements
      a = mul(a, mul(x, inv[V]));
      b = mul(b, inv[V - x + 1]);
      
      // Compute contribution according to inclusion-exclusion 
      int tmp = mul(choose[k], add(pot(add(a, -b), M), -pot(a, M)));
      
      // Add or subtract based on parity of k
      sol = add(sol, k % 2 ? -tmp : tmp);
    }
  }
  return sol;
}

int main() {
  inv[1] = 1;
  for (int i = 2; i < MAX; i++)
    inv[i] = MOD - mul(MOD / i, inv[MOD % i]);
  
  int tc;
  scanf("%d", &tc);
  while (tc--)
    printf("%d\n", solve());
  return 0;
}


// https://github.com/VaHiX/codeForces/