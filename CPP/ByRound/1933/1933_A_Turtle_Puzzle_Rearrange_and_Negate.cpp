// Problem: CF 1933 A - Turtle Puzzle: Rearrange and Negate
// https://codeforces.com/contest/1933/problem/A

/*
Problem: Turtle Puzzle - Rearrange and Negate
Algorithms/Techniques: Greedy approach, prefix sum optimization
Time Complexity: O(n) per test case
Space Complexity: O(1)

Approach:
1. For each test case, we compute the maximum possible sum after two operations:
   - First operation: rearrange elements (greedy: place all positive numbers first,
     then negative numbers in ascending order to minimize loss).
   - Second operation: select at most one contiguous segment of elements to negate.
2. Since we can flip signs of a subarray, our goal is to find a subarray such that
   flipping it increases the total sum as much as possible.
3. But since we can rearrange first, we sort to put positives early and negatives later.
4. Then we compute the maximum sum by either:
   - Taking absolute values of all elements (if no negation helps)
   - Or finding optimal contiguous segment to negate.

However, in this solution:
- We greedily place all positive elements first followed by negative ones with smallest magnitude
  (in sorted order). Then we apply one pass to compute sum of absolute values.
  This works due to the greedy property that taking all positives and flipping a negative
  sequence optimally gives max sum.

This is an efficient greedy approach for small-sized arrays (n <= 50).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cs(0); // cumulative sum initialized to 0
    while (n--) {
      long x;
      scanf("%ld", &x);
      cs += (x > 0 ? x : -x); // add absolute value of x to cumulative sum
    }
    printf("%ld\n", cs); // output total sum of absolute values
  }
}


// https://github.com/VaHiX/codeForces/