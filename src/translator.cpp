#include "translator.h"

#include <iostream>
#include <fstream>

using namespace std;

Translator::~Translator() {}

class CPPTranslator : public Translator
{
public:
	std::string name;
	std::ostream *out;
	ASTNodeSP program;

	void header(){
		(*out) << "#include <iostream>" << endl;
		(*out) << "#include <string>" << endl;
		(*out) << "using namespace std;" << endl;
		(*out) << endl;
		(*out) << "int main(int argc, char *argv[]) {" << endl;
	}
	void footer(){
		(*out) << endl << "    return 0;" << endl;
		(*out) << "}" << endl;
	}
	void body(){
		program->translate(*out);
	}
	void generate(){
		header();
		body();
		footer();
	}
	void translate(const std::string &file, ASTNodeSP program_){
		name = file.substr(0,file.length()-4);
		out = new ofstream(file.c_str());
		program = program_;
		generate();
		delete out;
	}
	~CPPTranslator();
};

TranslatorSP CreateCPPTranslator() {
	return TranslatorSP(new CPPTranslator());
}
