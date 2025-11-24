# Problem: CF 2072 C - Creating Keys for StORages Has Become My Main Skill
# https://codeforces.com/contest/2072/problem/C

"""
C. Creating Keys for StORages Has Become My Main Skill

Problem Description:
Given n and x, construct an array of length n such that:
- The bitwise OR of all elements equals x.
- The MEX (minimum excludant) of the array is maximized.

Approach:
1. Start by placing values 0, 1, ..., n-2 into the first n-1 positions.
   These are chosen to be as small and distinct as possible to maximize MEX.
2. For the last element, compute what value is needed to make the total OR equal to x.
   This is done by taking x and XORing it with all previous ORs (which gives us the required value).
3. If the computed value is less than k, we adjust the last element to ensure the final result meets the OR constraint.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the output array
"""

for _ in range(int(input())):
    n, k = map(int, input().split())
    ans = [i & k for i in range(n)]  # Initialize with values that are bitwise AND of i and k
    x = 0
    for i in ans:                    # Compute the OR of all elements so far
        x |= i
    if x < k:                        # If current OR is less than target k, adjust last element
        ans[-1] |= k                 # Set the last element to include all bits from k
    print(*ans)


# https://github.com/VaHiX/codeForces/