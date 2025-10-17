// Problem: CF 1956 E1 - Nene vs. Monsters (Easy Version)
// https://codeforces.com/contest/1956/problem/E1

/*
Algorithm: Simulation with optimizations for large number of iterations
Approach:
1. For small n (n=2 or n=3), directly simulate the process using loops until no more changes occur
2. For larger n, use a check function to detect if all consecutive 4 monsters have non-zero energy
3. After determining equilibrium state, use mathematical optimizations to determine which monsters will remain

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing monster energies and boolean flags

Techniques:
- Simulation with early termination
- Mathematical optimization for cycle detection
- Modular arithmetic for circular array handling
*/

#include <time.h>
#include <algorithm>
#include <iostream>
#include <random>

using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN = 2e5 + 5;
int n, a[MAXN];
bool b[MAXN];

// Check if there exists a sequence of 4 consecutive monsters with non-zero energy
bool check() {
  a[n + 1] = a[1], a[n + 2] = a[2], a[n + 3] = a[3];
  for (int i = 1; i <= n; i++)
    if (a[i] && a[i + 1] && a[i + 2] && a[i + 3])
      return true;
  return false;
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  
  // Special case for n=2: simulate until one monster dies
  if (n == 2) {
    while (a[1] && a[2]) {
      a[2] = max(0, a[2] - a[1]);
      a[1] = max(0, a[1] - a[2]);
    }
    b[1] = (a[1] > 0);
    b[2] = (a[2] > 0);
  } 
  // Special case for n=3: simulate until no three monsters can attack each other
  else if (n == 3) {
    while (a[1] && a[2] && a[3]) {
      a[2] = max(0, a[2] - a[1]);
      a[3] = max(0, a[3] - a[2]);
      a[1] = max(0, a[1] - a[3]);
    }
    b[1] = (!a[3] && a[1]);  // Monster 1 survives if it wasn't killed by monster 3
    b[2] = (!a[1] && a[2]);  // Monster 2 survives if it wasn't killed by monster 1
    b[3] = (!a[2] && a[3]);  // Monster 3 survives if it wasn't killed by monster 2
  } 
  else {
    // For larger n, continue until we find a stable state
    while (check()) {
      for (int i = 1; i <= n; i++)
        a[i % n + 1] = max(0, a[i % n + 1] - a[i]);  // Apply attack
    }
    
    // Reset the flag array
    for (int i = 1; i <= n; i++)
      b[i] = false;
    
    // Lambda function to compute mathematical result for optimization
    auto attack = [&](ll x, ll y) {
      ll k = x / y;
      return (2 * x - (k + 1) * y) * k / 2;
    };
    
    // First pass: apply attacks to determine initial conditions
    for (int p = 1; p <= n; p++)
      if (a[p] && a[p % n + 1])
        a[p % n + 1] = max(0, a[p % n + 1] - a[p]);  // Attack from monster p to monster p+1
      else
        break;  // Stop when no more attacks can be made
    
    // Second pass: analyze the final configuration to determine which monsters will survive
    for (int i = 1; i <= n; i++)
      if (!a[i] && a[i % n + 1]) {  // If monster i dies but monster i+1 survives
        b[i % n + 1] = true;       // Monster i+1 might survive
        b[(i + 2) % n + 1] =       // Monster i+2 might survive based on mathematical condition
            (a[(i + 2) % n + 1] > attack(a[(i + 1) % n + 1], a[i % n + 1]));
      }
  }
  
  // Count number of surviving monsters
  int cnt = 0;
  for (int i = 1; i <= n; i++)
    if (b[i])
      cnt++;
  
  cout << cnt << endl;
  for (int i = 1; i <= n; i++)
    if (b[i])
      cout << i << ' ';
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  int _;
  cin >> _;
  while (_--)
    solve();
}


// https://github.com/VaHiX/CodeForces/