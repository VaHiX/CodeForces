// Problem: CF 1714 B - Remove Prefix
// https://codeforces.com/contest/1714/problem/B

/*
B. Remove Prefix
Algorithm: Two-pointer technique with a set to track seen elements.
Approach:
  - Traverse the array from right to left.
  - Use a set to keep track of elements already seen.
  - If an element is already in the set, it means we found the first duplicate,
    so the prefix length to remove is the index + 1.
  - If no duplicates are found, the entire array needs to be removed (return n).
Time Complexity: O(n) amortized per test case, where n is the length of the sequence.
Space Complexity: O(n) for the set storage in worst case.

Input:
  The first line contains a single integer t (1 <= t <= 10^4) — the number of test cases.
  Each test case consists of two lines:
    - First line: an integer n (1 <= n <= 2*10^5) — length of sequence a.
    - Second line: n integers a_1, a_2, ..., a_n (1 <= a_i <= n) — elements of the sequence.
Output:
  For each test case, print the minimum number of moves (elements to remove from front) such that all remaining elements are unique.

Example:
Input:
5
4
3 1 4 3
5
1 1 1 1 1
1
1
6
6 5 4 3 2 1
7
1 2 1 7 1 2 1
Output:
1
4
0
0
5
*/

#include <cstdio>
#include <set>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::set<long> s;
    long res(0);
    for (long p = n - 1; p >= 0; p--) {
      if (s.count(a[p])) {   // If current element was seen before
        res = p + 1;         // The prefix to remove is up to this index
        break;
      }
      s.insert(a[p]);        // Insert the element into set
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/