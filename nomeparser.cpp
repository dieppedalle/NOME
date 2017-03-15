#include "nomeparser.h"

NomeParser::NomeParser()
{

}

bool testComments(string token)
{
    if(token[0] == '#') {
        return true;
    }
    return false;
}

/**
 * @brief warning: Helper function to output warnings.
 * @param type:
 *          0: Parameter reading error.
 *          1: Stoi exception. Line skipped.
 * @param lineNumber: The current line number.
 * @return
 */
string warning(int type, int lineNumber)
{
    switch(type)
    {
    case 0:
        return "Warning: parameter at line "
                + to_string(lineNumber) + " is not set because of insufficient parameters.";
    case 1:
        return "Warning: line " + to_string(lineNumber)
                + " contains string that can't be parsed, skipping this line.";
    case 2:
        return "Warning: parameter at line "
                + to_string(lineNumber) + " has duplicated names of existing parameters.";
    case 3:
        return "Warning: mesh at line "
                + to_string(lineNumber) + " has duplicated names of existing meshes.";
    case 4:
        return "Warning: group at line "
                + to_string(lineNumber) + " has duplicated names of existing groups.";
    case 5:
        return "Warninng: instance at line "
                + to_string(lineNumber) + " has not been created yet.";
    case 6:
        return "Warning: new instance at line"
                + to_string(lineNumber) + " does not have a name.";
    case 7:
        return "Warning: parameter name at line"
                + to_string(lineNumber) + " does not match any defined parameter.";
    case 8:
        return "Warning: parameter at line"
                + to_string(lineNumber) + " does not have a retored value.";
    case 9:
        return "Warning: vertex at line"
                + to_string(lineNumber) + " can't be restored.";
    case 10:
        return "Warning: point at line"
                + to_string(lineNumber) + " doesn't have a name. It can't be initiated.";
    case 11:
        return "Warning: point at line"
                + to_string(lineNumber) + " has already been created (duplicate names)." +
                                          " It can't be initiated.";
    case 12:
        return "Warning: polyline at line"
                + to_string(lineNumber) + " doesn't have a name. It can't be initiated.";
    case 13:
        return "Warning: polyline at line"
                + to_string(lineNumber) + " has already been created (duplicate names)." +
                                          " It can't be initiated.";
    case 14:
        return "Warning: vertex at line"
                + to_string(lineNumber) + " can't be added to polyline. It has not been created.";
    case 15:
        return "Warning: Color at line"
                + to_string(lineNumber) + " can't be assigned. It has not been created.";
    case 16:
        return "Warning: Color at line"
                + to_string(lineNumber) + " has already been created (duplicate names).";
    case 17:
        return "Warning: Color at line"
                + to_string(lineNumber) + " does not have enough input.";
    case 18:
        return "Warning: Instance at line"
                + to_string(lineNumber) + " does not complete color definition. " +
                "It can't be instantiated.";
    case 19:
        return "Warning: face at line"
                + to_string(lineNumber) + " doesn't have a name. It can't be initiated.";
    case 20:
        return "Warning: face at line"
                + to_string(lineNumber) + " has already been created (duplicate names)." +
                                          " It can't be initiated.";
    case 21:
        return "Warning: vertex at line"
                + to_string(lineNumber) + " can't be added to face. It has not been created.";

    case 22:
        return "Warning: Face at line"
                + to_string(lineNumber) + " does not complete color definition. " +
                "It can't be instantiated.";
    case 23:
        return "Warning: face at line"
                + to_string(lineNumber) + " can't be added to mesh. It has not been created.";

    case 24:
        return "Warning: face at line"
                + to_string(lineNumber) + " can't be deleted. It does not have a name.";

    case 25:
        return "Warning: face at line"
                + to_string(lineNumber) + " can't be deleted. It is not in the current scene.";

    case 26:
        return "Warning: mesh at line"
                + to_string(lineNumber) + " doesn't have a name.";
    case 27:
        return "Warning: face at line"
                + to_string(lineNumber) + " can't be added to mesh. The mesh does not have a name.";

    }
    return "";
}


