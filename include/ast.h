#pragma once
#include <memory>
#include <list>
#include <utility>
#include <string>
#include <

//#include "token.h"
using namespace std;

class ASTNode
{
public:
	virtual double eval() const=0;
	virtual void print(std::ostream &out) const=0;
	virtual void translate(std::ostream &out)=0;
	virtual ~ASTNode();
};
typedef std::shared_ptr < ASTNode > ASTNodeSP;
std::ostream& operator << (std::ostream &out, const ASTNode &node);


class ASTNumber : public ASTNode
{
public:
	double value;
	ASTNumber(double value_);
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
};
typedef std::shared_ptr < ASTNumber > ASTNumberSP;

class ASTString : public ASTNode
{
public:
	std::string value;
	ASTString(const std::string &value_);
	virtual double eval() const;
	std::string str() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
};
typedef std::shared_ptr < ASTString > ASTStringSP;

class ASTSymbol : public ASTNode
{
public:
	std::string name;
	ASTNumberSP val;
	ASTStringSP value;
	ASTSymbol(const std::string &name_);
	ASTSymbol(const std::string &name_, const ASTNumberSP &val_);
	ASTSymbol(const std::string &name_, const ASTStringSP &value_);
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
};
typedef std::shared_ptr < ASTSymbol > ASTSymbolSP;

class ASTSum : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTSum(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTSub : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTSub(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTProduct : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTProduct(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTDiv : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTDiv(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTExpression : public ASTNode
{
public:
	ASTNodeSP expr;
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTExpression(const ASTNodeSP &expr_);
};
typedef std::shared_ptr < ASTExpression > ASTExpressionSP;

class ASTStatements : public ASTNode
{
public:
	typedef std::list < ASTNodeSP > Statements;
	Statements statements;
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTStatements();
};
typedef std::shared_ptr < ASTStatements > ASTStatementsSP;

class ASTCond : public ASTNode
{
public:
	typedef std::list<std::pair<ASTExpressionSP, ASTStatementsSP> > Clauses;
	Clauses c;
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTCond();
};

class ASTIn : public ASTNode
{
public:
	ASTSymbolSP var;
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTIn(const ASTSymbolSP &var_);
};

class ASTOut : public ASTNode
{
public:
	ASTExpressionSP expr;
	virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTOut(const ASTExpressionSP &expr_);
};
