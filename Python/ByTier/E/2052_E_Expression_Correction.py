# Contest 2052, Problem E: Expression Correction
# URL: https://codeforces.com/contest/2052/problem/E


def eval(s):
    if len(s) == 0 or s[0] == "+" or s[-1] == "+" or s[0] == "-" or s[-1] == "-":
        return False, 0
    d = [""]
    op = [1]
    for c in s:
        if c == "+":
            op.append(1)
            d.append("")
        elif c == "-":
            op.append(-1)
            d.append("")
        else:
            d[-1] += c
    sm = 0
    for i in range(len(d)):
        if d[i] == "" or len(d[i]) > 10:
            return False, 0
        if d[i][0] == "0" and len(d[i]) > 1:
            return False, 0
        sm += int(d[i]) * op[i]
    return True, sm


def test(s):
    l, r = s.split("=")
    pl, nl = eval(l)
    pr, nr = eval(r)
    return pl and pr and nl == nr


s = input()
if test(s):
    print("Correct")
else:
    for i in range(len(s)):
        if s[i] != "+" and s[i] != "-":
            t = s[:i] + s[i + 1 :]
            for j in range(len(s)):
                q = t[:j] + s[i] + t[j:]
                if test(q):
                    print(q)
                    exit()
    print("Impossible")
