// Problem: CF 2116 D - Gellyfish and Camellia Japonica
// https://codeforces.com/contest/2116/problem/D

/*
 * Problem: D. Gellyfish and Camellia Japonica
 * Purpose: Given a final array 'b' after q operations of type c[z] = min(c[x], c[y]), 
 *          and knowing the operations, find any valid initial array 'a' such that it leads to 'b'.
 *          Return "-1" if no such 'a' exists.
 *
 * Algorithm:
 * - Build a binary tree from the given operations where each leaf represents an original element,
 *   and internal nodes represent intermediate computations of min operation.
 * - Use Union-Find like structure with parent relationships to track which variables are related.
 * - Assign values from bottom up, ensuring constraints from min operations are satisfied.
 * - Validate all constraints after assignment.
 *
 * Time Complexity: O(n + q)
 * Space Complexity: O(n + q)
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
    val rd = BufferedReader(InputStreamReader(System.`in`))
    val sb = StringBuilder()
    var tk = StringTokenizer(rd.readLine())
    val T = tk.nextToken().toInt()
    
    for (caseIndex in 1..T) {
        tk = StringTokenizer(rd.readLine())
        val n = tk.nextToken().toInt()
        val q = tk.nextToken().toInt()
        
        // finalB[i] stores the final value at position i after all operations
        val finalB = LongArray(n + 1)
        tk = StringTokenizer(rd.readLine())
        for (i in 1..n) {
            finalB[i] = tk.nextToken().toLong()
        }
        
        // Store operation parameters
        val ux = IntArray(q + 1)
        val uy = IntArray(q + 1)
        val uz = IntArray(q + 1)
        for (i in 1..q) {
            tk = StringTokenizer(rd.readLine())
            ux[i] = tk.nextToken().toInt()
            uy[i] = tk.nextToken().toInt()
            uz[i] = tk.nextToken().toInt()
        }
        
        // Tree representation using leftKid and rightKid arrays
        val leftKid = IntArray(n + q + 1)
        val rightKid = IntArray(n + q + 1)
        
        // Union-Find like structure to track which elements are connected
        val representative = IntArray(n + 1) { it }
        
        // Build the binary tree based on operations
        for (i in 1..q) {
            val nodeIndex = n + i
            leftKid[nodeIndex] = representative[ ux[i] ]   // Left child of new node
            rightKid[nodeIndex] = representative[ uy[i] ]  // Right child of new node
            representative[ uz[i] ] = nodeIndex            // Set parent of z[i] to current new node
        }
        
        // Values assigned to each node and whether value is fixed (from given b)
        val nodeValue = LongArray(n + q + 1)
        val isFixed = BooleanArray(n + q + 1)
        
        // Initialize root values for original elements with their final known values
        for (j in 1..n) {
            val rootNode = representative[j]
            if (!isFixed[rootNode]) {
                nodeValue[rootNode] = finalB[j]
                isFixed[rootNode] = true
            }
        }
        
        var valid = true
        
        // Propagate values from leaves up using min constraints
        for (u in (n + q) downTo 1) { 
            if (u > n) {  // This is an operation node not original element
                val v = nodeValue[u]
                val c1 = leftKid[u]   // Left child of node u
                val c2 = rightKid[u]  // Right child of node u
                
                // If left child value is less than our current v (and it's not fixed yet), 
                // then we must propagate the value v to c1 for consistency with min operation
                if (nodeValue[c1] < v) {
                    if (isFixed[c1]) {  // Left child already assigned but less than current node value - invalid!
                        valid = false
                        break
                    }
                    nodeValue[c1] = v   // Assign v to the left child
                }
                
                // Same for right child
                if (nodeValue[c2] < v) {
                    if (isFixed[c2]) {  // Right child already assigned but less than current node value - invalid!
                        valid = false
                        break
                    }
                    nodeValue[c2] = v   // Assign v to the right child
                }
            }
        }

        if (!valid) {
            sb.append("-1\n")
            continue
        }
        
        // Now ensure that all internal nodes' values correctly reflect min relationship
        for (u in 1..(n + q)) { 
            if (u > n) {  // This is an operation node now being checked for value consistency
                val v1 = nodeValue[ leftKid[u] ]     // Value of left child
                val v2 = nodeValue[ rightKid[u] ]    // Value of right child
                val want = if (v1 < v2) v1 else v2   // Should be min(v1, v2)
                
                if (isFixed[u]) {
                    // If value is fixed, see if it matches the expected computed value
                    if (nodeValue[u] != want) {
                        valid = false
                        break
                    }
                } else {
                    // Otherwise assign it the minimum of its children
                    nodeValue[u] = want
                }
            }
        }

        if (!valid) {
            sb.append("-1\n")
        } else {
            // Print all original values from nodes [1..n]
            for (i in 1..n) {
                sb.append(nodeValue[i])
                if (i < n) sb.append(' ')
            }
            sb.append('\n')
        }
    }
    
    print(sb)
}


// https://github.com/VaHiX/CodeForces/