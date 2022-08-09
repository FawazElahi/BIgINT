 #include<bits/stdc++.h>
 #include "bigint.h"
 using namespace std ; 

int main()
{
    big first("12345");
    cout << "The number of digits"
         << " in first big integer = "
         << length(first) << '\n';
    big second(12345);
    if (first == second) {
        cout << "first and second are equal!\n";
    }
    else
        cout << "Not equal!\n";
    big third("10000");
    big fourth("100000");
    if (third < fourth) {
        cout << "third is smaller than fourth!\n";
    }
    big fifth("10000000");
    if (fifth > fourth) {
        cout << "fifth is larger than fourth!\n";
    }
 
    // Printing all the numbers
    cout << "first = " << first << '\n';
    cout << "second = " << second << '\n';
    cout << "third = " << third << '\n';
    cout << "fourth = " << fourth<< '\n';
    cout << "fifth = " << fifth<< '\n';
 
    // Incrementing the value of first
    first++;
    cout << "After incrementing the"
         << " value of first is : ";
    cout << first << '\n';
    big sum;
    sum = (fourth + fifth);
    cout << "Sum of fourth and fifth = "
         << sum << '\n';
    big product;
    product = second * third;
    cout << "Product of second and third = "
         << product << '\n';
 
    // Print the fibonaccii number from 1 to 100
    cout << "-------------------------Fibonacci"
         << "------------------------------\n";
    for (int i = 0; i <= 100; i++) {
        big Fib;
        Fib = fibonacci(i);
        cout << "Fibonacci " << i << " = " << Fib<<'\n';
    }
    cout << "-------------------------Catalan"
         << "------------------------------\n";
    for (int i = 0; i <= 100; i++) {
        big Cat;
        Cat = catalan(i);
        cout << "Catalan " << i << " = " << Cat<<'\n';
    }
 
    // Calculating factorial of from 1 to 100
    cout << "-------------------------Factorial"
         << "------------------------------\n";
    for (int i = 0; i <= 100; i++) {
        big fact;
        fact = factorial(i);
        cout << "Factorial of "
             << i << " = ";
        cout << fact << '\n';
    }
    
    return 0 ;

}
