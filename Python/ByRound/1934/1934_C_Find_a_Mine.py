# Problem: CF 1934 C - Find a Mine
# https://codeforces.com/contest/1934/problem/C

"""
Interactive problem to find the location of one mine in a grid.
The approach uses a series of strategic queries to narrow down the possible locations of mines.

Algorithm:
- First query is at (1, 1) to get distance to nearest mine.
- Based on the result, we strategically choose next queries to narrow down the search space.
- We use the Manhattan distance properties to deduce mine positions.
- The solution uses at most 4 queries to identify one mine.

Time Complexity: O(1) - fixed number of queries (4)
Space Complexity: O(1) - only using a constant amount of extra space
"""

from sys import stdin, stdout

input = lambda: stdin.readline().rstrip()
print = lambda *x, sep=" ", end="\n": stdout.write(sep.join(map(str, x)) + end)


def out(x, y):
    print("!", x, y)
    stdout.flush()


def yes():
    print("Yes")


def no():
    print("No")


def alice():
    print("Alice")


def bob():
    print("Bob")


def ask(x, y):
    print("?", x, y)
    stdout.flush()
    d = int(input())
    return d


def solve():
    n, m = map(int, input().split())
    d1 = ask(1, 1)  # Query first corner
    if not d1:
        out(1, 1)  # If distance is 0, we found a mine
        return
    # Calculate second query position based on first result
    d2 = ask(min(d1 + 1, n), 2 + d1 - min(d1 + 1, n))
    if not d2:
        out(min(d1 + 1, n), 2 + d1 - min(d1 + 1, n))
        return
    # Based on parity of d2, choose different third query strategy
    if d2 % 2:
        # Odd case: query along the diagonal
        d3 = ask(2 + d1 - min(d1 + 1, m), min(d1 + 1, m))
        # Deduce position based on results
        out(2 + d1 - min(d1 + 1, m) + d3 // 2, min(d1 + 1, m) - d3 // 2)
    else:
        # Even case: query along another diagonal
        d3 = ask(min(d1 + 1, n) - d2 // 2, 2 + d1 - min(d1 + 1, n) + d2 // 2)
        if not d3:
            out(min(d1 + 1, n) - d2 // 2, 2 + d1 - min(d1 + 1, n) + d2 // 2)
            return
        # Final query to determine exact position
        d4 = ask(2 + d1 - min(d1 + 1, m), min(d1 + 1, m))
        out(2 + d1 - min(d1 + 1, m) + d4 // 2, min(d1 + 1, m) - d4 // 2)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/