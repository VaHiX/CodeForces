# Contest 2135, Problem B: For the Champion
# URL: https://codeforces.com/contest/2135/problem/B

import sys; input = sys.stdin.readline

for _ in range(int(input())):
    n, k = int(input()), 10**9; u = v = -float('inf')
    for i in range(n): i, j = map(int, input().split()); u = max(u, i + j); v = max(v, i - j)
    print(f"? U {k}", flush=True); input(); print(f"? U {k}", flush=True); input(); print(f"? R {k}", flush=True); input(); print(f"? R {k}", flush=True); b = int(input())
    print(f"? D {k}", flush=True); input(); print(f"? D {k}", flush=True); input(); print(f"? D {k}", flush=True); input(); print(f"? D {k}", flush=True); c = int(input())
    p = b - 4 * k + u; q = c - 4 * k + v; x = (p + q) // 2; y = (p - q) // 2; print(f"! {x} {y}", flush=True)