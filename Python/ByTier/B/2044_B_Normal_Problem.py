# Problem: CF 2044 B - Normal Problem
# https://codeforces.com/contest/2044/problem/B

# ==============================================================================
# Problem: Reverse and Transform String
# 
# Algorithm: String manipulation with translation
# 
# Time Complexity: O(n) where n is the length of the input string
# Space Complexity: O(n) for storing the reversed and translated string
# 
# Description:
# For each test case, we reverse the input string and then translate specific
# characters ('p' -> 'q', 'q' -> 'p', 'w' -> 'w') to simulate the reflection
# effect observed when looking at the glass window from inside the store.
# ==============================================================================

for _ in range(int(input())):  # Read number of test cases and iterate
    a = input().strip()  # Read the input string
    b = a[::-1].translate(str.maketrans("pqw", "qpw"))  # Reverse string and translate characters
    print(b)  # Output the result


# https://github.com/VaHiX/codeForces/