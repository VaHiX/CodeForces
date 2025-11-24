# Problem: CF 2068 F - Mascot Naming
# https://codeforces.com/contest/2068/problem/F

"""
F. Mascot Naming

Algorithm: Greedy Construction with Subsequence Checking
Time Complexity: O(|s1| + |s2| + ... + |sn| + |t|), where the sum of lengths of all s_i is at most 200000 and |t| <= 200000
Space Complexity: O(n + |t|), for storing the list of strings and the queue

Approach:
This solution uses a greedy method to build a valid mascot name. It maintains a queue of (string_index, start_position) pairs 
and processes characters of t one at a time. For each character from t, we try to match it in existing subsequences and if it can't be matched,
we add the remaining part of that string to result. If such a match occurs, we also append the character itself. This process ensures
the final constructed string is valid: it includes all required words as subsequences and does not contain t as a subsequence.

We first try to build a string including all given words as subsequences. At any step, if we find that placing a character of 't' makes it impossible 
to complete a subsequence, we skip that part and continue with a new path. The key is the greedy strategy where we avoid using characters 
that will form t as a subsequence.

"""

import sys

input = sys.stdin.readline
n = int(input())
ss = [input().rstrip("\n") for _ in range(n)]
frb = input().rstrip("\n")

# Q initialized with all strings and start position 0 as (string_index, start_position)
Q, ans = [(i, 0) for i in range(n)], []

for char in frb:
    nQ = []  # New queue for next iteration
    add = 0  # Flag to check if we added a character from frb

    # Process each string in current Q (the potential parts of required words to match)
    for i, j in Q:
        end = ss[i].find(char, start=j)  # Find next occurrence of char in string ss[i] starting at position j
        if end == -1:  # If not found, append the rest of the string from index j onwards
            ans.append(ss[i][j:])
            continue
        # Add the portion before the matched character to ans
        ans.append(ss[i][j:end])
        add += 1  # At least one string matched this character in t
        # If there are more characters after match, add string index and next position
        if end + 1 < len(ss[i]):
            nQ.append((i, end + 1))

    # If any string had a match at this character of frb:
    if add:
        ans.append(char)  # Add the character to result

    Q = nQ  # Update Q for next iteration

# After processing all characters of frb, append the remaining parts of strings
ans = "".join(ans)
assert len(ans) <= 1e6

k = 0  # Position in frb to track what has been matched
for char in ans:
    if k < len(frb) and frb[k] == char:  # Matched a character in the input string frb
        k += 1

if k < len(frb):
    print("YES")
    print(ans)
else:
    print("NO")


# https://github.com/VaHiX/codeForces/