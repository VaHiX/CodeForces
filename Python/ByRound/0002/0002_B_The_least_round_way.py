# Contest 2, Problem B: The least round way
# URL: https://codeforces.com/contest/2/problem/B


def dp(arr, n):
    for i in range(1, n):
        arr[0][i] += arr[0][i - 1]
        arr[i][0] += arr[i - 1][0]
    for i in range(1, n):
        for j in range(1, n):
            arr[i][j] += min(arr[i][j - 1], arr[i - 1][j])


n = int(input())
arr = [list(map(int, input().split())) for i in range(n)]
two = [[0] * n for i in range(n)]
five = [[0] * n for i in range(n)]
zero = None
for i in range(n):
    for j in range(n):
        x = arr[i][j]
        if x == 0:
            zero = (i, j)
            two[i][j] = 1
            five[i][j] = 1
        else:
            cnt = 0
            while x % 2 == 0:
                x //= 2
                cnt += 1
            two[i][j] = cnt
            cnt = 0
            while x % 5 == 0:
                x //= 5
                cnt += 1
            five[i][j] = cnt
dp(two, n)
dp(five, n)
x = two[n - 1][n - 1]
y = five[n - 1][n - 1]
z = min(x, y)
if x < y:
    omg = two
else:
    omg = five
if z > 1 and zero != None:
    z = 1
    i = zero[0]
    j = zero[1]
    ans = "D" * i + "R" * j + "D" * (n - i - 1) + "R" * (n - j - 1)
else:
    i = n - 1
    j = n - 1
    ans = ""
    while i != 0 and j != 0:
        if omg[i - 1][j] <= omg[i][j - 1]:
            i -= 1
            ans = "D" + ans
        else:
            j -= 1
            ans = "R" + ans
    if i == 0:
        ans = "R" * j + ans
    else:
        ans = "D" * i + ans
print(z)
print(ans)
