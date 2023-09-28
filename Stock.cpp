// Implementation file for the Stock class

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "Stock.h"

//**************************************************
// Constructor
//**************************************************
Stock::Stock()
{
    symbol = "";
    company = "";
    date = "";
    price = -1;
    high = -1;
    low = -1;
    change = -1;
    volume = -1;
    year_high = -1;
    year_low = -1;
}

//**************************************************
// Overloaded Constructor
//**************************************************
Stock::Stock(string sb, string cp, string dt, 
             double pr, double hi, double lo, double ch, 
             int vo, double yh, double yl)
{
    symbol = sb;
    company = cp;
    date = dt;
    price = pr;
    high = hi;
    low = lo;
    change = ch;
    volume = vo;
    year_high = yh;
    year_low = yl;
}

 //***********************************************************
 // Displays the values of the Stock object member variables
 // on one line (horizontal display)
 // using operator<< overloading
 //***********************************************************
ostream& operator<<(ostream& os, const Stock& obj) {

    os << obj.symbol << " ";
    os << obj.company << "; ";
    os << obj.date << "; ";
    os << obj.price << " ";
    os << obj.high << " ";
    os << obj.low << " ";
    os << obj.change << " ";
    os << obj.volume << " ";
    os << obj.year_high << " ";
    os << obj.year_low;
    os << endl;
    return os;
}

//***********************************************************
// overloading operator <
// It uses the unique key of the Stock object (symbol + date)
//***********************************************************
bool Stock::operator < (const Stock& obj) const {
    return (getUniqueKey() < obj.getUniqueKey());
}

//***********************************************************
// overloading operator >
// It uses the unique key of the Stock object (symbol + date)
//***********************************************************
bool Stock::operator > (const Stock& obj) const {
    return (getUniqueKey() > obj.getUniqueKey());
}

//***********************************************************
// overloading operator ==
// It uses the unique key of the Stock object (symbol + date)
//***********************************************************
bool Stock::operator == (const Stock& obj) const {
    return (getUniqueKey() == obj.getUniqueKey());
}

