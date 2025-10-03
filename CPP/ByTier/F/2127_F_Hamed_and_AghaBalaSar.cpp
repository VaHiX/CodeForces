// Problem: CF 2127 F - Hamed and AghaBalaSar
// https://codeforces.com/contest/2127/problem/F

/*
F. Hamed and AghaBalaSar
time limit per test2 seconds
memory limit per test512 megabytes

Problem Description:
Given integers n and m, count the sum of f(a) over all "snake" arrays a[1], ..., a[n], where:
- Each element is between 0 and m,
- Sum of elements equals m,
- Last element equals maximum element in array.

Function f(a):
- Uses an array nxt[x] to find the smallest index y > x such that a[y] > a[x]
- Computes sum of differences (nxt[pos] - pos) when a[pos] < a[n]

Algorithms/Techniques:
- Precomputed factorials and inverse factorials for combinatorics
- Inclusion-exclusion principle used in count function
- Modular exponentiation and modular inverse computations
- Dynamic programming and mathematical recurrence relations

Time Complexity: O(MAXN * log(MOD) + t * m)
Space Complexity: O(MAXN)

*/

#include <cstdio>
#include <iosfwd>

using namespace std;
const int MOD = 1e9 + 7; // Modulo value
const int MAXN = 200010;  // Maximum size for arrays
typedef long long LL;

int t, n, m;                // Input variables: test cases, length of array, sum of elements
int inv[MAXN];              // Array to store modular inverse values
int facto[MAXN << 1], invFacto[MAXN << 1];  // Factorials and inverse factorials

// Fast exponentiation function: computes (x^n) modulo MOD
int quickPower(int x, int n) {
  int ans = 1;
  while (n) {
    if (n & 1)          // If n is odd
      ans = (LL)ans * (LL)x % MOD;   // Multiply ans by x and take modulo
    x = (LL)x * (LL)x % MOD;     // Square x and take modulo
    n >>= 1;             // Right shift n by one bit (divide by 2)
  }
  return ans;
}

// Initialize precomputed factorials and inverse factorials
void init() {
  facto[0] = invFacto[0] = 1;  // Base cases for factorial and inverse factorial
  for (int i = 1; i < (MAXN << 1); i++) {   // Compute factorials from 1 to 2*MAXN-1
    facto[i] = (LL)facto[i - 1] * (LL)i % MOD;
  }
  invFacto[(MAXN << 1) - 1] = quickPower(facto[(MAXN << 1) - 1], MOD - 2); // Compute inverse of final factorial
  for (int i = (MAXN << 1) - 2; i > 0; i--) {   // Compute inverse factorials backwards
    invFacto[i] = (LL)invFacto[i + 1] * (LL)(i + 1) % MOD;
  }
  inv[1] = 1;
  for (int i = 2; i < MAXN; i++) {       // Compute modular inverses for all numbers up to MAXN
    inv[i] = (LL)(MOD - MOD / i) * (LL)inv[MOD % i] % MOD; // Use Fermat's little theorem
  }
}

// Returns combination C(n, m) modulo MOD using precomputed values
inline int get_combination(int n, int m) {
  if (m > n || m < 0)
    return 0;
  return ((LL)facto[n] * (LL)invFacto[m] % MOD) * (LL)invFacto[n - m] % MOD;
}

// Helper function for counting specific valid snake-like arrays
int get_count(int n, int m, int k) {
  if (m < 0)
    return 0;
  if (n == 0)
    return m == 0;
  if (n == 1)
    return m <= k;

  int ans = 0;
  int r = m / (k + 1);   // Calculate upper bound for inclusion-exclusion parameter s
  
  for (int s = 0; s <= r; s++) {
    int tmp = (LL)get_combination(n, s) *     // Combine multinomial coefficient
              (LL)get_combination(m + n - 1 - (k + 1) * s, n - 1) % MOD;
    
    if (s & 1) {   // If s is odd
      ans -= tmp;
      ans += (ans < 0) ? MOD : 0;
    } else {
      ans += tmp;
      ans -= (ans >= MOD) ? MOD : 0;
    }
  }
  return ans;
}

// Core calculation function for one k value
int calc(int n, int m, int k) {
  int t1 = get_count(n - 1, m - k, k);     // First recurrence term based on previous count
  int t2 = get_count(n - 2, m - 2 * k, k); // Second recurrence term

  int sum_max, sum_an, sum_other_max, sum_a1, sum_ai;
  int tmp = (LL)t2 * (LL)k % MOD;

  sum_an = (LL)t1 * (LL)k % MOD;   // Calculate sum of an contribution
  sum_other_max = (LL)tmp * (LL)(n - 1) % MOD;   // Other max term contribution
  sum_max = (sum_an + sum_other_max) % MOD;

  sum_a1 = (LL)t1 * (LL)(m - k) % MOD;
  sum_a1 = (LL)sum_a1 * (LL)inv[n - 1] % MOD;   // Contribution from a1 term

  sum_ai = (LL)t2 * (LL)(m - 2 * k) % MOD;
  sum_ai = (sum_ai + tmp) % MOD;

  int res = ((sum_max - sum_a1 + MOD) % MOD - sum_ai + MOD) % MOD; // Final result for this k

  return res;
}

int main() {
  init();   // Precompute all necessary factorials and inverse values
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    if (m == 0) {
      printf("0\n");
      continue;
    }
    int ans = 0;
    for (int k = 1; k <= m; k++) {   // Iterate over all possible k values (from min to max) 
      ans += calc(n, m, k);          // Add contribution of current k to final answer
      ans -= (ans >= MOD) ? MOD : 0; // Handle modular arithmetic correctly
    }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/