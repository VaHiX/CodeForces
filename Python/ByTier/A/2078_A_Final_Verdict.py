# Contest 2078, Problem A: Final Verdict
# URL: https://codeforces.com/contest/2078/problem/A

for _ in range(int(input())):
    a, b = map(int, input().split())
    c = sum(map(int, input().split())) / a
    print("YES" if c == b else "NO")
