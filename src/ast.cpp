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

void ASTTrue::print(std::ostream &out) const
{
	out << "true";
}

void ASTTrue::translate(std::ostream &out)
{
	out << "true";
}

void ASTSTDIO::print(std::ostream &out) const
{
	out << "#include <stdio.h>";
}

void ASTSTDIO::translate(std::ostream &out)
{
	out << "//<iostream> properly included!" << endl;
}

ASTPlusEquals::ASTPlusEquals(int val_) {
	val = val_;
}

void ASTPlusEquals::print(std::ostream &out) const
{
	out << "+=" << val;
}

void ASTPlusEquals::translate(std::ostream &out)
{
	out << "+=" << val;
}

ASTVariable::ASTVariable(const std::string &name_):name(name_){}

void ASTVariable::print(std::ostream &out) const
{
	out << name;
}

void ASTVariable::translate(std::ostream &out)
{
	out << " " << name << " ";
}

ASTString::ASTString(const std::string &value_):value(value_){}


void ASTString::print(std::ostream &out) const
{
	out << value;
}

void ASTString::translate(std::ostream &out)
{
	out << " " << value << " ";
}

ASTNumber::ASTNumber(double value_):value(value_){}

void ASTNumber::print(std::ostream &out) const 
{ 
	out << value;
}

void ASTNumber::translate(std::ostream &out)
{
	out << " " << value << " ";
}

ASTVarDeclaration::ASTVarDeclaration(const ASTVariableSP &lhs_): lhs(lhs_){}

ASTVarDeclaration::ASTVarDeclaration(const ASTVariableSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

void ASTVarDeclaration::print(std::ostream &out) const
{
	out << "var " << *lhs << "=" << *rhs << endl;
}

void ASTVarDeclaration::translate(std::ostream &out)
{
	out <<"var ";
	lhs->translate(out);
	if (rhs) {
		out << " = ";
		rhs->translate(out);
	}
	out << ";" << endl;
}

ASTVarAssignment::ASTVarAssignment(const ASTVariableSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}


void ASTVarAssignment::print(std::ostream &out) const
{
	out << *lhs << "=" << *rhs << endl;
}

void ASTVarAssignment::translate(std::ostream &out)
{
	lhs->translate(out);
	out << " = ";
	rhs->translate(out);
	out << ";" << endl;
}

ASTSum::ASTSum(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_):lhs(lhs_), rhs(rhs_){}

void ASTSum::print(std::ostream &out) const
{
	out << "(" << *lhs << "+" << *rhs << ")";
}

void ASTSum::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " + ";
	rhs->translate(out);
	out << " ";
}

ASTSub::ASTSub(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_):lhs(lhs_), rhs(rhs_){}


void ASTSub::print(std::ostream &out) const
{
	out << "(" << *lhs << "-" << *rhs << ")";
}

void ASTSub::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " - ";
	rhs->translate(out);
	out << " ";
}

ASTProduct::ASTProduct(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}


void ASTProduct::print(std::ostream &out) const
{
  out << "(" << *lhs << "*" << *rhs << ")";
}

void ASTProduct::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " * ";
	rhs->translate(out);
	out << " ";
}

ASTDiv::ASTDiv(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

void ASTDiv::print(std::ostream &out) const
{
	out << "(" << *lhs << "/" << *rhs << ")";
}

void ASTDiv::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " / ";
	rhs->translate(out);
	out << " ";
}

ASTMod::ASTMod(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}


void ASTMod::print(std::ostream &out) const
{
	out << "(" << *lhs << "%" << *rhs << ")";
}

void ASTMod::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " % ";
	rhs->translate(out);
	out << " ";
}

ASTEq::ASTEq(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

void ASTEq::print(std::ostream &out) const
{
	out << "(" << *lhs << "==" << *rhs << ")";
}

void ASTEq::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " == ";
	rhs->translate(out);
	out << " ";
}

ASTNeq::ASTNeq(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

void ASTNeq::print(std::ostream &out) const
{
	out << "(" << *lhs << "!=" << *rhs << ")";
}

void ASTNeq::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " != ";
	rhs->translate(out);
	out << " ";
}

ASTAnd::ASTAnd(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

void ASTAnd::print(std::ostream &out) const
{
	out << "(" << *lhs << "&&" << *rhs << ")";
}

void ASTAnd::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " && ";
	rhs->translate(out);
	out << " ";
}

ASTOr::ASTOr(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

void ASTOr::print(std::ostream &out) const
{
	out << "(" << *lhs << "||" << *rhs << ")";
}

void ASTOr::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " || ";
	rhs->translate(out);
	out << " ";
}

ASTXor::ASTXor(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

void ASTXor::print(std::ostream &out) const
{
	out << "(" << *lhs << "^^" << *rhs << ")";
}

void ASTXor::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " != ";
	rhs->translate(out);
	out << " ";
}

