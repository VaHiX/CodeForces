# Problem: CF 947 A - Primal Sport
# https://codeforces.com/contest/947/problem/A

from math import sqrt as sq


def largestPrimeFactor(x):
    maximum = 1
    while x % 2 == 0:
        x = x >> 1
        maximum = 2
    for i in range(3, int(sq(x)) + 1, 2):
        while x % i == 0:
            x = x // i
            maximum = i
    if maximum == 1:
        return maximum
    return max(maximum, x)


X2 = int(input())
p1 = largestPrimeFactor(X2)
possibleX0 = float("inf")
for i in range(X2 - p1 + 1, X2):
    temp = largestPrimeFactor(i)
    if temp >= (i - (X2 - p1)) and ((i - (X2 - p1)) % temp != 0 or temp == 1):
        possibleX0 = min(possibleX0, i - temp + 1)
        if temp >= i // 2:
            break
print(possibleX0)


# https://github.com/VaHiX/CodeForces/