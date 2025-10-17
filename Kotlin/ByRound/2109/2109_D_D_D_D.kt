// Problem: CF 2109 D - D/D/D
// https://codeforces.com/contest/2109/problem/D

/**
 * Problem: D. D/D/D
 *
 * Purpose:
 *   Given a simple, connected undirected graph and a multiset of integers A,
 *   determine for each vertex whether it's reachable from vertex 1 using
 *   walks whose lengths are elements of A.
 *
 * Approach:
 *   - Build graph using adjacency list representation.
 *   - For each node, compute shortest distances to nodes at even and odd depths
 *     (from root) via BFS traversal. This is used to determine if a node can be reached
 *     by an even or odd number of edges in the walk.
 *   - Based on parity of total steps (sum of elements in A), decide what kind of distance
 *     to compare against for reachability.
 *
 * Time Complexity:
 *   O(n + m) per test case, since BFS is run once across all vertices.
 *
 * Space Complexity:
 *   O(n + m) for storing graph and distances.
 */
fun main(args: Array<String>) {
    repeat(readln().toInt()) {
        val (n, m, _) = readln().split(" ").map { it.toInt() }
        val set = readln().split(" ").map { it.toInt() }
        val oddList = set.filter { it % 2 == 1 }.sorted()
        val leftOdd = (oddList.size % 2 == 1)
        val sum = set.sum()
        // Compute sum of elements in A, and distinguish sums for even vs odd walk parity.
        val sumOdd = if (leftOdd) sum else if (oddList.isNotEmpty()) sum - oddList.first() else 0
        val sumEven = if (leftOdd) sum - oddList.first() else sum
        val graph = Graph(n)
        repeat(m) {
            val (a, b) = readln().split(" ").map { it.toInt() }
            graph.addEdge(a - 1, b - 1) // Convert to 0-based indexing.
        }
        graph.calc() // Precompute distances to nodes with even/odd depth from root.
        repeat(n) {
            // For each vertex i, check if it can be reached using sumOdd or sumEven steps
            // based on constraints derived from total parity of A’s elements.
            if (graph.depthEven[it] <= sumEven) {
                print("1")
            } else if (graph.depthOdd[it] <= sumOdd) {
                print("1")
            } else {
                print("0")
            }
        }
        println()
    }
}

class Graph(val n: Int) {
    val edge = Array(n) { mutableListOf<Int>() } // Adjacency list for the graph.
    val depthOdd = IntArray(n) { Int.MAX_VALUE }  // Min odd distance to each node.
    val depthEven = IntArray(n) { Int.MAX_VALUE } // Min even distance to each node.
    val deque = ArrayDeque<Pair<Int, Int>>()     // BFS queue: (vertex, current_depth)

    fun addEdge(a: Int, b: Int) {
        edge[a].add(b)
        edge[b].add(a)
    }

    fun calc() {
        depthEven[0] = 0
        deque.add(0 to 0)
        while (deque.isNotEmpty()) {
            val (x, depth) = deque.removeFirst()
            for (i in edge[x]) {
                // If current depth is even, we can move to odd-depth nodes.
                if (depth % 2 == 0) {
                    if (depthOdd[i] > depth + 1) {
                        depthOdd[i] = depth + 1
                        deque.add(i to depth + 1)
                    }
                } else {
                    // Else, we're on an odd path; next step leads to even-depth.
                    if (depthEven[i] > depth + 1) {
                        depthEven[i] = depth + 1
                        deque.add(i to depth + 1)
                    }
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/