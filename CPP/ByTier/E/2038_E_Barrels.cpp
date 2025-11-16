// Problem: CF 2038 E - Barrels
// https://codeforces.com/contest/2038/problem/E

/*
 * Problem: E. Barrels
 * 
 * Purpose: The algorithm computes the maximum possible volume of water in the first barrel
 *          after adding clay to seal pipes and allow water to redistribute under equilibrium.
 * 
 * Techniques:
 * - Stack-based approach to determine which barrels are connected by working pipes.
 * - Simulation of water redistribution with clay addition, maintaining equilibrium at each step.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Algorithms:
 * 1. Preprocessing height array using stack to find connection points.
 * 2. Water redistribution simulation with pipe sealing logic.
 * 3. Optimization of water levels using accumulated volumes and pipe constraints.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;
constexpr int _ = 2e5 + 5, mod = 998244353;
int n, a[_], h[_], f[_];
double b[_];

void work() {
  cin >> n;
  // Compute prefix sums of water volumes
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    b[i] = b[i - 1] + a[i];  // b[i] holds sum of water up to barrel i
  }
  
  stack<int> st;  // Stack to track barrel indices for pipe connections
  st.push(1);
  h[1] = 1e9;  // Sentinel value for pipe height of first barrel
  
  // Process pipe heights to determine which barrels are connected by working pipes
  for (int i = 2; i <= n; ++i) {
    cin >> h[i];
    while (h[st.top()] <= h[i]) {
      st.pop();  // Pop barrels with lower or equal pipe heights
    }
    f[i] = st.top();  // f[i] stores the index of the previous barrel that is connected
    st.push(i);       // Push current barrel index to stack
  }
  
  // Simulation of water redistribution
  double x = a[n];  // Water level in the last barrel
  double y = 0;     // Accumulated additional water during redistribution
  int j = n;        // Current barrel being processed
  
  // Iterate backward through barrels to simulate water redistribution
  for (int i = n; i > 1; --i) {
    x += 1.0 * h[i] / (i - j + 1);  // Update water level based on added water from pipe
    
    // If water level exceeds current pipe height, handle pipe sealing and redistribution
    while (x > h[j]) {
      y += (x - h[j]) * (i - j + 1);  // Add overflow volume to accumulated water
      
      x = h[j];  // Set water level to pipe height since pipe is sealed
      
      // Check if water can be redistributed to lower barrels (based on accumulated volume)
      if (y + b[j - 1] - b[f[j] - 1] >= x * (j - f[j])) {
        // Rebalance water if there's enough volume to fill the lower region
        x = (y + b[j - 1] - b[f[j] - 1] + x * (i - j + 1)) / (i - f[j] + 1);
        y = 0;
        j = f[j];  // Update the current barrel to the one connected via working pipe
      }
    }
    
    // If we've reached the first barrel, prepare for further iteration
    if (j == i) {
      x = y + a[i - 1];  // Compute new water level in the previous barrel
      y = 0;
      --j;
    }
  }
  
  printf("%.10lf\n", x);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = 1;
  while (T--) {
    work();
  }
}


// https://github.com/VaHiX/CodeForces/