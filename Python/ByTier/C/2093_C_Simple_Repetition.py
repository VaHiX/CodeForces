# Contest 2093, Problem C: Simple Repetition
# URL: https://codeforces.com/contest/2093/problem/C

n = int(input())
while n != 0:
    n -= 1
    x, k = map(int, input().split())
    if k != 1 or x == 1:
        if k == 2 and x == 1:
            print("YES")
            continue
        print("NO")
        continue
    isPrime = True
    for i in range(2, int(x**0.5) + 1):
        if x % i == 0:
            isPrime = False
            break
    if isPrime:
        print("YES")
    else:
        print("NO")
