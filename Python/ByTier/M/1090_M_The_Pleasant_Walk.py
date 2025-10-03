# Contest 1090, Problem M: The Pleasant Walk
# URL: https://codeforces.com/contest/1090/problem/M

n, k = map(int, input().split())
a = list(map(int, input().split()))
b = [1] * n
j = 0
for i in range(1, n):
    if a[i] != a[i - 1]:
        b[j] += 1
    else:
        j += 1
b.sort(reverse=True)
ans = b[0]
print(ans)
