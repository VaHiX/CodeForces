# Problem: CF 1920 B - Summation Game
# https://codeforces.com/contest/1920/problem/B

"""
Purpose: Solve the Summation Game problem where Alice removes up to k elements and Bob multiplies up to x elements by -1,
         to optimize the final sum. The goal is to find the maximum possible sum after both players play optimally.
Algorithms/Techniques: 
    - Sorting the array in descending order to prioritize larger elements.
    - Using a sliding window approach to simulate Bob's optimal choice of flipping signs.
    - Iterating through all valid combinations of Alice's removals and Bob's flips.

Time Complexity: O(n log n) due to sorting; the rest of the operations are linear.
Space Complexity: O(1) excluding input storage, as we use only a few variables for computation.
"""

def solve():
    n, k, x = map(int, input().split())  # Read n, k, x
    a = list(map(int, input().split()))  # Read array elements
    a.sort(reverse=True)  # Sort in descending order to prioritize large elements
    
    s = sum(a)  # Initial sum of all elements
    
    # Initially, Bob flips the first x elements (largest ones) to negative
    for i in range(x):
        s -= a[i] * 2  # Subtract twice the value because we're flipping it from positive to negative
    
    m = s  # Initialize maximum sum with current sum
    
    # Try all valid positions for Alice to remove elements
    for i in range(k):
        s += a[i]  # Add the removed element back to sum
        
        # If there's an element to potentially flip (i + x < n), update the sum by removing it from the flipped set
        if (i + x) < n:
            s -= a[i + x] * 2  # Remove the element that is now flipped in the next round
        
        m = max(m, s)  # Update maximum sum found so far
    
    print(m)


def main():
    n = int(input())
    for _ in range(n):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/