int NomeParser::makeWithNome(vector<ParameterBank> &banks,
                              unordered_map<string, Parameter> &params,
                              Group &group,
                              string input,
                              vector<string> &colorlines,
                              vector<string> &banklines,
                              vector<string> &geometrylines,
                              vector<int> &postProcessingLines,
                              vector<string> &postProcessingLinesString)
{
    banks.clear();
    group.clear();
    ifstream file(input);
    if (!file.good())
    {
        cout<<"THE PATH OF MINI SIF FILE IS NOT VAILD.";
        exit(1);
    }
    string nextLine;
    int lineNumber = 1;
    bool createBank = false;
    bool constructingMesh = false;
    bool deletePhase = false;
    string currentGroup = "";
    unordered_map<string, Parameter>::iterator pIt;
    unordered_map<string, Mesh> meshes;
    unordered_map<string, Mesh>::iterator meshIt;
    unordered_map<string, Group> groups;
    unordered_map<string, Group>::iterator groupIt;
    unordered_map<string, Vertex*> global_vertices;
    unordered_map<string, Vertex*>::iterator vertIt;
    unordered_map<string, PolyLine> polylines;
    unordered_map<string, PolyLine>::iterator lineIt;
    unordered_map<string, Face*> global_faces;
    unordered_map<Face*, vector<Vertex*> > map_face_vertices;
    unordered_map<string, Face*>::iterator faceIt;
    string name = "";
    unordered_map<string, QColor> user_defined_colors;
    unordered_map<string, QColor>::iterator colorIt;
    string current_mesh_name = "";
    int isError = 0;
    char* p;
    long converted;

    while(std::getline(file, nextLine))
    {
        istringstream iss(nextLine);
        vector<string> tokens;
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter(tokens));
        vector<string>::iterator tIt;
        for(tIt = tokens.begin(); tIt < tokens.end(); tIt++)
        {
            //std::cout << *tIt << '\n';
            if(testComments(*tIt))
            {
                break;
            }
            else if(createBank){
                if((*tIt) == "endbank")
                {
                    banklines.push_back(nextLine);
                    createBank = false;
                    goto newLineEnd;
                }
                else if((*tIt) == "set")
                {
                    banklines.push_back(nextLine);
                    Parameter newParameter;
                    int i = 0;
                    //cout << "Hi" << endl;
                    //cout << nextLine << endl;
                    while(i < 5) {
                        if(tIt >= tokens.end() - 1) {
                            if (i < 2) {
                                cout << "Error: The set at line " + to_string(lineNumber) + " does not have 5 parameters. It only has " + to_string(i) + " parameter." << endl;
                            }
                            else {
                                cout << "Error: The set at line " + to_string(lineNumber) + " does not have 5 parameters. It only has " + to_string(i) + " parameters." << endl;
                            }
                            return 1;
                            goto newLineEnd;
                        }

                        string nextToken = *(++tIt);
                        if(testComments(nextToken)) {
                            cout<<warning(0, lineNumber)<<endl;
                            goto newLineEnd;
                        }
                        switch(i)
                        {
                        case 0:


                            newParameter.name = banks[banks.size() - 1].name
                                    + QString::fromStdString("." + nextToken);
                            name = nextToken;
                            break;
                        case 1:
                            try
                            {
                                converted = strtod(nextToken.c_str(), &p);

                                if (*p){
                                    cout << "Error: The set at line " + to_string(lineNumber) + " does not have the correct format."  << endl;
                                    return 1;
                                }

                                newParameter.value = std::stof(nextToken);
                                break;
                            }
                            catch (std::exception e)
                            {
                                cout << "Error: The set at line " + to_string(lineNumber) + " has the parameter " + nextToken + " that is not a number." << endl;
                                return 1;
                                cout<<warning(1, lineNumber)<<endl;
                                goto newLineEnd;
                            }
                        case 2:
                            try
                            {
                                converted = strtod(nextToken.c_str(), &p);

                                if (*p){
                                    cout << "Error: The set at line " + to_string(lineNumber) + " does not have the correct format."  << endl;
                                    return 1;
                                }
                                newParameter.start = std::stof(nextToken);
                                break;
                            }
                            catch (std::exception e)
                            {
                                cout << "Error: The set at line " + to_string(lineNumber) + " has the parameter " + nextToken + " that is not a number." << endl;
                                return 1;
                                cout<<warning(1, lineNumber)<<endl;
                                goto newLineEnd;
                            }
                        case 3:
                            try
                            {
                                converted = strtod(nextToken.c_str(), &p);

                                if (*p){
                                    cout << "Error: The set at line " + to_string(lineNumber) + " does not have the correct format."  << endl;
                                    return 1;
                                }
                                newParameter.end = std::stof(nextToken);
                                break;
                            }
                            catch (std::exception e)
                            {
                                cout << "Error: The set at line " + to_string(lineNumber) + " has the parameter " + nextToken + " that is not a number." << endl;
                                return 1;
                                cout<<warning(1, lineNumber)<<endl;
                                goto newLineEnd;
                            }
                        case 4:
                            try
                            {
                                converted = strtod(nextToken.c_str(), &p);

                                if (*p){
                                    cout << "Error: The set at line " + to_string(lineNumber) + " does not have the correct format."  << endl;
                                    return 1;
                                }

                                newParameter.stepsize = std::stof(nextToken);
                                break;
                            }
                            catch (std::exception e)
                            {
                                cout << "Error: The set at line " + to_string(lineNumber) + " has the parameter " + nextToken + " that is not a number." << endl;
                                return 1;
                                cout<<warning(1, lineNumber)<<endl;
                                goto newLineEnd;
                            }
                        }
                        i++;
                    }

                    //cout << *tIt << endl;
                    pIt = params.find(newParameter.name.toStdString());
                    if(pIt == params.end())
                    {
                        params[banks[banks.size() - 1].name.toStdString() + "." + name]
                                = newParameter;
                    }
                    else
                    {

                        cout << "Error: The set at line " + to_string(lineNumber) + " with name " + newParameter.name.toStdString() + " has already been defined."  << endl;
                        return 1;
                        goto newLineEnd;
                    }
                    banks[banks.size() - 1].addParameter(
                                &params[banks[banks.size() - 1].name.toStdString() + "." + name]);


                    if((tIt != tokens.end() - 1) && !testComments(*(tIt+1))) {
                        cout << "Error: The set at line " + to_string(lineNumber) + " does not have 5 parameters. It has too many parameters." << endl;
                        return 1;
                        goto newLineEnd;
                    }
                    //goto newLineEnd;
                }
                else {
                    cout << "Error: Wrong method at line " + to_string(lineNumber) + ". The method can only be a set, or you forgot to write endbank at the end of the bank." << endl;
                    return 1;
                    goto newLineEnd;
                }
            }
            else if((*tIt) == "bank")
            {
                banklines.push_back(nextLine);
                ParameterBank newBank;
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        newBank.setName(QString::fromStdString(*tIt));
                    }
                }
                else {
                    cout << "Error: The bank at line " + to_string(lineNumber) + " does not have a name." << endl;
                    return 1;
                }
                banks.push_back(newBank);
                createBank = true;
                goto newLineEnd;
            }
            else if((*tIt) == "surface")
            {
                colorlines.push_back(nextLine);
                string color_name;
                QColor new_color;
                if(++tIt < tokens.end())
                {
                    color_name = (*tIt);
                    colorIt = user_defined_colors.find(color_name);
                    if(colorIt != user_defined_colors.end())
                    {
                        cout << "Error: The surface " + color_name + " at line " + to_string(lineNumber) + " has already been defined."  << endl;
                        return 1;
                        goto newLineEnd;
                    }
                }
                else
                {
                    cout << "Error: The surface at line " + to_string(lineNumber) + " does not have a name."  << endl;
                    return 1;
                    cout<<warning(17, lineNumber)<<endl;
                }
                if(++tIt < tokens.end())
                {
                    if((*tIt) != "color")
                    {
                        cout << "Error: The surface " + color_name + " at line " + to_string(lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                        cout<<warning(17, lineNumber)<<endl;
                    }
                }
                else
                {
                    cout << "Error: The surface " + color_name + " at line " + to_string(lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                    cout<<warning(17, lineNumber)<<endl;
                }
                string color_expression;
                bool expression_input = false;
                bool inExpression = false;
                while(++tIt < tokens.end())
                {
                    for(char& c : (*tIt))
                    {
                        if(c == '(' && !inExpression)
                        {
                            expression_input = true;
                        }
                        else if(c == ')' && !inExpression)
                        {
                            expression_input = false;
                            goto colordone;
                        }
                        else if(c == '#')
                        {
                            goto newLineEnd;
                        }
                        else if(expression_input)
                        {
                            color_expression.push_back(c);
                        }
                        if(c == '{')
                        {
                            inExpression = true;
                        }
                        else if(c == '}')
                        {
                            inExpression = false;
                        }
                    }
                    color_expression.push_back(' ');
                }
                colordone:
                new_color = evaluate_color_expression(color_expression, lineNumber);
                if (!new_color.isValid()){
                    return 1;
                }

                user_defined_colors[color_name] = new_color;

                if(++tIt == tokens.end() || (*tIt) != "endsurface"){
                    cout << "Error: Missing endsurface on line " + to_string(lineNumber) + "." << endl;
                    return 1;
                }

                goto newLineEnd;
            }
            else if((*tIt) == "funnel")
            {
                geometrylines.push_back(nextLine);
                Mesh newFunnel(1);
                newFunnel.setGlobalParameter(&params);
                if(++tIt < tokens.end())
                {
                    newFunnel.name = (*tIt);
                }
                string funnel_expression;
                bool expression_input = false;
                bool inExpression = false;
                while(++tIt < tokens.end())
                {
                    for(char& c : (*tIt))
                    {
                        if(c == '(' && !inExpression)
                        {
                            expression_input = true;
                        }
                        else if(c == ')' && !inExpression)
                        {
                            expression_input = false;

                            //cout << *tIt << endl;
                            if(++tIt == tokens.end() || (*tIt) != "endfunnel"){
                                cout << "Error: Missing endfunnel on line " + to_string(lineNumber) + "." << endl;
                                return 1;
                            }
                        }
                        else if(c == '#')
                        {
                            goto newLineEnd;
                        }
                        else if(expression_input)
                        {
                            funnel_expression.push_back(c);
                        }
                        if(c == '{')
                        {
                            inExpression = true;
                        }
                        else if(c == '}')
                        {
                            inExpression = false;
                        }
                    }
                    funnel_expression.push_back(' ');
                }

                isError = newFunnel.setFunnelParameterValues(funnel_expression, lineNumber);
                if (isError == 1){
                    return 1;
                }

                newFunnel.makeFunnel();
                if(meshes.find(newFunnel.name) == meshes.end())
                {
                    meshes[newFunnel.name] = newFunnel;
                }
                else
                {
                    cout << "Error: The funnel at line " + to_string(lineNumber) + " with name " + newFunnel.name + " has already been created."  << endl;
                    return 1;
                    cout<<warning(3, lineNumber)<<endl;
                }


                //newFunnel.computeNormals();
            }
            else if((*tIt) == "tunnel")
            {
                geometrylines.push_back(nextLine);
                Mesh newTunnel(2);
                newTunnel.setGlobalParameter(&params);
                if(++tIt < tokens.end())
                {
                    newTunnel.name = (*tIt);
                }
                string tunnel_expression;
                bool expression_input = false;
                bool inExpression = false;
                while(++tIt < tokens.end())
                {
                    for(char& c : (*tIt))
                    {
                        if(c == '(' && !inExpression)
                        {
                            expression_input = true;
                        }
                        else if(c == ')' && !inExpression)
                        {
                            expression_input = false;
                        }
                        else if(c == '#')
                        {
                            goto newLineEnd;
                        }
                        else if(expression_input)
                        {
                            tunnel_expression.push_back(c);
                        }
                        if(c == '{')
                        {
                            inExpression = true;
                        }
                        else if(c == '}')
                        {
                            inExpression = false;
                        }
                    }
                    tunnel_expression.push_back(' ');
                }
                newTunnel.setTunnelParameterValues(tunnel_expression, lineNumber);
                newTunnel.makeTunnel();
                //*************
                /*cout << newTunnel.vertList.size() << endl;
                for (int i=0; i <newTunnel.vertList.size(); i++){
                    cout << newTunnel.vertList[i] << endl;
                }*/
                //*************
                if(meshes.find(newTunnel.name) == meshes.end())
                {
                    meshes[newTunnel.name] = newTunnel;
                }
                else
                {
                    cout << "Error: The tunnel at line " + to_string(lineNumber) + " with name " + newTunnel.name + " has already been created."  << endl;
                    return 1;
                    cout<<warning(3, lineNumber)<<endl;
                }
                /*if(++tIt == tokens.end() || (*tIt) != "endtunnel"){
                    cout << "Error: Missing endtunnel on line " + to_string(lineNumber) + "." << endl;
                }*/
                //newTunnel.computeNormals();
            }
            else if((*tIt) == "object")
            {
                geometrylines.push_back(nextLine);
                Mesh newMesh(0);
                newMesh.setGlobalParameter(&params);
                if(++tIt < tokens.end())
                {
                    if(!testComments(*tIt))
                    {
                        newMesh.name = *tIt;
                    }
                    else
                    {
                        cout<<warning(3, lineNumber)<<endl;
                        goto newLineEnd;
                    }
                }
                string faceInside = "";
                bool addingFace = false;
                while(++tIt < tokens.end())
                {

                    if((*tIt == "endobject"))
                    {
                        cout << "Error: Missing list of faces between () in object generator on line " + to_string(lineNumber) + "." << endl;
                        return 1;
                    }
                    for(char& c : (*tIt))
                    {
                        if(c == '(')
                        {
                            addingFace = true;
                        }
                        else if(c == ')')
                        {
                            //cout << faceInside << endl;
                            addingFace = false;
                            if(faceInside != "")
                            {

                                faceIt = global_faces.find(faceInside);

                                if(faceIt == global_faces.end())
                                {
                                    cout << "Error: Incorrect face name in object generator on line " + to_string(lineNumber) + ". The face " + faceInside + " has never been created." << endl;
                                    return 1;
                                    cout<<warning(23, lineNumber);
                                }
                                else
                                {
                                    Vertex * foundVertex;
                                    vector<Vertex*> vertices;
                                    for(Vertex * vc : map_face_vertices[(faceIt -> second)])
                                    {
                                        foundVertex = NULL;
                                        for(Vertex * v : newMesh.vertList)
                                        {
                                            if(v -> source_vertex == vc)
                                            {
                                                foundVertex = v;
                                                vertices.push_back(v);
                                            }
                                        }
                                        if(foundVertex == NULL)
                                        {
                                            Vertex * newVertex = new Vertex;
                                            newVertex -> isParametric = vc -> isParametric;
                                            newVertex -> position = vc -> position;
                                            newVertex -> ID = newMesh.vertList.size();
                                            newVertex -> source_vertex = vc;
                                            newVertex -> name = vc -> name;
                                            newVertex -> x_expr = vc -> x_expr;
                                            newVertex -> y_expr = vc -> y_expr;
                                            newVertex -> z_expr = vc -> z_expr;
                                            newVertex -> influencingParams = vc -> influencingParams;
                                            newVertex -> params = vc -> params;
                                            newMesh.addVertex(newVertex);
                                            vertices.push_back(newVertex);
                                        }
                                    }
                                    newMesh.addPolygonFace(vertices);
                                    newMesh.faceList[newMesh.faceList.size()-1]->user_defined_color = faceIt -> second -> user_defined_color;
                                    if(faceIt -> second -> user_defined_color)
                                    {
                                        newMesh.faceList[newMesh.faceList.size()-1]->color = faceIt -> second -> color;
                                    }
                                    newMesh.faceList[newMesh.faceList.size()-1] -> name = faceIt -> second -> name;
                                }
                                faceInside = "";
                            }

                            goto endAddingFaceInMesh;
                        }
                        else if(addingFace)
                        {
                            faceInside.push_back(c);
                        }

                    }
                    if(faceInside != "")
                    {
                        //cout << faceInside << endl;

                        faceIt = global_faces.find(faceInside);
                        if(faceIt == global_faces.end())
                        {
                            cout << "Error: Incorrect face name in object generator on line " + to_string(lineNumber) + ". The face " + faceInside + " has never been created." << endl;
                            return 1;
                            cout<<warning(23, lineNumber);
                        }
                        else
                        {
                            Vertex * foundVertex;
                            vector<Vertex*> vertices;
                            for(Vertex * vc : map_face_vertices[(faceIt -> second)])
                            {
                                foundVertex = NULL;
                                for(Vertex * v : newMesh.vertList)
                                {
                                    if(v -> source_vertex == vc)
                                    {
                                        foundVertex = v;
                                        vertices.push_back(v);
                                    }
                                }
                                if(foundVertex == NULL)
                                {
                                    Vertex * newVertex = new Vertex;
                                    newVertex -> isParametric = vc -> isParametric;
                                    newVertex -> position = vc -> position;
                                    newVertex -> ID = newMesh.vertList.size();
                                    newVertex -> source_vertex = vc;
                                    newVertex -> name = vc -> name;
                                    newVertex -> x_expr = vc -> x_expr;
                                    newVertex -> y_expr = vc -> y_expr;
                                    newVertex -> z_expr = vc -> z_expr;
                                    newVertex -> influencingParams = vc -> influencingParams;
                                    newVertex -> params = vc -> params;
                                    newMesh.addVertex(newVertex);
                                    vertices.push_back(newVertex);
                                }
                            }
                            newMesh.addPolygonFace(vertices);
                            newMesh.faceList[newMesh.faceList.size()-1]->user_defined_color = faceIt -> second -> user_defined_color;
                            if(faceIt -> second -> user_defined_color)
                            {
                                newMesh.faceList[newMesh.faceList.size()-1]->color = faceIt -> second -> color;
                            }
                        }
                        faceInside = "";
                    }
                }
                endAddingFaceInMesh:
                if(meshes.find(newMesh.name) == meshes.end())
                {
                    meshes[newMesh.name] = newMesh;
                }
                else
                {
                    cout << "Error: The mesh " + newMesh.name + " at line " + to_string(lineNumber) + " has already been created."  << endl;
                    return 1;
                    cout<<warning(3, lineNumber)<<endl;
                }

                if(++tIt == tokens.end() || (*tIt) != "endobject"){
                    cout << "Error: Missing endobject on line " + to_string(lineNumber) + "." << endl;
                    return 1;
                }
            }
            else if((*tIt) == "face" && (!deletePhase) && (!constructingMesh))
            {
                geometrylines.push_back(nextLine);
                Face * newFace = new Face;
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        faceIt = global_faces.find(*tIt);
                        if(faceIt == global_faces.end())
                        {
                            newFace -> name = *tIt;
                            global_faces[*tIt] = newFace;
                        }
                        else
                        {
                            cout << "Error: The face " + *tIt + " at line " + to_string(lineNumber) + " has already been created."  << endl;
                            return 1;
                            cout<<warning(20, lineNumber)<<endl;
                        }
                    }
                    else
                    {
                        cout<<warning(19, lineNumber)<<endl;
                    }
                }
                string vertInside = "";
                bool addingVert = false;
                vector<Vertex*> vertices;
                vertices.clear();
                while(++tIt < tokens.end() && (*tIt) != "endface")
                {
                    for(char & c: (*tIt))
                    {
                        if(c == '(')
                        {
                            addingVert = true;
                        }
                        else if(c == ')')
                        {
                            addingVert = false;
                            //cout << "FHHG" << endl;
                            //cout << vertInside << endl;
                            if(vertInside != "")
                            {
                                //cout << "GHHGHG" << endl;
                                vertIt = global_vertices.find(vertInside);

                                if(vertIt == global_vertices.end())
                                {
                                    cout << "Error: Incorrect vertex name in face generator on line " + to_string(lineNumber) + ". The vertex " + vertInside + " has never been created." << endl;
                                    return 1;
                                    cout<<warning(21, lineNumber);
                                }
                                else
                                {
                                    vertices.push_back(vertIt -> second);
                                }
                                vertInside = "";
                            }
                            goto endAddingVertInFace;
                        }
                        else if(addingVert)
                        {
                            vertInside.push_back(c);
                        }
                    }

                    if(vertInside != "")
                    {
                        //99999
                        /*banks[banks.size() - 1].name + QString::fromStdString("." + nextToken)
                        for ( auto it = global_vertices.begin(); it != global_vertices.end(); ++it )
                          {
                            cout << " " << it->first << ":" << it->second;
                            cout << endl;
                          }*/
                        //999999
                        vertIt = global_vertices.find(vertInside);
                        if(vertIt == global_vertices.end())
                        {
                            cout << "Error: Incorrect vertex name in face generator on line " + to_string(lineNumber) + ". The vertex " + vertInside + " has never been created." << endl;
                            return 1;
                            cout<<warning(21, lineNumber);
                        }
                        else
                        {
                            vertices.push_back(vertIt -> second);
                        }
                        vertInside = "";
                    }
                }
                endAddingVertInFace:
                map_face_vertices[newFace] = vertices;

                if(++tIt < tokens.end() && (*tIt) == "surface")
                {
                    string color_name = "";
                    QColor color;
                    bool foundColor = false;
                    if(++tIt < tokens.end())
                    {
                        color_name = *tIt;
                        colorIt = user_defined_colors.find(color_name);
                        if(colorIt != user_defined_colors.end())
                        {
                            foundColor = true;
                            color = colorIt -> second;
                        }
                        else
                        {
                            cout << "Error: Incorrect surface name in face generator on line " + to_string(lineNumber) + ". The surface " + color_name + " has never been created." << endl;
                            return 1;
                            cout<<warning(22, lineNumber)<<endl;
                        }
                    }
                    else
                    {
                        cout << "Error: The surface at line " + to_string(lineNumber) + "does not have any name."  << endl;
                        return 1;
                        cout<<warning(22, lineNumber)<<endl;
                    }
                    if(foundColor)
                    {
                        newFace -> color = color;
                        newFace -> user_defined_color = true;
                    }
                    ++tIt;
                }
                //cout << *tIt << endl;
                if(tIt == tokens.end() || (*tIt) != "endface"){
                    cout << "Error: Missing endface on line " + to_string(lineNumber) + "." << endl;
                    return 1;
                }

                //cout << *tIt << endl;
            }
            else if((*tIt) == "face" && deletePhase)
            {
                postProcessingLines.push_back(lineNumber);
                postProcessingLinesString.push_back(nextLine);
                /* Hmm, this is weird, I did not do anything here!
                   Except putting the delte into postProcessingLines.
                */
                goto newLineEnd;
            }
            else if((*tIt) == "face" && constructingMesh)
            {
                if(current_mesh_name == "")
                {
                    cout<<warning(27, lineNumber)<<endl;
                    goto newLineEnd;
                }
                else if(current_mesh_name == "consolidatedmesh")
                {
                    postProcessingLines.push_back(lineNumber);
                    postProcessingLinesString.push_back(nextLine);
                    goto newLineEnd;
                }
                geometrylines.push_back(nextLine);
                Face * newFace = new Face;

                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        faceIt = global_faces.find(*tIt);
                        if(faceIt == global_faces.end())
                        {
                            newFace -> name = *tIt;
                            global_faces[*tIt] = newFace;
                        }
                        else
                        {
                            cout << "Error: The face " + *tIt + " at line " + to_string(lineNumber) + " has already been created."  << endl;
                            return 1;
                            cout<<warning(20, lineNumber)<<endl;
                        }
                    }
                    else
                    {
                        cout<<warning(19, lineNumber)<<endl;
                    }
                }
                string vertInside = "";
                bool addingVert = false;
                vector<Vertex*> vertices;
                vertices.clear();
                while(++tIt < tokens.end() && (*tIt) != "endface")
                {
                    for(char & c: (*tIt))
                    {
                        if(c == '(')
                        {
                            addingVert = true;
                        }
                        else if(c == ')')
                        {
                            addingVert = false;
                            if(vertInside != "")
                            {
                                vertIt = global_vertices.find(vertInside);
                                if(vertIt == global_vertices.end())
                                {
                                    cout << "Error: The vertex " + vertInside + " at line " + to_string(lineNumber) + " has never been created."  << endl;
                                    return 1;
                                    cout<<warning(21, lineNumber);
                                }
                                else
                                {
                                    vertices.push_back(vertIt -> second);
                                }
                                vertInside = "";
                            }
                            goto endAddingVertInFace1;
                        }
                        else if(addingVert)
                        {
                            vertInside.push_back(c);
                        }
                    }
                    if(vertInside != "")
                    {
                        vertIt = global_vertices.find(vertInside);
                        if(vertIt == global_vertices.end())
                        {
                            cout << "Error: The vertex " + vertInside + " at line " + to_string(lineNumber) + " has never been created."  << endl;
                            return 1;
                            cout<<warning(21, lineNumber);
                        }
                        else
                        {
                            vertices.push_back(vertIt -> second);
                        }
                        vertInside = "";
                    }
                }
                endAddingVertInFace1:
                /* Add this face to the current mesh now.*/
                vector<Vertex*> mappedVertices;
                mappedVertices.clear();
                bool foundVertex;
                for(Vertex * vs : vertices)
                {
                    foundVertex = false;
                    for(Vertex * v : meshes[current_mesh_name].vertList)
                    {
                        if(v -> source_vertex == vs)
                        {
                            foundVertex = true;
                            mappedVertices.push_back(v);
                            break;
                        }
                    }
                    if(!foundVertex)
                    {
                        Vertex * newVertex = new Vertex;
                        newVertex -> isParametric = vs -> isParametric;
                        newVertex -> position = vs -> position;
                        newVertex -> ID = meshes[current_mesh_name].vertList.size();
                        newVertex -> source_vertex = vs;
                        newVertex -> name = vs -> name;
                        newVertex -> x_expr = vs -> x_expr;
                        newVertex -> y_expr = vs -> y_expr;
                        newVertex -> z_expr = vs -> z_expr;
                        newVertex -> influencingParams = vs -> influencingParams;
                        newVertex -> params = vs -> params;
                        meshes[current_mesh_name].addVertex(newVertex);
                        mappedVertices.push_back(newVertex);
                    }
                }
                meshes[current_mesh_name].addPolygonFace(mappedVertices);
                meshes[current_mesh_name].faceList[meshes[current_mesh_name].faceList.size() - 1]
                        -> name = newFace -> name;
                if(++tIt < tokens.end() && (*tIt) == "surface")
                {
                    string color_name = "";
                    QColor color;
                    bool foundColor = false;
                    if(++tIt < tokens.end())
                    {
                        color_name = *tIt;
                        colorIt = user_defined_colors.find(color_name);
                        if(colorIt != user_defined_colors.end())
                        {
                            foundColor = true;
                            color = colorIt -> second;
                        }
                        else
                        {
                            cout << "Error: The surface " + color_name + " at line " + to_string(lineNumber) + " has never been created."  << endl;
                            return 1;
                            cout<<warning(22, lineNumber)<<endl;
                        }
                    }
                    else
                    {
                        cout << "Error: The surface at line " + to_string(lineNumber) + " does not have a name."  << endl;
                        return 1;
                        cout<<warning(22, lineNumber)<<endl;
                    }
                    if(foundColor)
                    {
                        meshes[current_mesh_name].faceList[meshes[current_mesh_name].faceList.size() - 1]
                                -> color = color;
                        meshes[current_mesh_name].faceList[meshes[current_mesh_name].faceList.size() - 1]
                                -> user_defined_color = true;
                    }
                }
                delete newFace;
            }
            else if((*tIt) == "polyline")
            {
                geometrylines.push_back(nextLine);
                PolyLine newPolyline;
                if((++tIt) < tokens.end() && !testComments(*tIt))
                {
                    lineIt = polylines.find(*tIt);
                    if(lineIt == polylines.end())
                    {
                        newPolyline.name = *tIt;
                    }
                    else
                    {
                        cout << "Error: The polyline " + *tIt + " at line " + to_string(lineNumber) + " has already been created."  << endl;
                        return 1;
                        cout<<warning(13, lineNumber)<<endl;
                    }
                }
                else
                {
                    cout<<warning(12, lineNumber)<<endl;
                }
                string vertInside = "";
                bool addingVert = false;
                while(++tIt < tokens.end() && (*tIt) != "endpolyline")
                {
                    for(char& c : (*tIt))
                    {
                        if(c == '(')
                        {
                            addingVert = true;
                        }
                        else if(c == ')')
                        {
                            addingVert = false;
                            if(++tIt < tokens.end() && (*tIt) != "endpolyline")
                            {
                                if(*tIt == "closed")
                                {
                                    newPolyline.isLoop = true;
                                    ++tIt;
                                }
                            }
                            goto endPolyLineWhile;
                        }
                        else if(addingVert)
                        {
                            vertInside.push_back(c);
                        }
                    }

                    if(vertInside != "")
                    {
                        vertIt = global_vertices.find(vertInside);
                        if(vertIt == global_vertices.end())
                        {
                            cout << "Error: Incorrect vertex name in polyline generator on line " + to_string(lineNumber) + ". The vertex " + vertInside + " has never been created." << endl;
                            return 1;
                            cout<<warning(14, lineNumber);
                        }
                        else
                        {
                            newPolyline.addVertex(vertIt -> second);
                        }
                        vertInside = "";
                    }
                }

                endPolyLineWhile:
                if(vertInside != "")
                {
                    vertIt = global_vertices.find(vertInside);
                    if(vertIt == global_vertices.end())
                    {
                        cout << "Error: Incorrect vertex name in polyline generator on line " + to_string(lineNumber) + ". The vertex " + vertInside + " has never been created." << endl;
                        return 1;
                        cout<<warning(14, lineNumber);
                    }
                    else
                    {
                        newPolyline.addVertex(vertIt -> second);
                    }
                    vertInside = "";
                }

                //=========================================
                /*if(*tIt == "surface")
                {
                    string color_name;
                    bool foundColor = false;
                    QColor color;
                    if(++tIt < tokens.end())
                    {
                        color_name = *tIt;
                        colorIt = user_defined_colors.find(color_name);
                        if(colorIt != user_defined_colors.end())
                        {
                            color = colorIt -> second;
                            foundColor = true;
                        }
                        else
                        {
                            cout << "Error: The surface " + color_name + " at line " + to_string(lineNumber) + " has never been created."  << endl;
                            return 1;
                            cout<<warning(18, lineNumber)<<endl;
                        }
                    }
                    else
                    {
                        cout << "Error: The surface " + *tIt + " at line " + to_string(lineNumber) + " is missing a name."  << endl;
                        return 1;
                        cout<<warning(18, lineNumber)<<endl;
                    }
                    cout << "HELLO" << endl;
                    newPolyline.setColor(color);
                    ++tIt;
                }*/
                //=========================================

                if((*tIt) != "endpolyline"){
                    cout << "Error: Missing endpolyline on line " + to_string(lineNumber) + "." << endl;
                    return 1;
                }

                polylines[newPolyline.name] = newPolyline;

            }
            else if((*tIt) == "bspline3")
            {
                geometrylines.push_back(nextLine);
                BSpline newBSpline;
                if((++tIt) < tokens.end() && !testComments(*tIt))
                {
                    lineIt = polylines.find(*tIt);
                    if(lineIt == polylines.end())
                    {
                        newBSpline.name = *tIt;
                    }
                    else
                    {
                        cout << "Error: The bspline3 " + *tIt + " at line " + to_string(lineNumber) + " has already been created."  << endl;
                        return 1;
                        cout<<warning(13, lineNumber)<<endl;
                    }
                }
                else
                {
                    cout<<warning(12, lineNumber)<<endl;
                }
                string vertInside = "";
                bool addingVert = false;
                while(++tIt < tokens.end() && (*tIt) != "endbspline3")
                {
                    for(char& c : (*tIt))
                    {
                        if(c == '(')
                        {
                            addingVert = true;
                        }
                        else if(c == ')')
                        {
                            addingVert = false;
                            if(++tIt < tokens.end() && (*tIt) != "endbspline3")
                            {
                                if(*tIt == "closed")
                                {
                                    newBSpline.isLoop = true;
                                    ++tIt;
                                }
                            }
                            goto endBSplineWhile;
                        }
                        else if(addingVert)
                        {
                            vertInside.push_back(c);
                        }
                    }

                    if(vertInside != "")
                    {
                        vertIt = global_vertices.find(vertInside);
                        if(vertIt == global_vertices.end())
                        {
                            cout << "Error: Incorrect vertex name in polyline generator on line " + to_string(lineNumber) + ". The vertex " + vertInside + " has never been created." << endl;
                            return 1;
                            cout<<warning(14, lineNumber);
                        }
                        else
                        {
                            newBSpline.addVertex(vertIt -> second);
                        }
                        vertInside = "";
                    }
                }

                endBSplineWhile:
                if(vertInside != "")
                {
                    vertIt = global_vertices.find(vertInside);
                    if(vertIt == global_vertices.end())
                    {
                        cout << "Error: Incorrect vertex name in polyline generator on line " + to_string(lineNumber) + ". The vertex " + vertInside + " has never been created." << endl;
                        return 1;
                        cout<<warning(14, lineNumber);
                    }
                    else
                    {
                        newBSpline.set_proxy(vertIt -> second);
                    }
                    vertInside = "";
                }

                if((*tIt) != "endbspline3"){
                    cout << "Error: Missing endpolyline on line " + to_string(lineNumber) + "." << endl;
                    return 1;
                }
                newBSpline.cubic();
                polylines[newBSpline.name] = newBSpline;

            }
            else if((*tIt) == "point")
            {
                geometrylines.push_back(nextLine);
                Vertex * newVertex = new Vertex;
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        vertIt = global_vertices.find(*tIt);
                        if(vertIt == global_vertices.end())
                        {
                            newVertex -> name = *tIt;
                            global_vertices[*tIt] = newVertex;
                        }
                        else
                        {
                            cout << "Error: Point " + *tIt + " on line " + to_string(lineNumber) + " has already been created." << endl;
                            return 1;
                            cout<<warning(11, lineNumber)<<endl;
                        }
                    }
                    else
                    {
                        cout<<warning(10, lineNumber)<<endl;
                    }
                }
                string xyz;
                bool makingXYZ = false;
                bool inExpression = false;
                while(++tIt < tokens.end() && (*tIt) != "endpoint")
                {
                    for(char& c : (*tIt))
                    {
                        if(c == '(' && !inExpression)
                        {
                            makingXYZ = true;
                        }
                        else if(c == ')' && !inExpression)
                        {
                            makingXYZ = false;
                            //goto endPointWhile;
                        }
                        else if(makingXYZ)
                        {
                            xyz.push_back(c);
                            if(c == '{')
                            {
                                inExpression = true;
                            }
                            else if(c == '}')
                            {
                                inExpression = false;
                            }
                        }
                    }
                    if(xyz != "")
                    {
                        xyz.push_back(' ');
                    }
                }
                endPointWhile:
                newVertex->setGlobalParameter(&params);
                isError = 0;
                isError = newVertex->setVertexParameterValues(xyz, lineNumber);

                if (isError == 1){
                    return 1;
                }


                //cout << *tIt << endl;
                if((*tIt) != "endpoint"){
                    cout << "Error: Missing endpoint on line " + to_string(lineNumber) + "." << endl;
                    return 1;
                }
            }
            else if((*tIt) == "group")
            {
                geometrylines.push_back(nextLine);
                Group newGroup;
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        newGroup.setName(*tIt);
                    }
                }

                groups[newGroup.name] = newGroup;
                currentGroup = newGroup.name;
                goto newLineEnd;
            }
            else if((*tIt) == "endgroup")
            {
                geometrylines.push_back(nextLine);
                currentGroup = "";
                goto newLineEnd;
            }
            else if((*tIt) == "instance")
            {
                string instanceName;
                Mesh newMesh;
                Group newGroup;
                PolyLine newPolyline;
                string className;
                bool findMesh = false;
                bool findGroup = false;
                bool findPolyline = false;
                bool foundColor = false;
                QColor color;
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        instanceName = *tIt;
                    }
                } else {
                    cout<<warning(5, lineNumber)<<endl;
                }
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        className = *tIt;
                    }
                } else {
                    cout<<warning(6, lineNumber)<<endl;
                }
                if(className == "consolidatedmesh")
                {
                    postProcessingLines.push_back(lineNumber);
                    postProcessingLinesString.push_back(nextLine);
                    goto newLineEnd;
                }
                else
                {
                    geometrylines.push_back(nextLine);
                }
                meshIt = meshes.find(className);
                if(meshIt != meshes.end())
                {
                    newMesh = (meshIt -> second).makeCopy(instanceName);
                    findMesh = true;
                }
                else
                {
                    groupIt = groups.find(className);
                    if(groupIt != groups.end())
                    {
                        newGroup = (groupIt -> second).makeCopy(instanceName);
                        findGroup = true;
                    }
                    else
                    {
                        lineIt = polylines.find(className);
                        if(lineIt != polylines.end())
                        {
                            newPolyline = (lineIt -> second).makeCopy(instanceName);
                            findPolyline = true;
                        }
                        else
                        {
                            cout << "Error: The object " + className + " at line " + to_string(lineNumber) + " has never been created."  << endl;
                            return 1;
                            cout<<warning(5, lineNumber)<<endl;
                        }
                    }
                }
                vector<Transformation> transformations_up;
                while(++tIt < tokens.end() && (*tIt) != "endinstance")
                {
                    if(testComments(*tIt))
                    {
                        goto newLineEnd;
                    }
                    if(*tIt == "rotate")
                    {
                        string xyz;
                        string angle;
                        bool makingXYZ = false;
                        bool makingAngle = false;
                        bool doneXYZ = false;
                        bool inExpression = false;
                        while(++tIt < tokens.end() && (*tIt) != "endinstance")
                        {
                            for(char& c : (*tIt))
                            {
                                if(c == '(' && !inExpression)
                                {
                                    if(!doneXYZ)
                                    {
                                        makingXYZ = true;
                                    }
                                    else
                                    {
                                        makingAngle = true;
                                    }
                                }
                                else if(c == ')' && !inExpression)
                                {
                                    if(makingXYZ)
                                    {
                                        doneXYZ = true;
                                        makingXYZ = false;
                                    } else if(makingAngle)
                                    {
                                        makingAngle = false;
                                        goto endWhile1;
                                    }
                                }
                                else
                                {
                                    if(makingXYZ)
                                    {
                                        xyz.push_back(c);
                                        if(c == '{')
                                        {
                                            inExpression = true;
                                        }
                                        else if(c == '}')
                                        {
                                            inExpression = false;
                                        }
                                    }
                                    else if(makingAngle)
                                    {
                                        angle.push_back(c);
                                        if(c == '{')
                                        {
                                            inExpression = true;
                                        }
                                        else if(c == '}')
                                        {
                                            inExpression = false;
                                        }
                                    }
                                }
                            }
                            if(makingXYZ && xyz != "")
                            {
                                xyz.push_back(' ');
                            }
                            else if(makingAngle && angle != "")
                            {
                                angle.push_back(' ');
                            }
                        }
                        endWhile1:
                        Transformation t(1, &params, xyz, angle);
                        transformations_up.push_back(t);
                    }
                    else if(*tIt == "translate" || *tIt == "scale")
                    {
                        bool isTranslate = false;
                        if(*tIt == "translate")
                        {
                            isTranslate = true;
                        }
                        string xyz = "";
                        bool makingXYZ = false;
                        bool inExpression = false;
                        while(++tIt < tokens.end() && (*tIt) != "endinstance")
                        {
                            for(char& c : (*tIt))
                            {
                                if(c == '(' && !inExpression)
                                {
                                    makingXYZ = true;
                                }
                                else if(c == ')' && !inExpression)
                                {
                                    makingXYZ = false;
                                    goto endWhile2;
                                }
                                else if(makingXYZ)
                                {
                                    xyz.push_back(c);
                                    if(c == '{')
                                    {
                                        inExpression = true;
                                    }
                                    else if(c == '}')
                                    {
                                        inExpression = false;
                                    }
                                }
                            }
                            if(xyz != "")
                            {
                                xyz.push_back(' ');
                            }
                        }
                        endWhile2:
                        if(isTranslate)
                        {
                            Transformation t(3,&params, xyz);
                            transformations_up.push_back(t);
                        }
                        else
                        {
                            Transformation t(2, &params, xyz);
                            transformations_up.push_back(t);
                        }
                    }
                    else if(*tIt == "mirror")
                    {
                        string xyzw = "";
                        bool makingXYZW = false;
                        bool inExpression = false;
                        while(++tIt < tokens.end() && (*tIt) != "endinstance")
                        {
                            for(char& c : (*tIt))
                            {
                                if(c == '(' && !inExpression)
                                {
                                    makingXYZW = true;
                                }
                                else if(c == ')' && !inExpression)
                                {
                                    makingXYZW = false;
                                    goto endWhile3;
                                }
                                else if(makingXYZW)
                                {
                                    xyzw.push_back(c);
                                    if(c == '{')
                                    {
                                        inExpression = true;
                                    }
                                    else if(c == '}')
                                    {
                                        inExpression = false;
                                    }
                                }
                            }
                            if(xyzw != "")
                            {
                                xyzw.push_back(' ');
                            }
                        }
                        endWhile3:
                        Transformation t(4, &params, xyzw);
                        transformations_up.push_back(t);
                    }
                    else if(*tIt == "surface")
                    {
                        string color_name;
                        if(++tIt < tokens.end())
                        {
                            color_name = *tIt;
                            colorIt = user_defined_colors.find(color_name);
                            if(colorIt != user_defined_colors.end())
                            {
                                color = colorIt -> second;
                                foundColor = true;
                            }
                            else
                            {
                                cout << "Error: The surface " + color_name + " at line " + to_string(lineNumber) + " has never been created."  << endl;
                                return 1;
                                cout<<warning(18, lineNumber)<<endl;
                            }
                        }
                        else
                        {
                            cout << "Error: The surface " + *tIt + " at line " + to_string(lineNumber) + " is missing a name."  << endl;
                            return 1;
                            cout<<warning(18, lineNumber)<<endl;
                        }
                    }
                    else {
                        cout << "Error: The instance at line " + to_string(lineNumber) + " has the parameter " + *tIt + " which is incorrect."  << endl;
                        return 1;
                    }
                }
                if(currentGroup != "")
                {
                    if(findMesh)
                    {
                        newMesh.setTransformation(transformations_up);
                        if(foundColor)
                        {
                            newMesh.setColor(color);
                            newMesh.user_set_color = true;
                        }

                        groups[currentGroup].addMesh(newMesh);
                    }
                    else if(findGroup)
                    {
                        newGroup.setTransformation(transformations_up);
                        if(foundColor)
                        {
                            newGroup.setColor(color);
                            newGroup.user_set_color = true;
                        }
                        groups[currentGroup].addGroup(newGroup);
                    }
                    else if(findPolyline)
                    {
                        newPolyline.setTransformation(transformations_up);
                        if(foundColor)
                        {
                            newPolyline.setColor(color);
                            newPolyline.user_set_color = true;
                        }
                        groups[currentGroup].addPolyline(newPolyline);
                    }
                }
                else
                {
                    if(findMesh)
                    {
                        newMesh.setTransformation(transformations_up);
                        if(foundColor)
                        {
                            newMesh.setColor(color);
                            newMesh.user_set_color = true;
                        }
                        group.addMesh(newMesh);
                    }
                    else if(findGroup)
                    {
                        newGroup.setTransformation(transformations_up);
                        if(foundColor)
                        {
                            newGroup.setColor(color);
                            newGroup.user_set_color = true;
                        }
                        group.addGroup(newGroup);
                    }
                    else if(findPolyline)
                    {
                        newPolyline.setTransformation(transformations_up);
                        if(foundColor)
                        {
                            newPolyline.setColor(color);
                            newPolyline.user_set_color = true;
                        }
                        group.addPolyline(newPolyline);
                    }
                }

                if((*tIt) != "endinstance"){
                    cout << "Error: Missing endinstance on line " + to_string(lineNumber) + "." << endl;
                    return 1;
                }

            }
            else if(*tIt == "delete")
            {
                postProcessingLines.push_back(lineNumber);
                postProcessingLinesString.push_back(nextLine);
                deletePhase = true;
                goto newLineEnd;
            }
            else if(*tIt == "enddelete")
            {
                postProcessingLines.push_back(lineNumber);
                postProcessingLinesString.push_back(nextLine);
                deletePhase = false;
                goto newLineEnd;
            }
            else if(*tIt == "mesh")
            {
                constructingMesh = true;
                Mesh newMesh(0);
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        if(*tIt == "consolidatedmesh")
                        {
                            postProcessingLines.push_back(lineNumber);
                            postProcessingLinesString.push_back(nextLine);
                            current_mesh_name = "consolidatedmesh";
                            goto newLineEnd;
                        }
                        else
                        {
                            geometrylines.push_back(nextLine);
                        }
                        newMesh.name = *tIt;
                        newMesh.setGlobalParameter(&params);
                    }
                    else
                    {
                        cout << "Error: The mesh at line " + to_string(lineNumber) + " does not have a name."  << endl;
                        return 1;
                        cout<<warning(26, lineNumber);
                        goto newLineEnd;
                    }
                }
                else
                {
                    cout<<warning(26, lineNumber);
                    goto newLineEnd;
                }
                if(meshes.find(newMesh.name) == meshes.end())
                {
                    meshes[newMesh.name] = newMesh;
                    current_mesh_name = newMesh.name;
                }
                else
                {
                    cout << "Error: The mesh " + newMesh.name + " at line " + to_string(lineNumber) + " has already been created."  << endl;
                    return 1;
                    cout<<warning(3, lineNumber)<<endl;
                }
                goto newLineEnd;
            }
            else if(*tIt == "endmesh")
            {
                constructingMesh = false;
                if(current_mesh_name == "consolidatedmesh")
                {
                    postProcessingLines.push_back(lineNumber);
                    postProcessingLinesString.push_back(nextLine);
                }
                else
                {
                    geometrylines.push_back(nextLine);
                }
                current_mesh_name = "";
            }
            else{
                cout<< "Error: Method " + *tIt + " at line " + to_string(lineNumber) + " is not defined." << endl;
                return 1;
            }
        }
        newLineEnd:
        lineNumber++;
    }
    group.mapFromParameters();

    /*for ( auto it = meshes.begin(); it != meshes.end(); ++it ){
        cout << (*it).first << endl;
        cout << (*it).second.name << endl;
        cout << "JJJJ" << endl;
    }*/

}

