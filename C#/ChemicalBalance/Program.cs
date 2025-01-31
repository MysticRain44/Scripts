﻿using System;

namespace ChemicalBalance
{
    class Program
    {
        static void Main(string[] args)
        {
            //Declaration
            int termsLHS, termsRHS, kindsOfAtoms, chargeBalance;
            int[][] lhs, rhs;
            int[] chargeLhs, chargeRhs;

            //Input
            Console.WriteLine("How many terms in the left-hand side(LHS)?"); //Input
            termsLHS = int.Parse(Console.ReadLine());                         //Output
            Console.WriteLine("How many terms in the right-hand side(LHS)?");
            termsRHS = int.Parse(Console.ReadLine());
            Console.WriteLine("How many kinds of atoms?");
            kindsOfAtoms = int.Parse(Console.ReadLine());
            Console.WriteLine("Do you consider the balance of charge?");
            chargeBalance = int.Parse(Console.ReadLine());

            //Arrays
            lhs = new int[termsLHS][]; //Array with 'termsLHS' columns, null rows
            rhs = new int[termsRHS][];

            //LHS matrix
            Console.WriteLine("Enter number of atoms in each term, in order of input 3(LHS), Press ! to end input"); //Eg. 1,2,3!
            for (int i = 0; i < termsLHS; i++)
            {
                Console.WriteLine(i + "th term:");
                string temp = Console.ReadLine();
                int[] term = new int[kindsOfAtoms];
                int pos = 0;
                int arrayPos = 0;

                //Scan Input
                while (temp[pos] != '!') //Handle <no '!' in input> exception
                {
                    int current = temp[pos] - '0'; //Converting char to int
                    if (current >= 0 && current <= 9)
                    {
                        term[arrayPos] = current;
                        arrayPos++;
                        if (arrayPos == kindsOfAtoms) break;
                    }
                    pos++;
                }
                lhs[i] = term; //Assign Scanned input to Column 'i'
            }

            //RHS matrix
            Console.WriteLine("Enter number of atoms in each term, in order of input 3(RHS), Press ! to end input");
            for (int i = 0; i < termsRHS; i++)
            {
                Console.WriteLine(i + "th term:");
                string temp = Console.ReadLine();
                int[] term = new int[kindsOfAtoms];
                int pos = 0;
                int arrayPos = 0;

                //Scan Input
                while (temp[pos] != '!')
                {
                    int current = temp[pos] - '0'; //Converting char to int
                    if (current >= 0 && current <= 9)
                    {
                        term[arrayPos] = current;
                        arrayPos++;
                        if (arrayPos == kindsOfAtoms) break;
                    }
                    pos++;
                }
                rhs[i] = term; //Assign Scanned input to Column 'i'
            }

            if (chargeBalance == 1)
            {
                //Charge of LHS
                Console.WriteLine("Enter Number of Charge with its sign, in order of terms in LHS, Press ! to end line");

                string temp = Console.ReadLine();
                int[] term = new int[termsLHS];
                int pos = 0;
                int arrayPos = 0;

                //Scan Input
                while (temp[pos] != '!')
                {
                    int current = temp[pos] - '0'; //Converting char to int
                    if (current >= 0 && current <= 9)
                    {
                        term[arrayPos] = current;
                        arrayPos++;
                        if (arrayPos == kindsOfAtoms) break;
                    }
                    pos++;
                }
                chargeLhs = term; //Assign Scanned input to Column 'i'
            }
            if (chargeBalance == 1)
            {
                //Charge of RHS
                Console.WriteLine("Enter Number of Charge with its sign, in order of terms in RHS, Press ! to end line");

                string temp = Console.ReadLine();
                int[] term = new int[termsRHS];
                int pos = 0;
                int arrayPos = 0;

                //Scan Input
                while (temp[pos] != '!')
                {
                    int current = temp[pos] - '0'; //Converting char to int
                    if (current >= 0 && current <= 9)
                    {
                        term[arrayPos] = current;
                        arrayPos++;
                        if (arrayPos == kindsOfAtoms) break;
                    }
                    pos++;
                }
                chargeRhs = term; //Assign Scanned input to Column 'i'
            }

            //Matrices lhs and rhs, apply formula to them
        }
    }
}