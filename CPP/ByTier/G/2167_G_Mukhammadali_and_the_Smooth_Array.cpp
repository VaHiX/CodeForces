// Problem: CF 2167 G - Mukhammadali and the Smooth Array
// https://codeforces.com/contest/2167/problem/G

/*
 * Problem: G. Mukhammadali and the Smooth Array
 * 
 * Purpose: 
 *   Given an array of integers and costs to modify each element, find the minimum cost to make the array non-decreasing (no "drops").
 *   A drop occurs when an element is greater than the next one.
 * 
 * Algorithm:
 *   - Coordinate compression: map unique values of array to smaller indices for efficient DP.
 *   - Dynamic Programming with Fenwick Tree (Binary Indexed Tree):
 *     - For each element, we maintain the maximum cost of keeping it (i.e., not changing it) such that the resulting sequence remains non-decreasing.
 *     - Use a Fenwick Tree to efficiently query and update the maximum cost for elements less than or equal to the current element.
 *     - The answer is the total cost minus the maximum cost of keeping elements.
 * 
 * Time Complexity:
 *   O(n log n) per test case due to sorting, coordinate compression, and Fenwick tree operations.
 *   Total across all test cases: O(n log n) where sum of n is at most 8000.
 * 
 * Space Complexity:
 *   O(n) for storing the array, costs, compressed values, and Fenwick tree.
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<long long> a(n), c(n);
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> c[i];
    
    // Coordinate compression: sort and map unique values to smaller indices
    vector<long long> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    sorted_a.erase(unique(sorted_a.begin(), sorted_a.end()), sorted_a.end());
    
    map<long long, int> compress;
    for (int i = 0; i < sorted_a.size(); i++) {
      compress[sorted_a[i]] = i + 1;  // Use 1-based indexing for Fenwick tree
    }
    
    int m = sorted_a.size();
    vector<long long> fenwick(m + 2, 0);  // Fenwick tree with size m+2 to avoid bounds issues
    
    // Lambda functions for Fenwick tree operations
    auto update = [&](int idx, long long val) {
      while (idx <= m) {
        fenwick[idx] = max(fenwick[idx], val);
        idx += idx & -idx;
      }
    };
    
    auto query = [&](int idx) {
      long long res = 0;
      while (idx > 0) {
        res = max(res, fenwick[idx]);
        idx -= idx & -idx;
      }
      return res;
    };
    
    long long total_cost = 0;
    long long max_kept = 0;  // Maximum cost of keeping elements (not changing)
    
    for (int i = 0; i < n; i++) {
      total_cost += c[i];  // Add the cost to change this element if we decide to change it
      
      int comp_idx = compress[a[i]];  // Get the compressed index of this element
      long long best = query(comp_idx) + c[i];  // The best cost to keep this element
      max_kept = max(max_kept, best);  // Update the maximum cost of keeping any element
      update(comp_idx, best);  // Update the Fenwick tree with the best value at this index
    }
    
    cout << total_cost - max_kept << "\n";  // Minimum cost = Total cost - Maximum kept cost
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/