# Problem: CF 1753 A2 - Make Nonzero Sum (hard version)
# https://codeforces.com/contest/1753/problem/A2

"""
Algorithm: Greedy Partitioning with Alternating Sum Tracking
Approach:
1. First check if the total sum of the array is even. If odd, a valid partition is impossible.
2. Otherwise, process elements from left to right.
3. Keep track of cumulative sum (cur). 
4. For each element, update cur by adding A[i].
5. If absolute value of cur is less than 2, start a new segment with just this element.
6. Otherwise, backtrack by subtracting 2*A[i] from cur and extend the last segment to include current element.

Time Complexity: O(n)
Space Complexity: O(n) for storing the answer segments

This greedy approach works because:
- When we have a segment with alternating sum < 2 in absolute value, it's safe to start a new one.
- When cur >= 2 or cur <= -2, we try to balance by extending the last segment.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()

for _ in range(int(input())):
    N = int(input())
    A = list(map(int, input().split()))

    if sum(A) % 2:  # If sum is odd, it's impossible to make alternating sums sum to zero
        print(-1)
        continue

    cur = 0
    ans = []
    for i in range(N):
        cur += A[i]
        if abs(cur) < 2:  # If we can make a segment ending here without violating the alternating sum constraint
            ans.append([i + 1, i + 1])  # Start a new segment
        else:
            cur -= A[i] * 2  # Cancel out the effect of adding A[i] to balance the sum
            ans[-1][1] = i + 1  # Extend the last segment to cover this element

    print(len(ans))
    for a, b in ans:
        print(a, b)


# https://github.com/VaHiX/CodeForces/