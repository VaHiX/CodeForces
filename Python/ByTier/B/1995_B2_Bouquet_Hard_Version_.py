# Contest 1995, Problem B2: Bouquet (Hard Version)
# URL: https://codeforces.com/contest/1995/problem/B2

for _ in range(int(input())):
    n, m = map(int, input().split())
    cnt = {t: v for t, v in zip(map(int, input().split()), map(int, input().split()))}

    mx = 0
    for t, v in cnt.items():
        w = cnt.get(t + 1, 0)
        countA = min(m // t, v)
        a = t * countA

        diff = m - a
        countB = min(diff // (t + 1), w)
        b = (t + 1) * countB

        mx = max(mx, a + b + min((m - a - b), w - countB, countA))

    print(mx)
