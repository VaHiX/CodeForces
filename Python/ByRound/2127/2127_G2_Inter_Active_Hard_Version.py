# Problem: CF 2127 G2 - Inter Active (Hard Version)
# https://codeforces.com/contest/2127/problem/G2

"""
Interactive problem to find a hidden permutation p of length n.

Problem Description:
- Given a hidden permutation p[1..n]
- We can make queries by providing a permutation q[1..n]
- For each query, we get the number of inversions in q relative to p
- The goal is to find p using at most 10*n queries

Algorithm:
1. First Phase: Finding Fixed Points
   - Select k = (n-1)/2 as pivot point
   - Use random swaps and binary search to find pairs (i,j) where p[i]=j
   - Build up knowledge of the permutation structure iteratively

2. Second Phase: Resolving Remaining Elements
   - For each unresolved element i, determine its position using binary search
   - Use query differences to narrow down possible positions
   - Handle special cases where elements form cycles

Key Techniques:
- Binary search over sequence of swaps to detect inversions
- Query differencing to extract information about relative positions
- Random shuffling to avoid worst-case scenarios

Complexity Analysis:
- Time: O(n^2 * log(n)) 
  * Each element may need O(n) queries
  * Each query involves binary search O(log n)
  * Total queries limited to 10*n
- Space: O(n) for storing permutation and auxiliary arrays
"""

import random
import sys
from math import log2


def query(q):
    """
    Make a query to the interactive judge or debug environment.
    
    Args:
        q: List[int] - A permutation of length n (0-based indices)
    
    Returns:
        int: Number of inversions in q relative to hidden permutation p
            An inversion occurs when p[q[i]] appears after position i in q
            (excluding position k)
    
    Side effects:
        - Increments query counter (qc)
        - In debug mode: calculates inversions using known p
        - In judge mode: sends query to judge and receives response
    """
    global qc
    qc += 1  # Track number of queries made

    assert len(q) == n  # Validate query format

    # Judge mode: send query and get response
    print("?", " ".join(str(v + 1) for v in q))  # Convert to 1-based indices
    sys.stdout.flush()  # Ensure output is sent immediately
    return int(input())


t = int(input())
for _ in range(t):
    qc = 0

    n = int(input())

    k = (n - 1) // 2

    # Send pivot position to judge (1-based index)
    print(k + 1)

    # kn[i] stores the element that pairs with i in permutation p
    # -1 means we don't know the pair yet
    kn = [-1] * n

    # Track failed attempts to find new pairs
    fail = []
    
    # Main loop for first phase: finding pairs
    while 1:
        need = kn.count(-1)  # Count remaining unknown elements

        # Exit conditions:
        # 1. All pairs found (need = 0)
        # 2. Not enough remaining queries to complete search
        #    (estimated cost: log2(need) + 2.5 queries per element)
        if need == 0 or qc + need * (log2(need) + 2.5) >= 10 * n:
            break
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
            """
            Apply z swaps from the swaps list to base permutation.
            Returns a new permutation after applying first z swaps.
            """
            curr = base[:]  # Copy base permutation
            for i in range(z):
                u = swaps[i]
                curr[u], curr[u + 1] = curr[u + 1], curr[u]  # Apply swap
            return curr

        # Binary search setup
        lo = 0
        hi = len(swaps)

        # Query permutation before any swaps and after all swaps
        ql = query(ch(0))
        qh = query(ch(hi))

        # If queries give same result, this sequence of swaps is not useful
        if ql == qh:
            fail.append(qc)  # Track failed attempts
            continue  # Try a new random sequence

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

        kn[x] = y
        cv = y
        while kn[cv] == -1:
            assert cv in kn
            l = [kn.index(cv), cv]
            r = [i for i in range(n) if i not in l]

            lo = 0
            hi = n - 2

            def zz(z):
                x = r[:z] + l[1:] + r[z:]
                y = x[:k] + [l[0]] + x[k:]

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
                    kn[l[1]] = r[k - 1]
                    kn[r[k - 1]] = l[0]

                    break

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
            kn[cv] = y
            cv = y

    # Helper function for second phase queries
    def q2(l, v):
        """
        Make a modified query that accounts for already known pairs.
        
        Args:
            l: List[int] - Permutation of n-1 elements (excluding v)
            v: int - Element to insert at position k
        
        Returns:
            int: Modified inversion count after subtracting known inversions
        
        This function:
        1. Inserts v at position k in permutation l
        2. Makes a query with the resulting permutation
        3. Subtracts inversions we already know about (from kn array)
        4. Returns the adjusted inversion count
        """
        # Validate input format
        assert len(l) == n - 1
        assert len(set(l + [v])) == n

        # Insert v at position k
        y = l[:k] + [v] + l[k:]
        qq = query(y)  # Get raw inversion count

        # Subtract known inversions
        for i in range(n):
            if i == k:  # Skip pivot position
                continue
            # If we know where y[i] should go and its pair appears later
            if kn[y[i]] != -1 and y.index(kn[y[i]]) > i:
                qq -= 1

        return qq

    # Second phase: resolve remaining elements
    for i in range(n):
        # Skip if we already know the pair for i
        if kn[i] != -1:
            continue

        # Create base permutation without element i
        base = list(range(n))
        base.pop(i)

        # Query with i at pivot for both forward and reversed base
        a = q2(base, i)  # Forward order
        ar = q2(base[::-1], i)  # Reversed order

        # Use query difference to determine which half contains p[i]
        if a < ar:  # p[i] is in second half of forward order
            poss = base[k:]
        else:  # p[i] is in second half of reversed order
            poss = base[::-1][k:]

        poss = [i for i in poss if kn[i] == -1]
        op = [v for v in base if v not in poss]

        while len(poss) > 1:

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

        j = poss[0]

        kn[i] = j
        kn[j] = i

    print("!", *[v + 1 for v in kn])


# https://github.com/VaHiX/CodeForces/