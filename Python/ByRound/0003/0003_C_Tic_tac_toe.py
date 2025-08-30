# Contest 3, Problem C: Tic-tac-toe
# URL: https://codeforces.com/contest/3/problem/C

a, b, c = input(), input(), input()
players = ["first", "second"]
nx = (a + b + c).count("X")
no = (a + b + c).count("0")
d = nx - no
s = [a, b, c, a[0] + b[1] + c[2], a[2] + b[1] + c[0]] + list(map("".join, zip(a, b, c)))
w = ("XXX" in s) + 2 * ("000" in s) - 1
if (d not in (0, 1)) or w > 1 or d == w:
    print("illegal")
elif w >= 0:
    print("the " + players[w] + " player won")
elif nx + no == 9:
    print("draw")
else:
    print(players[d])
