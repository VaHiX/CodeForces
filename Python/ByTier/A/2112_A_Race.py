# Contest 2112, Problem A: Race
# URL: https://codeforces.com/contest/2112/problem/A

for t in range(int(input())):
    a, x, y = map(int, input().split())
    print("YES" if (a < x) == (a < y) else "NO")
