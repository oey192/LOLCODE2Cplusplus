#pragma once

#include <tr1/memory>
#include <list>
#include <pair>

#include "token.h"

class ASTNode
{
 public:
  virtual void print(std::ostream &out) const=0;
  virtual void translate(std::ostream &out)=0;
  virtual ~ASTNode();
};

std::ostream& operator<< (std::ostream&out, const ASTNode &node);

typedef std::tr1::shared_ptr < ASTNode > ASTNodeSP;

class ASTSymbol : public ASTNode
{
 public:
  std::string name;
  ASTSymbol(const std::string &name_);
  virtual void print(std::ostream &out) const;
  virtual void translate(std::ostream &out);
};

class ASTString : public ASTNode
{
public:
  std::string value;
  ASTString(const std::string &name_);
  virtual void print(std::ostream &out) const;
  virtual void translate(std::ostream &out);
};

class ASTNumber : public ASTNode
{
 public:
  double value;
  ASTNumber(double value_);
  virtual void print(std::ostream &out) const;
  virtual void translate(std::ostream &out);
};

class ASTSum : public ASTNode
{
 public:
  ASTNodeSP lhs;
  ASTNodeSP rhs;
  virtual void print(std::ostream &out) const;
  virtual void translate(std::ostream &out);
  ASTSum(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTSub : public ASTNode
{
public:
  ASTNodeSP lhs;
  ASTNodeSP rhs;
  virtual void print(std::ostream &out) const;
  virtual void translate(std::ostream &out);
  ASTSub(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTProduct : public ASTNode
{
 public:
  ASTNodeSP lhs;
  ASTNodeSP rhs;
  virtual void print(std::ostream &out) const;
  virtual void translate(std::ostream &out);
  ASTProduct(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTDiv : public ASTNode
{
 public:
  ASTNodeSP lhs;
  ASTNodeSP rhs;
  virtual void print(std::ostream &out) const;
  virtual void translate(std::ostream &out);
  ASTDiv(const ASTNodeSP &lhs_, const ASTNodeSP &rhs_);
};

class ASTExpression : public ASTNode
{
public:
  ASTNodeSP lhs;
  ASTNodeSP rhs;
  std::string op;
  bool value;
  virtual void print(std::ostream &out) const;
  virtual void translate(std::ostream &out);
  ASTExpression(bool value_);
  ASTExpression(const ASTNodeSP &lhs_, const std::string op_, const ASTNodeSP &rhs_);
};

typedef std::tr1::shared_ptr < ASTExpression > ASTExpressionSP;

class ASTStatements : public ASTNode
{
 public:
  typedef std::list < ASTNodeSP > Statements;
  Statements statements;
  virtual void print(std::ostream &out) const;
  virtual void translate(std::ostream &out);
  ASTStatements();
};

typedef std::tr1::shared_ptr < ASTStatements > ASTStatementsSP;

class ASTCond : public ASTNode
{
  typedef std::list<std::pair<ASTExpressionSP, ASTStatementsSP> > Clauses;
  Clauses c;
  virtual void print(std::ostream &out) const;
  virtual void translate(std::ostream &out);
  ASTCond();
};
