# Problem: CF 2159 D1 - Inverse Minimum Partition (Easy Version)
# https://codeforces.com/contest/2159/problem/D1

"""
D1. Inverse Minimum Partition (Easy Version)

Purpose:
This code solves the problem of finding the minimum cost partition of a sequence of positive integers, where the cost of a subsequence is defined as ceil(sum of elements / length of subsequence). The solution uses dynamic programming with a convex hull trick to optimize the computation.

Algorithms/Techniques:
- Dynamic Programming (DP)
- Convex Hull Trick (CHT) for optimizing linear functions
- Deque-based implementation for maintaining tangents of lines

Time Complexity: O(n log n) per test case due to sorting-like operations in CHT and loop over n elements.
Space Complexity: O(n) for storing the input, DP array, and deque structure.

Input Format:
- First line contains number of test cases t
- For each test case:
  - First line: n (length of sequence)
  - Second line: n space-separated integers (sequence a)

Output Format:
- For each test case: single integer representing f(a)
"""

import random
import sys
from collections import deque

input = lambda: sys.stdin.buffer.readline()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def solve(N, A):
    deq = deque()

    def check(f1, f2, f3):
        # Check if f2 is redundant between f1 and f3 (convex hull property)
        return (f2[0] - f1[0]) * (f3[1] - f2[1]) >= (f2[1] - f1[1]) * (f3[0] - f2[0])

    def f(f1, x):
        # Evaluate linear function at point x
        return f1[0] * x + f1[1]

    def add_line(a, b):
        # Add a new line (a, b) to the deque
        f1 = (a, b)
        while len(deq) >= 2 and check(f1, deq[0], deq[1]):
            # Remove redundant lines from front of deque
            deq.popleft()
        deq.appendleft(f1)

    def query(x):
        # Find minimum value among all lines at x
        while len(deq) >= 2 and f(deq[-1], x) >= f(deq[-2], x):
            # Remove redundant lines from back of deque
            deq.pop()
        return f(deq[-1], x)

    A = A[::-1]
    dp = [0] * (N + 1)
    tmp_mini = max(A) + 1 # Minimum value seen so far, initialized to large number
    for i in range(1, N + 1):
        add_line(dp[i - 1], A[i - 1])
        tmp_mini = min(tmp_mini, A[i - 1])
        val = query(tmp_mini)
        dp[i] = (val + tmp_mini - 1) // (tmp_mini)
    return dp[N]


def brute(N, A):
    deq = deque()

    def check(f1, f2, f3):
        # Check if f2 is redundant between f1 and f3 (convex hull property)
        return (f2[0] - f1[0]) * (f3[1] - f2[1]) >= (f2[1] - f1[1]) * (f3[0] - f2[0])

    def f(f1, x):
        # Evaluate linear function at point x
        return f1[0] * x + f1[1]

    def add_line(a, b):
        # Add a new line (a, b) to the deque
        f1 = (a, b)
        while len(deq) >= 2 and check(deq[-2], deq[-1], f1):
            # Remove redundant lines from front of deque
            deq.popleft()
        deq.appendleft(f1)

    def query(x):
        # Find minimum value among all lines at x
        while len(deq) >= 2 and f(deq[-1], x) >= f(deq[-2], x):
            # Remove redundant lines from back of deque
            deq.pop()
        return f(deq[-1], x)

    A = A[::-1]
    dp = [0] * (N + 1)
    tmp_mini = max(A) + 1 # Minimum value seen so far, initialized to large number
    for i in range(1, N + 1):
        add_line(dp[i - 1], A[i - 1])
        tmp_mini = min(tmp_mini, A[i - 1])
        val = min(dp[j] * tmp_mini + A[j] for j in range(i)) # Brute-force calculation
        dp[i] = (val + tmp_mini - 1) // (tmp_mini)
    return dp[N]


while False:
    N = random.randint(2, 20)
    A = [random.randint(1, 100) for i in range(N)]
    exp = brute(N, A[::])
    res = solve(N, A[::])
    if exp != res:
        print("WA")
        print(N)
        print(A)
        print(exp, res)
        exit()
    else:
        print("AC", N, exp)
for _ in range(int(input())):
    N = int(input())
    A = li()
    print(solve(N, A))


# https://github.com/VaHiX/CodeForces/