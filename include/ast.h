
#pragma once
#include <memory>
#include <list>
#include <utility>
#include <string>

//#include "token.h"
using namespace std;

class ASTNode
{
public:
	//virtual double eval() const=0;
	virtual void print(std::ostream &out) const=0;
	virtual void translate(std::ostream &out)=0;
	virtual ~ASTNode();
};
typedef std::shared_ptr < ASTNode > ASTNodeSP;

std::ostream& operator << (std::ostream &out, const ASTNode &node);

class ASTTrue : public ASTNode
{
public:
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
};

class ASTSTDIO : public ASTNode
{
public:
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
};

class ASTPlusEquals : public ASTNode
{
public:
	int val;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTPlusEquals(int val_);
};
typedef std::shared_ptr < ASTPlusEquals > ASTPlusEqualsSP;

class ASTNumber : public ASTNode
{
public:
	double value;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTNumber(double value_);
};

class ASTString : public ASTNode
{
public:
	std::string value;
	//virtual double eval() const;
	//std::string str() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTString(const std::string &value_);
};

class ASTVariable : public ASTNode
{
public:
	std::string name;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTVariable(const std::string &name_);
};
typedef std::shared_ptr < ASTVariable > ASTVariableSP;

class ASTVarDeclaration : public ASTNode
{
public:
	ASTVariableSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTVarDeclaration(const ASTVariableSP &lhs_);
	ASTVarDeclaration(const ASTVariableSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTVarAssignment : public ASTNode
{
public:
	ASTVariableSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTVarAssignment(const ASTVariableSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTSum : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTSum(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTSub : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTSub(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTProduct : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTProduct(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTDiv : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTDiv(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTMod : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTMod(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTEq : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTEq(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTNeq : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTNeq(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTAnd : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTAnd(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTOr : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTOr(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTXor : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTXor(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTNot : public ASTNode
{
public:
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTNot(const ASTNodeSP &rhs_);
};

class ASTMax : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTMax(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTMin : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTMin(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTSmoosh : public ASTNode
{
public:
	ASTNodeSP lhs;
	ASTNodeSP rhs;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTSmoosh(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTExpressions : public ASTNode
{
public:
	typedef std::list < ASTNodeSP > Expressions;
	Expressions expressions;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTExpressions();
	ASTExpressions(const ASTNodeSP &statement);
};
typedef std::shared_ptr < ASTExpressions > ASTExpressionsSP;

class ASTStatements : public ASTNode
{
public:
	typedef std::list < ASTNodeSP > Statements;
	Statements statements;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTStatements();
	ASTStatements(const ASTNodeSP &statement);
};
typedef std::shared_ptr < ASTStatements > ASTStatementsSP;

class ASTIf : public ASTNode
{
public:
	typedef std::list<std::pair<ASTNodeSP, ASTStatementsSP> > Clauses;
	Clauses clauses;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTIf();
};

class ASTLoop : public ASTNode
{
public:
	ASTPlusEqualsSP operation;
	ASTVariableSP var;
	ASTNodeSP condition;
	ASTStatementsSP statements;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTLoop(const ASTPlusEqualsSP &operation_, const ASTVariableSP &var_, const ASTNodeSP condition_, const ASTStatementsSP &statements_);
};

class ASTIn : public ASTNode
{
public:
	ASTVariableSP var;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTIn(const ASTVariableSP &var_);
};

class ASTOut : public ASTNode
{
public:
	bool newline;
	ASTExpressionsSP expressions;
	//virtual double eval() const;
	virtual void print(std::ostream &out) const;
	virtual void translate(std::ostream &out);
	ASTOut(const ASTExpressionsSP &expressions_, bool newline_);
};
