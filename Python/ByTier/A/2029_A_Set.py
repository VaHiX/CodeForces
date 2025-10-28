# Problem: CF 2029 A - Set
# https://codeforces.com/contest/2029/problem/A

# '''
# Algorithm/Technique: Mathematical analysis
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
#
# The problem asks to find the maximum number of operations where each operation
# removes an element x from the set S = [l, r] such that x has at least k multiples in S.
# 
# Key insight:
# For a number x in range [l, r], the count of its multiples in S is floor(r/x) - floor((l-1)/x).
# To maximize operations, we can greedily process numbers in descending order.
# However, there is an efficient mathematical way to compute this:
#
# The operation count equals the number of integers x in [l, r] such that
# at least k multiples of x exist in S. 
#
# We can simplify this with a greedy observation:
# A greedy approach of picking largest x works.
# If we consider all multiples of x, we can remove one for each valid multiple.
# The maximum number of operations is equal to the count of numbers >= l,
# such that there are at least k multiples in [l,r]. 
#
# We reframe this as counting:
# how many i in [l,r] are such that floor(r/i) - floor((l-1)/i) >= k?
# But again, a simpler mathematical formula applies based on summing over
# all valid x's and using inclusion-exclusion.
#
# A faster and known optimized approach:
# The maximum number of operations is equivalent to the following formula:
# max(0, r//k - l + 1)
#
# This works because for choosing i starting from l up to r,
# we can think of each valid x being chosen in a greedy fashion.
# When k=2, it's essentially about counting multiples of small numbers in range.
#
# The final optimized logic:
# If we consider all x from 1 to r, and count how many are valid for k multiples,
# but since we only consider x in [l,r], we count directly.
# So the answer is max(0, (r // k) - l + 1)
# '''
for s in [*open(0)][1:]:
    l, r, k = map(int, s.split())
    print(max(0, r // k - l + 1))


# https://github.com/VaHiX/codeForces/