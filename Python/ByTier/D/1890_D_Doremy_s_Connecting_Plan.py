# Problem: CF 1890 D - Doremy's Connecting Plan
# https://codeforces.com/contest/1890/problem/D

"""
Algorithm: Greedy approach to determine if a graph can be connected based on the given condition.
Time Complexity: O(n) for each test case, where n is the number of cities.
Space Complexity: O(1) as we only use a few variables for computation.

The approach is to simulate the process of connecting nodes. We maintain a running sum of people 
in the current component and check if we can connect the next node. If we can, we update our 
component. We keep track of the last node that was successfully connected. If that node is the 
last one (n-1), then the graph can be connected.

Key steps:
1. Start with the first node as the initial component.
2. For each subsequent node, check if adding it to the current component is valid.
3. Update the component size if valid.
4. Check if the last node was successfully connected.
"""

def fun1():
    t = int(input())
    results = []
    while t > 0:
        results.append(fun2())
        t -= 1
    for result in results:
        print(result)


def fun2():
    n, c = map(int, input().split())
    a = list(map(int, input().split()))
    return fun3(n, c, a)


def fun3(n, c, a):
    s = t = a[0]  # s is the sum of people in current component, t tracks total sum
    last = 0      # tracks the last successfully connected node
    j = 1         # current node index being considered
    while j < n:
        t += a[j]  # add current node's people to total
        # Check if we can connect node j with the current component
        if a[j] + s >= c * (j + 1):
            s = t  # update component sum
            last = j  # mark this node as successfully connected
        j += 1
    # If last node is connected, the graph is connected
    return "Yes" if last == n - 1 else "No"


fun1()


# https://github.com/VaHiX/CodeForces/