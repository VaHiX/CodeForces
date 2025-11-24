// Problem: CF 2125 B - Left and Down
// https://codeforces.com/contest/2125/problem/B

/*
B. Left and Down
Algorithms/Techniques: GCD, Mathematical Optimization

Time Complexity: O(log(min(a, b))) per test case due to GCD computation
Space Complexity: O(1) - only using a constant amount of extra space

The problem involves finding the minimum cost to move a robot from (a,b) to (0,0)
using moves of the form (dx, dy) where 0 <= dx, dy <= k. Each unique (dx, dy) pair
has cost 1 if used for the first time, otherwise 0. The key insight is that we can
reduce the problem to finding how many distinct steps are needed, which is based 
on the GCD of a and b after normalizing them by their greatest common divisor.

We compute GCD of a and b to find the minimal number of moves required.
If either a or b divided by GCD exceeds k, then we need at least 2 operations,
otherwise only 1 operation is sufficient.
 */

fun gcd (x:Long, y:Long):Long = if (y==0L) x else gcd(y, x%y)
fun main() = repeat(readLine()!!.toInt()){
    var (a, b, k) = readLine()!!.split(' ').map {it.toLong()}.toMutableList()
    var c = gcd(a, b) // Compute GCD of a and b
    println(if(a/c>k || b/c>k) 2 else 1) // If normalized coordinates exceed k, we need 2 moves; otherwise just 1
}


// https://github.com/VaHiX/CodeForces/