# Contest 2024, Problem E: C+K+S
# URL: https://codeforces.com/contest/2024/problem/E

import collections
import sys

def kmp_match(pattern, text):
    if not pattern:
        return []
    pi = [0] * len(pattern)
    k_val = 0
    for q in range(1, len(pattern)):
        while k_val > 0 and pattern[k_val] != pattern[q]:
            k_val = pi[k_val-1]
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
            q = pi[q-1]
        if pattern[q] == text[i]:
            q += 1
        else:
            q = 0
        if q == n_pattern:
            occurrences.append(i - n_pattern + 1)
            # After a match, we set q to the longest prefix which is also suffix
            q = pi[q-1] if q > 0 else 0
    return occurrences

def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    output_lines = []
    for _ in range(t):
        n = int(data[index]); k = int(data[index+1]); index += 2
        # Read type array for the first graph
        a = list(map(int, data[index:index+n])); index += n
        m1 = int(data[index]); index += 1
        graph1 = [[] for _ in range(n)]
        for i in range(m1):
            u = int(data[index]); v = int(data[index+1]); index += 2
            graph1[u-1].append(v-1)
        
        b = list(map(int, data[index:index+n])); index += n
        m2 = int(data[index]); index += 1
        graph2 = [[] for _ in range(n)]
        for i in range(m2):
            u = int(data[index]); v = int(data[index+1]); index += 2
            graph2[u-1].append(v-1)
        
        # Check type condition
        countA = sum(1 for x in a if x == 1)
        countB_prime = sum(1 for x in b if x == 0)
        countB = sum(1 for x in b if x == 1)
        countA_prime = n - countA

        if countA != countB_prime or countB != countA_prime:
            output_lines.append("NO")
            continue

        # BFS for graph1
        label1 = [-1] * n
        label1[0] = 0
        queue = collections.deque([0])
        while queue:
            u = queue.popleft()
            for v in graph1[u]:
                if label1[v] == -1:
                    label1[v] = (label1[u] + 1) % k
                    queue.append(v)
                    
        # BFS for graph2
        label2 = [-1] * n
        label2[0] = 0
        queue = collections.deque([0])
        while queue:
            u = queue.popleft()
            for v in graph2[u]:
                if label2[v] == -1:
                    label2[v] = (label2[u] + 1) % k
                    queue.append(v)
                    
        # If both countA and countB are zero, then no cross edges -> YES.
        # But note: type condition ensures countA = countB_prime and countB = countA_prime.
        # If countA==0 then countB_prime==0 and countB = n (which is not zero) and countA_prime = n.
        # So we only skip the frequency condition when at least one of countA or countB is zero.
        if countA == 0 or countB == 0:
            output_lines.append("YES")
            continue

        # Build lists for the four sets
        # U1: outgoing1 in G1 -> (label1[u] + 1) % k
        U1 = []
        for i in range(n):
            if a[i] == 1:
                U1.append((label1[i] + 1) % k)
                
        # T2: incoming2 in G2 -> label2[v] % k
        T2 = []
        for i in range(n):
            if b[i] == 0:
                T2.append(label2[i] % k)
                
        # U2: outgoing2 in G2 -> (label2[w] + 1) % k
        U2 = []
        for i in range(n):
            if b[i] == 1:
                U2.append((label2[i] + 1) % k)
                
        # T1: incoming1 in G1 -> label1[x] % k
        T1 = []
        for i in range(n):
            if a[i] == 0:
                T1.append(label1[i] % k)
                
        # Build frequency arrays of length k for U1, T2, U2, T1.
        A1 = [0] * k
        for x in U1:
            A1[x] += 1
            
        A2 = [0] * k
        for x in T2:
            A2[x] += 1
            
        A3 = [0] * k
        for x in U2:
            A3[x] += 1
            
        A4 = [0] * k
        for x in T1:
            A4[x] += 1
            
        # Condition1: Find d in [0, k-1] such that A1 shifted by d equals A2.
        text1 = A1 + A1   # length 2k
        d1_list = kmp_match(A2, text1)
        d1_set = set(d for d in d1_list if 0 <= d < k)
        
        # Condition2: Find d in [0, k-1] such that A3 shifted by d equals A4.
        text2 = A3 + A3   # length 2k
        d2_list = kmp_match(A4, text2)
        d2_set = set(d for d in d2_list if 0 <= d < k)
        
        # Check: there exists d in d1_set such that (k - d) % k is in d2_set.
        found = False
        for d in d1_set:
            d2_val = (k - d) % k
            if d2_val in d2_set:
                found = True
                break
                
        output_lines.append("YES" if found else "NO")
        
    sys.stdout.write("\n".join(output_lines))

if __name__ == '__main__':
    main()