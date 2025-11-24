# Problem: CF 949 A - Zebras
# https://codeforces.com/contest/949/problem/A

"""
Algorithm: Greedy approach to partition string into zebras
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(n) for storing the subsequences

The algorithm works by maintaining two lists of subsequences:
- q[0]: list of subsequences ending with '0' (bad day)
- q[1]: list of subsequences ending with '1' (good day)

For each character in the string:
1. If we encounter a '0', we either start a new subsequence (if no existing subsequence ends with '1')
   or append this '0' to an existing subsequence ending with '1' and remove that subsequence from q[1]
2. If we encounter a '1', we must append it to an existing subsequence ending with '0', 
   otherwise it's impossible to form a valid zebra (since zebra must start and end with '0')

After processing all characters, if there are any subsequences ending with '1', 
it means we couldn't form valid zebras, return -1.
Else, the answer is the list of subsequences ending with '0'.
"""

import sys

s = sys.stdin.readline().strip()
q = [[], []]  # q[0] stores subsequences ending with '0', q[1] stores subsequences ending with '1'
for i, c in enumerate(s):
    k = int(c)  # Convert character to integer (0 or 1)
    if not q[1 - k]:  # If no subsequence ends with the opposite character
        if k == 1:  # If current character is '1' (good day) but no subsequence ends with '0' (bad day)
            sys.stdout.write("-1")  # Cannot form a valid zebra
            sys.exit(0)
        q[k].append([i + 1])  # Start new subsequence with current index
    else:
        # Append current index to existing subsequence ending with opposite character
        q[k].append(q[1 - k].pop())  # Remove subsequence from q[1-k] and add index to q[k]
        q[k][-1].append(i + 1)  # Append index to the last subsequence in q[k]
if q[1]:  # If there are subsequences ending with '1'
    sys.stdout.write("-1")  # Not all characters can be part of valid zebras
else:
    ans = [str(len(q[0]))]  # Number of zebras
    for it in q[0]:  # For each zebra subsequence
        ans.append(f'{len(it)} {" ".join(map(str, it))}')  # Format output
    sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/