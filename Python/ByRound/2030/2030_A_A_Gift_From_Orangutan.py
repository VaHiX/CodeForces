# Contest 2030, Problem A: A Gift From Orangutan
# URL: https://codeforces.com/contest/2030/problem/A

for t in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print((n - 1) * (max(a) - min(a)))
