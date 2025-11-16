// Problem: CF 1108 A - Two distinct points
// https://codeforces.com/contest/1108/problem/A

/*
 * Code Purpose:
 *   For each query, given two segments [ls, rs] and [lt, rt], find two distinct integers 
 *   a and b such that a is in [ls, rs], b is in [lt, rt], and a != b.
 * 
 * Algorithm:
 *   - For each query, we simply pick the leftmost value from the first segment (ls).
 *   - Then we pick the leftmost value from the second segment (lt), but if it equals ls, 
 *     we increment it by 1 to ensure a != b.
 * 
 * Time Complexity: O(q), where q is the number of queries. Each query takes constant time.
 * Space Complexity: O(1), as only a constant amount of extra space is used.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  while (n--) {
    long ls, rs, lt, rt;
    scanf("%ld %ld %ld %ld\n", &ls, &rs, &lt, &rt);
    // Output ls from first segment and lt + (ls == lt) from second segment
    // If ls == lt, then (ls == lt) is 1, so we output lt + 1; else 0, so we output lt
    printf("%ld %ld\n", ls, lt + (ls == lt));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/