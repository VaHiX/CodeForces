# Problem: CF 1624 E - Masha-forgetful
# https://codeforces.com/contest/1624/problem/E

"""
Algorithm: Dynamic Programming with String Matching
Purpose: Split a given phone number string s into segments of length at least 2, 
         where each segment is a substring of one of the known phone numbers.

Approach:
1. For each known phone number, precompute all substrings of length 2 and 3,
   storing their start position, end position, and the number they belong to.
2. Use dynamic programming to determine if we can split the target string s
   into valid segments ending at each position.
3. Reconstruct the solution by backtracking through the DP array.

Time Complexity: O(n * m^2 + m^2)
Space Complexity: O(n * m^2 + m)

Where n is the number of known phone numbers and m is the length of each phone number.
"""

for _ in range(int(input())):
    input()
    n, m = map(int, input().split())
    pairs = {}  # Dictionary to store all substrings of length 2
    triples = {}  # Dictionary to store all substrings of length 3
    
    # Preprocessing: For each known phone number, extract all substrings of length 2 and 3
    for k in range(n):
        s = input()
        for i in range(m - 1):
            # Store substring of length 2 with its position and source number
            pairs[s[i : i + 2]] = (i + 1, i + 2, k + 1)
            # Store substring of length 3 with its position and source number
            if i + 3 <= m:
                triples[s[i : i + 3]] = (i + 1, i + 3, k + 1)

    s = input()  # The phone number to be split

    # DP array: dp[i] will be None if it's not possible to split s[i:] into valid segments,
    # otherwise it will be a tuple (start_pos, end_pos, number_index)
    dp = [None] * m
    
    # Backward DP: Process from right to left
    for i in range(m)[::-1]:
        # Check if we can form a segment of length 2 from current position
        x = pairs.get(s[i : i + 2])
        if x:
            # Check if a valid split can be formed after this segment
            res = i + 2 == m or dp[i + 2]
            if res is not None:
                dp[i] = x  # Mark this as valid split
                continue

        # Check if we can form a segment of length 3 from current position
        x = triples.get(s[i : i + 3])
        if x:
            # Check if a valid split can be formed after this segment
            res = i + 3 == m or dp[i + 3]
            if res is not None:
                dp[i] = x  # Mark this as valid split
                continue

    # If dp[0] is None, it means we couldn't split the entire string
    if dp[0]:
        out = []
        i = 0
        # Reconstruct the solution by backtracking through the DP array
        while i < m:
            a, b, c = dp[i]
            out.append((a, b, c))
            i += b - a + 1  # Move to the next unprocessed position
        print(len(out))
        for line in out:
            print(*line)
    else:
        print(-1)  # Cannot split the string


# https://github.com/VaHiX/CodeForces/