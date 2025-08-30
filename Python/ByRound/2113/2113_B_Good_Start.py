# Contest 2113, Problem B: Good Start
# URL: https://codeforces.com/contest/2113/problem/B

# klu2300080335
for _ in range(int(input())):
    w, h, a, b = map(int, input().split())
    x1, y1, x2, y2 = map(int, input().split())
    if ((x2 - x1) % a == 0 and x1 != x2) or ((y2 - y1) % b == 0 and y1 != y2):
        print("Yes")
    else:
        print("No")
