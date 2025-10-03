# Contest 2029, Problem B: Replacement
# URL: https://codeforces.com/contest/2029/problem/B

for t in range(int(input())):
    n = int(input())
    s = input()
    r = input()
    d = s.count("1")
    e = n - d
    for i in range(0, n - 2, 1):
        if r[i] == "1":
            e -= 1
        else:
            d -= 1
    if d == 1 and e == 1:
        print("YES")
    else:
        print("NO")
