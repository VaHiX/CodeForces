# Contest 2031, Problem F: Penchick and Even Medians
# URL: https://codeforces.com/contest/2031/problem/F

from random import shuffle


def query(s):
    print("?", str(len(s)), *s)
    m1, m2 = map(int, input().split())
    return (m1, m2)


"""
def query(s):
    #print("?",*s)
    global secret
    qs=sorted([secret[int(i)-1] for i in s])
    #print(qs[len(s)//2-1],qs[len(s)//2])
    return (qs[len(s)//2-1],qs[len(s)//2])"""
for _ in range(int(input())):
    n = int(input())
    cbl = []
    cbr = []
    split = []
    u = None
    cr = None
    cl = None
    for i in range(1, n, 2):
        ms = query(list(range(1, i)) + list(range(i + 2, n + 1)))
        if ms == (n // 2, n // 2 + 1):
            split.append((i, i + 1))
        elif ms == (n // 2 - 1, n // 2):
            cbr.append((i, i + 1))
        elif ms == (n // 2 + 1, n // 2 + 2):
            cbl.append((i, i + 1))
        elif ms == (n // 2 - 1, n // 2 + 2):
            u = (i, i + 1)
            break
        elif ms == (n // 2, n // 2 + 2):
            cr = (i, i + 1)
        elif ms == (n // 2 - 1, n // 2 + 1):
            cl = (i, i + 1)
        else:
            assert False
    if u != None:
        print("!", u[0], u[1])
        continue
    for i in range(len(cbl)):
        ms = query(cbl[i] + cbr[i])
        if n // 2 in ms:
            cl = cbl[i]
        if n // 2 + 1 in ms:
            cr = cbr[i]
    pl = 0
    pr = 0
    if len(split) > 0:
        ms = query((cr[1], cl[1]) + split[0])
        if n // 2 in ms:
            pl = 1
        if n // 2 + 1 in ms:
            pr = 1
    else:
        ol = [cbl[i] for i in range(len(cbl)) if cbl[i] != cl]
        ncr = [cbr[i] for i in range(len(cbr)) if cbr[i] != cr]
        if len(ol) > 0 and len(ncr) > 0:
            ms = query((cr[1], cl[1]) + (ol[0][0], ncr[0][0]))
            if n // 2 in ms:
                pl = 1
            if n // 2 + 1 in ms:
                pr = 1
        else:
            # must be 6 elmts, sorta hard coded
            if len(ol) > 0:
                ml = query((cl[1], ol[0][0]) + cr)
                if n // 2 in ml:
                    pl = 1
                mr = query((cr[1], ol[0][0]) + cl)
                if n // 2 + 1 in mr:
                    pr = 1
            if len(ncr) > 0:
                mr = query((cr[1], ncr[0][0]) + cl)
                if n // 2 + 1 in mr:
                    pr = 1
                ml = query((cl[1], ncr[0][0]) + cr)
                if n // 2 in ml:
                    pl = 1
    print("!", cl[pl], cr[pr])
