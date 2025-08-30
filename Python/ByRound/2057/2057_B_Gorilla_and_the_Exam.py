# Contest 2057, Problem B: Gorilla and the Exam
# URL: https://codeforces.com/contest/2057/problem/B

for t in range(int(input())):
    n, k = map(int, input().split())
    m = sorted(list(map(int, input().split())))
    p = [1]
    for i in range(1, n):
        if m[i] == m[i - 1]:
            p[-1] += 1
        else:
            p.append(1)
    p.sort()
    r = len(p)
    for i in range(len(p) - 1):
        if p[i] > k:
            break
        r -= 1
        k -= p[i]
    print(r)
