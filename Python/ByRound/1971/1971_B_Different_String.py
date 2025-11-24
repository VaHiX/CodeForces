# Problem: CF 1971 B - Different String
# https://codeforces.com/contest/1971/problem/B

"""
Problem: Rearrange characters in a string to form a new string that is not equal to the original.
If impossible, output "NO". Otherwise, output "YES" followed by any valid rearrangement.

Algorithms/Techniques:
- Greedy approach: Try to find a character that is different from its predecessor and swap it with the predecessor.
- If all characters are the same, it's impossible to rearrange to a different string.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for storing the character list and result.

"""

t = int(input())


def check(s):
    if len(s) == 1:
        return False  # A single character cannot be rearranged to a different string
    i = 1
    while i < len(s):
        if s[i] != s[i - 1]:
            # Swap current character with the previous one to make a different string
            s[i], s[i - 1] = s[i - 1], s[i]
            return True
        i += 1
    return False  # All characters are the same


ans = []
for _ in range(t):
    s = [x for x in input()]
    if check(s):
        ans.append("YES")
        ans.append("".join(s))  # Convert back to string and add to results
    else:
        ans.append("NO")
for x in ans:
    print(x)


# https://github.com/VaHiX/CodeForces/