# Problem: CF 1701 C - Schedule Management
# https://codeforces.com/contest/1701/problem/C

"""
Schedule Management

Algorithm:
- This problem uses binary search on the answer to find the minimum time to complete all tasks.
- The key insight is that for a given time limit T, we can determine if it's possible to complete all tasks.
- Workers can be assigned in a way that minimizes total time; this involves greedily distributing tasks.
- The minimum time is the minimum number of hours needed such that all tasks can be done.

Time Complexity: O(n * log(max(c))) where c is the count of tasks per worker
Space Complexity: O(n) for storing count of tasks per worker

"""
import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    c = [0] * n
    for i in a:
        c[i - 1] += 1    # Count tasks per worker (0-indexed)
    ng, ok = 0, max(c)
    while ok - ng > 1:
        m = (ng + ok) // 2    # Binary search mid-point for time limit
        b = 0
        for i in c:
            b += max(0, i - m)    # How many tasks worker needs to do in 2 hours due to inexperience
        for i in c:
            if i < m:
                b -= (m - i) // 2    # How many tasks the worker can save by being experienced (optimization)
        if b > 0:
            ng = m    # Not enough time, increase lower bound
        else:
            ok = m    # Sufficient time, try to minimize further
    print(ok)


# https://github.com/VaHiX/CodeForces/