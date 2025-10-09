// Problem: CF 2124 I - Lexicographic Partition
// https://codeforces.com/contest/2124/problem/I

/*
 * Problem: Lexicographic Partition
 * 
 * Description:
 * Given an array x of length n, determine if there exists a permutation a such that 
 * f([a_1, a_2, ..., a_i]) = x_i for each 1 <= i <= n.
 * 
 * Algorithm:
 * - Uses a stack-based approach with a greedy assignment strategy.
 * - Each element x[i] represents the maximum depth in the tree-like structure of the permutation.
 * - The solution builds a tree traversal order and assigns values to elements based on their depth.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Stack-based simulation
 * - Greedy assignment of indices
 * - Tree traversal logic
 */

import java.io.*;
import java.util.*;

public class LexicographicPartition {
    static class Node {
        int l, r, left, right, ok;
        Node(int l, int r, int left, int right, int ok) {
            this.l = l; this.r = r;
            this.left = left; this.right = right;
            this.ok = ok;
        }
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine().trim());
        StringBuilder output = new StringBuilder();
        
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());
            String[] parts = br.readLine().split(" ");
            int[] x = new int[n];
            for (int i = 0; i < n; i++) x[i] = Integer.parseInt(parts[i]);
            
            // Create inverse mapping: for each depth, store indices of elements at that depth
            List<List<Integer>> inv = new ArrayList<>();
            for (int i = 0; i <= n + 2; i++) {
                inv.add(new ArrayList<>());
            }
            
            for (int i = 0; i < n; i++) {
                int depth = x[i];
                if (depth < 1 || depth > n+1) continue;
                inv.get(depth).add(i);
            }
            
            // Check if root exists at depth 1 and is unique
            if (inv.get(1).size() != 1) {
                output.append("NO\n");
                continue;
            }
            
            int[] a = new int[n];
            Deque<Node> stack = new ArrayDeque<>();
            
            // Initialize root assignment
            if (inv.get(2).size() > 1) {
                a[0] = 1;
                stack.push(new Node(0, n-1, 2, n, 1));
            } else {
                a[0] = n;
                stack.push(new Node(0, n-1, 1, n-1, 1));
            }
            
            boolean bad = false;
            while (!stack.isEmpty() && !bad) {
                Node cur = stack.pop();
                int l = cur.l, r = cur.r;
                int leftNum = cur.left, rightNum = cur.right, ok = cur.ok;
                
                if (l == r) continue;
                
                // Validate sequence monotonicity
                if (l + 1 > r || x[l+1] != x[l] + 1) {
                    bad = true;
                    break;
                }
                
                int num = x[l] + 1;
                if (num >= inv.size()) { 
                    bad = true; 
                    break; 
                }
                
                // Collect children at next depth
                List<Integer> children = new ArrayList<>();
                List<Integer> listNum = inv.get(num);
                while (!listNum.isEmpty() && listNum.get(listNum.size()-1) > l) {
                    children.add(listNum.remove(listNum.size()-1));
                }
                
                if (children.isEmpty()) {
                    bad = true;
                    break;
                }
                
                // Ensure consistency of assignment when ok == 0
                if (ok == 0 && children.size() != 1) {
                    bad = true;
                    break;
                }
                
                if (children.size() == 1) {
                    int child = children.get(0);
                    List<Integer> nextList = (num+1 < inv.size() ? inv.get(num+1) : null);
                    if (nextList != null && nextList.size() > 1
                        && nextList.get(nextList.size()-2) > l) {
                        a[child] = leftNum++; // Assign from left
                    } else {
                        a[child] = rightNum--; // Assign from right
                    }
                    stack.push(new Node(l+1, r, leftNum, rightNum, 1));
                } else {
                    rightNum -= children.size(); // Adjust right boundary
                    int nx = rightNum + 1;
                    Collections.reverse(children); // Reverse for correct assignment order
                    
                    int curLeft = leftNum;
                    for (int i = 0; i < children.size(); i++) {
                        int pos = children.get(i);
                        a[pos] = nx++;
                        
                        int nextInd = (i+1 < children.size() ? children.get(i+1) - 1 : r);
                        int sz = nextInd - pos - 1;
                        stack.push(new Node(pos, nextInd, curLeft, curLeft + sz, 0));
                        curLeft += sz + 1;
                    }
                }
            }
            
            if (bad) {
                output.append("NO\n");
            } else {
                output.append("YES\n");
                for (int i = 0; i < n; i++) {
                    output.append(a[i]).append(i+1 < n ? ' ' : '\n');
                }
            }
        }
        System.out.print(output);
    }
}


// https://github.com/VaHiX/CodeForces/