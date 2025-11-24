// Problem: CF 540 B - School Marks
// https://codeforces.com/contest/540/problem/B

/*
Code Purpose:
This code determines the marks Vova needs to achieve in the remaining tests such that:
1. The total sum of all marks does not exceed x.
2. The median of all marks is at least y.
The solution uses a greedy approach:
- It counts how many of the existing marks are less than y.
- It calculates how many of the remaining marks should be 1 (to minimize sum and maintain median).
- It assigns the rest as y to maintain the median constraint and stay under the sum limit.

Algorithms/Techniques:
- Greedy algorithm
- Sorting concepts (median calculation)
- Simple arithmetic and constraints checking

Time Complexity: O(k) where k is the number of tests already written.
Space Complexity: O(1) - only a few variables are used, no additional data structures.

*/
#include <cstdio>
int main() {
  int n, k, p, x, y;
  scanf("%d %d %d %d %d\n", &n, &k, &p, &x, &y);
  int smallerCount(0); // Count of existing marks less than y
  long sumLeft(x); // Remaining sum allowed for the rest of the tests
  for (int p = 0; p < k; p++) {
    int temp;
    scanf("%d", &temp);
    sumLeft -= temp; // Deduct the existing mark from allowed sum
    smallerCount += (temp < y); // Check if mark is less than median threshold
  }
  int smallerLeft = n / 2 - smallerCount; // Number of marks less than y needed among remaining
  if (smallerLeft > n - k) { // If more than remaining tests are needed, cap it
    smallerLeft = n - k;
  }
  int largerLeft = n - k - smallerLeft; // Number of marks >= y needed among remaining
  if (smallerCount > n / 2 || sumLeft < smallerLeft + y * largerLeft) { // Check feasibility
    puts("-1");
    return 0;
  }
  while (smallerLeft--) { // Assign 1s for the smaller values
    printf("1 ");
  }
  while (largerLeft--) { // Assign y for the larger values
    printf("%d ", y);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/