# Contest 926, Problem A: 2-3-numbers
# URL: https://codeforces.com/contest/926/problem/A

x, y = map(int, input().split())
k = 0
for i in range(31):
    for j in range(20):
        if x <= 2**i * 3**j <= y:
            k += 1
print(k)
