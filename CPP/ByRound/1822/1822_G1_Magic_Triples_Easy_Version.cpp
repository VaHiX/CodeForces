// Problem: CF 1822 G1 - Magic Triples (Easy Version)
// https://codeforces.com/contest/1822/problem/G1

/*
 * Code Purpose: 
 *   This program counts the number of "magic triples" (i, j, k) in a given sequence of integers.
 *   A triple is magic if:
 *     - i, j, k are pairwise distinct indices
 *     - There exists a positive integer b such that a[i] * b = a[j] and a[j] * b = a[k]
 *   This implies that a[i], a[j], a[k] form a geometric progression with integer ratio.
 * 
 * Algorithm:
 *   1. Sort the input array.
 *   2. Group consecutive equal elements and count their occurrences.
 *   3. For each unique value, store its count and value.
 *   4. Use a hash map to quickly locate indices of elements.
 *   5. For each element as a starting point of geometric sequence, try to find valid b such that
 *      a[i] * b = a[j] and a[j] * b = a[k], using the hash map for fast lookup.
 *   6. Count valid triples using combinatorial multiplication of counts.
 *
 * Time Complexity: O(n log n + n^2) in worst case due to nested loops and sorting;
 *                  However, due to optimizations and constraints (sum of n <= 2*10^5),
 *                  the effective runtime is much better in practice.
 * Space Complexity: O(n) for storing the input, groups, and the hash map.
 */

#include <stdio.h>

typedef long long LL;
#include <algorithm>
#include <unordered_map>

using namespace std;

// Comparator for descending order sorting
bool rcmp(int a, int b) { return a > b; }

// Custom comparator class for ascending order
class mypcmp {
public:
  bool operator()(const int &a, const int &b) { return a < b; }
};

int as[200004];   // Input array
int cs[200004];   // Count of each unique element
int vs[200004];   // Unique values in sorted order

int main() {
  int n, i, c, j, d, nj, m, k, nk;
  LL r, t, inf, c0, nv;
  int tc;
  
  scanf("%d", &tc);
  while (tc--) {
    scanf("%d", &n);
    for (i = 0; i < n; i++)
      scanf("%d", &as[i]);
    
    // Sort the input array
    sort(as, as + n);
    
    // Group elements into unique values with their counts
    m = 0;
    r = 0;
    for (i = 0; i < n;) {
      j = i;
      while (j < n && as[j] == as[i])
        j++;
      c = j - i;
      if (c >= 3) {
        // If there are 3 or more same numbers, calculate combinations C(c,3)
        t = c;
        t *= c - 1;
        t *= c - 2;
        r += t;
      }
      cs[m] = j - i;
      vs[m] = as[i];
      m++;
      i = j;
    }
    
    // Build hash map for efficient lookup of index of a value
    unordered_map<int, int> xs;
    for (i = 0; i < m; i++)
      xs[vs[i]] = i;
    
    inf = vs[m - 1];  // Largest element
    
    // Process for valid geometric sequences where a[i] * b = a[j] and a[j] * b = a[k]
    for (i = 0; i < m - 2; i++) {
      j = i + 1;
      c0 = cs[i];
      for (k = 2;; k++) {
        if (j >= m - 1)
          break;
        nv = vs[i];
        nk = (vs[j] + nv - 1) / nv;  // Compute minimum required ratio
        if (k < nk)
          k = nk;
        if (inf / nv < k)
          break;
        nv *= k;
        if (inf / nv < k)
          break;
        if (xs.count(nv) == 0) {
          // Binary search for next element greater than nv
          d = m - j;
          while (d) {
            while (1) {
              nj = j + d;
              if (nj >= m)
                break;
              if (vs[nj] >= nv)
                break;
              j = nj;
            }
            d >>= 1;
          }
          j++;
        } else {
          // Found a value matching nv = vs[i] * k
          j = xs[nv];
          nv *= k;
          if (xs.count(nv)) {
            // Found a third value in geometric sequence
            nj = xs[nv];
            t = c0 * cs[j] * cs[nj];
            r += t;
          }
          j++;
        }
      }
    }
    printf("%lld\n", r);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/