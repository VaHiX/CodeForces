# Contest 2132, Problem B: The Secret Number
# URL: https://codeforces.com/contest/2132/problem/B

T = int(input())
for _ in range(T):
    n = int(input())
    a = []
    for d in range(20, 0, -1):
        z = 10**d + 1
        if n % z == 0:
            a.append(n // z)
    print(len(a))
    if len(a) > 0:
        print(" ".join(map(str, a)))
