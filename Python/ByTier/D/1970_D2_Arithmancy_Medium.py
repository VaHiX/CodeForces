# Problem: CF 1970 D2 - Arithmancy (Medium)
# https://codeforces.com/contest/1970/problem/D2

"""
Code Purpose:
This code solves the Arithmancy problem where we need to generate n distinct magic words
consisting of 'X' and 'O', and then for each given spell power, determine which two magic words
were concatenated in which order to produce that spell.

The solution uses a mathematical formula to compute a "power value" for each concatenation
of two magic words. The key insight is to construct magic words such that each unique
concatenation has a distinct power value, enabling perfect lookup.

Algorithms/Techniques:
- Constructing magic words using a pattern based on number of 'X's
- Using a formula f(a,b) to assign unique power values to spell combinations
- Precomputing all possible combinations and storing them in a hash map for O(1) lookup
- Interactive I/O handling for multiple requests

Time Complexity:
- Generating magic words: O(n^2) in worst case due to checking constraints
- Each spell lookup: O(1) using hash map
- Overall: O(n^2 + q) where q is number of queries

Space Complexity:
- Storage for magic words: O(n * L) where L is average word length
- Storage for mapping: O(n^2) in worst case
- Overall: O(n^2)
"""

n = int(input())

w = []  # List to store magic words (as integers representing number of X's)
q = {}  # Hash map to store power value -> (u,v) index pairs
i = -1  # Counter for generating candidate words


def f(a, b):
    # A custom formula to calculate a unique "power value" for concatenating two words
    # This function must ensure that different combinations produce different values
    return (a + 2) * (b + 4) - 1 if a >= b else (a + 5) * (b + 1) - 1


while len(w) < n:
    i += 1
    # Skip if this power value is already used
    if f(i, i) in q:
        continue
    # Check if any previous word combined with current produces a used value
    if any(f(i, j) in q for j in w):
        continue
    # Check if any previous word combined with current in reverse order produces a used value
    if any(f(j, i) in q for j in w):
        continue
    
    # Try to add current candidate word
    q1 = {f(i, i): (len(w), len(w))}  # Self-combination case
    ok = True
    
    # Check all existing words against new word (i-th word on left)
    for r, j in enumerate(w):
        v = f(i, j)
        if v in q1:
            ok = False
            break
        q1[v] = len(w), r  # Store u,v indices for this combination (i,j)
    
    if not ok:
        continue
    
    # Check all existing words against new word (i-th word on right)
    for r, j in enumerate(w):
        v = f(j, i)
        if v in q1:
            ok = False
            break
        q1[v] = r, len(w)  # Store u,v indices for this combination (j,i)
    
    if not ok:
        continue
    
    # If all checks passed, accept this word
    q.update(q1)
    w.append(i)

# Print generated magic words using pattern "XO" + i*'X'
for i in w:
    print("XO" + i * "X")

t = int(input())
for _ in range(t):
    x = int(input())
    u, v = q[x]
    print(u + 1, v + 1)  # Convert from 0-based to 1-based indexing


# https://github.com/VaHiX/CodeForces/