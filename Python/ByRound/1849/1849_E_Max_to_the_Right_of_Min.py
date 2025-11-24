# Problem: CF 1849 E - Max to the Right of Min
# https://codeforces.com/contest/1849/problem/E

"""
Algorithm: Two Stack Approach with Monotonic Stacks
Purpose: Count subarrays where the index of maximum element is greater than the index of minimum element.
Time Complexity: O(n)
Space Complexity: O(n)

This solution uses two monotonic stacks to keep track of indices of minimum and maximum elements in subarrays.
It maintains a 'valid' count of subarrays satisfying the condition and updates it as we iterate through the array.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


def solve() -> None:
    n = sint()
    nums = [1e7] + ints()  # Prepend a large number to simplify boundary handling

    stmn = []  # Stack for indices of minimum elements
    stmx = []  # Stack for indices of maximum elements

    ans = valid = 0
    end = [None] * (n + 1)  # Tracks end points of valid intervals for each index

    for r in range(n + 1):
        # Process stack for minimum elements
        while stmn and nums[r] > nums[stmn[-1]]:
            if end[stmn[-1]]:
                i, dec_i = end[stmn[-1]]

                if dec_i < len(stmx) and stmx[dec_i] == i:
                    # Adjust valid count based on popping from stacks
                    valid -= i - stmn[-1]

                    if dec_i == 0 or stmx[dec_i - 1] < stmn[-2]:
                        valid += i - stmn[-2]
                        end[stmn[-2]] = (i, dec_i)
                        end[i] = (stmn[-2], None)
                    else:
                        valid += i - stmx[dec_i - 1]
                        end[i] = (stmx[dec_i - 1], None)

            stmn.pop()

        # Process stack for maximum elements
        while stmx and nums[r] < nums[stmx[-1]]:
            if end[stmx[-1]]:
                valid -= stmx[-1] - end[stmx[-1]][0]

            stmx.pop()

        # Push current index to both stacks
        stmn.append(r)
        stmx.append(r)

        # Record the end point for current index
        end[r] = (r, len(stmx) - 1)

        # Add current valid count to total answer
        ans += valid

    print(ans)


solve()


# https://github.com/VaHiX/CodeForces/