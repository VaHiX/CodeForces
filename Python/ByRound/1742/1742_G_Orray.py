# Problem: CF 1742 G - Orray
# https://codeforces.com/contest/1742/problem/G

"""
Algorithm: Greedy approach to maximize lexicographically the prefix OR array.
Approach:
1. Start with an empty result list `r` and a cumulative OR `c` initialized to 0.
2. While the input array `a` is not empty:
   - Sort `a` in descending order based on the value of `i | c` (bitwise OR with current cumulative OR).
     This ensures we pick elements that will increase the OR the most.
   - Pop the largest element (after sorting) and add it to `r`.
   - Update `c` with the OR of `c` and the selected element.
   - If the OR doesn't change (i.e., `check == c`), break early.
3. Output the result list `r` followed by remaining elements in `a` (which are all 0s or have no effect).

Time Complexity: O(n^2 * log(n)) in worst case due to sorting inside loop
Space Complexity: O(n) for storing the array and result

"""

for _ in range(int(input())):
    n, a, r, c = int(input()), list(map(int, input().split())), [], 0
    while a:
        # Sort by the value of i | c in descending order to pick elements that maximize OR the most
        a.sort(key=lambda i: i | c)  # Sorting step
        r.append(a.pop())  # Take the element that maximizes the prefix OR
        check = c | r[-1]  # Compute new OR
        if check == c:  # If OR does not change, no point continuing
            break
        c = check  # Update cumulative OR
    print(*r, *a)  # Print result followed by remaining elements


# https://github.com/VaHiX/CodeForces/