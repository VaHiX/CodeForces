# Problem: CF 1891 E - Brukhovich and Exams
# https://codeforces.com/contest/1891/problem/E

"""
Algorithm: Greedy with Segment Analysis
Purpose: Minimize the number of adjacent pairs with GCD = 1 by setting at most k elements to 0.

Approach:
1. Identify segments of consecutive elements with GCD = 1.
2. Also identify segments of consecutive 1s.
3. Use greedy strategy to reduce the number of such pairs:
   - For pairs of consecutive non-1 elements that are coprime, we can reduce the number of such pairs by setting one element in each pair to 0.
   - For sequences of 1s, we can set elements to 0 to reduce the impact on the result.

Time Complexity: O(n log n) due to sorting operations.
Space Complexity: O(n) for storing segments.

"""

import math
import sys


def solute():
    n, k = map(int, sys.stdin.readline().strip().split())
    a_list = list(map(int, sys.stdin.readline().split()))

    def coprime(a, b):
        return math.gcd(a, b) == 1

    con_pairs = []      # Lengths of segments of consecutive coprime elements (not 1s)
    con_ones = []       # Lengths of segments of consecutive 1s
    special_con_ones = [] # For special handling of 1s
    curr = 0            # Current length of non-1 coprime sequence
    prev = 1            # Previous element
    con_one = 0         # Current length of 1s sequence
    divs, rems = 0, 0   # Count of pairs that can be halved and remainder

    for i, num in enumerate(a_list):
        if con_one:                # If we are currently in a sequence of 1s
            if num == 1:
                con_one += 1       # Extend the 1s sequence
                continue
            else:
                con_ones.append(con_one)  # Store the length of 1s sequence
                con_one = 0
                prev = num         # Update previous element
                continue
        if num == 1:               # If this element is 1
            con_one = 1
            if curr:
                con_pairs.append(curr)  # Store the non-1 coprime segment
                curr = 0
            prev = 1                # Update to current element
            continue
        if i == 0:                 # Skip first element for comparison
            prev = num
            continue
        if coprime(num, prev):     # If elements are coprime
            curr += 1              # Extend the coprime sequence
        else:
            if curr:
                con_pairs.append(curr)  # Store the length when sequence breaks
            curr = 0               # Reset current count
        prev = num                 # Update previous element
    if curr:
        con_pairs.append(curr)     # Add the last coprime sequence
    if con_one:
        rems += con_one            # Add last 1s sequence
        if all(num == 1 for num in a_list):
            return max(0, con_one - k)     # All elements are 1s
    if a_list[0] == 1:
        rems += con_ones.pop(0)    # Handle 1s at start separately

    con_ones.sort()                # Sort for greedy selection
    special_con_ones.sort()

    ans = 0
    divs += sum(i >> 1 for i in con_pairs)  # How many pairs we can "split"
    rems += sum(i & 1 for i in con_pairs)   # Number of remaining elements after "splitting"
    
    r_divs = min(divs, k)           # How many full splits we can do
    divs -= r_divs
    k -= r_divs

    # Greedily subtract from longer segment to minimize sadness
    for i in range(len(con_ones)):
        if k >= con_ones[i]:
            k -= con_ones[i]
        else:
            ans += con_ones[i] + 1  # Penalty for not being able to split the segment

    r_rems = min(rems, k)          # How many remaining elements can be removed
    rems -= r_rems
    k -= r_rems
    
    ans = ans + 2 * divs + rems     # Combine the results
    
    if ans and k:
        ans = max(0, ans - k)       # Extra reductions if possible
    return ans


t = int(sys.stdin.readline())
for _ in range(t):
    print(solute())


# https://github.com/VaHiX/CodeForces/