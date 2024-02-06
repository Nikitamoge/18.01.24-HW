#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

//Task 1 Drob
class Drob {
private:
    int numerator;
    int denominator;
    friend Drob operator*(const int& i, const Drob& other);

public:
    Drob(int num, int dem) {
        if (dem == 0) {
            cout << "ERROR: zero detected!";
            exit(1);
        }
        numerator = num;
        denominator = dem;
    }

    Drob operator+(const Drob& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int dem = denominator * other.denominator;
        return Drob(num, dem);
    }

    Drob operator-(const Drob& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int dem = denominator * other.denominator;
        return Drob(num, dem);
    }

    Drob operator*(const Drob& other) const {
        int num = numerator * other.numerator;
        int dem = denominator * other.denominator;
        return Drob(num, dem);
    }

    Drob operator*(const int& i) const
    {
        int num = numerator * i;
        int dem = denominator;
        return Drob(num, dem);
    }

    Drob operator/(const Drob& other) const {
        if (other.numerator == 0) {
            cout << "ERROR: zero detected!";
            exit(1);
        }
        int num = numerator * other.denominator;
        int dem = denominator * other.numerator;
        return Drob(num, dem);
    }

    Drob operator++()
    {
        numerator++;
        denominator++;
        return *this;
    }

    Drob operator++ (int)
    {
        Drob temp(*this);
        ++(*this);
        return temp;
    }

    operator double()
    {
        return double(numerator) / double(denominator);
    }
    friend istream& operator>>(istream& is, Drob& P);
    friend ostream& operator<<(ostream& os, const Drob& P);
};

Drob operator*(const int& i, const Drob& other)
{
    int num = other.numerator * i;
    int dem = other.denominator;
    return Drob(num, dem);
}

istream& operator>>(istream& is, Drob& P) {
    cout << "Numerator: " << endl;
    is >> P.numerator;
    cout << "Denominator: " << endl;
    is >> P.denominator;
    return is;
}

ostream& operator<<(ostream& os, const Drob& P)
{
    os << "Numerator = " << P.numerator << endl;
    os << "Denominator = " << P.denominator << endl;
    return os;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Task 2 MyString
class MyString
{
    char* str;
    static int count;
    int field = 69;
public:
    MyString()
    {
        str = new char[field];
        str[0] = '\0';
        count++;
    }
    MyString(const char* text)
    {
        str = new char[strlen(text) + 1];
        strcpy_s(str, strlen(text) + 1, text);
        count++;
    }

    MyString(const MyString& other)
    {
        str = new char[strlen(other.str) + 1];
        strcpy_s(str, strlen(other.str) + 1, other.str);
        count++;
    }

    MyString& operator=(const MyString& other)
    {
        if (this != &other)
        {
            delete[] str;
            str = new char[strlen(other.str) + 1];
            strcpy_s(str, strlen(other.str) + 1, other.str);
        }
        return *this;
    }

    MyString operator++()
    {
        int overload = strlen(str);
        char* temp = new char[overload + 2];
        strcpy_s(temp, overload + 2, str);
        temp[overload] = 'x';
        temp[overload + 1] = '\0';
        delete[] str;
        str = temp;
        return *this;
    }

    MyString operator--()
    {
        int overload = strlen(str);
        if (overload > 0)
        {
            char* temp = new char[overload];
            strncpy_s(temp, overload, str, overload - 1);
            temp[overload - 1] = '\0';
            delete[] str;
            str = temp;
        }
        return *this;
    }

    MyString operator++(int)
    {
        MyString postfixInc(*this);
        int overload = strlen(str);
        char* temp = new char[overload + 2];
        strcpy_s(temp, overload + 2, str);
        temp[overload] = 'x';
        temp[overload + 1] = '\0';
        delete[] str;
        str = temp;
        return postfixInc;
    }

    MyString operator--(int)
    {
        MyString postfixDic(*this);
        int overload = strlen(str);
        if (overload > 0)
        {
            char* temp = new char[overload];
            strncpy_s(temp, overload, str, overload - 1);
            temp[overload - 1] = '\0';
            delete[] str;
            str = temp;
        }
        return postfixDic;
    }

    friend MyString operator+(int n, const MyString& Str)
    {
        MyString result;
        delete[] result.str;
        result.str = new char[n + strlen(Str.str) + 1];
        for (int i = 0; i < n; ++i)
        {
            result.str[i] = 'x';
        }
        strcpy_s(result.str + n, strlen(Str.str) + 1, Str.str);
        return result;
    }

    MyString operator-(int n) const
    {
        MyString result(*this);
        int overload = strlen(result.str);
        if (n < overload)
        {
            char* temp = new char[overload - n + 1];
            strncpy_s(temp, overload - n + 1, result.str, overload - n);
            temp[overload - n] = '\0';
            delete[] result.str;
            result.str = temp;
        }
        else
        {
            delete[] result.str;
            result.str = new char[1];
            result.str[0] = '\0';
        }
        return result;
    }

    void input()
    {
        char buffer[256];
        cout << "Enter your string: ";
        cin.getline(buffer, 256);
        delete[] str;
        str = new char[strlen(buffer) + 1];
        strcpy_s(str, strlen(buffer) + 1, buffer);
    }


    void output() const
    {
        cout << "String: " << str << endl;
    }


    static int getCount()
    {
        return count;
    }


    ~MyString()
    {
        delete[] str;
        count--;
    }

    friend ostream& operator<<(ostream& os, const MyString& myStr)
    {
        os << "String: " << myStr.str;
        return os;
    }

    friend istream& operator>>(istream& is, MyString& myStr)
    {
        char buffer[256];
        is.getline(buffer, 256);
        delete[] myStr.str;
        myStr.str = new char[strlen(buffer) + 1];
        strcpy_s(myStr.str, strlen(buffer) + 1, buffer);

        return is;
    }
};

int MyString::count = 0;

int main()
{
    //Task 1 Drob
    Drob fract1(1, 5);
    Drob fract2(3, 10); 
    int int1 = 5;

    Drob result1 = fract1 * fract2;
    cout << "Fraction * Fraction = " << result1 << endl;

    Drob result2 = fract1 * int1;
    cout << "Fraction * int = " << result2 << endl;

    Drob result3 = int1 * fract1;
    cout << "Int * fraction = " << result3 << endl;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Task 2 MyString
    MyString str("Hello");
    MyString sum = 10 + str;
    sum.output();
}



