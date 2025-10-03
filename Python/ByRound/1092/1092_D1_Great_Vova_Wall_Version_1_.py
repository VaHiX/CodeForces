# Contest 1092, Problem D1: Great Vova Wall (Version 1)
# URL: https://codeforces.com/contest/1092/problem/D1

n = eval(input())
l = [int(x) & 1 for x in input().split()]
st = []
st.append(l[0])
for i in range(1, n):
    if len(st) and st[-1] == l[i]:
        st.pop()

    else:
        st.append(l[i])
# print(len(st))
if len(st) >= 2:
    print("NO")
else:
    print("YES")
