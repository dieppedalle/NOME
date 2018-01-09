#include "nomeparser.h"
#include "nomeFlexBison.cpp"
#include "stlFlexBison.cpp"

NomeParser::NomeParser()
{

}

Session* NomeParser::makeWithNome(vector<ParameterBank> &banks,
                              unordered_map<string, Parameter> &params,
                              Group &group,
                              string input,
                              vector<string> &colorlines,
                              vector<string> &banklines,
                              vector<string> &geometrylines,
                              vector<int> &postProcessingLines,
                              vector<string> &postProcessingLinesString,
                              unordered_map<string, Vertex*> &global_vertices, unordered_map<string, Face*> &global_faces)
{
    if(input.substr(input.find_last_of(".") + 1) == "stl") {
        StlCompiler* stlCompilerSession = new StlCompiler (input);
        return stlCompilerSession->getSession();
    } else {
        NOMECompiler* nomeCompilerSession = new NOMECompiler (input);
        return nomeCompilerSession->getSession();
    }
}

