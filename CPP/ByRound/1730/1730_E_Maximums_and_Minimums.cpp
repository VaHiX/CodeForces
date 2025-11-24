// Problem: CF 1730 E - Maximums and Minimums
// https://codeforces.com/contest/1730/problem/E

/*
Algorithm: Divide and Conquer with Preprocessing
Approach:
- For each element, precompute all divisors that exist in the array
- Use divide and conquer to count valid subarrays
- For each midpoint, check all subarrays that cross the midpoint
- Use prefix/suffix min/max to efficiently compute valid ranges
- Preprocessing step for divisors allows fast lookup during merge phase

Time Complexity: O(n * log(max_value) + n * log(n))
Space Complexity: O(n + max_value)
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int n;
int a[500005]; // Array elements (1-indexed)
int dem[1000005]; // Frequency counter for elements
int kt[1000005]; // Presence marker for elements
vector<int> uoc[1000005]; // uoc[i] stores all divisors of i that exist in array

// Recursive function to count valid subarrays using divide and conquer
long long calc(int l, int r) {
  // Base case: single element subarray always valid (min == max)
  if (l == r)
    return 1;
  
  int mid = (l + r) / 2; // Midpoint for divide and conquer
  long long kq = calc(l, mid) + calc(mid + 1, r); // Recursively count in left and right halves

  // Process subarrays crossing the midpoint from left to right
  int maxx = -1e9, minn = 1e9; // Current max and min
  int dd = mid; // Right pointer for expanding window
  int minnn = 1e9; // Minimum in current left window
  int dd2 = mid; // Secondary pointer for left window
  for (int i = mid; i >= l; i--) {
    maxx = max(maxx, a[i]); // Update max
    minnn = min(minnn, a[i]); // Update min
    
    // Expand window to the right while elements <= max
    while (dd < r && a[dd + 1] <= maxx) {
      dd++;
      minn = min(minn, a[dd]); // Update min while expanding
      dem[minn]++; // Count frequencies
    }
    
    // Adjust dd2 to maintain minnn constraint
    while (dd2 < dd && a[dd2 + 1] > minnn) {
      dd2++;
    }
    
    // Check if max is divisible by min and add valid ranges
    if (maxx % minnn == 0)
      kq += dd2 - mid;
      
    // Check all divisors of maxx that are <= minnn
    for (auto j : uoc[maxx]) {
      if (j <= minnn)
        kq += dem[j]; // Add count of valid elements
    }
  }
  
  // Reset frequencies for right half
  for (int i = mid + 1; i <= r; i++)
    dem[a[i]] = 0;
    
  // Process subarrays crossing the midpoint from right to left
  maxx = -1e9, minn = 1e9;
  minnn = 1e9;
  dd = mid + 1;
  dd2 = mid + 1;
  for (int i = mid + 1; i <= r; i++) {
    maxx = max(maxx, a[i]);
    minnn = min(minnn, a[i]);
    
    // Expand window to the left while elements < max
    while (dd > l && a[dd - 1] < maxx) {
      dd--;
      minn = min(minn, a[dd]);
      dem[minn]++;
    }
    
    // Adjust dd2 to maintain minnn constraint
    while (dd2 > dd && a[dd2 - 1] > minnn) {
      dd2--;
    }
    
    // Check if max is divisible by min and add valid ranges
    if (maxx % minnn == 0)
      kq += mid - dd2 + 1;
      
    // Check all divisors of maxx that are <= minnn
    for (auto j : uoc[maxx]) {
      if (j <= minnn)
        kq += dem[j]; // Add count of valid elements
    }
  }
  
  // Reset frequencies for left half
  for (int i = l; i <= mid; i++)
    dem[a[i]] = 0;
    
  return kq;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      kt[a[i]] = 1; // Mark presence
      uoc[a[i]].clear(); // Clear divisor list
    }
    
    // Precompute divisors for all elements that exist
    for (int i = 1; i <= 1e6; i++)
      if (kt[i] == 1) {
        for (int j = i; j <= 1e6; j += i)
          if (kt[j] == 1)
            uoc[j].push_back(i);
      }
    
    cout << calc(1, n) << '\n'; // Start divide and conquer
    
    // Reset presence markers for next test case
    for (int i = 1; i <= n; i++)
      kt[a[i]] = 0;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/