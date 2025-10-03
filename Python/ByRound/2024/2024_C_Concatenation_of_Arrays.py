# Contest 2024, Problem C: Concatenation of Arrays
# URL: https://codeforces.com/contest/2024/problem/C

from sys import stdin
input = lambda: stdin.readline().rstrip()
for _ in range(int(input())):
    a = [input() for _ in range(int(input()))]
    print(*sorted(a, key=lambda x:sum(map(int, x.split()))))