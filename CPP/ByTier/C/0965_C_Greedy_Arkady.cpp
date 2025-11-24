// Problem: CF 965 C - Greedy Arkady
// https://codeforces.com/contest/965/problem/C

#include <cstdio>
typedef long long ll;
int main() {
  ll n, k, m, D;
  scanf("%lld %lld %lld %lld", &n, &k, &m, &D);
  ll mx(0);
  for (ll d = 0; d < D; d++) {
    // Calculate x based on the number of times each person can receive candies (d+1)
    ll x = n / (k * d + 1);
    // Ensure x does not exceed the maximum allowed value M
    x = (x < m) ? x : m;
    if (x <= 0) {
      break;
    }
    // Calculate how many people will get candies (g)
    ll g = n / x;
    // Skip if more than (D+1) people would get candies (i.e., not valid)
    if (((g + k - 1) / k) > D + 1) {
      continue;
    }
    // Compute the total candies Arkady gets
    ll candy = x * ((g + k - 1) / k);
    // Update maximum candies Arkady can get
    mx = (mx > candy) ? mx : candy;
  }
  printf("%lld\n", mx);
  return 0;
}
// ### Flowerbox

// **Purpose:**  
// This code solves the "Greedy Arkady" problem. It determines the maximum number of candies Arkady can receive by choosing an optimal number of candies per person (`x`) according to constraints on maximum candies per person (`M`) and maximum number of times a person receives candies (`D`).  

// **Algorithm/Techniques:**  
// - Brute-force simulation of all valid distribution schemes  
// - Greedy approach to optimize Arkady's candy count  
// - Mathematical computation to determine `x` and total candies given  

// **Time Complexity:**  
// O(D × log(n))  
// - The loop runs up to `D`, and inside it, computations are done in constant time.  
// - `log(n)` factor is due to division and modulo operations, but they are effectively constant for large `n` under constraints.

// **Space Complexity:**  
// O(1)  
// - The algorithm uses only a few variables and does not require extra memory proportional to input size.

// https://github.com/VaHiX/CodeForces/