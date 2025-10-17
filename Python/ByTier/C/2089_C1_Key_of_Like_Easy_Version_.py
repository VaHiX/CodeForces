# Contest 2089, Problem C1: Key of Like (Easy Version)
# URL: https://codeforces.com/contest/2089/problem/C1

MOD = 10**9 + 7

t = int(input())
for _ in range(t):
    n, l, k = map(int, input().split())

    # tot = ((l + 1) * (l + 2) - 2) * pow(4, -1, MOD)
    # tot %= MOD

    tot = l

    mov = [0] * n
    mov[0] = 1

    out = [0] * n

    for i in range(l, 0, -1):
        p = pow(i, -1, MOD)

        # 1 to i
        i %= n

        if i == 0:
            break

        nex = [0] * n
        for u in range(n):
            for j in range(1, i + 1):
                nex[u] += mov[u - j] * p
                nex[u] %= MOD
        mov = nex

        for i in range(n):
            out[i - 1] += mov[i]

        # print(mov, out)
    """
    eq = 1 - sum(mov)
    eq %= MOD
    eq *= pow(n, -1, MOD)
    eq %= MOD
    mov = [eq + v for v in mov]

    #print(mov)

    pref = [0]
    for v in mov[::-1]:
        pref.append((v + pref[-1]) % MOD)

    #print(pref)

    pref.pop() 
    pref.reverse()

    ex = tot - sum(pref)
    ex %= MOD
    ex *= pow(n, -1, MOD)
    ex %= MOD

    for i in range(n):
        pref[i] += ex

    print(pref)
    """

    for i in range(n):
        out[i] %= MOD

    ex = tot - sum(out)
    ex %= MOD
    ex *= pow(n, -1, MOD)
    ex %= MOD

    for i in range(n):
        out[i] += ex
        out[i] %= MOD

    print(" ".join(map(str, out)))
