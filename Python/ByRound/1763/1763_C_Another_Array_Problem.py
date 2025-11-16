# Problem: CF 1763 C - Another Array Problem
# https://codeforces.com/contest/1763/problem/C

"""
Problem: Another Array Problem
Algorithm: Greedy approach with case analysis
Time Complexity: O(n) per test case, where n is the length of the array
Space Complexity: O(1) additional space (excluding input storage)

The problem allows replacing a subarray with the absolute difference of its first and last elements.
We analyze different cases based on array size:
- For n=1: Only one element, so sum is the element itself.
- For n=2: Only one operation possible, result is 2 * |a[0] - a[1]|
- For n=3: Consider various operations and their effects on the sum
- For n>3: The optimal strategy is to make all elements equal to the maximum element, leading to max_element * n
"""

IP = lambda: map(int, input().split())
(t,) = IP()
while t:
    t -= 1
    (n,) = IP()
    a = list(IP())
    print(
        max(sum(a), abs(a[0] - a[1]) * 2)  # For n == 2, either keep original or apply one operation
        if n < 3
        else (
            max(a) * n  # For n > 3, make all elements equal to max element
            if n > 3
            else max(
                sum(a), abs(a[0] - a[1]) * 3, abs(a[1] - a[2]) * 3, a[0] * 3, a[2] * 3
            )  # For n == 3, consider all possible operations
        )
    )


# https://github.com/VaHiX/CodeForces/