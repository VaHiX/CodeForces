# Problem: CF 2024 E - C+K+S
# https://codeforces.com/contest/2024/problem/E

"""
E. C+K+S

This problem involves determining whether it's possible to construct a bipartite matching between two strongly connected directed graphs such that:
1. Each outgoing vertex in the first graph has exactly one outgoing edge to the second graph.
2. Each incoming vertex in the second graph has exactly one incoming edge from the first graph.
3. The resulting graph maintains cycle lengths divisible by k.

Key techniques used:
- Graph labeling using BFS to assign labels modulo k to vertices based on their connectivity
- KMP string matching algorithm for pattern matching of label sequences
- Set intersection to find valid label alignments

Time Complexity: O(n + m1 + m2) per test case, where n is number of vertices and m1, m2 are edges in each graph.
Space Complexity: O(n + k) for storing labels and KMP tables.
"""

import collections
import sys


def kmp_match(pattern, text):
    if not pattern:
        return []
    pi = [0] * len(pattern)
    k_val = 0
    for q in range(1, len(pattern)):
        while k_val > 0 and pattern[k_val] != pattern[q]:
            k_val = pi[k_val - 1]
        if pattern[k_val] == pattern[q]:
            k_val += 1
        else:
            k_val = 0
        pi[q] = k_val
    q = 0
    occurrences = []
    n_pattern = len(pattern)
    for i in range(len(text)):
        while q > 0 and pattern[q] != text[i]:
            q = pi[q - 1]
        if pattern[q] == text[i]:
            q += 1
        else:
            q = 0
        if q == n_pattern:
            occurrences.append(i - n_pattern + 1)
            q = pi[q - 1] if q > 0 else 0
    return occurrences


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    output_lines = []
    for _ in range(t):
        n = int(data[index])
        k = int(data[index + 1])
        index += 2
        a = list(map(int, data[index : index + n]))
        index += n
        m1 = int(data[index])
        index += 1
        graph1 = [[] for _ in range(n)]
        for i in range(m1):
            u = int(data[index])
            v = int(data[index + 1])
            index += 2
            graph1[u - 1].append(v - 1)
        b = list(map(int, data[index : index + n]))
        index += n
        m2 = int(data[index])
        index += 1
        graph2 = [[] for _ in range(n)]
        for i in range(m2):
            u = int(data[index])
            v = int(data[index + 1])
            index += 2
            graph2[u - 1].append(v - 1)
        countA = sum(1 for x in a if x == 1)
        countB_prime = sum(1 for x in b if x == 0)
        countB = sum(1 for x in b if x == 1)
        countA_prime = n - countA
        # Check basic compatibility of types
        if countA != countB_prime or countB != countA_prime:
            output_lines.append("NO")
            continue
        label1 = [-1] * n
        label1[0] = 0
        queue = collections.deque([0])
        while queue: # BFS to assign labels based on cycle constraint modulo k
            u = queue.popleft()
            for v in graph1[u]:
                if label1[v] == -1:
                    label1[v] = (label1[u] + 1) % k
                    queue.append(v)
        label2 = [-1] * n
        label2[0] = 0
        queue = collections.deque([0])
        while queue: # BFS to assign labels based on cycle constraint modulo k
            u = queue.popleft()
            for v in graph2[u]:
                if label2[v] == -1:
                    label2[v] = (label2[u] + 1) % k
                    queue.append(v)
        if countA == 0 or countB == 0:
            output_lines.append("YES")
            continue
        # Prepare sequences of labels for matching based on types
        U1 = []
        for i in range(n):
            if a[i] == 1:
                U1.append((label1[i] + 1) % k)
        T2 = []
        for i in range(n):
            if b[i] == 0:
                T2.append(label2[i] % k)
        U2 = []
        for i in range(n):
            if b[i] == 1:
                U2.append((label2[i] + 1) % k)
        T1 = []
        for i in range(n):
            if a[i] == 0:
                T1.append(label1[i] % k)
        A1 = [0] * k
        for x in U1: # Create frequency array of labels from outgoing vertices of graph1
            A1[x] += 1
        A2 = [0] * k
        for x in T2: # Create frequency array of labels from incoming vertices of graph2
            A2[x] += 1
        A3 = [0] * k
        for x in U2: # Create frequency array of labels from outgoing vertices of graph2
            A3[x] += 1
        A4 = [0] * k
        for x in T1: # Create frequency array of labels from incoming vertices of graph1
            A4[x] += 1
        text1 = A1 + A1
        d1_list = kmp_match(A2, text1)
        d1_set = set(d for d in d1_list if 0 <= d < k) # Valid alignment shifts for matching sequence 1
        text2 = A3 + A3
        d2_list = kmp_match(A4, text2)
        d2_set = set(d for d in d2_list if 0 <= d < k) # Valid alignment shifts for matching sequence 2
        found = False
        for d in d1_set:
            d2_val = (k - d) % k
            if d2_val in d2_set:
                found = True
                break
        output_lines.append("YES" if found else "NO")
    sys.stdout.write("\n".join(output_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/