/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "vertex.h"
#include "parameter.h"

Vertex::Vertex()
{
    position = vec3(0, 0, 0);
    normal = vec3(0, 0, 0);
    oneEdge = NULL;
    ID = 0;
    selected = false;
    isParametric = false;
    before_transform_vertex = NULL;
    source_vertex = NULL;
}

Vertex::Vertex(float x, float y, float z, unsigned long ID)
{
    position = vec3(x, y, z);
    normal = vec3(0, 0, 0);
    oneEdge = NULL;
    ID = ID;
    selected = false;
    isParametric = false;
    before_transform_vertex = NULL;
}

void Vertex::addParam(Parameter* param)
{
    influencingParams.push_back(param);
}

int Vertex::setVertexParameterValues(string input, int lineNumber)
{
    float x, y, z;
    string nextExpression = "";
    bool expressionMode = false;
    string number = "";
    int i = 0;
    for(char& c : input)
    {
        if(c == '{')
        {
            expressionMode = true;
        }
        else if(c == '}')
        {
            expressionMode = false;
            //cout << nextExpression << endl;
            switch(i)
            {
            case 0:
                x_expr = nextExpression.substr(5);
                x = evaluate_vertex_expression(x_expr, params, this);
                //cout << x << endl;
                if (isnan(x)){
                    cout << "Error: Point method at line " + to_string(lineNumber) + " has the parameter " + x_expr + " from a bank that has not been defined." << endl;
                    return 1;
                }

                break;
            case 1:
                y_expr = nextExpression.substr(5);
                y = evaluate_vertex_expression(y_expr, params, this);
                if (isnan(y)){
                    cout << "Error: Point method at line " + to_string(lineNumber) + " has the parameter " + y_expr + " from a bank that has not been defined." << endl;
                    return 1;
                }

                break;
            case 2:
                z_expr = nextExpression.substr(5);
                z = evaluate_vertex_expression(z_expr, params, this);
                if (isnan(z)){
                    cout << "Error: Point method at line " + to_string(lineNumber) + " has the parameter " + z_expr + " from a bank that has not been defined." << endl;
                    return 1;
                }

                break;
            }
            nextExpression = "";
            i++;
        }
        else if(expressionMode)
        {
            nextExpression.push_back(c);
        }
        else if(!expressionMode && ((c >= '0' &&  c <= '9')
                                    || c == '.' || c == '-' || c == '+'))
        {
            number.push_back(c);
        }
        else
        {
            if(number != "")
            {
                switch(i)
                {
                case 0:
                    x = stof(number);
                    break;
                case 1:
                    y = stof(number);
                    break;
                case 2:
                    z = stof(number);
                    break;
                }
                number = "";
                i++;
            }
        }

    }
    if(number != "")
    {
        switch(i)
        {
        case 0:
            x = stof(number);
            break;
        case 1:
            y = stof(number);
            break;
        case 2:
            z = stof(number);
            break;
        }
    }

    if (i > 3){
        cout << "Error: Point method at line " + to_string(lineNumber) + " has too many parameters. A point can only have 3 parameters: x, y, and z." << endl;
        return 1;
    }
    else if(i <= 2){
        cout << "Error: Point method at line " + to_string(lineNumber) + " does not have enough parameters. A point can only have 3 parameters: x, y, and z." << endl;
        return 1;
    }
    isParametric = x_expr != "" || y_expr != "" || z_expr != "";
    position = vec3(x, y, z);
    return 0;
}

void Vertex::setGlobalParameter(unordered_map<string, Parameter> *params)
{
    this -> params = params;
}

void Vertex::update()
{
    if(isParametric)
    {
        float new_x, new_y, new_z;
        if(x_expr != "")
        {
            new_x = evaluate_expression(x_expr, params);
        }
        else
        {
            new_x = position[0];
        }
        if(y_expr != "")
        {
            new_y = evaluate_expression(y_expr, params);
        }
        else
        {
            new_y = position[1];
        }
        if(z_expr != "")
        {
            new_z = evaluate_expression(z_expr, params);
        }
        else
        {
            new_z = position[2];
        }
        position = vec3(new_x, new_y, new_z);
    }
}
