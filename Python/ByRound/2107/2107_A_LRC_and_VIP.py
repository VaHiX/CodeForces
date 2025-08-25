# Contest 2107, Problem A: LRC and VIP
# URL: https://codeforces.com/contest/2107/problem/A

for _ in range(int(input())):
    a = int(input())
    b = list(map(int, input().split()))

    dp = [1] * a
    q = b.index(max(b))
    dp[q] = 2

    if len(set(b)) == 1:
        print("No")
    else:
        print("Yes")
        print(*dp)
