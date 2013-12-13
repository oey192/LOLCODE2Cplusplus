#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "var.h"
using namespace std;


var::var() {}

var::var(int iNum) {
	setVal(iNum);
}

var::var(double dNum) {
	setVal(dNum);
}

var::var(char *sVal) {
	setVal(string(sVal));
}

var::var(string sVal) {
	setVal(sVal);
}

void var::setVal(int iNum_) {
	iNum = iNum_;
	type = INT;
}
void var::setVal(double dNum_) {
	dNum = dNum_;
	type = DOUBLE;
}
void var::setVal(string sVal_) {
	sVal = sVal_;
	type = STRING;
}

int var::getiVal() {
	return iNum;
}

double var::getdVal() {
	return dNum;
}

string var::getsVal() {
	return sVal;
}

var& var::operator=(var rhs) {
	if (this != &rhs) {
		if (rhs.type == INT) {
			this->setVal(rhs.getiVal());
		} else if (rhs.type == DOUBLE) {
			this->setVal(rhs.getdVal());
		} else if (rhs.type == STRING) {
			this->setVal(rhs.getsVal());
		}
	}
	return *this;
}

var& var::operator=(int rhs) {
	setVal(rhs);

	return *this;
}

var& var::operator=(double rhs) {
	setVal(rhs);

	return *this;
}

var& var::operator=(const char rhs[]) {
	setVal(rhs);

	return *this;
}

var& var::operator=(string &rhs) {
	setVal(rhs);

	return *this;
}


var& var::operator+=(var rhs) {
	if (this != &rhs) {
		if (this->type == INT) {
			if (rhs.type == INT) {
				this->setVal(this->getiVal() + rhs.getiVal());
			} else if (rhs.type == DOUBLE) {
				this->setVal(this->getiVal() + rhs.getdVal());
			} else if (rhs.type == STRING) {
				ostringstream str;
				str << this->getiVal();
				this->setVal(str.str() + rhs.getsVal());
			}
		} else if (this->type == DOUBLE) {
			if (rhs.type == INT) {
				this->setVal(this->getdVal() + rhs.getiVal());
			} else if (rhs.type == DOUBLE) {
				this->setVal(this->getdVal() + rhs.getdVal());
			} else if (rhs.type == STRING) {
				ostringstream str;
				str << this->getdVal();
				this->setVal(str.str() + rhs.getsVal());
			}
		} else if (this->type == STRING) {
			if (rhs.type == INT) {
				ostringstream str;
				str << rhs.getiVal();
				this->setVal(this->getsVal() + str.str());
			} else if (rhs.type == DOUBLE) {
				ostringstream str;
				str << rhs.getdVal();
				this->setVal(this->getsVal() + str.str());
			} else if (rhs.type == STRING) {
				this->setVal(this->getsVal() + rhs.getsVal());
			}
		}
	}
	return *this;
}

var& var::operator+=(int rhs) {
	if (this->type == INT) {
		setVal(this->getiVal() + rhs);
	} else if (this->type == DOUBLE) {
		setVal(this->getdVal() + rhs);
	} else if (this->type == STRING) {
		ostringstream str;
		str << rhs;
		setVal(this->getsVal() + str.str());
	}

	return *this;
}

var& var::operator+=(double rhs) {
	if (this->type == INT) {
		setVal(this->getiVal() + rhs);
	} else if (this->type == DOUBLE) {
		setVal(this->getdVal() + rhs);
	} else if (this->type == STRING) {
		ostringstream str;
		str << rhs;
		setVal(this->getsVal() + str.str());
	}

	return *this;
}

var& var::operator+=(const char rhs[]) {
	if (this->type == INT) {
		ostringstream str;
		str << this->getiVal();
		setVal(str.str() + rhs);
	} else if (this->type == DOUBLE) {
		ostringstream str;
		str << this->getdVal();
		setVal(str.str() + rhs);
	} else if (this->type == STRING) {
		setVal(this->getsVal() + rhs);
	}

	return *this;
}

