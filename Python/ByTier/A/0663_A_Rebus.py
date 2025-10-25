# Contest 663, Problem A: Rebus
# URL: https://codeforces.com/contest/663/problem/A

c = input()
p = c.count("+") + 1
m = c.count("-")
c = c.split()
n = int(c[-1])

if p - m * n <= n and p * n - m >= n:
    print("Possible")
    s = n
    ismin = False
    for i in c:
        if i == "?":
            x = min(max(s + m - n * (p - 1), 1), n)
            if ismin:
                x = min(max(-s + -(m - 1) + n * p, 1), n)
                m -= 1
            else:
                p -= 1
            print(x, end=" ")
            s -= x - 2 * x * int(ismin)

            ismin = False
        else:
            if i == "-":
                ismin = True
            print(i, end=" ")

else:
    print("Impossible")

# ? * p - ? * m = 10
