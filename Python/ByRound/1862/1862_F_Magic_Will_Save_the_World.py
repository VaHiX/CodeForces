# Problem: CF 1862 F - Magic Will Save the World
# https://codeforces.com/contest/1862/problem/F

"""
Algorithm: Binary Search with Bitmasking
Purpose: Find minimum time to defeat all monsters using water and fire magic.
Time Complexity: O(log(S) * (n + log(S))) where S is the sum of monster strengths
Space Complexity: O(1) excluding input storage

Approach:
- Binary search on time (seconds needed)
- For each time t:
  - Compute how much mana Vika can accumulate: w*t (water), f*t (fire)
  - Use bitmask to represent possible sums of monster strengths
  - Check if it's possible to form a subset of monsters with total strength <= available mana
"""

def main():
    import sys

    input = sys.stdin.read().split()
    ptr = 0
    t = int(input[ptr])
    ptr += 1
    for _ in range(t):
        w = int(input[ptr])
        f = int(input[ptr + 1])
        ptr += 2
        n = int(input[ptr])
        ptr += 1
        s_list = list(map(int, input[ptr : ptr + n]))
        ptr += n
        sum_s = sum(s_list)
        # Create a bitmask representing all possible subset sums
        bitmask = 1
        for s in s_list:
            bitmask |= bitmask << s
        upper1 = (sum_s + w - 1) // w
        upper2 = (sum_s + f - 1) // f
        initial_upper = max(upper1, upper2)
        low, high = 0, initial_upper
        while low < high:
            mid = (low + high) // 2
            L = max(0, sum_s - mid * f)  # Minimum required strength for fire
            U = mid * w  # Maximum possible strength from water
            current_upper = min(U, sum_s)
            if L > current_upper:
                feasible = False
            else:
                # Create a mask that marks all possible sums from L to current_upper
                mask = ((1 << (current_upper + 1)) - 1) ^ ((1 << L) - 1)
                feasible = (bitmask & mask) != 0
            if feasible:
                high = mid
            else:
                low = mid + 1
        print(low)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/