var& var::operator+=(string &rhs) {
	if (this->type == INT) {
		ostringstream str;
		str << this->getiVal();
		setVal(str.str() + rhs);
	} else if (this->type == DOUBLE) {
		ostringstream str;
		str << this->getdVal();
		setVal(str.str() + rhs);
	} else if (this->type == STRING) {
		setVal(this->getsVal() + rhs);
	}

	return *this;
}


istream& operator >> (istream &in, var &val) {
	double dVal;
	string sVal;
	in >> sVal;
	if (atof(sVal.c_str()) && sVal != "0" && sVal != "0.0") {
		dVal = atof(sVal.c_str());
		if (((int)dVal) == dVal) {
			val.setVal((int)dVal);
		} else {
			val.setVal(dVal);
		}
	} else {
		val.setVal(sVal);
	}
	return in;
}

ostream& operator << (ostream &out, var &val) {
	if (val.type == INT) {
		out << val.getiVal();
	} else if (val.type == DOUBLE) {
		out << val.getdVal();
	} else if (val.type == STRING) {
		out << val.getsVal();
	} else {
		out << "NULL";
	}
	return out;
}


var operator+(var l, var r) {
	var ans;
	if (l.type == INT) {
		if (r.type == INT) {
			ans.setVal(l.getiVal() + r.getiVal());
		} else if (r.type == DOUBLE) {
			ans.setVal(l.getiVal() + r.getdVal());
		} else if (r.type == STRING) {
			ostringstream str;
			str << l.getiVal();
			ans.setVal(str.str() + r.getsVal());
		}
	} else if (l.type == DOUBLE) {
		if (r.type == INT) {
			ans.setVal(l.getdVal() + r.getiVal());
		} else if (r.type == DOUBLE) {
			ans.setVal(l.getdVal() + r.getdVal());
		} else if (r.type == STRING) {
			ostringstream str;
			str << l.getdVal();
			ans.setVal(str.str() + r.getsVal());
		}
	} else if (l.type == STRING) {
		if (r.type == STRING) {
			ans.setVal(l.getsVal() + r.getsVal());
		} else if (r.type == INT) {
			ostringstream str;
			str << r.getiVal();
			ans.setVal(l.getsVal() + str.str());
		} else if (r.type == DOUBLE) {
			ostringstream str;
			str << r.getdVal();
			ans.setVal(l.getsVal() + str.str());
		}
	}
	return ans;
}

var operator+(var l, int r) {
	var ans;
	if (l.type == INT) {
		ans.setVal(l.getiVal() + r);
	} else if (l.type == DOUBLE) {
		ans.setVal(l.getdVal() + r);
	} else if (l.type == STRING) {
		ostringstream str;
		str << r;
		ans.setVal(l.getsVal() + str.str());
	}
	return ans;
}

var operator+(int l, var r) {
	var ans;
	if (r.type == INT) {
		ans.setVal(r.getiVal() + l);
	} else if (r.type == DOUBLE) {
		ans.setVal(r.getdVal() + l);
	} else if (r.type == STRING) {
		ostringstream str;
		str << l;
		ans.setVal(str.str() + r.getsVal());
	}
	return ans;
}

var operator+(var l, double r) {
	var ans;
	if (l.type == INT) {
		ans.setVal(l.getiVal() + r);
	} else if (l.type == DOUBLE) {
		ans.setVal(l.getdVal() + r);
	} else if (l.type == STRING) {
		ostringstream str;
		str << r;
		ans.setVal(l.getsVal() + str.str());
	}
	return ans;
}

var operator+(double l, var r) {
	var ans;
	if (r.type == INT) {
		ans.setVal(r.getiVal() + l);
	} else if (r.type == DOUBLE) {
		ans.setVal(r.getdVal() + l);
	} else if (r.type == STRING) {
		ostringstream str;
		str << l;
		ans.setVal(str.str() + r.getsVal());
	}
	return ans;
}

