# Contest 1599, Problem A: Weights
# URL: https://codeforces.com/contest/1599/problem/A

import sys

# store inf in a variable called inf
inf = float("inf")


# change stdout buffer size
buffer = open(1, "w", 10**6)


# fast printing function
def print(*args, sep=" ", end="\n"):
    buffer.write(sep.join(str(arg) for arg in args) + end)


# flush stdout
def flush():
    buffer.flush()


# fast input
def input():
    return sys.stdin.readline()


# read a list of integers from stdin
def read_ints(index=None):
    return [int(x) for x in input().split()]


def read_ints_indexed(index):
    return [(int(x), i + index) for i, x in enumerate(input().split())]


def solve():
    n = int(input())
    a = read_ints()
    s = input()

    sides = ["L", "R"]
    a.sort()
    x = 0
    for i in range(n - 1):
        if s[i] != s[i + 1]:
            x += 1

    left = n - x - 1
    left_side = sides.index(s[0])
    right = n - x - 1
    right_side = sides.index(s[0])
    print(a[left], s[0])

    for i in range(1, n):
        if s[i] == s[i - 1]:
            left -= 1
            left_side ^= 1
            print(a[left], sides[left_side])
        else:
            right += 1
            right_side ^= 1
            print(a[right], sides[right_side])


if __name__ == "__main__":
    solve()
