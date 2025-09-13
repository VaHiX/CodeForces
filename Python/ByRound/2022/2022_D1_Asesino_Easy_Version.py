# Contest 2022, Problem D1: Asesino (Easy Version)
# URL: https://codeforces.com/contest/2022/problem/D1

# https://codeforces.com/contest/2022

import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!


def ask(i, j):
    print(f"? {i} {j}", flush=True)
    reply = int(input())
    if reply == -1:
        exit()
    return reply


def answer(i):
    print(f"! {i}", flush=True)


def solve_case():
    n = int(input())

    for i in range(1, n, 2):
        a = ask(i, i + 1)
        b = ask(i + 1, i)
        if a != b:
            j = n if i == 1 else 1
            a = ask(i, j)
            b = ask(j, i)
            if a != b:
                answer(i)
            else:
                answer(i + 1)
            return

    answer(n)


for _ in range(int(input())):
    solve_case()