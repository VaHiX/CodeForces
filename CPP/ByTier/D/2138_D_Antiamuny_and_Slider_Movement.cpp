// Problem: CF 2138 D - Antiamuny and Slider Movement
// https://codeforces.com/contest/2138/problem/D

/*
 * Problem: D. Antiamuny and Slider Movement
 * Algorithm/Techniques: Combinatorics, Sorting, Modular Arithmetic, Prefix Sums
 *
 * Time Complexity: O(q^2 + n*q*log(q) + n*q)
 * Space Complexity: O(n + q)
 *
 * The solution computes for each slider the sum of its final positions over all permutations
 * of operations. It uses sorting and combinatorics to efficiently compute contributions.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 5010, maxn = 5000;

// Fast exponentiation for modular inverse
int mi(int x, int t) {
  int d = 1;
  while (t) {
    if (t & 1)
      d = (ll)d * x % mod;
    x = (ll)x * x % mod;
    t /= 2;
  }
  return d;
}

// Modular inverse using Fermat's little theorem
int ni(int x) { return mi(x, mod - 2); }

struct node {
  int id, x, y;
};

int fl[N]; // Factorial array for modular arithmetic

int main() {
  cin.sync_with_stdio(false);
  cin.tie(0);
  
  // Precompute factorials
  fl[0] = 1;
  for (int i = 1; i <= maxn; i++)
    fl[i] = (ll)fl[i - 1] * i % mod;

  int T;
  cin >> T;
  while (T--) {
    int n, m, q;
    cin >> n >> m >> q;
    
    // Read initial positions
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
      cin >> a[i];
      
    // Read operations
    vector<node> b(q + 1);
    for (int i = 1; i <= q; i++)
      cin >> b[i].id >> b[i].x;
    
    // Sort operations by (x - id) to process in a specific order
    sort(b.begin() + 1, b.end(),
         [&](auto n1, auto n2) { return (n1.x - n1.id < n2.x - n2.id); });
         
    // Precompute modular inverses of factorials
    vector<int> Ni(q + 1);
    for (int i = 1; i <= q; i++)
      Ni[i] = ni(i);
      
    // For each slider, calculate the sum across all permutations
    for (int i = 1; i <= n; i++) {
      int good = 0, bad = 0, zero = 0;
      
      // Update y values for all operations based on current slider position i
      for (int j = 1; j <= q; j++) {
        if (b[j].id <= i)
          good++;
        else
          zero++;
        b[j].y = b[j].x - b[j].id + i;
      }
      
      int ans;
      if (good) {
        // Initial contribution from permutations where current slider is not pushed
        ans = (ll)fl[q] * b[1].y % mod;
        
        for (int j = 1; j <= q; j++) {
          // Adjust counts after processing the j-th operation
          if (b[j].id <= i)
            good--;
          else
            zero--;
            
          if (b[j].id >= i)
            bad++;
          else
            zero++;
            
          if (j == q)
            break;
            
          // Handle special case when no good/bad items remain and a[i] > b[j].y
          if (!good && !bad) {
            if (a[i] > b[j].y) {
              ans = (ans + (ll)fl[q] * (min(a[i], b[j + 1].y) - b[j].y)) % mod;
            }
          } else {
            // General case: compute contribution using combinatorics
            int res = (ll)fl[q] * Ni[good + bad] % mod * good % mod;
            ans = (ans + (ll)res * (b[j + 1].y - b[j].y)) % mod;
          }
        }
        
        // Add contribution from final state
        if (!bad)
          ans = (ans + (ll)fl[q] * max(0, a[i] - b[q].y)) % mod;
      } else {
        // Case when no operation affects current slider's position
        ans = (ll)fl[q] * min(a[i], b[1].y) % mod;
      }
      
      cout << ans << ' ';
    }
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/