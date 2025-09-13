# Contest 1903, Problem A: Halloumi Boxes
# URL: https://codeforces.com/contest/1903/problem/A

_t = int(input())
for _ in range(_t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    print("YES" if k > 1 or a == list(sorted(a)) else "NO")