var operator+(var l, string r) {
	var ans;
	if (l.type == INT) {
		ostringstream str;
		str << l.getiVal();
		ans.setVal(str.str() + r);
	} else if (l.type == DOUBLE) {
		ostringstream str;
		str << l.getdVal();
		ans.setVal(str.str() + r);
	} else if (l.type == STRING) {
		ans.setVal(l.getsVal() + r);
	}
	return ans;
}

var operator+(string l, var r) {
	var ans;
	if (r.type == INT) {
		ostringstream str;
		str << r.getiVal();
		ans.setVal(l + str.str());
	} else if (r.type == DOUBLE) {
		ostringstream str;
		str << r.getdVal();
		ans.setVal(l + str.str());
	} else if (r.type == STRING) {
		ans.setVal(l + r.getsVal());
	}
	return ans;
}

var operator+(int l, string r) {
	ostringstream str;
	str << l;
	var ans(str.str() + r);
	return ans;
}

var operator+(string l, int r) {
	ostringstream str;
	str << r;
	var ans(l + str.str());
	return ans;
}

var operator+(double l, string r) {
	ostringstream str;
	str << l;
	var ans(str.str() + r);
	return ans;
}

var operator+(string l, double r) {
	ostringstream str;
	str << r;
	var ans(l + str.str());
	return ans;
}

var operator-(var l, var r) {
	var ans;
	if (l.type == INT) {
		if (r.type == INT) {
			ans.setVal(l.getiVal() - r.getiVal());
		} else if (r.type == DOUBLE) {
			ans.setVal(l.getiVal() - r.getdVal());
		}
	} else if (l.type == DOUBLE) {
		if (r.type == INT) {
			ans.setVal(l.getdVal() - r.getiVal());
		} else if (r.type == DOUBLE) {
			ans.setVal(l.getdVal() - r.getdVal());
		}
	}
	return ans;
}

var operator-(var l, int r) {
	var ans;
	if (l.type == INT) {
		ans.setVal(l.getiVal() - r);
	} else if (l.type == DOUBLE) {
		ans.setVal(l.getdVal() - r);
	}
	return ans;
}

var operator-(int l, var r) {
	var ans;
	if (r.type == INT) {
		ans.setVal(l - r.getiVal());
	} else if (r.type == DOUBLE) {
		ans.setVal(l - r.getdVal());
	}
	return ans;
}

var operator-(var l, double r) {
	var ans;
	if (l.type == INT) {
		ans.setVal(l.getiVal() - r);
	} else if (l.type == DOUBLE) {
		ans.setVal(l.getdVal() - r);
	}
	return ans;
}

var operator-(double l, var r) {
	var ans;
	if (r.type == INT) {
		ans.setVal(l - r.getiVal());
	} else if (r.type == DOUBLE) {
		ans.setVal(l - r.getdVal());
	}
	return ans;
}


var operator*(var l, var r) {
	var ans;
	if (l.type == INT) {
		if (r.type == INT) {
			ans.setVal(l.getiVal() * r.getiVal());
		} else if (r.type == DOUBLE) {
			ans.setVal(l.getiVal() * r.getdVal());
		}
	} else if (l.type == DOUBLE) {
		if (r.type == INT) {
			ans.setVal(l.getdVal() * r.getiVal());
		} else if (r.type == DOUBLE) {
			ans.setVal(l.getdVal() * r.getdVal());
		}
	}
	return ans;
}

var operator*(var l, int r) {
	var ans;
	if (l.type == INT) {
		ans.setVal(l.getiVal() * r);
	} else if (l.type == DOUBLE) {
		ans.setVal(l.getdVal() * r);
	}
	return ans;
}

var operator*(int l, var r) {
	var ans;
	if (r.type == INT) {
		ans.setVal(l * r.getiVal());
	} else if (r.type == DOUBLE) {
		ans.setVal(l * r.getdVal());
	}
	return ans;
}

