# Problem: CF 1684 H - Hard Cut
# https://codeforces.com/contest/1684/problem/H

"""
Algorithm: Hard Cut
Purpose: Given a binary string, partition it into non-overlapping substrings such that their sum in base 10 is a power of 2.
Approach:
- If the count of '1's is 0, return -1 (impossible to form a power of 2).
- If count of '1's is already a power of 2, each character is a separate substring.
- Otherwise, use a randomized greedy strategy to try and construct a valid partition:
  - Use a suffix count array to efficiently check remaining '1's.
  - Try multiple power-of-2 targets (ty) by left-shifting until solution is found.
  - For each try, use a random window size to greedily form substrings with bits.
  - If a valid partition is found, output the segments.

Time Complexity: O(T * n * log(n)) 
Space Complexity: O(n)
"""
import random
import sys


def main():
    input = sys.stdin.read().split()
    idx = 0
    T = int(input[idx])
    idx += 1
    for _ in range(T):
        s = input[idx]
        idx += 1
        n = len(s)
        v = s.count("1")
        if v == 0:
            print(-1)
            continue
        ans = []

        # If number of 1s is already a power of 2, each 1 is alone
        if (v & (v - 1)) == 0:
            for i in range(n):
                ans.append((i + 1, i + 1))
            print(len(ans))
            for seg in ans:
                print(seg[0], seg[1])
            continue

        # Start with a power of 2 greater than number of 1s
        ty = 1 << (v.bit_length())
        found = False
        while not found:

            # Build suffix array for counting 1s from right to left
            suffix = [0] * (n + 2)
            for i in range(n - 1, -1, -1):
                suffix[i] = suffix[i + 1] + (1 if s[i] == "1" else 0)

            for _ in range(30):
                current_ans = []
                rem = ty
                i = 0
                valid = True
                while i < n:
                    if s[i] == "0":
                        current_ans.append((i + 1, i + 1))
                        i += 1
                        continue

                    # Random window size for choosing 1s
                    window = random.randint(3, 5)
                    max_j = min(i + window, n)

                    best_j = i
                    nt = 0
                    # Find the best valid substring ending at or before max_j
                    for j in range(i, max_j):
                        nt = (nt << 1) | (1 if s[j] == "1" else 0)
                        if rem - nt < suffix[j + 1]:
                            break
                        best_j = j

                    # Recalculate the actual number from the best segment
                    nt = 0
                    for j in range(i, best_j + 1):
                        nt = (nt << 1) | (1 if s[j] == "1" else 0)
                    rem -= nt
                    current_ans.append((i + 1, best_j + 1))
                    i = best_j + 1
                    if rem < 0:
                        valid = False
                        break
                if valid and rem == 0:
                    ans = current_ans
                    found = True
                    break
            ty <<= 1  # Try next power of 2
        print(len(ans))
        for seg in ans:
            print(seg[0], seg[1])


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/