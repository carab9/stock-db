// Specification file for the Stock class
// The primary key of the Stock object is symbol + date
// The secondary key of the Stock object is company name

#ifndef STOCK_H_
#define STOCK_H_

#include<string>

using std::string;
using std::ostream;

class Stock; // Forward Declaration

// Function Prototypes for Overloaded Stream Operators
ostream& operator << (ostream&, const Stock&);

class Stock
{
private:
    string symbol;      // primary key symbol + date (unique)
    string company;     // secondary key (not unique)
    string date;
    double price;
    double high;
    double low;
    double change; 
    int volume;  
    double year_high;
    double year_low;

public:

    // constructors
    Stock();
    Stock(string, string, string, double, double, double, double, int, double, double);

    // setters
    void setSymbol(string sb) { symbol = sb;  }
    void setCompanyName(string cp) { company = cp;  }
    void setDate(string dt) { date = dt; }
    void setPrice(double pr) { price = pr; }
    void setHigh(double hi) { high = hi; }
    void setLow(double lo) { low = lo; }
    void setChange(double ch) { change = ch; }
    void setVolume(int vo) { volume = vo; }
    void setYearHigh(double yh) { year_high = yh; }
    void setYearLow(double yl) { year_low = yl; }
    

    // getters
    string getSymbol() const { return symbol; }
    string getCompanyName() const { return company; }
    string getDate() const { return date; }
    double getPrice() const { return price; }
    double getHigh() const { return high; }
    double getLow() const { return low; }
    int getVolume() const { return volume; }
    double getChange() const { return change; }
    double getYearHigh() const { return year_high; }
    double getYearLow() const { return year_low; }

    // get the unique key of the stock data (symbol + date)
    string getUniqueKey() const { return symbol + date; }

    // overloaded operators
    /* declare/define the following overloaded operators:
        - the stream insertion operator ( << )
        - the relational operators (<, >, == ) */

    // overloading the operator <<
    friend ostream& operator<<(ostream& os, const Stock& obj);

    // overloading the operator <
    bool operator < (const Stock& obj) const;
    
    // overloading the operator >
    bool operator > (const Stock& obj) const;
    
    // overloading the operator ==
    bool operator == (const Stock& obj) const;
};

#endif // STOCK_H_
