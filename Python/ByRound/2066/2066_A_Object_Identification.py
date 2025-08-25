# Contest 2066, Problem A: Object Identification
# URL: https://codeforces.com/contest/2066/problem/A


import sys


def solve():
    n = int(input())

    arr = list(map(int, input().split()))

    visited = [False] * (n + 1)

    for i in arr:
        visited[i] = True

    for i in range(1, n + 1):
        if not visited[i]:
            print(f"? {i} {arr[0]}")
            sys.stdout.flush()
            dist = int(input())

            if dist == 0:
                print("! A")

            else:
                print("! B")
            return

    # It is a permutation
    a = arr.index(1) + 1
    b = arr.index(n) + 1
    print(f"? {a} {b}")
    sys.stdout.flush()
    first = int(input())

    print(f"? {b} {a}")
    sys.stdout.flush()
    second = int(input())

    if first != second:
        print("! A")
        return

    if first < n - 1:
        print("! A")
        return

    print("! B")


for _ in range(int(input())):
    solve()
