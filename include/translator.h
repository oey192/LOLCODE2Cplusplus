#pragma once

#include <string>
#include <memory>
#include "ast.h"
class Translator
{
 public:
  virtual void translate(const std::string &file, ASTNodeSP program)=0;
  ~Translator();
};
typedef std::tr1::shared_ptr < Translator > TranslatorSP;

TranslatorSP CreateJasminTranslator();
