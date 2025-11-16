# Problem: CF 1791 G2 - Teleporters (Hard Version)
# https://codeforces.com/contest/1791/problem/G2

"""
Algorithm: Greedy with Prefix Sums and Binary Search
Time Complexity: O(n log n) due to sorting and binary search operations
Space Complexity: O(n) for storing prefix sums and auxiliary arrays

This problem involves finding the maximum number of teleporters that can be used given a limited number of coins.
The approach uses a greedy method combined with prefix sums and binary search.
For each teleporter, we calculate the minimum cost required to reach that teleporter and then use it to either teleport to 0 or n+1.
We sort these costs and use prefix sums to efficiently compute how many teleporters can be used within the coin limit.
"""

import sys
from bisect import bisect_right
from itertools import accumulate


def input():
    return sys.stdin.buffer.readline().rstrip(b"\r\n")


def dbp(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def a_str():
    return input().decode("ascii")


def get_int_list():
    return [int(x) for x in input().split()]


def minus_one():
    return [int(x) - 1 for x in input().split()]


def join_str(l, sep=" "):
    return sep.join([str(x) for x in l])


def do_thing():
    n, C = get_int_list()
    alist = get_int_list()

    def brute_farce():
        dbp("case:", n, C, "alist:", *alist)

        s0 = (0, C, frozenset(), tuple())
        q = [s0]
        seen = set()
        maxv = (float("-inf"), float("-inf"))
        best = None
        while q:
            x, coins, used, path = q.pop()
            rep = (x, coins, used)
            if rep in seen:
                continue
            seen.add(rep)
            if len(used) == n:
                dbp("used all:", path)
                return n
            for i in range(1, n + 1):
                if i in used:
                    continue
                cost = abs(x - i) + alist[i - 1]
                if cost <= coins:
                    newused = frozenset(used | set([i]))
                    frlr = "L" if x == 0 else "R"
                    q.append((0, coins - cost, newused, (*path, frlr + str(i))))
                    q.append((n + 1, coins - cost, newused, (*path, frlr + str(i))))
            v = (len(used), coins)
            if v == maxv:
                if path not in best:
                    best.append(path)
            elif v > maxv:
                maxv = v
                best = [path]
        dbp(best)
        return maxv[0]

    def stabstab():

        # Preprocessing: for each teleporter, calculate the minimum cost to use it
        # and also the cost to reach it from either 0 or n+1
        clist = [
            (min(a + i, n - i + 1 + a), a + i) for i, a in enumerate(alist, start=1)
        ]
        clist.sort(key=lambda x: x[0])  # Sort by minimum cost to use the teleporter
        pfx = [0] + list(accumulate([x[0] for x in clist]))  # Prefix sum array

        ans = 0
        for i in range(n):
            c = C - clist[i][1]  # Remaining coins after paying for the current teleporter

            # Binary search to find the maximum number of teleporters that can be used
            idx = bisect_right(pfx, c)

            # Adjust if necessary
            if idx >= i:
                idx = bisect_right(pfx, c + clist[i][0]) - 1

            ans = max(ans, idx)

        return ans

    r = stabstab()

    return r


if __name__ == "__main__":
    maxcc = 1
    maxcc = int(input())
    for cc in range(maxcc):
        print(do_thing())


# https://github.com/VaHiX/CodeForces/