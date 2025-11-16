# Problem: CF 1970 D3 - Arithmancy (Hard)
# https://codeforces.com/contest/1970/problem/D3

"""
Code Purpose:
This code solves the interactive problem "D3. Arithmancy (Hard)" where:
- Professor Vector needs to generate n distinct magic words (strings of 'X' and 'O')
- Each word is constructed in a specific way to ensure that the power (number of distinct substrings) of any concatenation of two words is unique
- Then, for each query (spell power), it must determine the two original words in order that were concatenated to form that spell

Algorithms/Techniques:
- Construction of magic words based on a mathematical function f(i, j) which computes a unique value for each pair of indices
- Uses a greedy method to generate words ensuring no two combinations yield the same power
- Binary search or hash mapping to quickly retrieve the indices for a given spell power

Time Complexity: O(n^3 * log n) in worst case due to checking uniqueness of powers and constructing words.
Space Complexity: O(n^2) for storing hash map of powers and words.
"""

n = int(input())

w = []
q = {}
i = -1


def f(a, b):
    # Mathematical function to compute a unique power value for word concatenation
    # Ensures that f(a,b) != f(c,d) for different (a,b) and (c,d) pairs
    return (a + 2) * (b + 4) - 1 if a >= b else (a + 5) * (b + 1) - 1


while len(w) < n:
    i += 1
    # If computed value already exists, skip this iteration
    if f(i, i) in q:
        continue
    
    # Check for overlaps with previously generated words
    if any(f(i, j) in q for j in w):
        continue
    if any(f(j, i) in q for j in w):
        continue
    
    # Try to add the new word and check if all combinations remain unique
    q1 = {f(i, i): (len(w), len(w))}  # Mapping for new word with itself
    ok = True
    for r, j in enumerate(w):
        v = f(i, j)
        if v in q1:
            ok = False
            break
        q1[v] = len(w), r  # Record the mapping for i+j combination
    if not ok:
        continue
    
    for r, j in enumerate(w):
        v = f(j, i)
        if v in q1:
            ok = False
            break
        q1[v] = r, len(w)  # Record the mapping for j+i combination
    if not ok:
        continue
    
    # If all checks pass, update global mapping and append new word
    q.update(q1)
    w.append(i)

# Output the constructed magic words (each is "XO" + i "X"s)
for i in w:
    print("XO" + i * "X")

t = int(input())
for _ in range(t):
    x = int(input())
    u, v = q[x]  # Retrieve indices from lookup table
    print(u + 1, v + 1)  # Convert to 1-based indexing as required


# https://github.com/VaHiX/CodeForces/