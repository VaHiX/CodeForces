# Contest 2033, Problem D: Kousuke's Assignment
# URL: https://codeforces.com/contest/2033/problem/D

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    s = 0
    st = {0}
    c = 0
    for x in a:
        s += x
        if s in st:
            c += 1
            st = {0}
            s = 0
        st.add(s)
    print(c)
