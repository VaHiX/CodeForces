# Contest 2132, Problem C1: The Cunning Seller (easy version)
# URL: https://codeforces.com/contest/2132/problem/C1

l = list()
t = int(input())
for i in range(t):
    n = int(input())
    c = 0
    s = 0
    while n > 0:
        a = int(n % 3)
        n = int(n / 3)
        s += a * (int(pow(3, c - 1) * (9 + c)))
        c += 1
    l.append(int(s))
for i in l:
    print(i)
