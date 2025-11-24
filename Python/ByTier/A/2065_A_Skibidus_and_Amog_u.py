# Problem: CF 2065 A - Skibidus and Amog'u
# https://codeforces.com/contest/2065/problem/A

# ====================================================================
# Problem: Convert Amog'u singular nouns to plural form.
# Algorithm/Technique: String manipulation using slicing and concatenation.
# Time Complexity: O(n) where n is the length of the string (constant up to 10).
# Space Complexity: O(n) for storing the output string (constant up to 10).
# ====================================================================

for s in [*open(0)][1:]:  # Read all lines from stdin, skip first line (test cases count)
    print(s[:-3] + "i")   # Remove last 3 characters ("us") and append "i"


# https://github.com/VaHiX/codeForces/