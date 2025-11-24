// Problem: CF 2111 E - Changing the String
// https://codeforces.com/contest/2111/problem/E

/*
 * Problem: E. Changing the String
 * Purpose: To transform a string of 'a', 'b', 'c' into lexicographically minimal form using a series of operations.
 * Algorithm:
 *   - For each character in the string from left to right, if it's 'b' or 'c':
 *     * Try to change it to 'a' by finding an operation that can be applied greedily.
 *     * Operations allow changing one occurrence of x to y.
 *     * Use TreeSet for efficient lookup of operations sorted by index.
 *   - Operations are stored in HashMap with keys like "ba", "bc", etc.
 * Time Complexity: O(n + q * log(q)) where n is the length of string, q is number of operations.
 * Space Complexity: O(q) for storing the operations in TreeSet data structures.
 */

import java.util.*;

public class codeforces {
    static int high(TreeSet<Integer> ts, int x) {
        Integer val = ts.higher(x); // Find the smallest value greater than x
        return val == null ? -1 : val;
    }
    
    static int low(TreeSet<Integer> ts, int x) {
        Integer val = ts.lower(x); // Find the largest value less than x
        return val == null ? -1 : val;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int tc = sc.nextInt() ;
        while (tc-- > 0) {
            int n = sc.nextInt() , q = sc.nextInt() ;
            char[] a = sc.next().toCharArray() ;
            
            // Map to store operations for each pair of characters as key
            HashMap<String, TreeSet<Integer>> mp = new HashMap<>() ;
            mp.put("ba", new TreeSet<>()) ; mp.put("bc", new TreeSet<>()) ;
            mp.put("cb", new TreeSet<>()) ; mp.put("ca", new TreeSet<>()) ;
            
            // Read operations and store them in respective TreeSets
            for (int i = 0; i < q; i++) {
                char x = sc.next().charAt(0) , y = sc.next().charAt(0) ;
                if(x == 'a' || x == y) continue ;  // Skip redundant operations
                String s = x+""+y ;
                mp.get(s).add(i) ; // Add operation to corresponding TreeSet
            }
            
            // Process each character of the string from left to right
            for (int i = 0; i < n; i++) {
                if(a[i] == 'a') continue ; // Already minimal, skip processing
                
                if(a[i] == 'b') {
                    TreeSet<Integer> ba = mp.get("ba") , bc = mp.get("bc") , ca = mp.get("ca") ;
                    
                    // Try to convert 'b' to 'a' using direct operation "ba"
                    if(!ba.isEmpty()) {
                        ba.remove(ba.first()) ; // Greedily use earliest available "ba" operation
                        a[i] = 'a' ;
                    } else {
                        // If no direct "ba" operation, try indirect conversion: "bc" -> "ca"
                        if(!bc.isEmpty()) {
                            int id = bc.first() , idx = high(ca, id) ; // Find a valid "ca" after current "bc"
                            if(idx != -1) {
                                bc.remove(id) ; ca.remove(idx) ; // Remove used operations
                                a[i] = 'a' ;
                            }
                        }
                    }
                } else if (a[i] == 'c') {
                    TreeSet<Integer> ca = mp.get("ca") , cb = mp.get("cb") , ba = mp.get("ba") ;

                    // Try to convert 'c' to 'a' using direct operation "ca"
                    if(!ca.isEmpty()) {
                        ca.remove(ca.first()) ;
                        a[i] = 'a' ;
                    } else {
                        // If no direct "ca" operation, try indirect conversion: "cb" -> "ba"
                        if(!cb.isEmpty()) {
                            int id = cb.first() , idx = high(ba, id) ; // Find a valid "ba" after current "cb"
                            a[i] = 'b' ; cb.remove(id) ;
                            if(idx != -1) {
                                a[i] = 'a' ;
                                ba.remove(idx) ; // Remove used operation
                            }
                        }
                    }
                }
            }
            
            System.out.println(new String(a)) ; // Print transformed string
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/