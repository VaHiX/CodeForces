// Problem: CF 1935 B - Informatics in MAC
// https://codeforces.com/contest/1935/problem/B

/*
 * Problem: B. Informatics in MAC
 * 
 * Algorithm/Technique: 
 * - Use mapping of first and last occurrence of each element to determine valid MEX values.
 * - Check if we can partition the array into exactly 2 segments such that both have the same MEX.
 * 
 * Time Complexity: O(n log n) per test case due to map operations (insertions and lookups)
 * Space Complexity: O(n) for storing first and last positions of elements in the map
 * 
 * Approach:
 * - For each element in the array, record its first and last occurrence.
 * - Iterate through potential MEX values (0 to n-1) to verify that for each MEX value,
 *   if it exists in the array, the first and last positions are different (since a single
 *   element cannot form a valid MEX of 0). 
 * - Based on first and last occurrences, compute the left and right boundaries for a valid
 *   2-segment partition.
 * - If valid boundaries are found, output a valid division into 2 segments.
 * - Otherwise output -1.
 */

#include <cstdio>
#include <map>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> first, last;
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      if (!first.count(x)) {
        first[x] = p;
      }
      last[x] = p;
    }
    bool possible(true);
    long left(1), right(n);
    for (int p = 0; p < n; p++) {
      if (!first.count(p)) {
        break; // No more elements with this MEX, so we can't form a valid partition
      } else if (first[p] == last[p]) {
        possible = false; // A single element cannot form a valid partition having this MEX
        break;
      }
      left = (left > first[p]) ? left : first[p]; // Update left boundary with max of current and new first occurrence
      right = (right < last[p]) ? right : last[p]; // Update right boundary with min of current and new last occurrence
      if (left > right) {
        possible = false; // Conflict in boundaries
      }
    }
    if (possible) {
      printf("2\n1 %ld\n%ld %ld\n", left, left + 1, n);
    } else {
      puts("-1");
    }
  }
}


// https://github.com/VaHiX/CodeForces/