# Problem: CF 1735 C - Phase Shift
# https://codeforces.com/contest/1735/problem/C

"""
Purpose: 
This code finds the lexicographically smallest original string `s` that could have been transformed into the given string `t` by a circular shift of the alphabet.

Approach:
The transformation works as follows:
- A circular arrangement of 26 lowercase letters is created.
- Each letter in `s` is replaced by the letter that follows it clockwise in the circle to produce `t`.
- To reverse this process, we reconstruct `s` by finding the unique preimage of each character in `t`.

Algorithm:
1. For each character in `t`:
   - Try to assign the lexicographically smallest available unused letter in the circle.
   - Use a mapping to track which original letter maps to which transformed letter.
   - If a character already has a mapping, skip it.
   - Avoid creating cycles in the mapping to ensure valid transformation.
2. Finally, transform `t` using the reverse mapping to get `s`.

Time Complexity: O(n * 26) = O(n), where n is the length of string t.
Space Complexity: O(1) since the mappings and used set are bounded by a constant (26 characters).
"""

for _ in range(int(input())):
    n = int(input())
    t = input()
    used = set()
    mapping = {}

    def has(l, c):
        # Check if character l leads back to c - prevents cycles in the mapping
        while l in mapping:
            l = mapping[l]
            if l == c:
                return True
        return False

    for c in t:
        if c in mapping:
            continue
        for i in range(26):
            l = chr(i + ord("a"))
            # Skip if already used, or same as current char, or would create a cycle
            if (
                l in used
                or l == c
                or (l in mapping and has(l, c) and len(mapping) < 25)
            ):
                continue
            mapping[c] = l
            used.add(l)
            break
    print("".join(mapping[c] for c in t))


# https://github.com/VaHiX/CodeForces/