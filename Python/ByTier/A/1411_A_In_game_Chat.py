# Contest 1411, Problem A: In-game Chat
# URL: https://codeforces.com/contest/1411/problem/A

for _ in range(int(input())):
    n = int(input())
    s = input().rstrip(')')
    ans = n - len(s) > len(s)
    print("Yes" if ans else "No")