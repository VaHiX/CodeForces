// Problem: CF 2107 D - Apple Tree Traversing
// https://codeforces.com/contest/2107/problem/D

/*
 * Problem: D. Apple Tree Traversing
 * 
 * Purpose:
 *   Given a tree with n nodes, each initially containing one apple, we repeatedly find
 *   the "apple path" (a path where all nodes have apples), write down (d,u,v) to a paper,
 *   and remove apples along that path. Goal is to maximize the lexicographically 
 *   largest sequence of (d, u, v) values.
 * 
 * Algorithm:
 *   - For each connected component of remaining apples (initially all nodes),
 *     we find the diameter of the tree (longest path).
 *   - This is done using two DFS traversals:
 *       1. Start from any node and find the farthest node (first end of diameter)
 *       2. From that farthest node, find another farthest node (second end of diameter)
 *     Diameter = number of nodes on this path.
 *   - Add this diameter as the first element in the priority queue.
 *   - Remove all nodes in this path from consideration, updating parent pointers for traversal.
 *   - Repeat until no apples are left.
 * 
 * Time Complexity: O(n^2) worst case due to repeated DFS, but can be optimized.
 * Space Complexity: O(n) for storing tree, parents, and intermediate structures.
 */
import java.util.PriorityQueue

fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    
    // DFS function to find the depth and last node in a path
    fun dfs(
        u: Int,
        parent: Int,
        parents: IntArray,
        rem: MutableSet<Int>,
        g: List<List<Int>>
    ): Pair<Int, Int> {
        var d = 1               // Depth starts at 1
        var last = u            // Last node in current branch
        parents[u] = parent     // Set the parent of current node
        
        for (v in g[u]) {       // Traverse neighbors
            if (v == parent || !rem.contains(v)) continue   // Skip parent and removed nodes
            
            val (ud, ulast) = dfs(v, u, parents, rem, g)    // Recursive call to child
            
            if (ud + 1 > d) {               // Update maximum depth
                d = ud + 1
                last = ulast
            }
            if (ud + 1 == d) last = maxOf(last, ulast)
        }
        
        return d to last        // Return max depth and farthest node
    }
    
    repeat(cin.readLine().toInt()) {
        val n = cin.readLine().toInt()
        val t = List(n + 1) { mutableListOf<Int>() }     // Tree structure
        
        repeat(n - 1) {                                 // Read edges
            val (u, v) = cin.readLine().split(" ").map { it.toInt() }
            t[u].add(v)
            t[v].add(u)
        }
        
        // Priority queue to store triplets in descending lexicographical order
        val q = PriorityQueue<Triple<Int, Int, Int>> { x, y ->
            if (x.first != y.first) y.first.compareTo(x.first)
            else if (x.second != y.second) y.second.compareTo(x.second)
            else y.third.compareTo(x.third)
        }
        
        val parents = IntArray(n + 1)    // Parents array for tree traversal
        val rem = (1..n).toMutableSet()  // Remaining apples
        var usedcnt = 0                  // Count of processed nodes
        
        while (rem.size > 0) {
            val u = rem.first()          // Pick arbitrary node
            
            val (_, last1) = dfs(u, -1, parents, rem, t)    // First DFS finds one end of diameter
            val (d2, last2) = dfs(last1, -1, parents, rem, t) // Second DFS from last1 gives diameter
            
            q.add(Triple(d2, maxOf(last2, last1), minOf(last2, last1)))  // Add to priority queue
            
            var node = last2             // Walk back up the tree from diameter end
            while (node != -1) {         // Until root (-1)
                rem.remove(node)         // Mark node as removed
                usedcnt++
                node = parents[node]     // Go to parent
            }
        }
        
        while (q.isNotEmpty()) {
            val (a, u, v) = q.poll()   // Pop maximum tuple
            cout.write("$a $u $v ")    // Output result
        }
        cout.newLine()
    }
    cout.flush()
}


// https://github.com/VaHiX/CodeForces/