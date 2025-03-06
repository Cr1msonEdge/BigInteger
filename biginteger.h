#pragma once
#include <iostream>
#include <string>

class BigInteger
{
private:
    bool minus_ = false;
    long long int count_ = 0;
    unsigned int* digits_;
public:
    BigInteger();
    BigInteger(const std::string);
    BigInteger(long long);
    BigInteger(unsigned long long);
    BigInteger(unsigned long);
    BigInteger(long);
    BigInteger(int);
    BigInteger(unsigned int);
    BigInteger(const BigInteger&);
    BigInteger(BigInteger&&) noexcept;
    ~BigInteger();

    //////////////////////////////////////////

    bool operator== (const BigInteger& a) const;
    friend bool operator== (long long a, const BigInteger& b);

    bool operator!= (const BigInteger& a) const;
    bool operator> (const BigInteger& a);
    bool operator< (const BigInteger& a);
    bool operator<= (const BigInteger& a);
    bool operator>= (const BigInteger& a);

    //////////////////////////////////////////

    friend std::ostream& operator<< (std::ostream& out, const BigInteger& digit);
    friend std::string to_string(const BigInteger& a);

    //////////////////////////////////////////

    BigInteger& operator=(const BigInteger& a);
    BigInteger operator=(BigInteger&&) noexcept;

    //////////////////////////////////////////

    BigInteger& operator++();
    BigInteger& operator--();
    const BigInteger& operator+() const;
    BigInteger operator-() const;
    BigInteger operator++(int);
    BigInteger operator--(int);
    BigInteger& operator+=(const BigInteger& a);
    BigInteger& dif(const BigInteger& a);
    BigInteger& operator-=(const BigInteger& a);
    BigInteger& sum(const BigInteger& a);
    BigInteger operator+(const BigInteger& a) const;
    BigInteger operator-(const BigInteger& a) const;
    //////////////////////////////////////////

    //BigInteger& mover(int a = 1);
    //BigInteger mult(unsigned int a);
    BigInteger& addZero(int cnt = 1);
    BigInteger& operator*= (const BigInteger& a);
    BigInteger operator*(const BigInteger& a) const;
    BigInteger& operator/=(const BigInteger& a);
    BigInteger operator/ (const BigInteger& a) const;
    BigInteger& operator%=(const BigInteger& a);
    BigInteger operator%(const BigInteger& a) const;

    //////////////////////////////////////////

    void bitter();
    void badZeros();
    BigInteger operator~();
    BigInteger operator&(const BigInteger& a) const;
    BigInteger& operator&=(const BigInteger& a);
    BigInteger& operator|=(const BigInteger& a);
    BigInteger& operator|= (long long a);
    BigInteger operator|(long long a) const;
    BigInteger operator|(const BigInteger& a) const;
    BigInteger& operator^=(const BigInteger& a);
    BigInteger& operator^= (long long a);
    BigInteger operator^(const BigInteger& a) const;
    BigInteger operator^(long long a) const;
    BigInteger& operator<<=(unsigned int a);
    BigInteger operator<<(unsigned int a) const;
    BigInteger& operator>>=(unsigned int a);
    BigInteger operator>>(unsigned int a) const;

    //////////////////////////////////////////

};

BigInteger operator+(long, const BigInteger&);
BigInteger operator-(long, const BigInteger&);
BigInteger operator*(long a, const BigInteger& b);
BigInteger operator/(long a, const BigInteger& b);
BigInteger operator%(long a, const BigInteger& b);

//////////////////////////////////////
int size(std::string str);
bool isNumber(char ch);
unsigned long long sToUI64(std::string str);
unsigned long long sToUI64(std::string, int);
unsigned int divideMAX(std::string& str);
std::string to_string(const long long a);
std::string no_zeros(std::string a);
std::string sum_strings(const std::string& a, const std::string& b);
std::string multiply(std::string a, std::string b);
int size(const long long a);
