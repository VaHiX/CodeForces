# Contest 1172, Problem A: Nauuo and Cards
# URL: https://codeforces.com/contest/1172/problem/A

n = int(input())
hand = list(map(int, input().split()))
deck = list(map(int, input().split()))
flg = True
if deck[-1] == 0:
    flg = False
if deck[-1] != 0:
    num = deck[-1]

    for i in range(num):
        if deck[-i - 1] != num - i:
            flg = False
    for i in range(n - num):
        if deck[i] != 0:
            if num + i + 2 > deck[i]:
                flg = False

    if flg:
        print(n - num)
if not flg:
    ans = n
    for i in range(n):
        if deck[i] != 0:
            ans = max(ans, i - deck[i] + n + 2)

    print(ans)
