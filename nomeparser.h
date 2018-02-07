#ifndef NOMEPARSER_H
#define NOMEPARSER_H

#include <vector>
#include "parameterbank.h"
#include "nomeglwidget.h"
#include "mesh.h"
#include "polyline.h"
#include "group.h"
#include "utils.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "bspline.h"
#include "newNOME/Session.h"

class NomeParser
{
public:
    NomeParser();
    Session* makeWithNome(vector<ParameterBank> &banks,
                      unordered_map<string, Parameter> &params,
                      Group &group,
                      string input,
                      vector<string> &colorlines,
                      vector<string> &banklines,
                      vector<string> &geometrylines,
                      vector<int> &postProcessingLines,
                      vector<string> &postProcessingLinesString,
                      unordered_map<string, Vertex*> &global_vertices, unordered_map<string, Face*> &global_faces);

    int postProcessingWithNome(unordered_map<string, Parameter> &params,
                                vector<int> &postProcessingLines,
                                SlideGLWidget * canvas,
                                Group &group,
                                string input,
                                vector<string> &postProcessingLinesString,
                                unordered_map<string, Vertex*> &global_vertices, unordered_map<string, Face*> &global_faces);

    void appendWithANOM(unordered_map<string, Parameter> &params,
                        Group &group,
                        SlideGLWidget * canvas,
                        string input);

};

#endif // MINISLFPARSER_H
