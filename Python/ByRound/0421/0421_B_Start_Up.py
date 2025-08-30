# Contest 421, Problem B: Start Up
# URL: https://codeforces.com/contest/421/problem/B


# https://codeforces.com/contest/421/problem/B
# 1000
def palin(n, k):
    for i in range(k // 2):
        if n[i] != n[k - i - 1]:
            return False
    return True


s = input()
l = ["A", "H", "W", "I", "M", "Y", "X", "O", "T", "U", "V"]
if palin(s, len(s)):
    for i in s:
        if i not in l:
            print("NO")
            exit()
    print("YES")
else:
    print("NO")
