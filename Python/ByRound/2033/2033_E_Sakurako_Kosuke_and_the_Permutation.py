# Contest 2033, Problem E: Sakurako, Kosuke, and the Permutation
# URL: https://codeforces.com/contest/2033/problem/E

t = int(input())
while t:
    t -= 1
    n = int(input())
    p = [0] + list(map(int, input().split()))
    us = [0] * (n + 1)
    re = 0
    for i in range(1, n + 1):
        if us[i] == 0:
            cu, le = i, 0
            while us[cu] == 0:
                le += 1
                us[cu] = 1
                cu = p[cu]
            re += (le - 1) // 2
    print(re)
