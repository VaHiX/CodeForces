# Contest 1479, Problem A: Searching Local Minimum
# URL: https://codeforces.com/contest/1479/problem/A

n = int(input())
t = [0] * n
l, r = 0, n
while r - l > 1:
    m = (l + r) // 2
    print('?', m)
    x = int(input())
    print('?', m + 1)
    y = int(input())
    if x < y:
        r = m
    else:
        l = m
print('!', r)