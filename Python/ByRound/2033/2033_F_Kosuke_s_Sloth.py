# Contest 2033, Problem F: Kosuke's Sloth
# URL: https://codeforces.com/contest/2033/problem/F

for _ in range(int(input())):
    n, k = map(int, input().split(" "))
    a, b, c = 0, 1 % k, 1
    while b:
        a, b = b, (a + b) % k
        c += 1
    print((c * n) % (10**9 + 7))
