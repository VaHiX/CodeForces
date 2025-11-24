# Problem: CF 1707 A - Doremy's IQ
# https://codeforces.com/contest/1707/problem/A

"""
Algorithm: Greedy Approach
Approach:
We process the contests from right to left (last to first). For each contest, we decide whether to take it based on:
1. If our current IQ (curr) is less than the required IQ (q), we can take it only if the difficulty is less than or equal to our current IQ.
2. If our current IQ is equal to q, we can only take it if difficulty is less than or equal to curr.
3. When we take a contest:
   - If difficulty > current IQ, we increment the IQ by 1.
   - Otherwise, IQ remains unchanged.

Time Complexity: O(n) for each test case, where n is the number of contests.
Space Complexity: O(n) for storing the result string.

This greedy algorithm works because taking a contest early (from right to left) gives more flexibility to use the remaining IQ for later contests.
"""

import sys

input = sys.stdin.readline
ans = []
for _ in range(int(input())):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    ll = [0] * n
    curr = 0
    for i in range(n - 1, -1, -1):  # Process contests from right to left
        if curr != q:  # If current IQ is below maximum IQ
            ll[i] = 1  # Take the contest
            if a[i] > curr:  # If difficulty exceeds current IQ
                curr += 1  # Increase IQ by 1
        else:  # If current IQ equals maximum IQ
            if a[i] <= curr:  # If contest is feasible
                ll[i] = 1  # Take the contest
    ans.append("".join(map(str, ll)))  # Convert list to binary string
print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/