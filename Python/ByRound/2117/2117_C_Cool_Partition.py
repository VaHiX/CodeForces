# Contest 2117, Problem C: Cool Partition
# URL: https://codeforces.com/contest/2117/problem/C

for _ in range(int(input())):
    n, a = int(input()), list(input().split())
    r, l = set(), set()
    cnt = 0
    for _ in a:
        r.add(_)
        l.add(_)
        if len(r) == len(l):
            cnt += 1
            r.clear()
    print(cnt)
