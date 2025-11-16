# Problem: CF 1730 D - Prefixes and Suffixes
# https://codeforces.com/contest/1730/problem/D

from collections import Counter

for _ in range(int(input())):
    # Read the length and two strings
    _, s1, s2 = (input() for _ in range(3))
    
    # Create a counter of character pairs from reversed s1 and s2
    # This helps to understand which characters can be matched up
    pair_counter = Counter(frozenset((x, y)) for x, y in zip(reversed(s1), s2))
    
    # Find all pairs that appear an odd number of times
    odd = [
        p
        for p, v in pair_counter.items()
        if v % 2
    ]
    
    # If there are no odd pairs, or there's exactly one odd pair and it's a single character,
    # then it's possible to make the strings equal
    print(("NO", "YES")[len(odd) == 0 or len(odd) == 1 and len(odd[0]) == 1])


# https://github.com/VaHiX/CodeForces/