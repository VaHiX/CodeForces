# Contest 1063, Problem C: Dwarves, Hats and Extrasensory Abilities
# URL: https://codeforces.com/contest/1063/problem/C


def solv(n):
    l = 0
    r = int(1e9)
    print(r, 1)
    rc = input()  # right color
    lc = "white" if rc == "black" else "black"
    for i in range(1, n):
        m = (l + r) // 2
        print(m, 1)
        mc = input()
        if mc == lc:
            l = m
        else:
            r = m
    print(l, 0, r, 2)


n = int(input())
solv(n)
