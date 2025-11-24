# Problem: CF 1746 A - Maxmina
# https://codeforces.com/contest/1746/problem/A

# Flowerbox:
# Purpose: Determine if a binary array of 0s and 1s can be reduced to a single 1 using two types of operations.
# Algorithm/Techniques: Greedy simulation with key observation that:
#   - Operation 1 (min): removes two elements, keeps min; reduces size by 1
#   - Operation 2 (max): removes k elements, keeps max; reduces size by k-1
# Key insight: To produce a final 1, there must be at least one 1 in the array.
#   But more importantly, we need to check if there exists a way to group elements so that
#   we end up with 1 using type 2 operations and then reduce it to 1 using type 1.
# Time Complexity: O(n) per test case (linear scan)
# Space Complexity: O(1) (no extra space used apart from input reading)

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skipping n,k and empty lines)
    print("NYOE S"["1" in s :: 2])  # Check if '1' exists in the current line:
                                    # If '1' is in s, "1" in s evaluates to True -> index = 1
                                    # Then slice "NYOE S"[1::2] = "Y S"
                                    # Else index = 0 -> slice "NYOE S"[0::2] = "N O"
                                    # So result is "YES" or "NO" based on existence of '1'


# https://github.com/VaHiX/codeForces/