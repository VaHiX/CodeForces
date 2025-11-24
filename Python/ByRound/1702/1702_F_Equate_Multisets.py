# Problem: CF 1702 F - Equate Multisets
# https://codeforces.com/contest/1702/problem/F

"""
Algorithm: 
This problem is about matching elements from two multisets such that operations (doubling or halving) on elements of multiset b can make it equal to multiset a.
Key insight:
- For each number in a, we need to find a number in b that can be transformed to match it.
- The transformation can be done by multiplying or dividing by 2, which means we need to "normalize" the numbers to their "base" form (the odd number obtained by repeatedly dividing by 2).
- We can use a greedy approach: for each element in a, we try to match it with an element in b in a way that the normalized version is the same.
- We use a map of counts to track how many numbers in b can be transformed to match each normalized number.

Time Complexity: O(n * log(max_value)) where n is the size of the multiset and max_value is the maximum element value.
Space Complexity: O(n) for storing the counts of normalized elements.
"""

Z = lambda: map(int, input().split())


def t(n):
    # Normalize the number to its odd representative by continuously dividing by 2
    while ~n & 1:
        n >>= 1
    return n


from collections import defaultdict

for _ in range(next(Z())):
    Z()  # Read n (not used further)
    l = defaultdict(int)  # Dictionary to store count of normalized numbers from a
    for a in Z():
        l[t(a)] += 1  # Count the normalized version of each element in a
    for b in Z():
        b = t(b)  # Normalize the number in b
        # Try to match b with a number in l
        while b:
            if l[b]:  # If there's a matching normalized number
                l[b] -= 1  # Use one instance
                break  # Matched, move to next element in b
            b >>= 1  # If no match, try with b/2
        if not b:  # No normalization of b matched any in a
            print("NO")
            break
    else:
        print("YES")  # All elements matched


# https://github.com/VaHiX/CodeForces/