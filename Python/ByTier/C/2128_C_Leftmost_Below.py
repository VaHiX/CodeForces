# Contest 2128, Problem C: Leftmost Below
# URL: https://codeforces.com/contest/2128/problem/C


def f(n, arr):
    min_prefix = arr[0]
    for val in arr:
        if val >= 2 * min_prefix:
            return False
        min_prefix = min(min_prefix, val)
    return True


t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    res = f(n, arr)
    if res:
        print("Yes")
    else:
        print("No")
