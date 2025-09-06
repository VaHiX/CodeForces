# Contest 21, Problem A: Jabber ID
# URL: https://codeforces.com/contest/21/problem/A

s = input().split("@")
if len(s) != 2:
    print("NO")
    exit()

s[1] = s[1].split("/")
if len(s[1]) > 2:
    print("NO")
    exit()


def check1(s):
    if not s or len(s) > 16:
        return False
    for c in s:
        if not c.isalnum() and c != "_":
            return False
    return True


def check2(s):
    s = s.split(".")
    if not s or len(s) > 32:
        return False
    for s in s:
        if not check1(s):
            return False
    return True


ok = check1(s[0]) and check2(s[1][0])
if len(s[1]) == 2:
    ok = ok and check1(s[1][1])
print("YES" if ok else "NO")
