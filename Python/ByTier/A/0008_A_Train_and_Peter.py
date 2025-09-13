# Contest 8, Problem A: Train and Peter
# URL: https://codeforces.com/contest/8/problem/A

s = input()
a = input()
b = input()
l = []
if (a in s) and (b in s[s.index(a) + len(a) :]):
    l.append("forward")
s = s[::-1]
if (a in s) and (b in s[s.index(a) + len(a) :]):
    l.append("backward")
if len(l) == 0:
    print("fantasy")
elif len(l) == 1:
    print(l[0])
else:
    print("both")
