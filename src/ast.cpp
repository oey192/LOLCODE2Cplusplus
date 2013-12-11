#include "ast.h"
#include <iostream>
#include <iomanip>
#include <typeinfo>

using namespace std;

ASTNode::~ASTNode() {}

std::ostream& operator<< (std::ostream&out, const ASTNode &node)
{
  node.print(out);
  return out;
}

ASTSymbol::ASTSymbol(const std::string &name_):name(name_){}

ASTSymbol::ASTSymbol(const std::string &name_, const ASTNumberSP &val_):name(name_), val(val_){}

ASTSymbol::ASTSymbol(const std::string &name_, const ASTStringSP &value_):name(name_), value(value_){}

double ASTSymbol::eval() const
{
	return (val)? val->eval() : value->eval();
}

void ASTSymbol::print(std::ostream &out) const
{
	out << name;
}

void ASTSymbol::translate(std::ostream &out)
{
	if (value) {
		out << "string " << name << " = \"" << value->str() << "\";" << endl;
	} else {
		out << "double " << name << " = " << val->eval() << ";" << endl;
	}
}

ASTString::ASTString(const std::string &value_):value(value_){}

double ASTString::eval() const
{
	double ans = 0;
	for (unsigned int i = 0; i < value.length(); i++) ans += (char)value[i];
	return ans;
}

string ASTString::str() const
{
	return value;
}

void ASTString::print(std::ostream &out) const
{
	out << "\"" << value << "\"";
}

void ASTString::translate(std::ostream &out)
{
	out << " \"" << value << "\" ";
}

ASTNumber::ASTNumber(double value_):value(value_){}

double ASTNumber::eval() const
{
	return value;
}

void ASTNumber::print(std::ostream &out) const 
{ 
	out << value;
}

void ASTNumber::translate(std::ostream &out)
{
	out << " " << value << " ";
}

ASTSum::ASTSum(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_):lhs(lhs_), rhs(rhs_){}

double ASTSum::eval() const
{
	return lhs->eval() + rhs->eval();
}

void ASTSum::print(std::ostream &out) const
{
	out << "(" << *lhs << "+" << *rhs << ")";
}

void ASTSum::translate(std::ostream &out)
{
	lhs->translate(out);
	out << " + ";
	rhs->translate(out);
	out << endl;
}

ASTSub::ASTSub(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_):lhs(lhs_), rhs(rhs_){}

double ASTSub::eval() const
{
	return lhs->eval() - rhs->eval();
}

void ASTSub::print(std::ostream &out) const
{
	out << "(" << *lhs << "+" << *rhs << ")";
}

void ASTSub::translate(std::ostream &out)
{
	lhs->translate(out);
	out << " - ";
	rhs->translate(out);
	out << endl;
}

ASTProduct::ASTProduct(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

double ASTProduct::eval() const
{
	return lhs->eval() * rhs->eval();
}

void ASTProduct::print(std::ostream &out) const
{
  out << "(" << *lhs << "*" << *rhs << ")";
}

void ASTProduct::translate(std::ostream &out)
{
	lhs->translate(out);
	out << " * ";
	rhs->translate(out);
	out << endl;
}

ASTDiv::ASTDiv(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

double ASTDiv::eval() const
{
	return lhs->eval() / rhs->eval();
}

void ASTDiv::print(std::ostream &out) const
{
	out << "(" << *lhs << "*" << *rhs << ")";
}

void ASTDiv::translate(std::ostream &out)
{
	lhs->translate(out);
	out << " / ";
	rhs->translate(out);
	out << endl;
}

ASTExpression::ASTExpression(const ASTNodeSP &expr_): expr(expr_){}

double ASTExpression::eval() const
{
	return expr->eval();
}

void ASTExpression::print(std::ostream &out) const
{
	expr->print(out);
}

void ASTExpression::translate(std::ostream &out)
{
	expr->translate(out);
}

ASTStatements::ASTStatements()
{}

double ASTStatements::eval() const
{
	double ans = 0;
	for (Statements::const_iterator i = statements.begin();
		i != statements.end();
		++i) {
		ans += (*i)->eval();
	}
	return ans;
}

void ASTStatements::print(std::ostream &out) const
{
	for (Statements::const_iterator i = statements.begin();
		 i != statements.end(); ++i){
		(*i)->print(out); out << std::endl;
	}
}

void ASTStatements::translate(std::ostream &out)
{
	for (Statements::const_iterator i = statements.begin();
		 i != statements.end(); ++i) {
		(*i)->translate(out);
		out << endl;
	}
}

ASTIn::ASTIn(const ASTSymbolSP &var_)
  : var(var_)
{}

double ASTIn::eval() const
{
  return 0;
}

void ASTIn::print(std::ostream &out) const
{
  out << "Input into " << var << endl;
}

void ASTIn::translate(std::ostream &out)
{
  out << "cin >> " << var << ";" << endl;
}

ASTOut::ASTOut(const ASTExpressionSP &expr_)
  : expr(expr_)
{}

double ASTOut::eval() const
{
  return 0;
}

void ASTOut::print(std::ostream &out) const
{
  out << "Output " << expr << endl;
}

void ASTOut::translate(std::ostream &out)
{
  out << "cout << " << expr->eval() << " << endl;" << endl;
}

