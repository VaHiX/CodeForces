# Contest 2056, Problem B: Find the Permutation
# URL: https://codeforces.com/contest/2056/problem/B

from sys import stdin

input = stdin.readline
for _ in range(int(input())):
    for i in range([int(input()), arr := []][0]):
        arr.insert(input()[:i].count("1"), i + 1)
    print(*arr)
