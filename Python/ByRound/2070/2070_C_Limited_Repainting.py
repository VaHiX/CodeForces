# Contest 2070, Problem C: Limited Repainting
# URL: https://codeforces.com/contest/2070/problem/C

for _ in range(int(input())):
    n, k = map(int, input().split())
    s = input()
    a = [int(x) for x in input().split()]
    l = 0
    r = 10**9
    ans = 0
    while r >= l:
        m = (l + r) >> 1
        last = "R"
        cnt = 0
        for i in range(n):
            if a[i] > m:
                if s[i] == "B" and last != "B":
                    cnt += 1
                last = s[i]
        if cnt <= k:
            ans = m
            r = m - 1
        else:
            l = m + 1
    print(ans)
