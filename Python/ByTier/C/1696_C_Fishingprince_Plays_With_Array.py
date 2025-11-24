# Problem: CF 1696 C - Fishingprince Plays With Array
# https://codeforces.com/contest/1696/problem/C

import sys

I = sys.stdin.readline
L = list
M = lambda: map(int, I().split())


def solve(arr, N, m):
    # res will store pairs of (reduced_value, count_of_that_value)
    # reduced_value is the value after dividing by m until it's no longer divisible by m
    # count_of_that_value is how many times this reduced value appears in a group
    res = []
    for i in arr:
        t = i
        # Keep dividing by m while possible to get the reduced value
        while t % m == 0:
            t //= m
        # If result list is empty or the last reduced value is different,
        # add a new group
        if not res or res[-1][0] != t:
            res.append([t, i // t])
        else:
            # If the last reduced value is same, increment the count
            res[-1][1] += i // t
    return res


t = int(I())
for _ in range(t):
    n, m = M()
    a = L(M())
    k = int(I())
    b = L(M())
    # Compare the final reduced representations of both arrays
    print("Yes" if solve(a, n, m) == solve(b, k, m) else "No")


# https://github.com/VaHiX/CodeForces/