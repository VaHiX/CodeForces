// Problem: CF 1991 H - Prime Split Game
// https://codeforces.com/contest/1991/problem/H

/*
Algorithm/Techniques:
- Sieve of Eratosthenes for prime number generation
- Preprocessing to determine which numbers can be split into two primes
- Game theory using Grundy numbers and nim-like logic

Time Complexity: O(MAXN * log(log(MAXN)) + t * n) where t is number of test cases and n is the number of piles
Space Complexity: O(MAXN) for storing primes and auxiliary arrays

The problem is a variant of Nim game where players make moves by splitting piles into two prime-sized piles.
We precompute which numbers can be split into two primes and use this to determine optimal play.
*/
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<pll> vpll;
#define PB push_back
#define PF push_front
#define PPB pop_back
#define PPF pop_front
#define X first
#define Y second
#define MP make_pair
#define all(x) (x).begin(), (x).end()
const int mod = 1e9 + 7;
const int inf = 1e9 + 7;
const ll INF = 1e18 + 7;
const int logo = 20;
const int MAXN = 2e5 + 7;
const int off = 1 << logo;
const int trsz = off << 1;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int pr[MAXN]; // Array to mark primes
bool gd[MAXN], sp[MAXN]; // gd[i] = true if i can be split into two primes; sp[i] = true if i can be split into two primes (for second condition)
vi p, op, odl; // p = list of primes, op = list of primes that are valid for splitting, odl = unused
void pre() {
  // Sieve of Eratosthenes to find all primes up to MAXN
  for (int i = 2; i < MAXN; i++) {
    pr[i] = !pr[i]; // Mark if prime (initially all marked as non-prime except 2)
    if (pr[i])
      p.PB(i); // Add prime to list
    else
      continue;
    for (int j = i * 2; j < MAXN; j += i) // Mark multiples as non-prime
      pr[j] = 1;
  }
  // Check for each number if it can be written as sum of two primes
  for (int i = 2; i < MAXN; i++) {
    bool ans = 0;
    for (auto &x : p) {
      if (x * 2 > i)
        break; // No need to check if x > i/2
      if (ans)
        break;
      if (i % 2 and x > 2)
        break; // For odd numbers, only check if x = 2 (since 2 is the only even prime)
      if (pr[i - x] and pr[x] and !gd[i - x] and !gd[x]) // Both primes and not already marked
        ans = 1;
    }
    gd[i] = ans; // Mark whether number can be split into two primes
    if (gd[i] and pr[i])
      op.PB(i); // Add to list of primes that can be split
  }
  // Mark all numbers that can be split into two primes
  for (auto &x : op)
    for (auto &y : op)
      if (x + y < MAXN)
        sp[x + y] = 1; // Mark sums of two primes
}
void solve() {
  int n;
  cin >> n;
  int a = 0, b = 0;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    a += gd[x]; // Count how many numbers can be split into two primes
    b += sp[x]; // Count valid split sums
  }
  if (a == 0)
    cout << "Bob\n"; // No valid move for Alice
  else if (a < n)
    cout << "Alice\n"; // There are valid moves
  else if (n % 2 == 0)
    cout << "Alice\n"; // Even number of piles
  else {
    if (b == n or b == 0)
      cout << "Bob\n"; // All splits valid or none valid
    else
      cout << "Alice\n"; // Mixed valid/invalic splits
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  pre(); // Preprocessing step
  int tt = 1;
  cin >> tt;
  while (tt--)
    solve(); // Solve each test case
  return 0;
}


// https://github.com/VaHiX/CodeForces/