# Contest 2128, Problem E1: Submedians (Easy Version)
# URL: https://codeforces.com/contest/2128/problem/E1

def possible(n, k, l, v):
    sommePref = [0]
    for i in range(len(l)):
        sommePref.append(sommePref[-1] + (1 if l[i] >= v else -1))
    deb = 0
    for i in range(k, len(l)+1):
        if sommePref[i-k] < sommePref[deb]:
            deb = i-k
        if sommePref[i]  >= sommePref[deb]:
            return [deb, i-1]
    return 0

tests = int(input())
for _ in range(tests):
    n, k = list(map(int, input().split()))
    l = list(map(int, input().split()))
    resu = 0
    intervalle = [0, 0]
    v = 2**20
    while v:
        if resu + v <= len(l) and possible(n, k, l, resu+v):
            resu+=v
        v = v//2
    res = possible(n, k, l, resu)
    print(resu, res[0] + 1, res[1] + 1)