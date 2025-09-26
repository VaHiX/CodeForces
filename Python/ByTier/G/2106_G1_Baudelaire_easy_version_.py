# Contest 2106, Problem G1: Baudelaire (easy version)
# URL: https://codeforces.com/contest/2106/problem/G1

import sys

input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    n = int(input())
    for _ in range(n - 1):
        _ = input()

    def solve():
        v = [0] * n
        print(f"? 1 1 1", flush=True)
        s = int(input())
        if abs(s) == 1:
            v[0] = s
            for i in range(1, n):
                print(f"? 1 1 {i+1}", flush=True)
                v[i] = int(input()) - v[0]
            return v
        if s ^ 0:
            v[0] = -s >> 1
            print(f"? 2 1", flush=True)
        for i in range(1, n):
            print(f"? 1 1 {i+1}", flush=True)
            v[i] = int(input())
        if v[0] == 0:
            print(f"? 2 1", flush=True)
            print(f"? 1 1 1", flush=True)
            v[0] = int(input()) >> 1
        return v

    v = " ".join(map(str, solve()))
    print(f"! {v}", flush=True)
