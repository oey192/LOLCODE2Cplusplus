#pragma once
#include <string>


enum vType {INT, DOUBLE, STRING};


class var {
public:
	vType type;

	void setVal(int iNum_);
	void setVal(double dNum_);
	void setVal(string sVal_);

	int getiVal();
	double getdVal();
	std::string getsVal();

	var& operator=(var rhs);
	var& operator=(int rhs);
	var& operator=(double rhs);
	var& operator=(const char rhs[]);
	var& operator=(std::string &rhs);

private:
	int iNum;
	double dNum;
	std::string sVal;
};

istream& operator >> (istream &in, var &val);
ostream& operator << (ostream &out, var &val);

var operator+(var l, var r);
var operator+(var l, int r);
var operator+(int l, var r);
var operator+(var l, double r);
var operator+(double l, var r);
var operator+(var l, string r);
var operator+(string l, var r);

var operator-(var l, var r);
var operator-(var l, int r);
var operator-(int l, var r);
var operator-(var l, double r);
var operator-(double l, var r);

var operator*(var l, var r);
var operator*(var l, int r);
var operator*(int l, var r);
var operator*(var l, double r);
var operator*(double l, var r);

var operator-(var l, var r);
var operator-(var l, int r);
var operator-(int l, var r);
var operator-(var l, double r);
var operator-(double l, var r);

var operator%(var l, var r);
var operator%(var l, int r);
var operator%(int l, var r);

bool operator&&(var l, var r);
bool operator&&(var l, int r);
bool operator&&(int l, var r);
bool operator&&(var l, double r);
bool operator&&(double l, var r);

bool operator||(var l, var r);
bool operator||(var l, int r);
bool operator||(int l, var r);
bool operator||(var l, double r);
bool operator||(double l, var r);

bool operator==(var l, var r);
bool operator==(var l, int r);
bool operator==(int l, var r);
bool operator==(var l, double r);
bool operator==(double l, var r);
bool operator==(var l, string r);
bool operator==(string l, var r);

bool operator!=(var l, var r);
bool operator!=(var l, int r);
bool operator!=(int l, var r);
bool operator!=(var l, double r);
bool operator!=(double l, var r);
bool operator!=(var l, string r);
bool operator!=(string l, var r);

bool operator!(var r);

double max(double a, double b);
double max(var a, var b);
double max(var a, double b);
double max(double a, var b);

double min(double a, double b);
double min(var a, var b);
double min(var a, double b);
double min(double a, var b);

