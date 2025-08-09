# Contest 2130, Problem E2: Interactive RBS (Medium Version)
# URL: https://codeforces.com/contest/2130/problem/E2

def ask(s):
    print("?", len(s), *s, flush=True)
    return int(input())

def answer(s):
    print("!","".join(s), flush=True)

for _ in range(int(input())):
    n = int(input())
    s = [' ' for i in range(n+1)]
    if ask(list(range(1, n+1))) == 0:
        fq = 1
        fp = n
    else:
        l = 2 
        r = n
        ans = -1
        while l <= r:
            mid = (l + r)>>1
            if ask(list(range(1, mid+1))):
                ans = mid
                r = mid - 1
            else:
                l = mid + 1
        fq = ans
        fp = ans - 1
    for i in range(1, n+1, 8):
        idx = [min(j, n) for j in range(i, i+8)]
        q = []
        for j in range(7,-1, -1):
            q += [idx[7-j], fq, fq] * (1<<j)
        res = ask(q)
        for j in range(7, -1, -1):
            if res>>j & 1:
                s[idx[7-j]] = '('
            else:
                s[idx[7-j]] = ')'
    answer(s[1:])

    