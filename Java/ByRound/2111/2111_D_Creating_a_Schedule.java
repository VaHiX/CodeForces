// Problem: CF 2111 D - Creating a Schedule
// https://codeforces.com/contest/2111/problem/D

/*
 * Problem: D. Creating a Schedule
 * Purpose: Create a schedule for n groups and m classrooms such that students move as much as possible between floors,
 *          maximizing total floor movements across all groups. Each group has exactly 6 classes, and each class must
 *          be assigned to a unique classroom.
 *
 * Algorithms/Techniques:
 * - Sorting classrooms by their indices (to extract floor numbers easily).
 * - Assigning pairs of classrooms to maximize floor differences for each group.
 * - Cyclic assignment pattern to balance load and maximize movement.
 *
 * Time Complexity: O(m log m) per test case, dominated by sorting.
 * Space Complexity: O(m) for storing classroom array.
 */
import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
        while (t-->0){
            int n=sc.nextInt(); // number of groups
            int m=sc.nextInt(); // number of classrooms
            int[] classroom=new int[m]; // array to store classroom indices
            for (int i = 0; i < m; i++){
                classroom[i]=sc.nextInt(); // read classroom indices
            }
            Arrays.sort(classroom); // sort classrooms by index to facilitate floor extraction
            int ci=n/2; // calculate how many pairs we need to assign to groups
            if(n%2==1){ // if odd number of groups, adjust pair count
                ci+=1;
            }
            for (int i = 0; i < ci; i++){
                if(n%2==1&&i==ci-1){ // special handling for the last group if total is odd
                    // Assign same classroom to the same group multiple times to fill all 6 slots
                    System.out.println(classroom[i]+" "+classroom[m-i-1]+" "+classroom[i]+" "+classroom[m-i-1]+" "+classroom[i]+" "+classroom[m-i-1]);
                }
                else {
                    // For every other group: assign two distinct classrooms alternately to maximize floor difference
                    System.out.println(classroom[i] + " " + classroom[m - i - 1] + " " + classroom[i] + " " + classroom[m - i - 1] + " " + classroom[i] + " " + classroom[m - i - 1]);
                    System.out.println(classroom[m - i - 1] + " " + classroom[i] + " " + classroom[m - i - 1] + " " + classroom[i] + " " + classroom[m - i - 1] + " " + classroom[i]);
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/