# Contest 1995, Problem C: Squaring
# URL: https://codeforces.com/contest/1995/problem/C

for _ in range(int(input())):
    n = int(input())
    p = 1
    ans = 0
    c = 0
    for i in map(int, input().split()):
        while p < i and c:
            p *= p
            c -= 1
        if i == 1 and i < p:
            ans = -1
            break
        a = i
        while a < p:
            a *= a
            c += 1
        p = i
        ans += c
    print(ans)
