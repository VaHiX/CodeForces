# Problem: CF 1721 E - Prefix Function Queries
# https://codeforces.com/contest/1721/problem/E

"""
Prefix Function Queries

This problem involves computing the prefix function (also known as the failure function) for the concatenation of two strings, s and t.
The prefix function p[i] for a string is the length of the longest proper prefix which is also a suffix for the substring ending at position i.

Approach:
- Preprocess the string s to compute its prefix function.
- For each query t, compute the prefix function for s + t, but only output the values from position |s|+1 to |s|+|t|.
- Use an incremental algorithm to update the prefix function efficiently.

Time Complexity: O(|s| + sum of |t| across all queries)
Space Complexity: O(|s| + max(|t|)) - for storing string and prefix function array
"""

def get_next(j, k, nxt, p):
    # Compute the prefix function for string p
    # j: current index in p
    # k: current match length
    # nxt: prefix function array
    # p: the string being processed
    while p[j] != "$":  # While not at the end of string
        if k == -1 or p[j] == p[k]:  # If character matches or at start
            j += 1  # Move to next character
            k += 1  # Increase match length
            if p[j] == p[k]:  # If next characters are equal
                # Use previously computed value to avoid recomputation
                nxt[j] = nxt[k]
            else:
                # Set to current match length
                nxt[j] = k
        else:
            # Fall back using the prefix function
            k = nxt[k]
    return j, k, nxt


def solve():
    s = input().strip()  # Read the base string s

    len_s = len(s)
    ns = [ch for ch in s]  # Convert to list for mutability
    for i in range(11):  # Add padding for safety
        ns.append("$")

    j, k, nxt = get_next(0, -1, [-1 for i in range(len(ns))], ns)

    q = int(input().strip())  # Read number of queries
    for _ in range(q):
        t = input().strip()  # Read query string t
        ans = []

        # Reset the end part of ns to "$" for correct computation
        for i in range(10):
            ns[i + len_s] = "$"

        # Process each character of t
        for i in range(len(t)):
            ns[i + len_s] = t[i]  # Append character of t to ns

            # Reuse prefix function computation from previous step
            nj, nk, n_nxt = get_next(j, k, nxt, ns)

            ans.append(n_nxt[len_s + i + 1])  # Record result at correct position
        print(" ".join(map(str, ans)))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/