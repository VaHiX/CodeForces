# Contest 2028, Problem A: Alice's Adventures in ''Chess''
# URL: https://codeforces.com/contest/2028/problem/A

t = int(input())
for i in range(t):
    n, a, b = map(int, input().split())
    s = input()
    s += s
    s += s
    s += s
    s += s
    for c in s:
        if c == "N":
            b -= 1
        elif c == "S":
            b += 1
        elif c == "E":
            a -= 1
        else:
            a += 1
        if not (a or b):
            print("YES")
            break
    else:
        print("NO")
