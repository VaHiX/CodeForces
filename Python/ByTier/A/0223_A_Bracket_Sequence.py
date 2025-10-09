# Contest 223, Problem A: Bracket Sequence
# URL: https://codeforces.com/contest/223/problem/A

s = input()
n = len(s)
st = []
mt = [0] * n

for i in range(n):
    if s[i] == "(" or s[i] == "[":
        st.append(i)
    elif s[i] == ")":
        if st and s[st[-1]] == "(":
            mt[i] = mt[st[-1]] = 1
            st.pop()
        else:
            st.clear()
    elif s[i] == "]":
        if st and s[st[-1]] == "[":
            mt[i] = mt[st[-1]] = 1
            st.pop()
        else:
            st.clear()

mx = 0
l0 = r0 = 0
i = 0

while i < n:
    if mt[i]:
        j = i
        while j < n and mt[j]:
            j += 1

        ct = s[i:j].count("[")
        if ct > mx:
            mx = ct
            l0, r0 = i, j
        i = j
    else:
        i += 1

print(mx)
print(s[l0:r0])
