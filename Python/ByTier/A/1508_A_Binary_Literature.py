# Problem: CF 1508 A - Binary Literature
# https://codeforces.com/contest/1508/problem/A

"""
Purpose: Solve the Binary Literature problem where we need to find a bitstring of length at most 3n that contains at least two of the three given bitstrings as subsequences.

Approach:
- For each test case, we have three bitstrings of length 2n.
- We want to construct a new bitstring of length at most 3n containing at least two of the input strings as subsequences.
- Strategy: Try all pairs of the three strings, and for each pair, find a character (0 or 1) that appears at least n times in both strings.
  This ensures that such a character can be used as a "pivot" to merge the two strings in a way that maintains the subsequence property.
- Then merge these two strings by interleaving their characters, inserting the chosen character when needed to form valid subsequences.

Algorithms/Techniques:
- Two-pointer merge technique to combine two strings into one while ensuring subsequence properties.
- Greedy selection of character from pairs of strings.

Time Complexity: O(n) per test case, since we iterate through strings a constant number of times.
Space Complexity: O(n) for storing the output string and intermediate results.
"""

def solve():
    import sys

    data = sys.stdin.read().strip().split()
    if not data:
        return
    t = int(data[0])
    index = 1
    out_lines = []

    def merge(s, t, n, ch):
        L = 2 * n  # Length of each input string
        i = 0
        j = 0
        need = n  # Number of occurrences of ch we need to include in result
        res = []
        while need:  # Continue until we've placed n occurrences of ch
            # Skip characters in s that are not ch and we still have enough chars left
            while i < L and s[i] != ch and (L - i) > need:
                res.append(s[i])
                i += 1
            # Skip characters in t that are not ch and we still have enough chars left
            while j < L and t[j] != ch and (L - j) > need:
                res.append(t[j])
                j += 1
            # Place the required character ch
            res.append(ch)
            if i < L:
                i += 1
            if j < L:
                j += 1
            need -= 1
        # Append remaining characters from both strings
        res.extend(s[i:])
        res.extend(t[j:])
        return "".join(res)

    for _ in range(t):
        n = int(data[index])
        index += 1
        s1 = data[index]
        index += 1
        s2 = data[index]
        index += 1
        s3 = data[index]
        index += 1
        strings = [s1, s2, s3]
        chosen = None
        chosen_char = None
        pairs = [(0, 1), (0, 2), (1, 2)]
        # Try all pairs of strings to find a good character to merge on
        for i, j in pairs:
            for ch in ["0", "1"]:
                if strings[i].count(ch) >= n and strings[j].count(ch) >= n:
                    chosen = (i, j)
                    chosen_char = ch
                    break
            if chosen is not None:
                break
        sA = strings[chosen[0]]
        sB = strings[chosen[1]]
        res = merge(sA, sB, n, chosen_char)
        out_lines.append(res)
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/