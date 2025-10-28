# Problem: CF 2005 B2 - The Strict Teacher (Hard Version)
# https://codeforces.com/contest/2005/problem/B2

"""
B2. The Strict Teacher (Hard Version)

Algorithms/Techniques: Binary search, optimal game strategy, greedy approach

Time Complexity: O(m * log(m) + q * log(m)) per test case
Space Complexity: O(m + q) per test case

The problem models a game between David and teachers on a line. David tries to maximize the number of moves until caught,
while teachers try to minimize it. The optimal strategy is determined by finding the closest teacher to David's position.
For each query, we compute the minimal time for the nearest teacher to catch David, which equals the distance from David to
the nearest teacher, divided by 2 (since both move toward each other optimally).

We preprocess the teacher positions by sorting them. For a given David position x:
- If x is to the left of all teachers, answer = x - 1
- If x is to the right of all teachers, answer = n - x
- Else, find the two closest teachers and return (right - left) // 2
"""

from sys import stdin

input = stdin.readline
import bisect

t = int(input())
for _ in range(t):
    n, m, q = map(int, input().split())
    b = list(map(int, input().split()))
    a = list(map(int, input().split()))
    b = sorted(b)  # Sort teacher positions for binary search
    for x in a:
        t = bisect.bisect_left(b, x)  # Find insertion point of x in sorted b
        if t == 0:
            # David is to the left of all teachers; distance to leftmost teacher
            print(b[0] - 1)
        elif t == m:
            # David is to the right of all teachers; distance to rightmost teacher
            print(n - b[-1])
        else:
            # David is between two teachers; compute optimal catch time
            print((b[t] - b[t - 1]) // 2)


# https://github.com/VaHiX/codeForces/