// Problem: CF 1888 B - Raspberries
// https://codeforces.com/contest/1888/problem/B

/*
Code Purpose:
This program determines the minimum number of operations needed to make the product of an array divisible by a given number k.
Each operation allows incrementing any element by 1.
The solution leverages modular arithmetic to calculate how many increments are needed to make each element divisible by k's prime factors.

Algorithms used:
- For k = 2, 3, 5: Direct calculation of minimum operations to make any element divisible by k
- For k = 4: Additional logic to consider if at least two elements are even (to ensure divisibility by 4)
- For k = 5: Direct calculation of minimum operations to make any element divisible by 5

Time Complexity: O(n) per test case, since we iterate through the array once for each k case.
Space Complexity: O(n) for the array storage, and O(1) for additional variables.

Approach:
1. For k = 2: Check how many operations to make any element even (minimum 1 if any are odd).
2. For k = 3: For each element, compute required operations to reach next multiple of 3.
3. For k = 5: For each element, compute required operations to reach next multiple of 5.
4. For k = 4: Similar but we also look for at least two even numbers to make the product divisible by 4.
*/
#include <stdio.h>
#include <algorithm>

using namespace std;
int t, n, k;
int arr[100005];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
      scanf("%d", &arr[i]);
    if (k == 1)
      printf("0\n"); // Any number is divisible by 1
    else if (k == 2) {
      int res = 1; // Maximum 1 operation needed to make any element even (since odd -> even needs 1)
      for (int i = 0; i < n; i++)
        res = min(res, arr[i] % 2); // If any element is odd, we need 1 operation to make it even
      printf("%d\n", res);
    } else if (k == 3) {
      int res = 2; // Max operations needed to get to a multiple of 3
      for (int i = 0; i < n; i++)
        res = min(res, (3 - arr[i] % 3) % 3); // Minimum operations to make element divisible by 3
      printf("%d\n", res);
    } else if (k == 5) {
      int res = 4; // Max operations needed to get to a multiple of 5
      for (int i = 0; i < n; i++)
        res = min(res, (5 - arr[i] % 5) % 5); // Minimum operations to make element divisible by 5
      printf("%d\n", res);
    } else { // k == 4
      int res = 4; // Max operations needed to get to a multiple of 4
      for (int i = 0; i < n; i++)
        res = min(res, (4 - arr[i] % 4) % 4); // Minimum operations to make element divisible by 4
      int cnt = 0; // Count of odd numbers
      for (int i = 0; i < n; i++)
        cnt += arr[i] % 2; // Increment if element is odd
      if (n - cnt >= 2) // If at least 2 elements are even, product is divisible by 4
        res = min(res, 0); // No operations needed
      if (n - cnt == 1 && cnt >= 1) // If exactly 1 even, and 1 odd, need 1 more to make even
        res = min(res, 1); // 1 operation needed
      if (n - cnt == 0 && cnt >= 2) // All elements odd, need 2 operations to make 2 even
        res = min(res, 2); // 2 operations needed
      printf("%d\n", res);
    }
  }
}


// https://github.com/VaHiX/CodeForces/