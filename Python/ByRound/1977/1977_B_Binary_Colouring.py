# Problem: CF 1977 B - Binary Colouring
# https://codeforces.com/contest/1977/problem/B

"""
Binary Colouring

Algorithm:
The problem asks us to represent a given integer x as a sum of powers of 2 with coefficients from {-1, 0, 1}, such that no two consecutive coefficients are non-zero.

Approach:
We use a greedy method:
1. For each bit of x, if it's 0, we set the coefficient to 0.
2. If it's 1, we determine whether to use +1 or -1 based on the next bit:
   - If (x - 1) // 2 is even, we use +1 and subtract 1 from x.
   - Otherwise, we use -1 and add 1 to x.
3. Then we divide x by 2 and repeat until x is 0.

Time Complexity: O(log x) - We iterate through each bit of x.
Space Complexity: O(log x) - For storing the result array.
"""

MULTI_TEST = True
PRINT_RETURN_VALUES = True


def solve():
    x = int(input())

    res = []
    while x:
        if x % 2 == 0:
            res.append(0)
        else:
            if ((x - 1) // 2) % 2 == 0:
                res.append(1)
                x -= 1
            else:
                res.append(-1)
                x += 1

        x //= 2

    return f"{len (res )}\n" + " ".join(map(str, res))


def _solve2():
    x = int(input())
    xc = x
    xseq = []
    while xc:
        xseq.append(xc % 2)
        xc //= 2

    n = len(xseq)
    res = [0] * (n + 1)
    for i in range(n):
        if xseq[i] == 1:
            if res[i] == 1:
                res[i] = 0
                res[i + 1] = 1
            elif i > 0 and res[i - 1] == 1:
                res[i - 1] = -1
                res[i + 1] = 1
            else:
                res[i] = 1

    return f"{len (res )}\n" + " ".join(map(str, res))


def main():
    t = int(input()) if MULTI_TEST else 1
    if PRINT_RETURN_VALUES:
        output = []
        for _ in range(t):
            ans = solve()
            output.append(ans)

        print_lines(output)
    else:
        for _ in range(t):
            solve()


def read_ints():
    return [int(c) for c in input().split()]


def print_lines(seq):
    print("\n".join(map(str, seq)))


def traceback_handler(_exception_type, _value, t):
    import os
    import traceback

    exc = traceback.TracebackException(_exception_type, _value, t)

    for frame_summary in exc.stack:
        frame_summary.filename = os.path.relpath(frame_summary.filename)

    print("".join(exc.format()))


if __name__ == "__main__":
    import sys
    from os import environ as env

    sys.excepthook = traceback_handler
    if "COMPUTERNAME" in env and "L2A6HRI" in env["COMPUTERNAME"]:
        sys.stdout = open("out.txt", "w")
        sys.stdin = open("in.txt", "r")

    def input():
        return sys.stdin.readline().rstrip()

    main()


def read_ints():
    return [int(c) for c in input().split()]


def print_lines(lst):
    print("\n".join(map(str, lst)))


# https://github.com/VaHiX/CodeForces/