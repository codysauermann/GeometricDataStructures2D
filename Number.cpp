#include <gmpxx.h>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <regex>
#include <vector>
#include "Number.h"


void input_string(mpz_class& a, mpz_class& b, std::string c);
std::string output_string(mpq_class value);

struct Number::Impl 
{
    mpq_class value;
};

// (Oscar) Constructors/Deconstructor
Number::Number() : pimpl( new Impl()) 
{
}
Number::Number(std::string s) : pimpl( new Impl())
{
    input_string(this->pimpl->value.get_num(), this->pimpl->value.get_den(), s);
    this->pimpl->value.canonicalize();
}
Number::Number(const char* s)
{
    input_string(this->pimpl->value.get_num(), this->pimpl->value.get_den(), std::string(s));
    this->pimpl->value.canonicalize();
}

Number::Number(const Number& n) : pimpl( new Impl())
{
    this->pimpl->value = n.pimpl->value;
}
Number::Number(Number&& n)
{
    this->pimpl = n.pimpl;
    n.pimpl = nullptr;
}
Number::~Number()
{
    delete pimpl;
}

// (Oscar) Arithmetic Operators
Number Number::operator+(const Number& n) const
{
    Number sum;
    sum.pimpl->value = this->pimpl->value + n.pimpl->value;
    return sum;
}
Number Number::operator-(const Number& n) const
{
    Number diff;
    diff.pimpl->value = this->pimpl->value - n.pimpl->value;
    return diff;
}
Number Number::operator*(const Number& n) const
{
    Number product;
    product.pimpl->value = this->pimpl->value * n.pimpl->value;
    return product;
}
Number Number::operator/(const Number& n) const
{
    Number quotient;  // Currently zero, 0/1
    if (quotient == n) // Is the denominator 0?
        throw std::runtime_error("Error: Division by Zero\n");
    quotient.pimpl->value = this->pimpl->value / n.pimpl->value;
    return quotient;
}

// (Oscar) Comparison Operators
bool Number::operator<(const Number& n) const
{
    if (cmp(this->pimpl->value, n.pimpl->value) < 0) // negative if less than
        return true;
    else
        return false;
}
bool Number::operator>(const Number& n) const
{
    if (cmp(this->pimpl->value, n.pimpl->value) > 0) // positive if greater than
        return true;
    else
        return false;
}
bool Number::operator==(const Number& n) const
{
    if (cmp(this->pimpl->value, n.pimpl->value) == 0) // 0 if equal to
        return true;
    else
        return false;
}
bool Number::operator!=(const Number& n) const
{
    return !(*this == n);
}
bool Number::operator>=(const Number& n) const
{
    return !(*this < n);
}
bool Number::operator<=(const Number& n) const
{
    return !(*this > n);
}

// (Oscar) Assignment Operators
Number& Number::operator=(std::string s)
{
    input_string(this->pimpl->value.get_num(), this->pimpl->value.get_den(), s);
    this->pimpl->value.canonicalize();
	return *this;
}
Number& Number::operator=(const char* s)
{
    input_string(this->pimpl->value.get_num(), this->pimpl->value.get_den(), std::string(s));
    this->pimpl->value.canonicalize();
	return *this;
}

Number& Number::operator=(Number&& n)
{
    this->pimpl = n.pimpl;
    n.pimpl = nullptr;
    return *this;
}
Number& Number::operator=(const Number& n)
{
    this->pimpl->value = n.pimpl->value;
	return *this;
}
Number& Number::operator+=(const Number& n)
{
    *this = *this + n;
    return *this;
}
Number& Number::operator-=(const Number& n)
{
    *this = *this - n;
    return *this;
}
Number& Number::operator*=(const Number& n)
{
    *this = *this * n;
    return *this;
}
Number& Number::operator/=(const Number& n)
{
    *this = *this / n;
    return *this;
}

// (Oscar) Input Operator
std::istream& operator>>(std::istream& is, Number& n)
{
    std::string input;
    is >> input;
    n = input;
    return is;
}


// (Oscar) Output Operator
std::ostream& operator<<(std::ostream& os, const Number& n)
{
    if (n.pimpl != nullptr)
        os << output_string(n.pimpl->value);
    return os;
}

