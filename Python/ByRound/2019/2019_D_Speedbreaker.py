# Problem: CF 2019 D - Speedbreaker
# https://codeforces.com/contest/2019/problem/D

"""
D. Speedbreaker

Problem Description:
We have n cities in a row, each with a deadline a[i] by which it must be conquered.
At time 1, we choose a starting city and conquer it.
At each subsequent time t=2,3,...,n, we can only conquer a city adjacent to an already conquered city.
The goal is to count how many starting cities allow us to win - i.e., conquer all cities by their deadlines.

Algorithm:
- This problem uses a two-pointer technique combined with a greedy approach.
- For each possible starting city, we compute the maximum range of cities that can be conquered.
- The key idea is to determine for each position what is the furthest it can be conquered from the current starting point, using adjacency constraints.
- Time and Space Complexity:
  - Time: O(n) amortized over all test cases due to the two-pointer technique.
  - Space: O(1) extra space (excluding input storage).

"""

import sys


def rs():
    return sys.stdin.readline().rstrip()


def ri():
    return int(sys.stdin.readline())


def ria():
    return list(map(int, sys.stdin.readline().split()))


def ria1():
    return list(map(lambda x: int(x) - 1, sys.stdin.readline().split()))


def ria2d(n):
    return [list(map(int, sys.stdin.readline().split())) for _ in range(n)]


def rg(directed=False):
    n, m = ria()
    g = [[] for _ in range(n)]
    for _ in range(m):
        u, v = ria1()
        g[u].append(v)
        if not directed:
            g[v].append(u)
    return n, m, g


def ws(s):
    sys.stdout.write(s)
    sys.stdout.write("\n")


def wi(n):
    sys.stdout.write(str(n))
    sys.stdout.write("\n")


def wia(a, sep=" "):
    sys.stdout.write(sep.join([str(x) for x in a]))
    sys.stdout.write("\n")


def wia1(a, sep=" "):
    sys.stdout.write(sep.join([str(x + 1) for x in a]))
    sys.stdout.write("\n")


def solve(n, a):
    # Two pointers l, r to maintain the valid segment of cities we can conquer
    l = 0
    r = n - 1
    
    # Iterate from largest to smallest deadline (in reverse)
    for i in range(n, 0, -1):
        # Move left pointer while leftmost element exceeds current deadline
        while l < r and a[l] > i:
            l += 1
        # Move right pointer while rightmost element exceeds current deadline
        while l < r and a[r] > i:
            r -= 1
        # If segment length is sufficient to meet deadline, we can win
        if r - l >= i:
            return 0

    # Reset pointers
    l = 0
    r = n - 1
    
    # Greedy computation of valid range for each city
    for i, num in enumerate(a):
        # For city i, the earliest we can start is i - a[i] + 1
        l = max(l, i - num + 1)
        # For city i, the latest we can finish is i + a[i] - 1
        r = min(r, i + num - 1)
    
    # Return number of valid starting cities in range [l, r]
    return r - l + 1


def main():
    for _ in range(ri()):
        n = ri()
        a = ria()
        wi(solve(n, a))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/