# Contest 1268, Problem A: Long Beautiful Integer
# URL: https://codeforces.com/contest/1268/problem/A

n, k = map(int, input().split())
a = input()
ind = -1
if all(a[i] == a[i + k] for i in range(n - k)):
    print(n)
    print(a)
elif a[:k] * (n // k) + a[:k][: n % k] >= a:
    print(n)
    print(a[:k] * (n // k) + a[:k][: n % k])
else:
    mx = ["0"] * k
    for i in range(n):
        mx[i % k] = max(mx[i % k], a[i])
    for i in range(k):
        if a[i] != "9":
            ind = i
    if ind == -1:
        print(n)
        print("9" * n)
    else:
        print(n)
        t = a[:ind] + str(int(a[ind]) + 1) + "0" * (k - ind - 1)
        print(t * (n // k) + t[: n % k])
