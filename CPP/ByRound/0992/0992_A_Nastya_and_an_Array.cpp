// Problem: CF 992 A - Nastya and an Array
// https://codeforces.com/contest/992/problem/A

/*
 * Problem: Nastya and an Array
 * 
 * Purpose: 
 *   Given an array of integers, we want to find the minimum number of seconds 
 *   to make all elements zero, where in each second we can subtract an arbitrary 
 *   integer from all non-zero elements. The key insight is that each unique 
 *   non-zero value in the array requires a separate operation to reduce it to zero.
 * 
 * Algorithm:
 *   - Use a set to store all unique non-zero values in the array.
 *   - The size of the set gives the minimum number of operations required.
 * 
 * Time Complexity: O(n log n)
 *   - Inserting each of the n elements into the set takes O(log n) time.
 *   - Therefore, total time is O(n log n).
 * 
 * Space Complexity: O(n)
 *   - In the worst case, all elements are unique and stored in the set.
 * 
 * Techniques:
 *   - Set data structure to store unique elements.
 *   - Greedy approach: Each unique non-zero value corresponds to one operation.
 */

#include <cstdio>
#include <set>
int main() {
  long n;
  scanf("%ld", &n);
  std::set<long> s;  // Set to store unique non-zero values
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    if (x != 0) {
      s.insert(x);  // Only insert non-zero elements
    }
  }
  printf("%ld\n", s.size());  // Output the number of unique non-zero elements
  return 0;
}


// https://github.com/VaHiX/CodeForces/