var operator*(var l, double r) {
	var ans;
	if (l.type == INT) {
		ans.setVal(l.getiVal() * r);
	} else if (l.type == DOUBLE) {
		ans.setVal(l.getdVal() * r);
	}
	return ans;
}

var operator*(double l, var r) {
	var ans;
	if (r.type == INT) {
		ans.setVal(l * r.getiVal());
	} else if (r.type == DOUBLE) {
		ans.setVal(l * r.getdVal());
	}
	return ans;
}


var operator/(var l, var r) {
	var ans;
	if (l.type == INT) {
		if (r.type == INT) {
			ans.setVal(1.0 * l.getiVal() / r.getiVal());
		} else if (r.type == DOUBLE) {
			ans.setVal(l.getiVal() / r.getdVal());
		}
	} else if (l.type == DOUBLE) {
		if (r.type == INT) {
			ans.setVal(l.getdVal() / r.getiVal());
		} else if (r.type == DOUBLE) {
			ans.setVal(l.getdVal() / r.getdVal());
		}
	}
	return ans;
}

var operator/(var l, int r) {
	var ans;
	if (l.type == INT) {
		ans.setVal(1.0 * l.getiVal() / r);
	} else if (l.type == DOUBLE) {
		ans.setVal(l.getdVal() / r);
	}
	return ans;
}

var operator/(int l, var r) {
	var ans;
	if (r.type == INT) {
		ans.setVal(1.0 * l / r.getiVal());
	} else if (r.type == DOUBLE) {
		ans.setVal(l / r.getdVal());
	}
	return ans;
}

var operator/(var l, double r) {
	var ans;
	if (l.type == INT) {
		ans.setVal(l.getiVal() / r);
	} else if (l.type == DOUBLE) {
		ans.setVal(l.getdVal() / r);
	}
	return ans;
}

var operator/(double l, var r) {
	var ans;
	if (r.type == INT) {
		ans.setVal(l / r.getiVal());
	} else if (r.type == DOUBLE) {
		ans.setVal(l / r.getdVal());
	}
	return ans;
}


var operator%(var l, var r) {
	var ans;
	if (l.type == INT) {
		if (r.type == INT) {
			ans.setVal(l.getiVal() % r.getiVal());
		}
	}
	return ans;
}

var operator%(var l, int r) {
	var ans;
	if (l.type == INT) {
		ans.setVal(l.getiVal() % r);
	}
	return ans;
}

var operator%(int l, var r) {
	var ans;
	if (r.type == INT) {
		ans.setVal(l % r.getiVal());
	}
	return ans;
}


bool operator&&(var l, var r) {
	bool ans = false;
	if (l.type == INT) {
		if (r.type == INT) {
			ans = (l.getiVal() && r.getiVal());
		} else if (r.type == DOUBLE) {
			ans = (l.getiVal() && r.getdVal());
		}
	} else if (l.type == DOUBLE) {
		if (r.type == INT) {
			ans = (l.getdVal() && r.getiVal());
		} else if (r.type == DOUBLE) {
			ans = (l.getdVal() && r.getdVal());
		}
	}
	return ans;
}

bool operator&&(var l, int r) {
	bool ans = false;
	if (l.type == INT) {
		ans = (l.getiVal() && r);
	} else if (l.type == DOUBLE) {
		ans = (l.getdVal() && r);
	}
	return ans;
}

bool operator&&(int l, var r) {
	bool ans = false;
	if (r.type == INT) {
		ans = (l && r.getiVal());
	} else if (r.type == DOUBLE) {
		ans = (l && r.getdVal());
	}
	return ans;
}

bool operator&&(var l, double r) {
	bool ans = false;
	if (l.type == INT) {
		ans = (l.getiVal() && r);
	} else if (l.type == DOUBLE) {
		ans = (l.getdVal() && r);
	}
	return ans;
}

