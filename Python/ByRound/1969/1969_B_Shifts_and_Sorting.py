# Problem: CF 1969 B - Shifts and Sorting
# https://codeforces.com/contest/1969/problem/B

"""
Algorithm: Greedy approach to find minimum cost to sort binary string
Techniques: Single pass through the string, tracking transitions from '0' to '1' and vice versa

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables for tracking

The key insight is to count how many "10" transitions there are, because each such transition
requires a shift operation to move the '0' to the right of the '1'. For each such pair,
the minimum cost is the length of the substring that needs to be shifted.
"""

def main():
    t = int(input())
    for _ in range(t):
        s = input()
        rezh = 0  # State to track whether we're in a sequence of 1's
        sum_val = 0  # Total cost
        stoi = 0  # Counter for current sequence length of 1's
        for char in s:
            if rezh == 1:  # If we are currently in a sequence of 1's
                stoi += 1  # Increment the count
                if char == "0":  # If we hit a 0, we must shift this 0 to the right
                    sum_val += stoi  # Add the cost of shifting the current sequence of 1's plus this 0
                    stoi -= 1  # Decrement because we've accounted for one element (the 0 we just shifted)
            else:  # If we are not in a sequence of 1's
                if char == "1":  # If we hit a 1, start counting
                    rezh = 1  # Change state to in-sequence of 1's
                    stoi += 1  # Increment counter
        print(sum_val)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/