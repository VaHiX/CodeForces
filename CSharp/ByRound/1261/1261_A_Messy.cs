using System;
using System.Collections.Generic;
namespace c_olymp4
{
    class Program
    {
        class t_s
        {
            public int n, k;
            public string s;
            public t_s(int N, int K, string S) { n = N; k = K; s = S; }
            public static List<t_s> T_s = new List<t_s>();
        }
        static int t;
        static void Main(string[] args)
        {
            t = Convert.ToInt32(Console.ReadLine());
            for(int step = 1; step <= t; step++)
            {
                int n = 0;
                int k = 0;
                int[] nk = new int[2];
                string line = Console.ReadLine();
                var line1 = line.Split(" ");
                for(int num = 0; num < line1.Length; num++)
                    nk[num] = int.Parse(line1[num]);
                n = nk[0]; k = nk[1];
                string second_line = Console.ReadLine();
                t_s ts = new t_s(n, k, second_line);
                t_s.T_s.Add(ts);
            }
            foreach(var t_ in t_s.T_s)
            {
                int m = 0;
                int[] m_s_l = new int[0];
                int[] m_s_r = new int[0];
                string t = null;
                string s = t_.s;
                int small_brackets = t_.k - 1;
                if(small_brackets != 0)
                    for(int new_bracket = 0; new_bracket < small_brackets; new_bracket++)
                        t += "()";
                int big_bracket_Length;
                try
                { big_bracket_Length = t_.n - t.Length; }
                catch(NullReferenceException) { big_bracket_Length = t_.n; }
                string big_bracket = null;
                for(int first_half_bracket = 1; first_half_bracket <= (big_bracket_Length / 2); first_half_bracket++)
                    big_bracket += "(";
                for(int second_half_bracket = 1; second_half_bracket <= (big_bracket_Length / 2); second_half_bracket++)
                    big_bracket += ")";
                t += big_bracket;
                while(true)
                {
                    bool state = true;
                    for(int i = 0; i < t.Length; i++)
                    {
                        if(s[i] != t[i])
                        {
                            state = false;
                            for(int j = i + 1; j < t.Length; j++)
                            {
                                if(s[j] == t[i])
                                {
                                    string first_part_line = null;
                                    string second_part_line = null;
                                    string changed_secord_part_line = null;
                                    string third_part_line = null;
                                    for(int f_i = 0; f_i < i; f_i++)
                                        first_part_line += s[f_i];
                                    for(int s_i = i; s_i <= j; s_i++)
                                        second_part_line += s[s_i];
                                    for(int th_i = j + 1; th_i < s.Length; th_i++)
                                        third_part_line += s[th_i];
                                    for(int mark = 0; mark < second_part_line.Length; mark++)
                                        changed_secord_part_line = second_part_line[mark] + changed_secord_part_line;
                                    s = first_part_line + changed_secord_part_line + third_part_line;
                                    //Console.WriteLine(s);
                                    //Console.WriteLine(m);
                                    //Console.WriteLine($"{i + 1} {j + 1}");
                                    m++;
                                    int[] current_m_s_l = new int[m];
                                    int[] current_m_s_r = new int[m];
                                    if(m_s_l.Length != 0)
                                    {
                                        int current_m_s_l_Index = 0;
                                        int current_m_s_r_Index = 0;
                                        for(int l = 0; l < m_s_l.Length; l++)
                                        { current_m_s_l[l] = m_s_l[l]; current_m_s_l_Index = l; }
                                        for(int R = 0; R < m_s_r.Length; R++)
                                        { current_m_s_r[R] = m_s_r[R]; current_m_s_r_Index = R; }
                                        current_m_s_l[current_m_s_l_Index + 1] = i;
                                        current_m_s_r[current_m_s_r_Index + 1] = j;
                                        m_s_l = current_m_s_l;
                                        m_s_r = current_m_s_r;
                                    }
                                    else 
                                    {
                                        current_m_s_l[0] = i;
                                        current_m_s_r[0] = j;
                                        m_s_l = current_m_s_l;
                                        m_s_r = current_m_s_r;
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    if(state)
                        break;
                }
                Console.WriteLine(m);
                for(int i = 0; i < m_s_l.Length; i++)
                    Console.WriteLine($"{m_s_l[i] + 1} {m_s_r[i] + 1}");
            }
        }
    }
}