bool operator&&(double l, var r) {
	bool ans = false;
	if (r.type == INT) {
		ans = (l && r.getiVal());
	} else if (r.type == DOUBLE) {
		ans = (l && r.getdVal());
	}
	return ans;
}


bool operator||(var l, var r) {
	bool ans = false;
	if (l.type == INT) {
		if (r.type == INT) {
			ans = (l.getiVal() || r.getiVal());
		} else if (r.type == DOUBLE) {
			ans = (l.getiVal() || r.getdVal());
		}
	} else if (l.type == DOUBLE) {
		if (r.type == INT) {
			ans = (l.getdVal() || r.getiVal());
		} else if (r.type == DOUBLE) {
			ans = (l.getdVal() || r.getdVal());
		}
	}
	return ans;
}

bool operator||(var l, int r) {
	bool ans = false;
	if (l.type == INT) {
		ans = (l.getiVal() || r);
	} else if (l.type == DOUBLE) {
		ans = (l.getdVal() || r);
	}
	return ans;
}

bool operator||(int l, var r) {
	bool ans = false;
	if (r.type == INT) {
		ans = (l || r.getiVal());
	} else if (r.type == DOUBLE) {
		ans = (l || r.getdVal());
	}
	return ans;
}

bool operator||(var l, double r) {
	bool ans = false;
	if (l.type == INT) {
		ans = (l.getiVal() || r);
	} else if (l.type == DOUBLE) {
		ans = (l.getdVal() || r);
	}
	return ans;
}

bool operator||(double l, var r) {
	bool ans = false;
	if (r.type == INT) {
		ans = (l || r.getiVal());
	} else if (r.type == DOUBLE) {
		ans = (l || r.getdVal());
	}
	return ans;
}


bool operator==(var l, var r) {
	bool ans = false;
	if (l.type == INT) {
		if (r.type == INT) {
			ans = (l.getiVal() == r.getiVal());
		} else if (r.type == DOUBLE) {
			ans = (l.getiVal() == r.getdVal());
		} else if (r.type == STRING) {
			ostringstream str;
			str << l.getiVal();
			ans = (str.str() == r.getsVal());
		}
	} else if (l.type == DOUBLE) {
		if (r.type == INT) {
			ans = (l.getdVal() == r.getiVal());
		} else if (r.type == DOUBLE) {
			ans = (l.getdVal() == r.getdVal());
		} else if (r.type == STRING) {
			ostringstream str;
			str << l.getdVal();
			ans = (str.str() == r.getsVal());
		}
	} else if (l.type == STRING) {
		if (r.type == INT) {
			ostringstream str;
			str << r.getiVal();
			ans = (l.getsVal() == str.str());
		} else if (r.type == DOUBLE) {
			ostringstream str;
			str << r.getdVal();
			ans = (l.getsVal() == str.str());
		} else if (r.type == STRING) {
			ans = l.getsVal() == r.getsVal();
		}
	}
	return ans;
}

bool operator==(var l, int r) {
	bool ans = false;
	if (l.type == INT) {
		ans = (l.getiVal() == r);
	} else if (l.type == DOUBLE) {
		ans = (l.getdVal() == r);
	} else if (l.type == STRING) {
		ostringstream str;
		str << r;
		ans = (l.getsVal() == str.str());
	}
	return ans;
}

bool operator==(int l, var r) {
	bool ans = false;
	if (r.type == INT) {
		ans = (l == r.getiVal());
	} else if (r.type == DOUBLE) {
		ans = (l == r.getdVal());
	} else if (r.type == STRING) {
		ostringstream str;
		str << l;
		ans = (str.str() == r.getsVal());
	}
	return ans;
}

bool operator==(var l, double r) {
	bool ans = false;
	if (l.type == INT) {
		ans = (l.getiVal() == r);
	} else if (l.type == DOUBLE) {
		ans = (l.getdVal() == r);
	} else if (l.type == STRING) {
		ostringstream str;
		str << r;
		ans = (l.getsVal() == str.str());
	}
	return ans;
}

