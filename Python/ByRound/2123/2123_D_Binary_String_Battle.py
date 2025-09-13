# Contest 2123, Problem D: Binary String Battle
# URL: https://codeforces.com/contest/2123/problem/D

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    s = input()
    if s.count("1") <= k or k > n // 2:
        print("Alice")
    else:
        print("Bob")
