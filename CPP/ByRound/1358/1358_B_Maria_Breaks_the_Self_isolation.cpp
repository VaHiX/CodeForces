// Problem: CF 1358 B - Maria Breaks the Self-isolation
// https://codeforces.com/contest/1358/problem/B

/*
B. Maria Breaks the Self-isolation

Algorithm: Greedy + Sorting
Approach:
1. Sort the array 'a' in ascending order.
2. For each element from right to left (largest to smallest), check if the current element 
   is less than or equal to the number of people who are already in the courtyard (including Maria).
3. If yes, we can include this granny in the ceremony. We increment count and continue.
4. The answer is the maximum number of grannies that can be included, including Maria.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(1) additional space (excluding input storage)

Input:
- First line contains t (number of test cases)
- For each test case:
  - First line contains n (number of grannies)
  - Second line contains n integers a_i

Output:
- Maximum number of grannies that can attend the ceremony, including Maria
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read each granny's requirement
    }
    sort(a.begin(), a.end()); // Sort in ascending order to process from smallest to largest
    long cnt(1); // Start with Maria (1 person)
    for (long p = n - 1; p >= 0; p--) {
      if (a[p] <= p + 1) { // If current granny's requirement is satisfied by the number of people already here
        cnt = p + 2; // Include one more granny and Maria (p+2 total)
        break;
      }
    }
    printf("%ld\n", cnt); // Output maximum grannies that can attend
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/