bool operator==(double l, var r) {
	bool ans = false;
	if (r.type == INT) {
		ans = (l == r.getiVal());
	} else if (r.type == DOUBLE) {
		ans = (l == r.getdVal());
	} else if (r.type == STRING) {
		ostringstream str;
		str << l;
		ans = (str.str() == r.getsVal());
	}
	return ans;
}

bool operator==(var l, string r) {
	bool ans = false;
	if (l.type == INT) {
		ostringstream str;
		str << l.getiVal();
		ans = (str.str() == r);
	} else if (l.type == DOUBLE) {
		ostringstream str;
		str << l.getdVal();
		ans = (str.str() == r);
	} else if (l.type == STRING) {
		ans = (l.getsVal() == r);
	}
	return ans;
}

bool operator==(string l, var r) {
	bool ans = false;
	if (r.type == INT) {
		ostringstream str;
		str << r.getiVal();
		ans = (l == str.str());
	} else if (r.type == DOUBLE) {
		ostringstream str;
		str << r.getdVal();
		ans = (l == str.str());
	} else if (r.type == STRING) {
		ans = (l == r.getsVal());
	}
	return ans;
}

bool operator==(int l, string r) {
	ostringstream str;
	str << l;
	return (str.str() == r);
}

bool operator==(string l, int r) {
	ostringstream str;
	str << r;
	return (l == str.str());
}

bool operator==(double l, string r) {
	ostringstream str;
	str << l;
	return (str.str() == r);
}

bool operator==(string l, double r) {
	ostringstream str;
	str << r;
	return (l == str.str());
}


bool operator!=(var l, var r) {
	bool ans = false;
	if (l.type == INT) {
		if (r.type == INT) {
			ans = (l.getiVal() != r.getiVal());
		} else if (r.type == DOUBLE) {
			ans = (l.getiVal() != r.getdVal());
		} else if (r.type == STRING) {
			ostringstream str;
			str << l.getiVal();
			ans = (str.str() != r.getsVal());
		}
	} else if (l.type == DOUBLE) {
		if (r.type == INT) {
			ans = (l.getdVal() != r.getiVal());
		} else if (r.type == DOUBLE) {
			ans = (l.getdVal() != r.getdVal());
		} else if (r.type == STRING) {
			ostringstream str;
			str << l.getdVal();
			ans = (str.str() != r.getsVal());
		}
	} else if (l.type == STRING) {
		if (r.type == INT) {
			ostringstream str;
			str << r.getiVal();
			ans = (l.getsVal() != str.str());
		} else if (r.type == DOUBLE) {
			ostringstream str;
			str << r.getdVal();
			ans = (l.getsVal() != str.str());
		} else if (r.type == STRING) {
			ans = l.getsVal() != r.getsVal();
		}
	}
	return ans;
}

bool operator!=(var l, int r) {
	bool ans = false;
	if (l.type == INT) {
		ans = (l.getiVal() != r);
	} else if (l.type == DOUBLE) {
		ans = (l.getdVal() != r);
	} else if (l.type == STRING) {
		ostringstream str;
		str << r;
		ans = (l.getsVal() != str.str());
	}
	return ans;
}

bool operator!=(int l, var r) {
	bool ans = false;
	if (r.type == INT) {
		ans = (l != r.getiVal());
	} else if (r.type == DOUBLE) {
		ans = (l != r.getdVal());
	} else if (r.type == STRING) {
		ostringstream str;
		str << l;
		ans = (str.str() != r.getsVal());
	}
	return ans;
}

bool operator!=(var l, double r) {
	bool ans = false;
	if (l.type == INT) {
		ans = (l.getiVal() != r);
	} else if (l.type == DOUBLE) {
		ans = (l.getdVal() != r);
	} else if (l.type == STRING) {
		ostringstream str;
		str << r;
		ans = (l.getsVal() != str.str());
	}
	return ans;
}

