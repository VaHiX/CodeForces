# Problem: CF 1952 A - Are You a Robot, Again?
# https://codeforces.com/contest/1952/problem/A

"""
Problem: A. Are You a Robot, Again?
Algorithm: Simulation
Time Complexity: O(1)
Space Complexity: O(1)

This problem appears to be a simple simulation where we just need to print "safety"
and return. The solution doesn't require any complex algorithms or data structures,
just a basic output operation.
"""

import sys


def li():
    # Read line and convert to list of integers
    return list(map(int, sys.stdin.readline().strip().split()))


def intp():
    # Read line and convert to integer
    return int(sys.stdin.readline().strip())


def string():
    # Read line and return as string
    return sys.stdin.readline().strip()


def fast_io():
    # Redirect stdin and stdout for faster I/O
    sys.stdin = open(0)
    sys.stdout = open(1, "w")


def solve():
    # Simple solution that just prints "safety"
    print("safety")
    return


if __name__ == "__main__":
    # Enable fast I/O
    fast_io()
    # Call the solve function
    solve()


# https://github.com/VaHiX/CodeForces/