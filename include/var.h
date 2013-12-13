#pragma once
#include <string>


enum vType {INT, DOUBLE, STRING};


class var {
public:
	vType type;

	var();
	var(int iNum);
	var(double dNum);
	var(char *sVal);
	var(std::string sVal);

	void setVal(int iNum_);
	void setVal(double dNum_);
	void setVal(std::string sVal_);

	int getiVal();
	double getdVal();
	std::string getsVal();

	var& operator=(var rhs);
	var& operator=(int rhs);
	var& operator=(double rhs);
	var& operator=(const char rhs[]);
	var& operator=(std::string &rhs);

	var& operator+=(var rhs);
	var& operator+=(int rhs);
	var& operator+=(double rhs);
	var& operator+=(const char rhs[]);
	var& operator+=(std::string &rhs);

private:
	int iNum;
	double dNum;
	std::string sVal;
};

std::istream& operator >> (std::istream &in, var &val);
std::ostream& operator << (std::ostream &out, var &val);

var operator+(var l, var r);
var operator+(var l, int r);
var operator+(int l, var r);
var operator+(var l, double r);
var operator+(double l, var r);
var operator+(var l, std::string r);
var operator+(std::string l, var r);
var operator+(int l, std::string r);
var operator+(std::string l, int r);
var operator+(double l, std::string r);
var operator+(std::string l, double r);

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

var operator/(var l, var r);
var operator/(var l, int r);
var operator/(int l, var r);
var operator/(var l, double r);
var operator/(double l, var r);

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
bool operator==(var l, std::string r);
bool operator==(std::string l, var r);
bool operator==(int l, std::string r);
bool operator==(std::string l, int r);
bool operator==(double l, std::string r);
bool operator==(std::string l, double r);

bool operator!=(var l, var r);
bool operator!=(var l, int r);
bool operator!=(int l, var r);
bool operator!=(var l, double r);
bool operator!=(double l, var r);
bool operator!=(var l, std::string r);
bool operator!=(std::string l, var r);
bool operator!=(int l, std::string r);
bool operator!=(std::string l, int r);
bool operator!=(double l, std::string r);
bool operator!=(std::string l, double r);

bool operator!(var r);

double max(double a, double b);
double max(var a, var b);
double max(var a, double b);
double max(double a, var b);

double min(double a, double b);
double min(var a, var b);
double min(var a, double b);
double min(double a, var b);

