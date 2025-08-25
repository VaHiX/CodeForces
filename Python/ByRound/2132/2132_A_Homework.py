# Contest 2132, Problem A: Homework
# URL: https://codeforces.com/contest/2132/problem/A

for _ in range(int(input())):
    n = int(input())
    s = input()
    a = int(input())
    t = input()
    u = input()
    for i in range(len(t)):
        if u[i] == "D":
            s = s + t[i]
        else:
            s = t[i] + s
    print(s)
