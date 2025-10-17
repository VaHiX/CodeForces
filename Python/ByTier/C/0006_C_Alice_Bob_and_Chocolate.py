# Contest 6, Problem C: Alice, Bob and Chocolate
# URL: https://codeforces.com/contest/6/problem/C

n = int(input())
arr = [int(x) for x in input().split(" ")]
l = 0
r = n - 1
ta = 0
tb = 0
while l <= r:
    if ta <= tb:
        ta += arr[l]
        l += 1
    else:
        tb += arr[r]
        r -= 1
print(l, n - l)