ASTNot::ASTNot(const ASTNodeSP &rhs_): rhs(rhs_){}

void ASTNot::print(std::ostream &out) const
{
	out << "!(" << *rhs << ")";
}

void ASTNot::translate(std::ostream &out)
{
	out << " !";
	rhs->translate(out);
	out << " ";
}

ASTMax::ASTMax(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

void ASTMax::print(std::ostream &out) const
{
	out << "max(" << *lhs << "," << *rhs << ")";
}

void ASTMax::translate(std::ostream &out)
{
	out << " max(";
	lhs->translate(out);
	out << ", ";
	rhs->translate(out);
	out << ")";
}

ASTMin::ASTMin(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

void ASTMin::print(std::ostream &out) const
{
	out << "min(" << *lhs << "," << *rhs << ")";
}

void ASTMin::translate(std::ostream &out)
{
	out << " min(";
	lhs->translate(out);
	out << ", ";
	rhs->translate(out);
	out << ")";
}

ASTSmoosh::ASTSmoosh(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_): lhs(lhs_), rhs(rhs_){}

void ASTSmoosh::print(std::ostream &out) const
{
	out << "(" << *lhs << "+" << *rhs << ")";
}

void ASTSmoosh::translate(std::ostream &out)
{
	out << " ";
	lhs->translate(out);
	out << " + ";
	rhs->translate(out);
	out << " ";
}

ASTExpressions::ASTExpressions() {}

ASTExpressions::ASTExpressions(const ASTNodeSP &expression) {
	expressions.push_back(expression);
}

void ASTExpressions::print(std::ostream &out) const
{
	for (Expressions::const_iterator i = expressions.begin();
		 i != expressions.end(); ++i){
		(*i)->print(out);
	}
}

void ASTExpressions::translate(std::ostream &out)
{
	for (Expressions::const_iterator i = expressions.begin();
		 i != expressions.end(); ++i) {
		(*i)->translate(out);
	}
}

ASTStatements::ASTStatements() {}

ASTStatements::ASTStatements(const ASTNodeSP &statement) {
	statements.push_back(statement);
}

void ASTStatements::print(std::ostream &out) const
{
	for (Statements::const_iterator i = statements.begin();
		 i != statements.end(); ++i){
		(*i)->print(out); out << endl;
	}
}

void ASTStatements::translate(std::ostream &out)
{
	for (Statements::const_iterator i = statements.begin();
		 i != statements.end(); ++i) {
		(*i)->translate(out);
		out << ";" << endl;
	}
}

ASTIf::ASTIf(){}

void ASTIf::print(std::ostream &out) const
{
	out << "if statement" << endl;
}

void ASTIf::translate(std::ostream &out)
{
	int j = 0;
	for (Clauses::const_iterator i = clauses.begin(); i != clauses.end(); ++i) {
		if (j == 0) {
			out << "if (";
			(*i).first->translate(out);
			out << ") {" << endl;
			(*i).second->translate(out);
			out << "}";
		} else {
			out << "else if (";
			(*i).first->translate(out);
			out << ") {" << endl;
			(*i).second->translate(out);
			out << "}";
		}
		out << endl;
		++j;
	}
}

ASTLoop::ASTLoop(const ASTPlusEqualsSP &operation_, const ASTVariableSP &var_, const ASTNodeSP condition_, const ASTStatementsSP &statements_)
  : operation(operation_), var(var_), condition(condition_), statements(statements_){}

void ASTLoop::print(std::ostream &out) const
{
  out << "for loop" << endl;
}

void ASTLoop::translate(std::ostream &out)
{
	out << "for (; ";
	condition->translate(out);
	out << "; ";
	var->translate(out);
	operation->translate(out);
	out << ") {" << endl;
	statements->translate(out);
	out << "}" << endl;
}

ASTIn::ASTIn(const ASTVariableSP &var_)
  : var(var_)
{}

void ASTIn::print(std::ostream &out) const
{
  out << "Input into " << var << endl;
}

void ASTIn::translate(std::ostream &out)
{
  out << "cin >> ";
  var->translate(out);
  out << ";" << endl;
}

ASTOut::ASTOut(const ASTExpressionsSP &expressions_, bool newline_)
  : expressions(expressions_), newline(newline_)
{}

void ASTOut::print(std::ostream &out) const
{
  out << "Output " << expressions;
  if (newline) out << endl;
}

void ASTOut::translate(std::ostream &out)
{
  out << "cout << ";
  int j = 0;
  for (ASTExpressions::Expressions::const_iterator i = expressions->expressions.begin(); i != expressions->expressions.end(); ++i) {
  		if (j > 0) out << "<<";
		(*i)->translate(out);
		++j;
	}
  if (newline) out << " << endl";
  out << ";" << endl;
}

