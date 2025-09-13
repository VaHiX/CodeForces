# Contest 2139, Problem C: Cake Assignment
# URL: https://codeforces.com/contest/2139/problem/C

q = int(input())
for _ in range(q):
    k, x = map(int, input().split())
    n = 2**k
    ans = []
    while x != n:
        if x > n:
            x = (x - n) * 2
            ans.append("2")
        else:
            x = 2 * x
            ans.append("1")
    ans.reverse()
    print(len(ans))
    print(" ".join(ans))
