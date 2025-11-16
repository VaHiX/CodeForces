# Problem: CF 1876 A - Helmets in Night Light
# https://codeforces.com/contest/1876/problem/A

"""
Algorithm: Greedy approach to minimize the cost of spreading information.
Techniques: Sorting, greedy selection based on cost per share, and simulation of information propagation.

Time Complexity: O(n log n) due to sorting of the residents based on their sharing cost.
Space Complexity: O(n) for storing the list of residents and auxiliary variables.

This solution uses a greedy strategy to determine the optimal way to spread the announcement:
1. First, Pak Chanek directly informs some residents (cost p each).
2. Then, the informed residents use their helmets to spread the message further, 
   choosing the cheapest way to propagate the message at each step.
3. The greedy choice is based on minimizing the cost per additional person informed.
"""

def single(n, p, a, b):
    all_len = n
    person_list = list(range(all_len))
    # Sort residents by their sharing cost (b[i]) to prioritize cheaper propagators
    person_list.sort(key=lambda x: b[x])
    cost = p  # Cost of direct announcement to one person
    informed_len = 1  # Start with one person informed (Pak Chanek)
    front = 0
    while informed_len < all_len:
        index = person_list[front]
        item_a = a[index]  # Maximum number of people this resident can inform
        item_b = b[index]  # Cost per share for this resident
        # If sharing cost is less than direct cost, it's beneficial to use helmet
        if item_b < p:
            # If this resident can inform enough people to cover the rest
            if item_a < all_len - informed_len:
                informed_len += item_a
                cost += item_a * item_b  # Add total cost for sharing
            else:
                # Can't cover all remaining, inform the rest at current cost
                rest_len = all_len - informed_len
                cost += rest_len * item_b
                break
        else:
            # If sharing cost exceeds direct cost, just inform the rest directly
            rest_len = all_len - informed_len
            cost += rest_len * p
            break
        front += 1
    return cost


def main():
    test_num = int(input())
    for _ in range(test_num):
        first_line = [int(i) for i in input().split(" ")]
        n = first_line[0]
        p = first_line[1]
        a = [int(i) for i in input().split(" ")]
        b = [int(i) for i in input().split(" ")]
        print(single(n, p, a, b))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/