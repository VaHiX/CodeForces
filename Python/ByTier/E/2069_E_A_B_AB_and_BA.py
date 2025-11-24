# Problem: CF 2069 E - A, B, AB and BA
# https://codeforces.com/contest/2069/problem/E

"""
E. A, B, AB and BA

Purpose:
This solution determines whether a given string s of 'A' and 'B' characters can be split into blocks of length 1 or 2 such that:
- At most `a` strings equal to "A"
- At most `b` strings equal to "B"
- At most `ab` strings equal to "AB"
- At most `ba` strings equal to "BA"
- Strings "AA" and "BB" are not allowed.
Each character in s must belong to exactly one block.

Approach:
1. Parse input to extract string s and counts for each pattern type.
2. Identify contiguous segments of same characters.
3. Determine if these segments can be optimally matched with available patterns.
4. Use greedy logic to assign blocks:
   - First try using "AB" or "BA" where possible.
   - Then adjust the remaining segments using extra "A" and "B".
5. Finally validate if counts of remaining A and B are within limits.

Time Complexity: O(n log n) due to sorting, where n is the length of string s.
Space Complexity: O(n) for storing segments and intermediate data.
"""

def solve():
    import sys

    data = sys.stdin.read().split()
    if not data:
        return
    t = int(data[0])
    idx = 1
    res = []
    for _ in range(t):
        s = data[idx]
        idx += 1
        a = int(data[idx])
        b = int(data[idx + 1])
        ab = int(data[idx + 2])
        ba = int(data[idx + 3])
        idx += 4
        sa = s.count("A")  # Count of 'A' characters in the string
        sb = s.count("B")  # Count of 'B' characters in the string
        n = len(s)
        extras = 0  # Extra lengths of segments that cannot be assigned to AB/BA patterns yet
        aval = []   # For segments starting with A and being processed
        bval = []   # For segments starting with B and being processed
        i = 0
        while i < n:
            j = i
            # Extend j until character changes
            while j + 1 < n and s[j + 1] != s[j]:
                j += 1
            # Check if start/end indices have same parity (i % 2 == j % 2)
            if (i % 2) == (j % 2):
                # If segment is of even parity, it must be handled specially - possibly as a group of AB or BA
                extras += (j - i) // 2
            elif s[i] == "A":
                # Segment starts with 'A', so it may be assigned to pattern "A" only if applicable
                aval.append((j - i + 1) // 2)
            else:
                # Segment starts with 'B', so it may be assigned to pattern "B" only if applicable
                bval.append((j - i + 1) // 2)
            i = j + 1
        # Sort segments by size to use greedy approach (prefer larger ones first)
        aval.sort()
        bval.sort()
        # Try assigning segments from aval (A-started) 
        for x in aval:
            if ab >= x:  # Check if we can take 'x' number of AB patterns
                ab -= x
                sa -= x
                sb -= x
            else:
                # Otherwise, remaining part of this block must be counted as extra (since it cannot be fully covered)
                extras += x - 1
        # Similar for segments from bval (B-started)
        for x in bval:
            if ba >= x:  # Check if we can take 'x' number of BA patterns
                ba -= x
                sa -= x
                sb -= x
            else:
                extras += x - 1  # Count remainder after using up available BA patterns
                
        # Assign leftover segments that might contribute to "A" or "B"
        while extras > 0:
            if ab > 0:
                ab -= 1
            elif ba > 0:
                ba -= 1
            else:
                break  # No more allowed changes to meet constraints
            extras -= 1
            sa -= 1
            sb -= 1
        # Final check: ensure the remaining A/B counts fit the allowed limits
        res.append("YES" if (sa <= a and sb <= b) else "NO")
    sys.stdout.write("\n".join(res))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/