// Problem: CF 2112 D - Reachability and Tree
// https://codeforces.com/contest/2112/problem/D

/*
 * Problem: D. Reachability and Tree
 *
 * Purpose:
 *   Given an undirected tree with n vertices, determine if it's possible to direct all edges such that
 *   exactly n ordered pairs (u, v) exist where there is a directed path from u to v.
 *
 * Algorithm:
 *   - If the tree has a vertex with degree 2, we can orient edges so that the number of good pairs is exactly n.
 *     We treat this vertex as a "pivot" and direct edges away from it toward its neighbors.
 *   - Then, for each neighbor of the pivot, we perform DFS to orient all remaining edges in a way that
 *     respects the condition of getting exactly n good pairs.
 *
 * Time Complexity: O(n) per test case — linear traversal of edges and vertices.
 * Space Complexity: O(n) — for storing adjacency list, visited array, stack, etc.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter

data class StackElem(val u: Int, val parent: Int, val source: Boolean)

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val out = PrintWriter(System.out)
    val T = br.readLine().toInt()
    
    repeat(T) {
        val n = br.readLine().toInt()
        val g = Array(n + 1) { mutableListOf<Pair<Int, Int>>() }
        
        // Build adjacency list with edge indices
        for (eid in 0 until n - 1) {
            val (u, v) = br.readLine().split(" ").map { it.toInt() }
            g[u].add(Pair(v, eid))
            g[v].add(Pair(u, eid))
        }
        
        var pivot = -1
        // Find a vertex with degree 2 — this is the key for forming correct orientation
        for (i in 1..n) {
            if (g[i].size == 2) {
                pivot = i
                break
            }
        }
        
        if (pivot == -1) {
            out.println("NO")
        } else {
            val a = g[pivot][0].first
            val idA = g[pivot][0].second
            val b = g[pivot][1].first
            val idB = g[pivot][1].second
            
            val vis = BooleanArray(n - 1) { false } // Track processed edges
            val orient = mutableListOf<Pair<Int, Int>>()
            
            // Mark edges to pivot as visited and add their directed form to result
            vis[idA] = true
            vis[idB] = true
            orient.add(Pair(a, pivot))  // Direct from a to pivot
            orient.add(Pair(pivot, b))  // Direct from pivot to b
            
            val stack = ArrayDeque<StackElem>()
            
            // Push neighbors with their direction flags (source indicates if we came from this node)
            stack.addLast(StackElem(a, pivot, true))
            stack.addLast(StackElem(b, pivot, false))
            
            while (stack.isNotEmpty()) {
                val (u, parent, source) = stack.removeLast()
                
                // Traverse neighbors of current node
                for ((v, eid) in g[u]) {
                    if (vis[eid]) continue  // Skip already processed edges
                    
                    vis[eid] = true
                    
                    // According to the orientation logic, direct edges to maintain n good pairs
                    if (source) {
                        orient.add(Pair(u, v))  // Direct from u to v
                        stack.addLast(StackElem(v, u, false))  // Mark next traversal direction
                    } else {
                        orient.add(Pair(v, u))  // Direct from v to u
                        stack.addLast(StackElem(v, u, true))   // Mark next traversal direction
                    }
                }
            }
            
            out.println("YES")
            for ((u, v) in orient) {
                out.println("$u $v")
            }
        }
    }
    out.flush()
}


// https://github.com/VaHiX/CodeForces/