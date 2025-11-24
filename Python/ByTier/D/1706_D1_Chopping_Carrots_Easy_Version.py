# Problem: CF 1706 D1 - Chopping Carrots (Easy Version)
# https://codeforces.com/contest/1706/problem/D1

"""
Algorithm: Brute-force with optimization
The problem asks to minimize the difference between the maximum and minimum 
values of floor(a[i]/p[i]) where p[i] is in [1, k].

Key insight:
- For each possible minimum value of floor(a[i]/p[i]) (denoted as l), 
  we compute the corresponding maximum value (r) such that all a[i] 
  can be covered with p[i] in [1, k].
- We iterate through all possible l values from 1 to a[0] (since 
  a[0] is the smallest a[i]).
- For each l, we calculate the minimum r by considering how 
  large p[i] must be for a[i] // p[i] >= l.
- The answer is the minimum of (r - l) over all valid l.

Time Complexity: O(a[0] * n)
Space Complexity: O(1)

This approach works because:
- The minimum value of floor(a[i]/p[i]) can't exceed a[0] (since a[0] is the smallest a[i]).
- The maximum value of floor(a[i]/p[i]) is at most a[-1] (last element).
- We try every possible value of minimum floor(a[i]/p[i]) and find the best corresponding maximum.
"""
tc = int(input())
for case in range(tc):

    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    # Initialize ans with the case where all a[i] are divided by 1
    # This corresponds to l=1, r=max(a) 
    ans = a[-1] - a[0]

    # Try all possible minimum values for floor(a[i]/p[i])
    for l in range(1, a[0] + 1):
        r = l  # Initialize r with l (we want at least l)
        for num in a:
            # For each num in a, calculate the minimal p[i] such that 
            # a[i] // p[i] >= l. If p[i] > k, then p[i] = k.
            # So we want to minimize max(0, (num // l)) but subject to p[i] <= k.
            # So p[i] should be at least (num // l) but at most k.
            # Hence, floor(a[i]/p[i]) <= (num // l) when p[i] = (num // l) if it's <= k.
            # But that's not right.
            # We want to find minimum max value of floor(a[i]/p[i]) over all a[i].
            # Given that p[i] must be between 1 and k.
            # For a fixed l (the minimum value we want), we need to find 
            # maximum value r such that for each a[i] there exists p[i] in [1,k] 
            # where a[i]//p[i] >= l, which implies p[i] <= a[i]//l.
            # To get max possible r, we want p[i] = min(k, ceil(a[i]/l)) = min(k, (a[i] + l - 1) // l)  
            # But we want floor(a[i]/p[i]) which is at most a[i]//p[i] and at least l.
            # Since l is the minimum, so for a[i], we want p[i] to be such that
            # a[i]//p[i] >= l. Therefore, p[i] <= a[i] // l. 
            # So for a[i], the minimum value a[i]//p[i] can have is min(k, a[i] // l).
            # But we're iterating over l, and l is target min value,
            # so for the current l, we are computing what's the maximum
            # floor(a[i]/p[i]) could be for p[i] in range 1 to k.
            # r = max(r, num // min(k, num // l)) does this.
            # If num // l = x, then k >= x iff p[i] = x, so floor(a[i]/p[i]) = l.
            # If num // l < k, we can still set p[i] = min(k, num // l)
            # Actually, we want floor(a[i]/p[i]) to be >= l, which is achieved by
            # setting p[i] <= a[i] // l, but we're subject to p[i] <= k.  
            # So if a[i]//l > k, then we must set p[i] = k, giving floor(a[i]/k).
            # Otherwise, we can try p[i] = a[i]//l, giving exactly l.
            # So we want to find max floor(a[i]/p[i]) for p[i] in [1,k] such that
            # it's at least l.
            # So for each element, p[i] = min(k, a[i] // l) 
            # then floor(a[i]/p[i]) should be calculated correctly.
            r = max(r, num // min(k, num // l))
        ans = min(ans, r - l)
    print(ans)


# https://github.com/VaHiX/CodeForces/