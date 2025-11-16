// Problem: CF 1030 D - Vasya and Triangle
// https://codeforces.com/contest/1030/problem/D

#include <cstdio>
typedef long long ll;
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  ll n, m, k;
  scanf("%lld %lld %lld", &n, &m, &k);
  // Check if it's possible to form a triangle with area nm/k
  // For a triangle with vertices at (0,0), (a,0), (0,b), area = (1/2)*a*b
  // So we need (1/2)*a*b = nm/k => a*b = 2*nm/k
  // So 2*n*m must be divisible by k for a valid solution
  if ((2 * m * n) % k != 0) {
    puts("NO");
    return 0;
  }
  // Simplify the fraction 2*n/k by dividing by gcd(2*n, k)
  ll g = gcd(2 * n, k);
  if (g == 1) {
    // If gcd is 1, then 2*n and k are coprime, so we can take m = 2*m/k
    m = 2 * m / k;
  } else {
    // Otherwise, divide both numerator and denominator by their gcd
    n = 2 * n / g;
    m = m * g / k;
  }
  // Output the triangle vertices at (0,0), (n,0), (0,m)
  // This ensures triangle area = (1/2)*n*m = nm/k
  printf("YES\n0 0\n%lld 0\n0 %lld\n", n, m);
  return 0;
}


// https://github.com/VaHiX/CodeForces/