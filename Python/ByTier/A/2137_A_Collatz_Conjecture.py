# Contest 2137, Problem A: Collatz Conjecture
# URL: https://codeforces.com/contest/2137/problem/A

for _ in range(int(input())):
    k, x = map(int, input().split())
    print(x * 2**k)
