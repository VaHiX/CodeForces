# Contest 2131, Problem B: Alternating Series
# URL: https://codeforces.com/contest/2131/problem/B

for _ in range(int(input())):
    n = int(input())
    if n % 2:
        print("-1 3 " * (n//2) + "-1")
    else:
        print("-1 3 " * (n//2 - 1) + "-1 2")
