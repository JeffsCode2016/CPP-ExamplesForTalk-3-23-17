#include <iostream>
#include <vector>
#include <sstream>
#include "coins.h"

using namespace std;

typedef pair<int,string> Denomination;

void introduction()
{
    cout << "               \033[1;31m Small program highlighting some C++11 functions\033[0m" << endl;
    cout << "                              Written by Jeff G" << endl;
    cout << "                                March 19, 2017" << endl;
    cout << "                          Not ready for distribution " << endl << endl;
}


// Template overloading procedure to identify the TemplateTest parameters that are strings and prevent comparison to see if they are negative
void TypePassed(int &ReadNumber, string &value)
{
    stringstream ExceptionText;

    ExceptionText << "The above was a string passed at item number: " << ReadNumber << endl;

    throw ExceptionText.str();  // threw as a string as wanted to include the ReadNumber, generally not a good idea through as strings can throw their own exceptions
}


// Template overloading to compare those int and double values that are not strings (caught in above procedure) to see if they are negative
template<typename T>
void TypePassed(int &ReadNumber, T &value)
{
    stringstream ExceptionText;

    if (static_cast<double>(value) < 0)
    {
        ExceptionText << "A negative number was passed at item number " << ReadNumber << endl;
        throw ExceptionText.str();  // threw as a string as wanted to include the ReadNumber, generally not a good idea through as strings can throw their own exceptions
    }
}


// example of a variadic template - procedure for the final value
template<typename T>
void TemplateTest(int &ReadNumber, T &value)
{
    stringstream ExceptionText;

    cout << "The last item (item number " << ReadNumber << ") was:   " << value << endl;

    try  // playing around with exceptions
    {
        TypePassed(ReadNumber, value); // Throw exception if a string is passed
    }
    catch (string MyException)
    {
        cout << "Caught the following exception: " << MyException << endl;
    }
}


// example of a variadic template - when there are additional args
template<typename T, typename... Args>
void TemplateTest(int &ReadNumber, T &value, Args... args)
{

    if (!ReadNumber)  // ReadNumber is 0 which is the first iteration
    {
        cout << "Made it inside variadic template to find negative numbers..." << endl;
        ReadNumber = 1; // means this is the first item
    }

    cout << "Item number " << ReadNumber << " was:   " << value << endl;

    try  // playing around with exceptions
    {
        TypePassed(ReadNumber, value); // Throw exception if a string is passed or if value is below 0 (negative)
    }
    catch (string MyException)
    {
        cout << "Caught the following exception: " << MyException << endl;
    }

    ReadNumber++;  // increment the read number
    TemplateTest(ReadNumber, args...);  // recursive call
}


int main()
{
    introduction();

    cout << "\e[1mPart 1 - Test of normal pointers:\e[0m" << endl;
    int *IntPointer = new int;
    *IntPointer = 3;
    cout << "The value of IntPointer is " << *IntPointer << endl << endl;
    IntPointer = nullptr;
    delete IntPointer;


    cout << "\e[1mPart 2 - Test of unique_pointer:\e[0m" << endl;
    unique_ptr<int> UniquePointer (new int);
    *UniquePointer = 10;
    cout << "The value of UniquePointer is " << *UniquePointer << endl << endl;


    //Test of the different constructors/assignments
    pair<int,string> penny(1,"penny");
    auto nickel = make_pair(5, "nickel");
    Denomination dime(10,"dime");
    pair<int,string> quarter(25,"quarter");
    auto half = make_pair(50, "half");
    Denomination dollar(100,"dollar");

    vector<Denomination> CoinTypes;
    CoinTypes.push_back(penny);
    CoinTypes.push_back(nickel);
    CoinTypes.push_back(dime);
    CoinTypes.push_back(quarter);
    CoinTypes.push_back(half);
    CoinTypes.push_back(dollar);


    cout << "\e[1mPart 3 - Test of Object Oriented Programming on stack:\e[0m" << endl;
    coins TestCoins(CoinTypes);  // used the parameter constructor (overloading)
    cout << endl;
    //  Because its not a pointer, destructor was not called here


    cout << "\e[1mPart 4 - Test of Object Oriented Programming on heap:\e[0m" << endl;
    coins *GroupCoins = new coins(); // used the default constructor
    GroupCoins->Setvalue(25);  // use a pointer to an object function
    cout << "Group coins value is $" << GroupCoins->Getvalue() << endl << endl;
    GroupCoins = nullptr;
    delete GroupCoins;  // calls destructor for Betsycoins


    // Test of variadic templates and exception throwing
    int FirstCall(0);
    cout << "\e[1mPart 5 - Test of the variadic templates:\e[0m" << endl;
    string StringSample = "Testing variadic templates";
    int i(10);
    double d(50.0234);
    // call to the variadic template
    TemplateTest(FirstCall, i, d, StringSample, (i-20), (d*55), 2*i, StringSample);


    //  Just a notice that the destructor was called.
    cout << endl;
    cout << "\e[1mPart 6 - Will call the destructor for OOP on heap:\e[0m" << endl;


    cin.get();  // A pause for the compiled program
    return 0;  // Calls destructor for TestCoins
}
