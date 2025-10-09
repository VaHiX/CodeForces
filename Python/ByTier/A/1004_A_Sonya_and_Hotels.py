# Contest 1004, Problem A: Sonya and Hotels
# URL: https://codeforces.com/contest/1004/problem/A

n, b = map(int, input().split())
lst = [*map(int, input().split())]
sum = 2
for x in range(n - 1):
    d = lst[x + 1] - lst[x]
    if d == 2 * b:
        sum += 1
    elif d > 2 * b:
        sum += 2
print(sum)
