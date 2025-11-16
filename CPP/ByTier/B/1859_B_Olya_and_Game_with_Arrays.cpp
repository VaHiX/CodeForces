// Problem: CF 1859 B - Olya and Game with Arrays
// https://codeforces.com/contest/1859/problem/B

/*
B. Olya and Game with Arrays

Purpose:
This program solves the problem of maximizing the "beauty" of a list of arrays,
where beauty is defined as the sum of minimum elements from each array.
The allowed operation is to move at most one element from any array to another.

Algorithm:
1. For each array, compute its local minimum (mn) and second minimum (smn).
2. Find global minimum (gmn) among all local minima.
3. Identify the index (idx) of the array with smallest second minimum (gsmn).
4. For each array:
   - If it's not the one with smallest second minimum, add its second minimum to sum.
   - Otherwise, add the global minimum (gmn) to sum.
5. Output this computed sum.

Time Complexity: O(sum of m_i) over all test cases
Space Complexity: O(n)

Input Format:
- First line contains number of test cases t
- For each test case:
  - Line 1: n (number of arrays)
  - For each array i:
    - Line 1: m_i (size of array)
    - Line 2: m_i integers representing the elements

Output Format:
- For each test case, a single integer representing maximum beauty
*/

#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<long, long>> v(n); // Store min and second min for each array
    long idx(-1), gmn(1e9 + 7), gsmn(1e9 + 7); // Global min, global second min, index of array with smallest second min
    for (long p = 0; p < n; p++) {
      long m;
      scanf("%ld", &m);
      long mn(1e9 + 7), smn(1e9 + 7); // Local min and second min for current array
      for (long q = 0; q < m; q++) {
        long x;
        scanf("%ld", &x);
        if (x <= mn) { // Update both min and second min
          smn = mn;
          mn = x;
        } else if (x < smn) { // Only update second min
          smn = x;
        }
      }
      v[p] = std::make_pair(mn, smn); // Store min and second min for this array
      gmn = (gmn < mn) ? gmn : mn; // Update global minimum
      if (smn < gsmn) { // If this array has smaller second min than current global
        gsmn = smn;
        idx = p;
      }
    }
    long long sum(0);
    for (long p = 0; p < n; p++) {
      sum += (p != idx) ? v[p].second : gmn; // Add appropriate minimum to total
    }
    printf("%lld\n", sum);
  }
}


// https://github.com/VaHiX/codeForces/