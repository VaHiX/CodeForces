# Problem: CF 1697 D - Guess The String
# https://codeforces.com/contest/1697/problem/D

"""
Algorithm: Interactive String Guessing
Approach:
- Use queries of type 1 to get individual characters.
- Use queries of type 2 to get the number of distinct characters in a range.
- Maintain a dictionary mapping characters to their last seen positions.
- For each new character, use binary search on the known characters to determine
  which character is at the current position based on the count of distinct characters
  in a range ending at the current position.

Time Complexity: O(n * log(k)) where k is at most 26 (number of distinct characters).
Space Complexity: O(n) for storing the string and the position map.
"""

def ask_char(i):
    print("? 1", i + 1, flush=True)
    return input()


def ask_inteval(l, r):
    print("? 2", l + 1, r + 1, flush=True)
    return int(input())


mx_pos = {}
n = int(input())
s = ask_char(0)
mx_pos[s[0]] = 0

last = 1
for i in range(1, n):
    now = ask_inteval(0, i)
    if now > last:
        # If the number of distinct characters increased, we found a new character
        ch = ask_char(i)
        s += ch
        last = now
        mx_pos[ch[0]] = i
        continue

    # Binary search to find the character at position i
    keys = sorted(mx_pos, key=lambda x: mx_pos[x])
    ans = ""
    l, r = 0, len(mx_pos) - 1
    while l <= r:
        m = (l + r) >> 1
        # Query the number of distinct characters in the range from the last occurrence of keys[m] to i
        cnt = ask_inteval(mx_pos[keys[m]], i)
        if cnt + m == now:
            # This key is not the one at position i
            l = m + 1
            ans = keys[m]
        else:
            # This key might be the one at position i
            r = m - 1

    mx_pos[ans] = i
    s += ans
    last = now

print("!", s, flush=True)


# https://github.com/VaHiX/CodeForces/