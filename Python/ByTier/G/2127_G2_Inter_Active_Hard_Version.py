# Contest 2127, Problem G2: Inter Active (Hard Version)
# URL: https://codeforces.com/contest/2127/problem/G2

import random
from math import log2
import sys

def query(q):
    global qc
    qc += 1
    
    assert len(q) == n
    if dbg:
        out = 0
        for i in range(n):
            if i == k:
                continue
            if q.index(p[q[i]]) > i:
                out += 1
                
        return out
    else:
        print('?', ' '.join(str(v + 1) for v in q))
        sys.stdout.flush()
        return int(input())

    

dbg = 0

t = int(input())
for _ in range(t):
    qc = 0
    
    if dbg:
        n = random.randint(4, 5)
        p = list(range(n))

        while any(p[i] == i for i in range(n)):
            random.shuffle(p)

        '''
        if n % 2 == 0:
            p = list(range(n))[::-1]
        '''
    else:
        n = int(input())

    k = (n - 1) // 2
    if dbg == 0:
        print(k + 1)

    kn = [-1] * n

    fail = []
    while 1:
        need = kn.count(-1)
        
        if need == 0 or qc + need * (log2(need) + 2.5) >= 10 * n:
            # print(qc, need)
            break

        '''
        if dbg:
            ctt = sum(p[p[i]] == i for i in range(n))
            if ctt == kn.count(-1):
                print(qc, ctt)
                break
        '''
        
        #print(kn.count(-1), qc)
        l = []
        r = []

        for i in range(n):
            if kn[i] == -1:
                r.append(i)
            else:
                l.append(i)
        
        random.shuffle(r)
        base = l + r

        swaps = []
        for i in range(random.randint(800, 900)):
            swaps.append(random.randint(len(l), n - 2))
            if swaps[-1] == k or swaps[-1] == k - 1:
                swaps.pop()
                
        if len(swaps) % 2 == 0:
            swaps.pop()

        def ch(z):
            curr = base[:]
            for i in range(z):
                u = swaps[i]
                curr[u], curr[u + 1] = curr[u + 1], curr[u]
            return curr

        lo = 0
        hi = len(swaps)
        
        ql = query(ch(0))
        qh = query(ch(hi))

        if ql == qh:
            fail.append(qc)
            continue
        
        while hi - lo > 1:
            mid = (lo + hi) // 2
            qm = query(ch(mid))
            if ql != qm:
                hi = mid
                qh = qm
            elif qm != qh:
                lo = mid
                ql = qm
            else:
                assert 0

            assert ql != qh

        assert abs(ql - qh) == 1
        
        curr = ch(lo)
        u = swaps[lo]

        x = curr[u]
        y = curr[u + 1]
        if qh > ql:
            x, y = y, x

        if dbg:
            assert p[x] == y

        kn[x] = y
        cv = y
        while kn[cv] == -1:
            assert cv in kn
            l = [kn.index(cv), cv]
            r = [i for i in range(n) if i not in l]

            if dbg:
                assert p[l[0]] == cv

            lo = 0
            hi = n - 2

            def zz(z):
                x = r[:z] + l[1:] + r[z:]
                y = x[:k] + [l[0]] + x[k:]

                #if dbg:
                #    print(y)
                    
                return query(y)

            lv = zz(lo)
            hv = zz(hi)
            
            if hv == lv:
                if zz(k) == lv + 1:
                    lo = k
                    lv = lv + 1
                elif zz(k - 1) == lv - 1:
                    hi = k - 1
                    hv = lv - 1
                else:
                    if dbg:
                        assert p[l[1]] == r[k - 1]
                        assert p[r[k - 1]] == l[0]

                    #print(l, r)
                    #print(kn)
                    
                    kn[l[1]] = r[k - 1]
                    kn[r[k - 1]] = l[0]

                    #print('sus', kn)
                    break
                    

            if dbg:
                assert zz(lo) == lv
                assert zz(hi) == lv - 1

            while hi - lo > 1:
                mid = (lo + hi) // 2
                zm = zz(mid)
                if zm == lv:
                    lo = mid
                elif zm == lv - 1:
                    hi = mid
                else:
                    assert 0

            y = r[lo]
            if dbg:
                assert p[cv] == y

            kn[cv] = y
            cv = y

    if dbg:
        for i in range(n):
            if kn[i] == -1:
                assert p[p[i]] == i

    def q2(l, v):
        assert len(l) == n - 1
        assert len(set(l + [v])) == n

        y = l[:k] + [v] + l[k:]
        qq = query(y)
        
        for i in range(n):
            if i == k:
                continue
            if kn[y[i]] != -1 and y.index(kn[y[i]]) > i:
                qq -= 1

        return qq

    for i in range(n):
        if kn[i] != -1:
            continue

        base = list(range(n))
        base.pop(i)

        a = q2(base, i)
        ar = q2(base[::-1], i)

        if a < ar:
            poss = base[k:]
        else:
            poss = base[::-1][k:]

        if dbg:
            assert p[i] in poss

        poss = [i for i in poss if kn[i] == -1]
        op = [v for v in base if v not in poss]
        
        while len(poss) > 1:
            # print(i, poss)
            cut = len(poss) // 2

            lp = poss[:cut]
            rp = poss[cut:]

            base = lp + op + rp

            a = q2(base, i)
            ar = q2(base[::-1], i)

            if a > ar:
                poss = lp
                op += rp
            else:
                poss = rp
                op += lp

            if dbg:
                assert p[i] in poss

        j = poss[0]
        
        if dbg:
            assert p[i] == j
            assert p[j] == i

        kn[i] = j
        kn[j] = i

    if dbg:
        assert p == kn
        assert qc <= 10 * n
    else:
        print('!', *[v + 1 for v in kn])
        
            
        
