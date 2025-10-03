# Contest 2032, Problem C: Trinity
# URL: https://codeforces.com/contest/2032/problem/C

from sys import stdin

input = lambda: stdin.readline().rstrip()
for test in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()
    i = 0
    for j in range(n):
        if a[i] + a[i + 1] <= a[j]:
            i += 1
    print(i)
