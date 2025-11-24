# Problem: CF 2134 B - Add 0 or K
# https://codeforces.com/contest/2134/problem/B

"""
B. Add 0 or K
Time Complexity: O(n)
Space Complexity: O(1)

Algorithm:
- For each element in the array, we compute arr[i] + (arr[i] % (k + 1)) * k
- This operation ensures that all elements become multiples of (k + 1) after at most k operations.
- Since we are adding a value that is a multiple of k to each element,
  and we're using the modulo with (k+1), this guarantees that the final GCD will be greater than 1.

This works because:
- For any integer a, when you compute a % (k + 1), it gives a remainder in range [0, k].
- Adding (a % (k + 1)) * k to a ensures that arr[i] becomes a multiple of (k + 1) with at most k operations.
- As all elements are now multiples of (k + 1), their GCD will be at least (k + 1) > 1.

Example:
For input [2, 7, 1], k = 3:
- arr[0] = 2 + (2 % 4) * 3 = 2 + 2 * 3 = 8
- arr[1] = 7 + (7 % 4) * 3 = 7 + 3 * 3 = 16 → but we use 10 since we take mod of the result.
Instead, the intended approach is to ensure all values end up divisible by k + 1.
So the final array elements are multiples of (k + 1).
"""

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    for i in range(n):
        # Adding (arr[i] % (k + 1)) * k to make all numbers multiples of (k+1)
        arr[i] += (arr[i] % (k + 1)) * k
    print(*arr)


# https://github.com/VaHiX/codeForces/