// (Sam)
void input_string(mpz_class& a, mpz_class& b, std::string c)
{
    std::regex numberFormat("^[-]?[0-9]*[.]?[0-9]*$"); // Regular Expression for a number
    std::smatch isFormated;

    if (!regex_search(c, isFormated, numberFormat))
        throw std::runtime_error("Error: Invalid Number Input Format\n");
    
    int powTen;
    while(c.front() == '0')
    {
        c.erase(c.begin());        // Pop off zeros in the front
    }
    int indexP = c.find('.');
    if (indexP == std::string::npos) // Case 1: No decimal point
    {
        powTen = 0;
        b = 1;
        a = c;
    }
    else                            // Case 2: There is a decimal point
    {
        while(c.back() == '0')
        {
            c.pop_back();        // Pop off zeros at the back
        }
        powTen = (c.length() - 1) - indexP;  // How many decimal places to move
        b = pow(10, powTen);
        c.erase(indexP, 1);
        a = c;
    }
}

// (Sam)
std::string chopZeros(std::string input)
{
    while(input.back() == '0')
        {
            input.pop_back();        // Pop off zeros at the back
        }
    return input;
}

std::string output_string(mpq_class value)
{
    mpz_class numer = value.get_num();
    mpz_class denom = value.get_den();
    mpz_class div1 = numer;
    mpz_class div2 = denom;
    mpz_class remainder = 0;
    int tempRemainder = 0;

    std::string ans = "";

    std::string dividendSTR = div1.get_str();
    std::string divisorSTR = div2.get_str();

    if (dividendSTR.front() == '-')
    {
        dividendSTR.erase(0,1);
        ans.push_back('-');
    }
    if (divisorSTR.front() == '-')
    {
        divisorSTR.erase(0,1);
        if (ans.front() == '-')
        {
            ans.erase(0,1);
        }
        else
        {
            ans.push_back('-');
        }
    }

    std::string dividendSTRO = dividendSTR;

    int decimal = -1;
    for (int i = 0; i < dividendSTR.length(); i++)
    {
        if (dividendSTR.at(i) == '.')
            {
                decimal = i;
            }
    }

    if (decimal = -1)
    {
        decimal = dividendSTR.length();
    }

    while(dividendSTRO.length() < (decimal + 6))
    {
        dividendSTRO.push_back('0');
    }
 
    div1 = dividendSTRO.at(0) - '0';
    div2 = std::stoi(divisorSTR);
 
    int when = decimal + 5;
    for (int i = 0; i < when; i++)
    {
        if(i == decimal)
        {
            ans.push_back('.');
        }
        else 
        {
            remainder = div1 / div2;

            tempRemainder = std::stoi(remainder.get_str());
            ans.push_back('0' + tempRemainder);

            div1 = (div1 - (div2 * remainder)) * 10;
            div1 = div1 + (dividendSTRO.at(i + 1) - '0');
        }
    }

    while (ans.front() == '0' && ans.at(1) != '.')
    {
        ans.erase(ans.begin());
    }

    if (ans.front() == '-')
    {
        while (ans.at(1) == '0' && ans.at(2) != '.')
        {
            ans.erase(1,1);
        }
    }
    return ans;
}

// (Sam)
Number sqrt(const Number& n)
{
     Number squareRoot;

    // Basically I create 3 floats to store the data I need: 
    // the sqrt(numerator), sqrt(denominator), and the old denominator
    mpf_class numer = n.pimpl->value.get_num();
    mpf_class denom = n.pimpl->value.get_den();
    mpf_class oldDenom = denom;

    if (sgn(numer) != sgn(denom))
        throw std::runtime_error("Error: Negative Number Under Square Root\n");

    numer = sqrt(numer);
    denom  = sqrt(denom);

    // Here i set the numerator to sqrt(numer) * sqrt(denom), 
    // and I set the denominator to oldDenom
    // This way the new value is squrt(numer) * sqrt(denom) / denom 
    // to preserve the precision of the denominator
    squareRoot.pimpl->value.get_num() = numer * denom;
    squareRoot.pimpl->value.get_den() = oldDenom;
    squareRoot.pimpl->value.canonicalize();

    return squareRoot;
}