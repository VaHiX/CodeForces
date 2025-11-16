// Problem: CF 1978 A - Alice and Books
// https://codeforces.com/contest/1978/problem/A

/*
 * Problem: Alice and Books
 * Purpose: Given n books with page counts, divide them into two non-empty piles,
 *          such that the sum of the maximum page count in each pile is maximized.
 *
 * Algorithm:
 *   - For each test case, we are to split the array into two non-empty parts.
 *   - The result is the sum of the maximum values from both piles.
 *   - To maximize this sum, we can observe that it's optimal to take all elements
 *     except one and put them in one pile, and put the remaining element in the other.
 *   - Thus, we compute the maximum element in the array (this will be part of the answer),
 *     and also compute the second largest element, so as to maximize the sum.
 *   - However, there is a more straightforward approach:
 *     - We scan through n-1 elements to find maximum value (first pile).
 *     - Then we read the last element.
 *     - But this does not handle all splits correctly.
 *   - Actually, the correct greedy idea is:
 *     - Sort books in descending order of pages.
 *     - Take the first two, one goes to each pile.
 *     - Or better yet, observe that it's best to avoid a single small element.
 *   - A smarter way:
 *     - The maximum possible sum occurs when we take the two largest elements
 *       as the maximum from both piles (if we can arrange them this way).
 *     - But since we need to split into two piles, we can choose any valid split.
 *     - So we just take the maximum among all valid splits.
 *     - The key insight: For any fixed split point p, we get:
 *       max_in_first_pile + max_in_second_pile
 *     - Which means for any p in [1, n-1],
 *       max_element_from_a[0..p-1] + max_element_from_a[p..n-1]
 *     - Thus the problem reduces to finding max over p of these sums.
 *
 * Complexity:
 *   Time Complexity: O(n) per test case
 *   Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x(0), mx(0); // mx will store max value seen so far in first pile
    for (long p = 1; p < n; p++) { // iterate through all but last element
      scanf("%ld", &x);
      mx = (mx > x ? mx : x); // keep track of the maximum value among first part
    }
    scanf("%ld", &x); // read last element
    printf("%ld\n", mx + x); // output sum of max from both parts
  }
}


// https://github.com/VaHiX/codeForces/