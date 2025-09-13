# Contest 2117, Problem A: False Alarm
# URL: https://codeforces.com/contest/2117/problem/A

for _ in range(int(input())):
    n, x = map(int, input().split())
    a = input().split()
    print("YES" if n - a[::-1].index("1") - a.index("1") <= x else "NO")
