# Contest 1795, Problem A: Two Towers
# URL: https://codeforces.com/contest/1795/problem/A

for a in range(int(input())):
    l = input()
    s1 = input()
    s2 = input()[::-1]
    s = s1 + s2
    n = 0
    for i in range(len(s) - 1):
        if s[i] == s[i + 1]:
            n += 1
    if n < 2:
        print("YES")
    else:
        print("NO")
