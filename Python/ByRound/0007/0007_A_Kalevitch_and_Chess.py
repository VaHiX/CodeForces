# Contest 7, Problem A: Kalevitch and Chess
# URL: https://codeforces.com/contest/7/problem/A

ans = 0
chars = ["W"] * 8
checked = False
for i in range(8):
    s = input()

    if s == "BBBBBBBB":
        ans += 1
    elif not checked:
        for char in s:
            if char == "B":
                ans += 1
        checked = True
print(ans)