void NomeParser::postProcessingWithNome(unordered_map<string, Parameter> &params,
                                        vector<int> &postProcessingLines,
                                        SlideGLWidget *canvas,
                                        Group &group,
                                        string input, vector<string> &postProcessingLinesString)
{
    //cout << "HI" << endl;
    //cout << postProcessingLines << endl;
    /*for(int i : postProcessingLines){
      cout << "i = " << i << endl;
    }*/
    if(postProcessingLines.size() == 0)
    {
        return;
    }
    ifstream file(input);
    if (!file.good())
    {
        cout<<"THE PATH OF MINI SIF FILE IS NOT VAILD.";
        exit(1);
    }
    string nextLine;
    int lineNumber = 1;
    bool deletePhase = false;
    bool restoreConsolidatedMesh = false;
    string current_mesh_name = "";
    unordered_map<string, QColor> user_defined_colors;
    unordered_map<string, QColor>::iterator colorIt;
    vector<int>::iterator fileLineIter = postProcessingLines.begin();
    unordered_map<string, Mesh> meshes;
    unordered_map<string, Mesh>::iterator meshIt;
    unordered_map<string, Face*> global_faces;
    unordered_map<string, Face*>::iterator faceIt;
    while(std::getline(file, nextLine))
    {
        //cout << "JJJ" << endl;
        istringstream iss(nextLine);
        vector<string> tokens;
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter(tokens));
        vector<string>::iterator tIt;
        for(tIt = tokens.begin(); tIt < tokens.end(); tIt++)
        {
            if((*tIt) != "surface" && lineNumber != (*fileLineIter))
            {
                goto newLineEnd;
            }
            else if((*tIt) == "surface")
            {
                //cout<<*tIt<<endl;
                string color_name;
                QColor new_color;
                if(++tIt < tokens.end())
                {
                    color_name = (*tIt);
                    colorIt = user_defined_colors.find(color_name);
                    if(colorIt != user_defined_colors.end())
                    {
                        cout<<warning(16, lineNumber)<<endl;
                        goto newLineEnd;
                    }
                }
                else
                {
                    cout<<warning(17, lineNumber)<<endl;
                }
                if(++tIt < tokens.end())
                {
                    if((*tIt) != "color")
                    {
                        cout<<warning(17, lineNumber)<<endl;
                    }
                }
                else
                {
                    cout<<warning(17, lineNumber)<<endl;
                }
                string color_expression;
                bool expression_input = false;
                bool inExpression = false;
                while(++tIt < tokens.end())
                {
                    for(char& c : (*tIt))
                    {
                        if(c == '(' && !inExpression)
                        {
                            expression_input = true;
                        }
                        else if(c == ')' && !inExpression)
                        {
                            expression_input = false;
                            goto colordone;
                        }
                        else if(c == '#')
                        {
                            goto newLineEnd;
                        }
                        else if(expression_input)
                        {
                            color_expression.push_back(c);
                        }
                        if(c == '{')
                        {
                            inExpression = true;
                        }
                        else if(c == '}')
                        {
                            inExpression = false;
                        }
                    }
                    color_expression.push_back(' ');
                }
                colordone:
                new_color = evaluate_color_expression(color_expression, lineNumber);

                user_defined_colors[color_name] = new_color;
                goto newLineEnd;
            }
            else
            {
                fileLineIter++;
            }
            if((*tIt) == "mesh")
            {
                //cout << "HELLL:" << endl;
                restoreConsolidatedMesh = true;
                Mesh newMesh(0);
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {

                        if(*tIt != "consolidatedmesh")
                        {
                            cout<<"Error: there is a bug in the program. Check!"<<endl;
                            goto newLineEnd;
                        }
                        newMesh.name = *tIt;
                        //cout << params << endl;
                        newMesh.setGlobalParameter(&params);
                    }
                    else
                    {
                        cout<<warning(26, lineNumber)<<endl;
                        goto newLineEnd;
                    }
                }
                else
                {
                    cout<<warning(26, lineNumber)<<endl;
                    goto newLineEnd;
                }

                if(meshes.find(newMesh.name) == meshes.end())
                {
                    meshes[newMesh.name] = newMesh;
                    current_mesh_name = newMesh.name;
                }
                else
                {
                    cout<<warning(3, lineNumber)<<endl;
                }
                goto newLineEnd;
            }
            else if((*tIt) == "endmesh")
            {
                restoreConsolidatedMesh = false;
                goto newLineEnd;
            }
            else if((*tIt) == "delete")
            {
                deletePhase = true;
                goto newLineEnd;
            }
            else if((*tIt) == "enddelete")
            {
                deletePhase = false;
                goto newLineEnd;
            }
            else if((*tIt) == "face" && deletePhase)
            {
                string deleteFaceName = "";
                if(++tIt < tokens.end())
                {
                    deleteFaceName = *tIt;
                }
                else
                {
                    cout<<warning(24, lineNumber)<<endl;
                    goto newLineEnd;
                }
                //cout<<deleteFaceName<<endl;
                bool found = (canvas
                              -> hierarchical_scene_transformed).deleteFaceInThisGroup(deleteFaceName);
                if(!found)
                {
                    cout<<warning(25, lineNumber)<<endl;
                }
                goto newLineEnd;
            }
            else if((*tIt) == "face" && restoreConsolidatedMesh)
            {
                if(current_mesh_name != "consolidatedmesh")
                {
                    cout<<"Error: there is a bug in the program. Check!"<<endl;
                    goto newLineEnd;
                }

                //cout << "HI" << endl;
                Face * newFace = new Face;
                if((++tIt) < tokens.end()) {

                    if(!testComments(*tIt))
                    {

                        faceIt = global_faces.find(*tIt);
                        if(faceIt == global_faces.end())
                        {
                            newFace -> name = *tIt;
                            global_faces[*tIt] = newFace;
                        }
                        else
                        {
                            cout<<warning(20, lineNumber)<<endl;
                        }
                    }
                    else
                    {
                        cout<<warning(19, lineNumber)<<endl;
                    }
                }
                string vertInside = "";
                bool addingVert = false;
                vector<Vertex*> vertices;
                vertices.clear();

                while(++tIt < tokens.end() && (*tIt) != "endface")
                {
                    for(char & c: (*tIt))
                    {
                        if(c == '(')
                        {
                            addingVert = true;
                        }
                        else if(c == ')')
                        {
                            addingVert = false;

                            if(vertInside != "")
                            {
                                //cout << vertInside << endl;
                                Vertex *v = (canvas -> hierarchical_scene_transformed).findVertexInThisGroup(vertInside);
                                if(!(canvas -> master_mesh.isEmpty())) /* Dealing with recovery of SIF.*/
                                {
                                    //cout << vertInside << endl;
                                    v = (canvas -> master_mesh.findVertexInThisMesh(vertInside));

                                }
                                if(v == NULL)
                                {
                                    cout<<warning(9, lineNumber)<<endl;
                                }
                                else
                                {
                                    vertices.push_back(v);
                                }

                                vertInside = "";
                            }
                            goto endAddingVertInFace;
                        }
                        else if(addingVert)
                        {
                            vertInside.push_back(c);
                        }

                    }
                    if(vertInside != "")
                    {
                        Vertex *v = (canvas -> hierarchical_scene_transformed).findVertexInThisGroup(vertInside);
                        if(!(canvas -> master_mesh.isEmpty())) /* Dealing with recovery of SIF.*/
                        {
                            v = (canvas -> master_mesh.findVertexInThisMesh(vertInside));
                        }
                        if(v == NULL)
                        {
                            cout<<warning(9, lineNumber)<<endl;
                        }
                        else
                        {
                            vertices.push_back(v);
                        }
                        vertInside = "";
                    }

                    //cout << vertices << endl;
                }
                endAddingVertInFace:
                /* Add this face to the current mesh.*/
                vector<Vertex*> mappedVertices;
                mappedVertices.clear();
                bool foundVertex;
                for(Vertex * vs : vertices)
                {

                    //cout << current_mesh_name << endl;
                    foundVertex = false;
                    for(Vertex * v : meshes[current_mesh_name].vertList)
                    {
                        //cout << v->ID << endl;
                        if(v -> source_vertex == vs)
                        {
                            foundVertex = true;
                            mappedVertices.push_back(v);
                            break;
                        }
                    }

                    if(!foundVertex)
                    {
                        Vertex * newVertex = new Vertex;
                        newVertex -> isParametric = vs -> isParametric;
                        newVertex -> position = vs -> position;
                        newVertex -> ID = meshes[current_mesh_name].vertList.size();
                        newVertex -> source_vertex = vs;
                        newVertex -> name = vs -> name;
                        newVertex -> x_expr = vs -> x_expr;
                        newVertex -> y_expr = vs -> y_expr;
                        newVertex -> z_expr = vs -> z_expr;
                        newVertex -> influencingParams = vs -> influencingParams;
                        newVertex -> params = vs -> params;
                        meshes[current_mesh_name].addVertex(newVertex);
                        mappedVertices.push_back(newVertex);
                    }
                }
                //cout << mappedVertices << endl;
                meshes[current_mesh_name].addPolygonFace(mappedVertices);
                meshes[current_mesh_name].faceList[meshes[current_mesh_name].faceList.size() - 1]
                        -> name = newFace -> name;

                if(++tIt < tokens.end() && (*tIt) == "surface")
                {
                    string color_name = "";
                    QColor color;
                    bool foundColor = false;
                    if(++tIt < tokens.end())
                    {
                        color_name = *tIt;
                        colorIt = user_defined_colors.find(color_name);
                        if(colorIt != user_defined_colors.end())
                        {
                            foundColor = true;
                            color = colorIt -> second;
                        }
                        else
                        {
                            cout<<warning(22, lineNumber)<<endl;
                        }
                    }
                    else
                    {
                        cout<<warning(22, lineNumber)<<endl;
                    }
                    if(foundColor)
                    {
                        meshes[current_mesh_name].faceList[meshes[current_mesh_name].faceList.size() - 1]
                                -> color = color;
                        meshes[current_mesh_name].faceList[meshes[current_mesh_name].faceList.size() - 1]
                                -> user_defined_color = true;
                    }
                }
                delete newFace;


            }
            else if((*tIt) == "instance")
            {
                //cout << "MMNN" << endl;
                string instanceName;
                Mesh newMesh;
                string className;
                bool findMesh = false;
                bool foundColor = false;
                QColor color;
                if((++tIt) < tokens.end())
                {
                    if(!testComments(*tIt))
                    {
                        instanceName = *tIt;
                    }
                }
                else
                {
                    cout<<warning(5, lineNumber)<<endl;
                }

                if((++tIt) < tokens.end())
                {
                    if(!testComments(*tIt))
                    {
                        className = *tIt;
                        //cout << className << endl;
                    }
                }
                else
                {
                    cout<<warning(6, lineNumber)<<endl;
                }

                if(className != "consolidatedmesh")
                {
                    //cout << "HELLO" << endl;
                    cout<<"Error: there is a bug in the program. Check!"<<endl;
                    goto newLineEnd;
                }
                else
                {
                    meshIt = meshes.find(className);
                    if(meshIt != meshes.end())
                    {
                        newMesh = (meshIt -> second).makeCopyForTempMesh(instanceName);
                        findMesh = true;
                    }
                }
                vector<Transformation> transformations_up;
                while(++tIt < tokens.end() && (*tIt) != "endinstance")
                {
                    if(testComments(*tIt))
                    {
                        goto newLineEnd;
                    }
                    if(*tIt == "rotate")
                    {
                        string xyz;
                        string angle;
                        bool makingXYZ = false;
                        bool makingAngle = false;
                        bool doneXYZ = false;
                        bool inExpression = false;
                        while(++tIt < tokens.end() && (*tIt) != "endinstance")
                        {
                            for(char& c : (*tIt))
                            {
                                if(c == '(' && !inExpression)
                                {
                                    if(!doneXYZ)
                                    {
                                        makingXYZ = true;
                                    }
                                    else
                                    {
                                        makingAngle = true;
                                    }
                                }
                                else if(c == ')' && !inExpression)
                                {
                                    if(makingXYZ)
                                    {
                                        doneXYZ = true;
                                        makingXYZ = false;
                                    } else if(makingAngle)
                                    {
                                        makingAngle = false;
                                        goto endWhile1;
                                    }
                                }
                                else
                                {
                                    if(makingXYZ)
                                    {
                                        xyz.push_back(c);
                                        if(c == '{')
                                        {
                                            inExpression = true;
                                        }
                                        else if(c == '}')
                                        {
                                            inExpression = false;
                                        }
                                    }
                                    else if(makingAngle)
                                    {
                                        angle.push_back(c);
                                        if(c == '{')
                                        {
                                            inExpression = true;
                                        }
                                        else if(c == '}')
                                        {
                                            inExpression = false;
                                        }
                                    }
                                }
                            }
                            if(makingXYZ && xyz != "")
                            {
                                xyz.push_back(' ');
                            }
                            else if(makingAngle && angle != "")
                            {
                                angle.push_back(' ');
                            }
                        }
                        endWhile1:
                        Transformation t(1, &params, xyz, angle);
                        transformations_up.push_back(t);
                    }
                    else if(*tIt == "translate" || *tIt == "scale")
                    {
                        bool isTranslate = false;
                        if(*tIt == "translate")
                        {
                            isTranslate = true;
                        }
                        string xyz = "";
                        bool makingXYZ = false;
                        bool inExpression = false;
                        while(++tIt < tokens.end() && (*tIt) != "endinstance")
                        {
                            for(char& c : (*tIt))
                            {
                                if(c == '(' && !inExpression)
                                {
                                    makingXYZ = true;
                                }
                                else if(c == ')' && !inExpression)
                                {
                                    makingXYZ = false;
                                    goto endWhile2;
                                }
                                else if(makingXYZ)
                                {
                                    xyz.push_back(c);
                                    if(c == '{')
                                    {
                                        inExpression = true;
                                    }
                                    else if(c == '}')
                                    {
                                        inExpression = false;
                                    }
                                }
                            }
                            if(xyz != "")
                            {
                                xyz.push_back(' ');
                            }
                        }
                        endWhile2:
                        if(isTranslate)
                        {
                            Transformation t(3,&params, xyz);
                            transformations_up.push_back(t);
                        }
                        else
                        {
                            Transformation t(2, &params, xyz);
                            transformations_up.push_back(t);
                        }
                    }
                    else if(*tIt == "mirror")
                    {
                        string xyzw = "";
                        bool makingXYZW = false;
                        bool inExpression = false;
                        while(++tIt < tokens.end() && (*tIt) != "endinstance")
                        {
                            for(char& c : (*tIt))
                            {
                                if(c == '(' && !inExpression)
                                {
                                    makingXYZW = true;
                                }
                                else if(c == ')' && !inExpression)
                                {
                                    makingXYZW = false;
                                    goto endWhile3;
                                }
                                else if(makingXYZW)
                                {
                                    xyzw.push_back(c);
                                    if(c == '{')
                                    {
                                        inExpression = true;
                                    }
                                    else if(c == '}')
                                    {
                                        inExpression = false;
                                    }
                                }
                            }
                            if(xyzw != "")
                            {
                                xyzw.push_back(' ');
                            }
                        }
                        endWhile3:
                        Transformation t(4, &params, xyzw);
                        transformations_up.push_back(t);
                    }
                    if(*tIt == "surface")
                    {
                        string color_name;
                        if(++tIt < tokens.end())
                        {
                            color_name = *tIt;
                            colorIt = user_defined_colors.find(color_name);
                            if(colorIt != user_defined_colors.end())
                            {
                                color = colorIt -> second;
                                foundColor = true;
                            }
                            else
                            {
                                cout<<warning(18, lineNumber)<<endl;
                            }
                        }
                        else
                        {
                            cout<<warning(18, lineNumber)<<endl;
                        }
                    }
                }
                if(findMesh)
                {
                    newMesh.setTransformation(transformations_up);
                    if(foundColor)
                    {
                        newMesh.setColor(color);
                        newMesh.user_set_color = true;
                    }
                    group.addMesh(newMesh);
                }
                else
                {
                    cout<<"Error: there is a bug in the program. Check!"<<endl;
                }
            }
            else
            {
                cout<<nextLine<<endl;
                goto newLineEnd;
            }
        }
    newLineEnd:
    lineNumber++;
    }

    canvas -> set_to_editing_mode(true);
    canvas -> updateFromSavedMesh();
}

