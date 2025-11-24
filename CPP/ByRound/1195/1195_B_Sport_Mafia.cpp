// Problem: CF 1195 B - Sport Mafia
// https://codeforces.com/contest/1195/problem/B

/*
 * B. Sport Mafia
 *
 * Problem Description:
 * Alya performs n actions to fill a box with candies. The first action always puts 1 candy.
 * For subsequent actions, she can either eat 1 candy (if available) or add k+1 candies (where k is the number added in previous step).
 * Given total actions n and final number of candies k, determine how many candies were eaten.
 *
 * Algorithm:
 * - Use mathematical approach to derive the number of candies eaten.
 * - Let x be the number of candies eaten (i.e., number of "eat" operations).
 * - The number of "put" operations is (n - x).
 * - If we put candies for t steps, and eat for x steps (t = n - x), total candies added = 1 + 2 + ... + t = t*(t+1)/2.
 * - Total candies remaining after eating = t*(t+1)/2 - x = k
 * - Rearranging the equation: t^2 + t - 2x - 2k = 0 --> t = (-1 + sqrt(1 + 8*x + 8*k)) / 2
 * - Using quadratic formula to find possible values of x.
 *
 * Time Complexity: O(1) - constant time operations including square root
 * Space Complexity: O(1) - only a few variables used
 */

#include <math.h>
#include <stdio.h>
#include <utility>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 200100
#define inf 1e18
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
#define pp pair<int, int>
using namespace std;

// Function to test if a given value x leads to correct number of candies
ll tester(ll n, ll x) { return ((n - x) * (n - x + 1)) / 2 - x; }

int main() {
  ll i, j, k;
  ll n, m;
  sffl(n, k);

  // Derive possible solutions using quadratic equation
  ll x = (2 * n + 3);                    // Part of the derived formula (constant term)
  ll y = sqrt(1.0 * (8 * n + 8 * k + 9)); // Square root part of derived formula
  ll ans1 = (x + y) / 2;                 // First solution from quadratic formula
  ll ans2 = (x - y) / 2;                 // Second solution from quadratic formula

  // Ensure ans1 >= ans2 for consistent comparison later
  if (ans1 < ans2)
    swap(ans1, ans2);

  // Check which answer is valid by verifying the constraint and calculated formula
  if (n - 1 >= ans1 && tester(n, ans1) == k)
    pf(ans1);
  else
    pf(ans2);

  return 0;
}


// https://github.com/VaHiX/codeForces/