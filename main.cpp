#include "Lexer.h"
#include "MatcherAutomaton.h"
#include "Parser.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Interpreter.h"
int main(int argc, char** argv) {

    std::string fileName = argv[1];
    std::string line;
    //ifstream input("Lab1PassOffCases/1-70/input1.txt");
    std::ifstream input(fileName);
    std::string content( (std::istreambuf_iterator<char>(input) ),
                         (std::istreambuf_iterator<char>()    ) );

    Lexer* lexer = new Lexer();
    lexer->Run(content);
    //std::cout << lexer->toString();

    std::vector<Token*> withComments = lexer->ReturnTokens();
    std::vector<Token*> noComments;
    for(size_t i = 0; i < withComments.size(); i++) {
        if(withComments.at(i)->tokenTypeToString() == "COMMENT") {
            //do nothing
        }
        else {
            noComments.push_back(withComments.at(i));
        }
    }

    Parser* parser = new Parser(noComments);

    try {
        parser->Parse();
        //TODO make this just the tostring of parser
        //std::cout << "Success!" << std::endl;
        //std::cout << parser->toString();
        Interpreter* interp = new Interpreter(parser->getDataLog());
        std::cout << interp->printDB() << std::endl;
    }
    catch (Token* error) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << error->toString();
    }





    delete lexer;

    return 0;
}