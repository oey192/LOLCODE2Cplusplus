#include "ast.h"

#include <iostream>
#include <iomanip>

using namespace std;

ASTNode::~ASTNode() {}

std::ostream& operator<< (std::ostream&out, const ASTNode &node)
{
  node.print(out);
  return out;
}

ASTSymbol::ASTSymbol(const std::string &name_)
  : name(name_)
{}

void ASTSymbol::print(std::ostream &out) const
{
  out << name;
}

void ASTSymbol::translate(std::ostream &out)
{
  out << " " << name " ";
}

ASTNumber::ASTNumber(double value_) 
  : value(value_) 
{}

void ASTNumber::print(std::ostream &out) const 
{ 
  out << value;
}

void ASTNumber::translate(std::ostream &out)
{
  out << " " << value << " ";
}

ASTSum::ASTSum(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_)
  : lhs(lhs_), rhs(rhs_)
{}

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

ASTSub::ASTSub(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_)
  : lhs(lhs_), rhs(rhs_)
{}

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

ASTProduct::ASTProduct(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_)
  : lhs(lhs_), rhs(rhs_)
{}

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

ASTDiv::ASTDiv(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_)
  : lhs(lhs_), rhs(rhs_)
{}

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

ASTExpression::ASTExpression(bool value_)
{
  value = value_;
}

ASTExpression::ASTExpression(const ASTNodeSP &lhs_, const std::string op_, const ASTNodeSP &rhs_)
  : lhs(lhs_), op(op_), rhs(rhs_)
{}

ASTStatements::ASTStatements()
{}

void ASTStatements::print(std::ostream &out) const
{
  for (Statements::const_iterator i = statements.begin();
       i != statements.end();
       ++i) {
    (*i)->print(out); out << std::endl;
  }
}

void ASTStatements::translate(std::ostream &out)
{
  for (Statements::const_iterator i = statements.begin();
       i != statements.end();
       ++i) {

    (*i)->translate(out);
    out << endl;
  }
}



