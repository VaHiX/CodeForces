# Problem: CF 1982 C - Boring Day
# https://codeforces.com/contest/1982/problem/C

"""
Algorithm: Two-pointer sliding window approach
Time Complexity: O(n) where n is the number of cards
Space Complexity: O(1) as we use only a few variables for tracking

The problem asks to find the maximum number of rounds Egor can win,
where each round consists of taking a contiguous subsequence of cards
from the top of the deck such that the sum of the numbers on the cards
in that round is between l and r (inclusive). 

We use a two-pointer approach:
- 'i' marks the start of the current round.
- 'j' marks the end of the current round.
- 'current_sum' tracks the sum of cards in the current round.
- We incrementally expand the window by moving 'j' when the sum is less than 'l',
  and shrink it by moving 'i' when the sum is greater than 'r'.
- When we find a valid range [i, j) where sum is between l and r, 
  we increment the win count, reset the window, and continue.
"""

def process_test_case(n, l, r, a):
    i = j = 0
    current_sum = 0
    count = 0
    while i < n and j <= n:
        if l <= current_sum <= r:  # If current sum is within the win range
            count += 1
            current_sum = 0
            i = j  # Move the start of the next round to the current end
        elif current_sum < l:  # If current sum is less than l, expand the window
            if j < n:
                current_sum += a[j]
                j += 1
            else:
                break
        else:  # If current sum is greater than r, shrink the window
            current_sum -= a[i]
            i += 1
            if i > j:
                j = i
                current_sum = 0
    return count


def main():
    import sys

    t = int(sys.stdin.readline())
    for _ in range(t):
        while True:
            line = sys.stdin.readline()
            if line.strip():
                n, l, r = map(int, line.strip().split())
                break
        a = []
        while len(a) < n:
            line = sys.stdin.readline()
            if line.strip():
                a.extend(map(int, line.strip().split()))
        result = process_test_case(n, l, r, a)
        print(result)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/