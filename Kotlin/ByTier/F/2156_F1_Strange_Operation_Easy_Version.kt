// Problem: CF 2156 F1 - Strange Operation (Easy Version)
// https://codeforces.com/contest/2156/problem/F1


// ### Complexity Analysis:
// - **Time Complexity**: $ O(n^2) $  
//   In the worst case, the algorithm performs a number of iterations proportional to $ n^2 $, due to nested loops checking conditions and updating the permutation.
  
// - **Space Complexity**: $ O(n) $  
//   The space is used to store the permutation array and the locations array, both of size $ n+1 $, which results in linear space usage.

// ### Algorithm Overview:
// This problem uses an iterative approach with a greedy strategy to transform a permutation into its lexicographically smallest form by repeatedly applying a specific operation. The key idea is to iteratively reduce values in a way that brings smaller numbers towards the front of the permutation.

// The operation allows us to decrease a value (in position $ i $) by 2 and increase two other values (in positions $ j $ and $ k $) by 1 each, under certain constraints:
// $$ p_i = \max(p_j, p_k) + 1 \quad \text{and} \quad p_i = \min(p_j, p_k) + 2 $$

// These rules ensure that we can only perform operations when there exist three indices $ i < j < k $ satisfying the constraints and allow us to effectively shift smaller values toward their correct positions in a sorted fashion.

fun main() {
    val testCases = readLine()!!.toInt()
    repeat(testCases) {
        val size = readLine()!!.toInt()
        val permutation = IntArray(size + 1)
        val locations = IntArray(size + 1)
        readLine()!!.split(" ").forEachIndexed { index, value ->
            val num = value.toInt()
            val idx = index + 1
            permutation[idx] = num
            locations[num] = idx // Store the position of each value in the permutation
        }
        if (size >= 3) {
            var modified = true
            while (modified) {
                modified = false
                var value = 1
                while (value + 2 <= size) {
                    val posNext = locations[value + 1] // Position of value+1
                    val posCurrent = locations[value]     // Position of value
                    val posNextNext = locations[value + 2] // Position of value+2
                    // Check if we can perform the operation:
                    // The position of value+2 should be before positions of value and value+1
                    if (posNextNext < posCurrent && posNextNext < posNext) {
                        // Update the permutation values according to operation rules
                        permutation[posNextNext] -= 2
                        permutation[posCurrent]++
                        permutation[posNext]++
                        // Update positions in locations array
                        locations[value] = posNextNext
                        locations[value + 1] = posCurrent
                        locations[value + 2] = posNext
                        modified = true // Mark that a change was made, continue loop
                    }
                    value++
                }
            }
        }
        // Build the output string for the final permutation
        val output = buildString {
            for (idx in 1..size) {
                if (idx > 1) append(' ')
                append(permutation[idx])
            }
        }
        println(output)
    }
}

// https://github.com/VaHiX/CodeForces/