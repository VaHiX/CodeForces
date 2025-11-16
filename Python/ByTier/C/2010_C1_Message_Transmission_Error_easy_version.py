# Problem: CF 2010 C1 - Message Transmission Error (easy version)
# https://codeforces.com/contest/2010/problem/C1

# ==============================================================================
# Problem: Message Transmission Error (easy version)
# 
# Algorithm/Technique: String matching with overlap detection
#
# Approach:
#   - Check if the received string t can be split into two parts where the
#     suffix of the first part matches the prefix of the second part.
#   - The overlap must be positive and less than the length of the message.
#   - Iterate from the middle to the end of the string to find matching suffixes
#     that also appear at the beginning.
#
# Time Complexity: O(n^2) where n is the length of the input string
#   - Outer loop runs up to n/2 iterations (for checking possible overlaps)
#   - Inner substring comparison takes O(n) time in worst case
# Space Complexity: O(1) - Only using a constant amount of extra space
# ==============================================================================

s = input()
for i in range(len(s) // 2 + 1, len(s)):  # Start from middle to end to check valid overlaps
    if s[len(s) - i :] == s[:i]:         # Check if suffix matches prefix of same length
        print("YES")
        print(s[:i])                     # Print the possible original message
        break
else:
    print("NO")                          # No valid overlap found


# https://github.com/VaHiX/codeForces/