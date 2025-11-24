// Problem: CF 1872 D - Plus Minus Permutation
// https://codeforces.com/contest/1872/problem/D

/* 
D. Plus Minus Permutation
Algorithm: 
This problem involves maximizing the score of a permutation where:
- The score is defined as sum of elements at indices divisible by x minus sum of elements at indices divisible by y.
- To maximize this, we want to place large numbers at positions divisible by x (to add) and small numbers at positions divisible by y (to subtract).
- We compute how many multiples of x and y exist up to n, account for overlaps using LCM.
- Use greedy strategy: place largest possible values where they contribute positively (i.e., indices divisible by x), and smallest where they contribute negatively (indices divisible by y).
Time Complexity: O(log(min(x,y))) per test case due to GCD computation
Space Complexity: O(1) - only using fixed-size variables
*/

#include <cstdio>
typedef long long ll;

// Compute greatest common divisor of two numbers
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, x, y;
    scanf("%lld %lld %lld", &n, &x, &y);
    
    // Calculate LCM of x and y to determine period
    ll lcm = (x / gcd(x, y)) * y; // LCM = (x * y) / GCD(x, y)
    
    // Count number of multiples of x in range [1, n]
    // nx represents count of positions divisible by x
    ll nx = (n / lcm) * (lcm / x - 1) + (n % lcm) / x;
    
    // Count number of multiples of y in range [1, n]
    // ny represents count of positions divisible by y  
    ll ny = (n / lcm) * (lcm / y - 1) + (n % lcm) / y;
    
    // Sum of first nx largest numbers (we want these at indices divisible by x)
    // plus = nx * (2*n - nx + 1) / 2 (sum of an arithmetic progression from (n-nx+1) to n)
    ll plus = nx * (2 * n - nx + 1) / 2;
    
    // Sum of first ny smallest numbers (we want these at indices divisible by y)
    // minus = ny * (ny + 1) / 2 (sum of first ny natural numbers)
    ll minus = ny * (ny + 1) / 2;
    
    printf("%lld\n", plus - minus);
  }
}

// https://github.com/VaHiX/codeForces/