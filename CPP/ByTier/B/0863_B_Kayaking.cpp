// Problem: CF 863 B - Kayaking
// https://codeforces.com/contest/863/problem/B

/*
 * Problem: Kayaking
 * 
 * Approach:
 * This solution uses a brute-force method to try all possible pairs of people
 * to assign to the single kayaks, and then assigns the remaining people optimally
 * to the tandem kayaks to minimize total instability.
 * 
 * For each pair of people selected for single kayaks, the remaining 2*n - 2 people
 * are sorted and paired consecutively (greedy pairing minimizes the sum of differences).
 * 
 * Time Complexity: O(n^2 * (2*n) * log(2*n)) = O(n^3 * log n)
 * Space Complexity: O(2*n) = O(n)
 * 
 * Algorithms/Techniques:
 * - Brute-force enumeration of pairs for single kayaks
 * - Greedy pairing after sorting for tandem kayaks
 * - Sorting and minimal difference calculation
*/

#include <algorithm>
#include <iostream>
#include <vector>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
#define inf 99999
using namespace std;

int main() {
  int i, j, k;
  int n, m, sum;
  cin >> n;
  n = n * 2; // Total number of people
  int a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  m = inf;
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      sum = 0;
      vector<int> v;
      // Build vector of remaining people (excluding the two chosen for single kayaks)
      for (k = 0; k < n; k++) {
        if (k != j && k != i)
          v.push_back(a[k]);
      }
      sort(v.begin(), v.end()); // Sort the remaining people
      // Pair consecutive people and sum up the differences
      for (k = 0; k < v.size(); k += 2)
        sum += (v[k + 1] - v[k]);
      m = min(m, sum);
    }
  }
  cout << m;
  return 0;
}


// https://github.com/VaHiX/CodeForces/