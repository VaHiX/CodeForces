# Problem: CF 1907 B - YetnotherrokenKeoard
# https://codeforces.com/contest/1907/problem/B

"""
Algorithm: Process string from right to left, keeping track of how many backspace operations (b or B) are pending.
For each character:
- If it's 'b' or 'B', increment the respective counter (il for lowercase, ul for uppercase).
- If it's a letter:
  - For uppercase: if ul > 0, decrement ul; otherwise, add to result.
  - For lowercase: if il > 0, decrement il; otherwise, add to result.
Time Complexity: O(n) where n is the total length of the input string across all test cases.
Space Complexity: O(n) for storing the temporary result list.
"""

import sys


def out(v):
    sys.stdout.write(v)


import sys


def main():
    test = int(sys.stdin.readline().strip())
    for t in range(test):
        s = sys.stdin.readline().strip()
        temp = []
        il = 0  # Count of pending lowercase backspaces
        ul = 0  # Count of pending uppercase backspaces
        for i in s[::-1]:  # Iterate from right to left
            if i == "B":
                ul += 1  # Increment uppercase backspace counter
            elif i == "b":
                il += 1  # Increment lowercase backspace counter
            elif i.isupper():
                if ul > 0:
                    ul -= 1  # Use up one uppercase backspace
                else:
                    temp.append(i)  # Add to result if no backspace to consume
            elif i.islower():
                if il > 0:
                    il -= 1  # Use up one lowercase backspace
                else:
                    temp.append(i)  # Add to result if no backspace to consume
        print("".join(temp[::-1]))  # Reverse and print the result


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/