bool operator!=(double l, var r) {
	bool ans = false;
	if (r.type == INT) {
		ans = (l != r.getiVal());
	} else if (r.type == DOUBLE) {
		ans = (l != r.getdVal());
	} else if (r.type == STRING) {
		ostringstream str;
		str << l;
		ans = (str.str() != r.getsVal());
	}
	return ans;
}

bool operator!=(var l, string r) {
	bool ans = false;
	if (l.type == INT) {
		ostringstream str;
		str << l.getiVal();
		ans = (str.str() != r);
	} else if (l.type == DOUBLE) {
		ostringstream str;
		str << l.getdVal();
		ans = (str.str() != r);
	} else if (l.type == STRING) {
		ans = (l.getsVal() != r);
	}
	return ans;
}

bool operator!=(string l, var r) {
	bool ans = false;
	if (r.type == INT) {
		ostringstream str;
		str << r.getiVal();
		ans = (l != str.str());
	} else if (r.type == DOUBLE) {
		ostringstream str;
		str << r.getdVal();
		ans = (l != str.str());
	} else if (r.type == STRING) {
		ans = (l != r.getsVal());
	}
	return ans;
}

bool operator!=(int l, string r) {
	ostringstream str;
	str << l;
	return (str.str() != r);
}

bool operator!=(string l, int r) {
	ostringstream str;
	str << r;
	return (l != str.str());
}

bool operator!=(double l, string r) {
	ostringstream str;
	str << l;
	return (str.str() != r);
}

bool operator!=(string l, double r) {
	ostringstream str;
	str << r;
	return (l != str.str());
}


bool operator!(var r) {
	bool ans = false;
	if (r.type == INT) {
		ans = !r.getiVal();
	} else if (r.type == DOUBLE) {
		ans = !r.getdVal();
	} else if (r.type == STRING) {
		ans = r.getsVal().length() == 0;
	}
	return ans;
}

double max(double a, double b) {
	return (a > b) ? a : b;
}

double max(var a, var b) {
	if (a.type == INT) {
		if (b.type == INT) {
			return max(a.getiVal(), b.getiVal());
		} else if (b.type == DOUBLE) {
			return max(a.getiVal(), b.getdVal());
		} else {
			return 0;
		}
	} else if (a.type == DOUBLE) {
		if (b.type == INT) {
			return max(a.getdVal(), b.getiVal());
		} else if (b.type == DOUBLE) {
			return max(a.getdVal(), b.getdVal());
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

double max(var a, double b) {
	if (a.type == INT) {
		return max(a.getiVal(), b);
	} else if (a.type == DOUBLE) {
		return max(a.getdVal(), b);
	} else {
		return 0;
	}
}

double max(double a, var b) {
	if (b.type == INT) {
		return max(a, b.getiVal());
	} else if (b.type == DOUBLE) {
		return max(a, b.getdVal());
	} else {
		return 0;
	}
}


double min(double a, double b) {
	return (a < b) ? a : b;
}

double min(var a, var b) {
	if (a.type == INT) {
		if (b.type == INT) {
			return min(a.getiVal(), b.getiVal());
		} else if (b.type == DOUBLE) {
			return min(a.getiVal(), b.getdVal());
		} else {
			return 0;
		}
	} else if (a.type == DOUBLE) {
		if (b.type == INT) {
			return min(a.getdVal(), b.getiVal());
		} else if (b.type == DOUBLE) {
			return min(a.getdVal(), b.getdVal());
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

double min(var a, double b) {
	if (a.type == INT) {
		return min(a.getiVal(), b);
	} else if (a.type == DOUBLE) {
		return min(a.getdVal(), b);
	} else {
		return 0;
	}
}

double min(double a, var b) {
	if (b.type == INT) {
		return min(a, b.getiVal());
	} else if (b.type == DOUBLE) {
		return min(a, b.getdVal());
	} else {
		return 0;
	}
}
