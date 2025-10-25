# Contest 7, Problem E: Defining Macros
# URL: https://codeforces.com/contest/7/problem/E


def parse(s):
    i = 0
    while s[i] != "n":  # locate define
        i += 1
    i += 2
    while s[i] == " ":  # locate begin of name
        i += 1
    l = i
    while s[i] != " ":  # locate end of name
        i += 1
    return s[l:i], i  # exp can begin with space


def chk(s, i, map0):  # return valid flag, level, end index
    def nxt():  # i is always at the first index not visited
        nonlocal i
        while i < n and s[i] == " ":
            i += 1
        if i == n:
            return ")"  # when right parenthesis is found, chk function will return
        if s[i] in {"+", "-", "*", "/", "(", ")"}:  # find sign
            res = s[i]
            i += 1
        else:  # find number or parameter
            r = i + 1
            while r < n and s[r] not in {" ", "+", "-", "*", "/", "(", ")"}:
                r += 1
            res = s[i:r]
            i = r
        return res

    # parameter is complex; we can always get sign after a parameter, or ) if it is end of s
    def getP():  # return level of parameter got, 3 if it is not a macro
        nonlocal i, valid
        tmp = nxt()
        if tmp == "(":
            flag, level, i = chk(s, i, map0)
            valid &= flag
            return 3  # parenthesis as a whole always has the highest priority
        elif tmp in map0:  # found a macro
            valid &= map0[tmp][0]
            return map0[tmp][1]
        else:
            return 3

    valid = True
    n = len(s)
    ll = getP()  # last level
    res = ll  # minimum level to return
    while True:
        sign = nxt()
        if sign == ")":
            return valid, res, i
        if ll < pl[sign]:
            valid = False
        ll = getP()
        if ll < pr[sign]:
            valid = False
        res = min(res, pl[sign])


n = int(input())
map0 = {}  # {name: [flag, level]}; 1: + safe; 2: +-* salfe; 3: all safe
pr = {"+": 1, "-": 2, "*": 2, "/": 3}  # minimum valid level of a parameter after sign
pl = {"+": 1, "-": 1, "*": 2, "/": 2}  # minimum valid level of a parameter before sign
for _ in range(n):
    s = input()
    name, begin = parse(s)
    map0[name] = chk(s, begin, map0)[:2]
print("OK" if chk(input(), 0, map0)[0] else "Suspicious")
