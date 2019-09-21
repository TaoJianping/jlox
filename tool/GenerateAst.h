//
// Created by taojianping on 2019/9/9.
//

#ifndef JLOX_GENERATEAST_H
#define JLOX_GENERATEAST_H


#include <string>
#include <vector>

class GenerateAst {

private:
    void defineAst(std::string outputDir, std::string basename, std::vector<std::string> types);

public:

    void main() {
        std::string outputDir = ".\\tool";
    }
};


#endif //JLOX_GENERATEAST_H
