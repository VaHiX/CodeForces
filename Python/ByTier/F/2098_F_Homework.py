# Contest 2098, Problem F: Homework
# URL: https://codeforces.com/contest/2098/problem/F

import sys

input = sys.stdin.readline


def gaussian_rank(rows):

    basis = {}
    for v in rows:
        x = v
        while x:
            p = x.bit_length() - 1
            if p in basis:
                x ^= basis[p]
            else:
                basis[p] = x
                break
    return basis


def can_tr(s, t):
    n = len(s)
    g = n & -n
    r = n // g

    rows_s = [int(s[i * r : (i + 1) * r], 2) if r else 0 for i in range(g)]
    rows_t = [int(t[i * r : (i + 1) * r], 2) if r else 0 for i in range(g)]

    bs = gaussian_rank(rows_s)
    bt = gaussian_rank(rows_t)
    if len(bs) != len(bt):
        return False
    for v in bt.values():
        x = v
        while x:
            p = x.bit_length() - 1
            if p in bs:
                x ^= bs[p]
            else:
                return False
    return True


def solve():
    t = int(input())
    answer = []
    for _ in range(t):
        n = int(input())
        s = input().strip()
        t_str = input().strip()
        answer.append("Yes" if can_tr(s, t_str) else "No")
    sys.stdout.write("\n".join(answer))


if __name__ == "__main__":
    solve()
