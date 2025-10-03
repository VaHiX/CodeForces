# Contest 2056, Problem C: Palindromic Subsequences
# URL: https://codeforces.com/contest/2056/problem/C

for _ in range(int(input())):
    n = int(input())
    res = [1, 1, 2, 3] + [i for i in range(4, n - 2)] + [1, 2]
    print(*res)
