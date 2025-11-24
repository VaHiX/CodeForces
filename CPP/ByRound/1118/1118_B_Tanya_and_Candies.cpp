// Problem: CF 1118 B - Tanya and Candies
// https://codeforces.com/contest/1118/problem/B

/*
Problem: Tanya and Candies
Purpose: Given n candies with weights, determine how many candies can be given to dad such that the sum of weights eaten on odd days equals the sum eaten on even days.

Algorithms/Techniques:
- Prefix sum technique for even and odd indexed elements.
- Two pass approach:
  1. Forward pass to compute prefix sums of even and odd indexed elements.
  2. Backward pass to compute suffix sums of even and odd indexed elements.
- For each candy, check if the total sum of odd/even days is equal when that candy is removed.

Time Complexity: O(n)
Space Complexity: O(n)

Input:
The first line contains one integer n — the number of candies.
The second line contains n integers a_1, a_2, ..., a_n — weights of candies.

Output:
Print one integer — the number of good candies.
*/

#include <stdio.h>
#include <utility>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 100100
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<ll, ll>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  sf(n);
  int a[n];
  for (i = 0; i < n; i++)
    sf(a[i]);
  
  pp x[n], y[n]; // x: prefix sums, y: suffix sums
  ll odd, even;
  odd = 0, even = 0;
  
  // Forward pass: Compute prefix sums for even/odd positions
  for (i = 0; i < n; i++) {
    x[i] = {even, odd}; // Store current even and odd sums before adding a[i]
    if ((i + 1) % 2)
      odd += (ll)a[i];
    else
      even += (ll)a[i];
  }
  
  odd = 0, even = 0;
  
  // Backward pass: Compute suffix sums for even/odd positions
  for (i = n - 1; i >= 0; i--) {
    y[i] = {even, odd}; // Store current even and odd sums before adding a[i]
    if ((i + 1) % 2)
      odd += (ll)a[i];
    else
      even += (ll)a[i];
  }
  
  int cnt = 0;
  
  // Check first candy
  if (y[0].first == y[0].second)
    cnt++;
    
  // Check last candy (if n > 1)
  if (n > 1 && x[n - 1].first == x[n - 1].second)
    cnt++;
    
  // Check middle candies
  for (i = 1; i < n - 1; i++) {
    even = x[i].first + y[i].second; // Even sum in the remaining sequence after removing candy i
    odd = x[i].second + y[i].first;  // Odd sum in the remaining sequence after removing candy i
    if (even == odd)
      cnt++;
  }
  
  pf(cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/