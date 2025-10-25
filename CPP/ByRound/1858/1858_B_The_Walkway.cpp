// Problem: CF 1858 B - The Walkway
// https://codeforces.com/contest/1858/problem/B

/*
 * Purpose: Solves the problem of minimizing the number of cookies Petya eats
 *          by removing exactly one cookie seller from the walkway.
 *
 * Algorithm: 
 * 1. First, we calculate the total number of cookies Petya would eat without removing any seller.
 *    This is done by simulating his walk and applying the rules for eating cookies.
 * 2. For each possible seller to remove, we compute how much the number of cookies would decrease.
 *    This is done by calculating the "gain" for removing a seller at position i.
 * 3. We find the minimum gain and count how many sellers give that minimum gain.
 *
 * Time Complexity: O(m) per test case, where m is the number of sellers.
 * Space Complexity: O(m) due to the arrays used to store intermediate results.
 *
 * Techniques:
 * - Simulation with greedy approach
 * - Prefix sum concept for optimization
 * - Difference array technique for efficient computation
 */

#include <iostream>
#include <vector>
using namespace std;

long long q, w, e, r, t, y, u, arr[100010], arr2[100010];
vector<long long> v;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  cin >> q; // Read number of test cases
  
  while (q--) {
    cin >> w >> e >> r; // w: benches, e: sellers, r: d parameter
    v.resize(e); // Resize vector to hold seller positions
    
    // Read positions of cookie sellers
    for (int i = 0; i < e; i++) {
      cin >> v[i];
    }
    
    // Calculate cookies eaten without removing any seller
    // arr[i] represents the number of cookies eaten if we remove seller at position i
    if (v[0] == 1) {
      // If first seller is at bench 1, Petya eats 1 cookie immediately
      arr[0] = 1;
    } else {
      // Otherwise, Petya eats a cookie at bench 1, and then needs to wait
      // (v[0] - 2) / r more benches after bench 1 to eat another cookie
      arr[0] = 1 + (v[0] - 2) / r + 1;
    }
    
    t = arr[0]; // Total cookies eaten initially
    
    // Process remaining sellers
    for (int i = 1; i < e; i++) {
      // Number of cookies eaten between sellers i-1 and i
      arr[i] = (v[i] - v[i - 1] - 1) / r + 1;
      t += arr[i];
    }
    
    // Cookies eaten after last seller until bench n
    arr[e] = (w - v[e - 1]) / r;
    t += arr[e];
    
    // arr2[i] represents the number of cookies eaten if we remove seller at position i
    // This is done to compute the "gain" in cookies avoided by removing each seller
    
    // First seller removal case
    arr2[0] = 1 + (v[1] - 2) / r + 1;
    
    // Middle sellers removal case
    for (int i = 1; i + 1 < e; i++) {
      arr2[i] = (v[i + 1] - v[i - 1] - 1) / r + 1;
    }
    
    // Last seller removal case
    arr2[e - 1] = (w - v[e - 2]) / r;
    
    // Compute the minimum gain for removing one seller
    // gain = (arr2[i] - arr[i] - arr[i + 1])  
    y = arr2[0] - arr[0] - arr[1]; // Initial minimum gain
    u = 1; // Count of sellers giving minimum gain
    
    // Check all sellers for minimum gain
    for (int i = 1; i < e; i++) {
      if (y == arr2[i] - arr[i] - arr[i + 1]) {
        ++u; // Found another seller with same minimum gain
      }
      if (y > arr2[i] - arr[i] - arr[i + 1]) {
        // Found a better (smaller) gain, update
        y = arr2[i] - arr[i] - arr[i + 1];
        u = 1; // Reset count
      }
    }
    
    // Output total cookies eaten and number of best sellers to remove
    cout << t + y << " " << u << '\n';
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/