# Contest 1456, Problem A: Bouncing Ball
# URL: https://codeforces.com/contest/1456/problem/A

import sys

input = sys.stdin.buffer.readline


def process(S, p, k, x, y):
    n = len(S)
    """
    if R y moves:
    need p+R, p+R+k, ..., p+R+j*k
    
    to all be present
    how many are absent at each point?
    
    etc.
    """
    answer = float("inf")
    for s in range(k):
        """
        largest
        s+t*k <= n
        t*k <= n-s
        t = (n-s)//k
        """
        t = (n - s) // k
        missing = 0
        for t2 in range(t, -1, -1):
            i = s + t2 * k
            if i < p:
                break
            if S[i - 1] == "0":
                missing += 1
            x_cost = x * missing
            y_cost = y * (i - p)
            answer = min(answer, x_cost + y_cost)
    print(answer)


t = int(input())
for i in range(t):
    n, p, k = [int(x) for x in input().split()]
    S = input().decode().strip()
    x, y = [int(x) for x in input().split()]
    process(S, p, k, x, y)