void NomeParser::appendWithANOM(unordered_map<string, Parameter> &params,
                                Group &group,
                                SlideGLWidget* canvas,
                                string input)
{

    ifstream file(input);
    if (!file.good())
    {
        cout<<"THE PATH OF MINI SIF FILE IS NOT VAILD.";
        exit(1);
    }
    string nextLine;
    int lineNumber = 1;
    bool restoreBank = false;
    bool restoreConsolidateMesh = false;
    unordered_map<string, Parameter>::iterator pIt;
    vector<Vertex*> restore_vertices;
    unordered_map<string, Group> groups;
    string currentGroup = "";
    while(std::getline(file, nextLine))
    {
        istringstream iss(nextLine);
        vector<string> tokens;
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter(tokens));
        vector<string>::iterator tIt;
        for(tIt = tokens.begin(); tIt < tokens.end(); tIt++)
        {
            if(testComments(*tIt))
            {
                break;
            }
            else if((*tIt) == "savedparameter")
            {
                restoreBank = true;
                goto newLineEnd;
            }
            else if((*tIt) == "endsavedparameter")
            {
                restoreBank = false;
                goto newLineEnd;
            }
            else if((*tIt) == "consolidate")
            {
                restoreConsolidateMesh = true;
                goto newLineEnd;
            }
            else if((*tIt) == "endconsolidate")
            {
                restoreConsolidateMesh = false;
                goto newLineEnd;
            }
            else if(restoreBank)
            {
                pIt = params.find(*tIt);
                if(pIt == params.end())
                {
                    cout<<warning(7, lineNumber)<<endl;
                }
                else
                {
                    tIt++;
                    if(tIt >= tokens.end() || testComments(*tIt))
                    {
                        cout<<warning(8, lineNumber)<<endl;
                    }
                    else
                    {
                        float value = stof(*tIt);
                        (pIt -> second).changeParameterValue(value);
                    }
                }
                goto newLineEnd;
            }
            else if(restoreConsolidateMesh)
            {
                if(*tIt == "consolidateface")
                {
                    restore_vertices.clear();
                    goto newLineEnd;
                }
                else if(*tIt == "endconsolidateface")
                {
                    canvas->consolidate_mesh.addPolygonFace(restore_vertices);
                    goto newLineEnd;
                }
                else if(*tIt == "vertex")
                {
                    tIt++;
                    if(tIt >= tokens.end() || testComments(*tIt))
                    {
                        cout<<warning(9, lineNumber)<<endl;
                    }
                    Vertex *v = (canvas -> hierarchical_scene_transformed).findVertexInThisGroup(*tIt);
                    if(!(canvas -> master_mesh.isEmpty())) /* Dealing with recovery of SIF.*/
                    {
                        v = (canvas -> master_mesh.findVertexInThisMesh(*tIt));
                    }
                    if(v == NULL)
                    {
                        cout<<warning(9, lineNumber);
                    }
                    else
                    {
                        (canvas -> consolidate_mesh).addVertex(v);
                        restore_vertices.push_back(v);
                    }
                    goto newLineEnd;
                }
            }
            else if((*tIt) == "instance")
            {

                //cout << "HELFFD" << endl;
                string instanceName;
                Mesh newMesh;
                string className;
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        instanceName = *tIt;
                    }
                }
                else
                {
                    cout<<warning(5, lineNumber);
                }
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        className = *tIt;
                    }
                }
                else
                {
                    cout<<warning(6, lineNumber);
                }
                if(className == "consolidatemesh")
                {
                    newMesh = (canvas -> consolidate_mesh).makeCopyForTempMesh(instanceName);
                }
                else
                {
                    goto newLineEnd;
                }
                vector<Transformation> transformations_up;
                while(++tIt < tokens.end() && (*tIt) != "endinstance")
                {
                    if(testComments(*tIt))
                    {
                        goto newLineEnd;
                    }
                    if(*tIt == "rotate")
                    {
                        string xyz;
                        string angle;
                        bool makingXYZ = false;
                        bool makingAngle = false;
                        bool doneXYZ = false;
                        bool inExpression = false;
                        while(++tIt < tokens.end() && (*tIt) != "endinstance")
                        {
                            for(char& c : (*tIt))
                            {
                                if(c == '(' && !inExpression)
                                {
                                    if(!doneXYZ)
                                    {
                                        makingXYZ = true;
                                    }
                                    else
                                    {
                                        makingAngle = true;
                                    }
                                }
                                else if(c == ')' && !inExpression)
                                {
                                    if(makingXYZ)
                                    {
                                        doneXYZ = true;
                                        makingXYZ = false;
                                    } else if(makingAngle)
                                    {
                                        makingAngle = false;
                                        goto endWhile1;
                                    }
                                }
                                else
                                {
                                    if(makingXYZ)
                                    {
                                        xyz.push_back(c);
                                        if(c == '{')
                                        {
                                            inExpression = true;
                                        }
                                        else if(c == '}')
                                        {
                                            inExpression = false;
                                        }
                                    }
                                    else if(makingAngle)
                                    {
                                        angle.push_back(c);
                                        if(c == '{')
                                        {
                                            inExpression = true;
                                        }
                                        else if(c == '}')
                                        {
                                            inExpression = false;
                                        }
                                    }
                                }
                            }
                            if(makingXYZ && xyz != "")
                            {
                                xyz.push_back(' ');
                            }
                            else if(makingAngle && angle != "")
                            {
                                angle.push_back(' ');
                            }
                        }
                        endWhile1:
                        Transformation t(1, &params, xyz, angle);
                        transformations_up.push_back(t);
                    }
                    else if(*tIt == "translate" || *tIt == "scale")
                    {
                        bool isTranslate = false;
                        if(*tIt == "translate")
                        {
                            isTranslate = true;
                        }
                        string xyz = "";
                        bool makingXYZ = false;
                        bool inExpression = false;
                        while(++tIt < tokens.end() && (*tIt) != "endinstance")
                        {
                            for(char& c : (*tIt))
                            {
                                if(c == '(' && !inExpression)
                                {
                                    makingXYZ = true;
                                }
                                else if(c == ')' && !inExpression)
                                {
                                    makingXYZ = false;
                                    goto endWhile2;
                                }
                                else if(makingXYZ)
                                {
                                    xyz.push_back(c);
                                    if(c == '{')
                                    {
                                        inExpression = true;
                                    }
                                    else if(c == '}')
                                    {
                                        inExpression = false;
                                    }
                                }
                            }
                            if(xyz != "")
                            {
                                xyz.push_back(' ');
                            }
                        }
                        endWhile2:
                        if(isTranslate)
                        {
                            Transformation t(3,&params, xyz);
                            transformations_up.push_back(t);
                        }
                        else
                        {
                            Transformation t(2, &params, xyz);
                            transformations_up.push_back(t);
                        }
                    }
                    else if(*tIt == "mirror")
                    {
                        string xyzw = "";
                        bool makingXYZW = false;
                        bool inExpression = false;
                        while(++tIt < tokens.end() && (*tIt) != "endinstance")
                        {
                            for(char& c : (*tIt))
                            {
                                if(c == '(' && !inExpression)
                                {
                                    makingXYZW = true;
                                }
                                else if(c == ')' && !inExpression)
                                {
                                    makingXYZW = false;
                                    goto endWhile3;
                                }
                                else if(makingXYZW)
                                {
                                    xyzw.push_back(c);
                                    if(c == '{')
                                    {
                                        inExpression = true;
                                    }
                                    else if(c == '}')
                                    {
                                        inExpression = false;
                                    }
                                }
                            }
                            if(xyzw != "")
                            {
                                xyzw.push_back(' ');
                            }
                        }
                        endWhile3:
                        Transformation t(4, &params, xyzw);
                        transformations_up.push_back(t);
                    }
                }
                if(currentGroup != "")
                {
                    newMesh.setTransformation(transformations_up);
                    groups[currentGroup].addMesh(newMesh);
                }
                else
                {
                    newMesh.setTransformation(transformations_up);
                    group.addMesh(newMesh);
                }
            }
        }
        newLineEnd:
        lineNumber++;
    }
    canvas -> updateFromSavedMesh();
}
