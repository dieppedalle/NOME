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



char * convertFileToString(string fileName){
    /*
     * convertFileToString
     * Input: fileName as a string
     * Output: Returns the content of the file as a string with comments removed and
     * space next to parenthesis (to later be able to tokenize the string according to spaces)
     */
    // Create variables for opening file
    FILE *fileParser;
    //char *buffer = "";
    int size;

    std::string buffer = "";

    // Opens the file
    fileParser = fopen(fileName.c_str(), "r");
    if (fileParser == NULL) return NULL;

    // Get the size of the file
    fseek(fileParser, 0, SEEK_END);
    size = ftell(fileParser);
    fseek(fileParser, 0, SEEK_SET);

    // Initialize our buffer string
    //buffer = (char *) calloc(size, sizeof(char));
    //memset( buffer, 0, size * sizeof(char));

    // Keep track of the previous and current character
    char previousC = ' ';
    char c = getc(fileParser);

    int numberOfline = 1;
    int i = 0;

    // Iterate through the file
    while (c != EOF){
        // Check for comments using #
        if (c == '#'){
            while (c != '\n' && c != EOF){
                c = getc(fileParser);
            }
        }
        else{
            // Check for parenthesis and add space in between them
            if (c == '(' || c == ')' || c == '{' || c == '}' || c == '\n'){
                // Change the size of the buffer as we are adding 2 space characters

                buffer.push_back(' ');
                i++;
                buffer.push_back(c);
                i++;
                buffer.push_back(' ');
                i++;

                previousC = c;
                c = getc(fileParser);
                // Check if the ( is in fact a comment
                if ((c == '*') && (previousC == '(')){
                    buffer.pop_back();
                    i--;
                    buffer.pop_back();
                    i--;
                    size -= 1;
                    //realloc(buffer, size * sizeof(char));
                    while ((previousC != '*') || (c != ')')){
                        if (c == '\n'){
                            buffer.push_back(' ');
                            i++;
                        }
                        else if (c == EOF){
                            return NULL;
                        }
                        previousC = c;
                        c = getc(fileParser);
                    }
                    c = getc(fileParser);

                }
            }
            else{
                buffer.push_back(c);
                i++;
                c = getc(fileParser);

            }
        }

    }

    char * S = new char[buffer.length() + 1];
    std::strcpy(S,buffer.c_str());

    return S;
}

typedef struct {
    char *value;
    int lineNumber;
} token;

struct node{
    char *value;
    int lineNumber;
    struct node *next;
};

class Queue{
    private:
        node *rear;
        node *front;
    public:
        Queue();
        void enqueue(char * value, int lineNumber);
        token dequeue();
        void display();

};

Queue::Queue(){
    rear = NULL;
    front = NULL;
}

void Queue::enqueue(char * value, int lineNumber){
    node *temp = new node;

    temp->value = value;
    temp->lineNumber = lineNumber;
    temp->next = NULL;
    if(front == NULL){
        front = temp;
    }else{
        rear->next = temp;
    }
    rear = temp;

}

token Queue::dequeue(){
    node *temp = new node;
    token returnData = {"", -1};
    if(front == NULL){
        return returnData;
    }else{
        temp = front;
        front = front->next;
        returnData = {temp->value, temp->lineNumber};
        delete temp;
        return returnData;
    }
}

void Queue::display(){
    node *p = new node;
    p = front;
    if(front == NULL){
        cout<<"\nNothing to Display\n";
    }else{
        while(p != NULL){
            cout<< p->value << endl;
            cout<< p->lineNumber << endl;
            p = p->next;
        }
    }
}

Queue tokenize(char *inputString){
    char * token;
    token = strtok(inputString , " \t");

    int lineNumberFile = 1;
    Queue tokens = Queue();

    while (token != NULL)
    {
        if (strcmp(token, "\n")==0){
            lineNumberFile++;
        }
        else{
            tokens.enqueue(token, lineNumberFile);

        }

        token = strtok (NULL, " \t");
    }
    return tokens;
}

int isReserved(std::vector<std::string> mylist, const std::string &myinput){
    if (std::find(std::begin(mylist), std::end(mylist), myinput) != std::end(mylist)){
        return 1;
    }
    else{
        return 0;
    }
}

int NomeParser::makeWithNome(vector<ParameterBank> &banks,
                              unordered_map<string, Parameter> &params,
                              Group &group,
                              string input,
                              vector<string> &colorlines,
                              vector<string> &banklines,
                              vector<string> &geometrylines,
                              vector<int> &postProcessingLines)
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

    //====

    std::vector<std::string> reservedWords{"#", "\n", "point", "endpoint", "surface",
                                   "endsurface", "face", "endface", "object",
                                   "endobject", "bank", "endbank", "mesh",
                                   "endmesh", "tunnel", "endtunnel", "funnel",
                                   "endfunnel", "polyline", "endpolyline","instance"
                                   "endinstance", "delete", "enddelete", "group",
                                   "endgroup", "translate", "rotate", "mirror"};

    char * inputString;

    // Reads the input file and tokenizes it
    inputString = convertFileToString(input);
    if (inputString == NULL){
        cout << "Error: Missing *) closing comment." << endl;
        return 1;
    }

    Queue tokens = tokenize(inputString);

    // Convert string to tokens
    token currentToken = tokens.dequeue();

    while (currentToken.lineNumber != -1){
        if(strcmp("surface", currentToken.value) == 0) {
            string color_name;
            QColor new_color;


            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            color_name = currentToken.value;
            colorIt = user_defined_colors.find(color_name);

            if((colorIt != user_defined_colors.end()) || (isReserved(reservedWords, color_name) == 1)){
                cout << "Error: The surface " + color_name + " at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }

            reservedWords.push_back(color_name);

            currentToken = tokens.dequeue();

            if(currentToken.lineNumber == -1){
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "color") != 0){
                cout << "Error: The surface " + color_name + " at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "(") != 0){
                cout << "Error: The surface " + color_name + " at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            char * e;
            double r = std::strtod(currentToken.value, &e);


            if (*e != '\0')
            {
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }


            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            double g = std::strtod(currentToken.value, &e);

            if (*e != '\0')
            {
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();

            if(currentToken.lineNumber == -1){
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            double b = std::strtod(currentToken.value, &e);

            if (*e != '\0')
            {
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }


            new_color = QColor(255*r, 255*g, 255*b);
            if (!new_color.isValid()){
                return 1;
            }

            user_defined_colors[color_name] = new_color;

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  ")") != 0){
                cout << "Error: The surface " + color_name + " at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The surface at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "endsurface") != 0){
                cout << "Error: Missing endsurface on line " + to_string(currentToken.lineNumber) + "." << endl;
                return 1;
            }

            currentToken = tokens.dequeue();


        }
        else if (strcmp("bank", currentToken.value) == 0) {
            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(isReserved(reservedWords, currentToken.value) == 1){
                cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }
            reservedWords.push_back(currentToken.value);

            ParameterBank newBank;
            newBank.setName(QString::fromStdString(currentToken.value));
            banks.push_back(newBank);

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }


            while (strcmp(currentToken.value,  "endbank") != 0){
                Parameter newParameter;
                //cout << "HELLO" << endl;

                if (strcmp(currentToken.value,  "set") != 0){
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }


                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                string strToken = currentToken.value;

                newParameter.name = banks[banks.size() - 1].name + QString::fromStdString("_" + strToken);

                if(isReserved(reservedWords, newParameter.name.toUtf8().constData()) == 1){
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                    return 1;
                }
                reservedWords.push_back(newParameter.name.toUtf8().constData());

                name = currentToken.value;



                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                char * e;
                double convertedValue;
                convertedValue = std::strtod(currentToken.value, &e);

                if (*e != '\0')
                {
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }
                newParameter.value = convertedValue;

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                convertedValue = std::strtod(currentToken.value, &e);

                if (*e != '\0')
                {
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                newParameter.start = convertedValue;

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                convertedValue = std::strtod(currentToken.value, &e);

                if (*e != '\0')
                {
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                newParameter.end = convertedValue;

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                convertedValue = std::strtod(currentToken.value, &e);

                if (*e != '\0')
                {
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                newParameter.stepsize = convertedValue;

                pIt = params.find(newParameter.name.toStdString());
                if(pIt == params.end())
                {
                    params[banks[banks.size() - 1].name.toStdString() + "_" + name] = newParameter;
                }
                else
                {
                    cout << "Error: The set at line " + to_string(lineNumber) + " with name " + newParameter.name.toStdString() + " has already been defined."  << endl;
                    return 1;
                }
                banks[banks.size() - 1].addParameter(&params[banks[banks.size() - 1].name.toStdString() + "_" + name]);

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The bank at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }
            }
            currentToken = tokens.dequeue();

        }
        else if (strcmp("point", currentToken.value) == 0) {
            Vertex * newVertex = new Vertex;
            currentToken = tokens.dequeue();

            if(currentToken.lineNumber == -1){
                cout << "Error: The point at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(isReserved(reservedWords, currentToken.value) == 1){
                cout << "Error: The point at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }

            reservedWords.push_back(currentToken.value);

            vertIt = global_vertices.find(currentToken.value);
            if(vertIt == global_vertices.end()){
                newVertex -> name = currentToken.value;
                global_vertices[currentToken.value] = newVertex;
            }
            else
            {
                cout << "Error: Point " << currentToken.value << " on line " << to_string(currentToken.lineNumber) << " has already been created." << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The point at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "(") != 0){
                cout << "Error: The point at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The point at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            string xyz;
            while (strcmp(currentToken.value,  ")") != 0){
                xyz.append(currentToken.value);
                //xyz.push_back(currentToken.value);
                xyz.push_back(' ');

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The point at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }
            }

            newVertex->setGlobalParameter(&params);
            isError = 0;
            isError = newVertex->setVertexParameterValues(xyz, currentToken.lineNumber);

            if (isError == 1){
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The point at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "endpoint") != 0){
                cout << "Error: The point at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();

        }
        else if (strcmp("face", currentToken.value) == 0){
            Face * newFace = new Face;

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The face at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(isReserved(reservedWords, currentToken.value) == 1){
                cout << "Error: The face at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }

            reservedWords.push_back(currentToken.value);

            faceIt = global_faces.find(currentToken.value);
            if(faceIt == global_faces.end())
            {
                newFace -> name = currentToken.value;
                global_faces[currentToken.value] = newFace;
            }
            else
            {
                cout << "Error: The face " << currentToken.value << " at line " << to_string(currentToken.lineNumber) << " has already been defined."  << endl;
                return 1;
            }

            string vertInside = "";
            bool addingVert = false;
            vector<Vertex*> vertices;
            vertices.clear();

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The face at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "(") != 0){
                cout << "Error: The face at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The face at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            while (strcmp(currentToken.value,  ")") != 0){
                vertIt = global_vertices.find(currentToken.value);

                if(vertIt == global_vertices.end()){
                    cout << "Error: Incorrect vertex name in face generator on line " + to_string(currentToken.lineNumber) + ". The vertex " + currentToken.value + " has never been created." << endl;
                    return 1;
                }
                else{
                    vertices.push_back(vertIt -> second);
                }

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The face at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }
            }
            map_face_vertices[newFace] = vertices;

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The face at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp("surface", currentToken.value) == 0)
            {
                string color_name = "";
                QColor color;
                bool foundColor = false;

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The face at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                color_name = currentToken.value;
                colorIt = user_defined_colors.find(color_name);
                if(colorIt != user_defined_colors.end())
                {
                    foundColor = true;
                    color = colorIt -> second;
                }
                else
                {
                    cout << "Error: Incorrect surface name in face generator on line " + to_string(currentToken.lineNumber) + ". The surface " + color_name + " has never been defined." << endl;
                    return 1;
                }
                if(foundColor)
                {
                    newFace -> color = color;
                    newFace -> user_defined_color = true;
                }

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The face at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }
            }

            if (strcmp("endface", currentToken.value) != 0){
                cout << "Error: Missing endface on line " + to_string(currentToken.lineNumber) + "." << endl;
                return 1;
            }

            currentToken = tokens.dequeue();

        }
        else if (strcmp("polyline", currentToken.value) == 0){
            PolyLine newPolyline;

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The polyline at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(isReserved(reservedWords, currentToken.value) == 1){
                cout << "Error: The polyline at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }

            reservedWords.push_back(currentToken.value);

            lineIt = polylines.find(currentToken.value);

            if(lineIt == polylines.end())
            {
                newPolyline.name = currentToken.value;
            }
            else
            {
                cout << "Error: The polyline " << currentToken.value << " at line " << to_string(currentToken.lineNumber) << " has already been created."  << endl;
                return 1;
            }


            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The polyline at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "(") != 0){
                cout << "Error: The polyline at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The polyline at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }


            while (strcmp(currentToken.value,  ")") != 0){
                vertIt = global_vertices.find(currentToken.value);
                if(vertIt == global_vertices.end())
                {
                    cout << "Error: Incorrect vertex name in polyline generator on line " + to_string(currentToken.lineNumber) + ". The vertex " + currentToken.value + " has never been created." << endl;
                    return 1;
                }
                else
                {
                    newPolyline.addVertex(vertIt -> second);
                }

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The polyline at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The polyline at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "closed") != 0){
                newPolyline.isLoop = true;
            }

            if(strcmp(currentToken.value,  "endpolyline") != 0){
                cout << "Error: Missing endpolyline on line " + to_string(currentToken.lineNumber) + "." << endl;
                return 1;
            }

            polylines[newPolyline.name] = newPolyline;

            currentToken = tokens.dequeue();

        }
        else if (strcmp("tunnel", currentToken.value) == 0){
            Mesh newTunnel(2);
            newTunnel.setGlobalParameter(&params);

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The tunnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(isReserved(reservedWords, currentToken.value) == 1){
                cout << "Error: The tunnel at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }

            reservedWords.push_back(currentToken.value);

            newTunnel.name = currentToken.value;

            string tunnel_expression;
            bool expression_input = false;
            bool inExpression = false;

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The tunnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "(") != 0){
                cout << "Error: The tunnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The tunnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            while (strcmp(currentToken.value,  ")") != 0){
                tunnel_expression.append(currentToken.value);
                tunnel_expression.push_back(' ');

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The tunnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }
            }

            newTunnel.setTunnelParameterValues(tunnel_expression, currentToken.lineNumber);
            newTunnel.makeTunnel();

            if(meshes.find(newTunnel.name) == meshes.end())
            {
                meshes[newTunnel.name] = newTunnel;
            }
            else
            {
                cout << "Error: The tunnel at line " + to_string(currentToken.lineNumber) + " with name " + newTunnel.name + " has already been created."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The tunnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if (strcmp("endtunnel", currentToken.value) != 0){
                cout << "Error: Missing endtunnel on line " + to_string(currentToken.lineNumber) + "." << endl;
                return 1;
            }

            currentToken = tokens.dequeue();

        }
        else if (strcmp("funnel", currentToken.value) == 0){
            Mesh newFunnel(1);
            newFunnel.setGlobalParameter(&params);

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The funnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            newFunnel.name = (currentToken.value);

            if(isReserved(reservedWords, currentToken.value) == 1){
                cout << "Error: The funnel at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }

            reservedWords.push_back(currentToken.value);

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The funnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            string funnel_expression;
            bool expression_input = false;
            bool inExpression = false;

            if(strcmp(currentToken.value,  "(") != 0){
                cout << "Error: The funnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The funnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            while (strcmp(currentToken.value,  ")") != 0){
                funnel_expression.append(currentToken.value);
                funnel_expression.push_back(' ');

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The funnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }
            }

            newFunnel.setFunnelParameterValues(funnel_expression, currentToken.lineNumber);
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
                cout << "Error: The funnel at line " + to_string(currentToken.lineNumber) + " with name " + newFunnel.name + " has already been created."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The funnel at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if (strcmp("endfunnel", currentToken.value) != 0){
                cout << "Error: Missing endfunnel on line " + to_string(currentToken.lineNumber) + "." << endl;
                return 1;
            }

            currentToken = tokens.dequeue();


        }
        else if(strcmp("group", currentToken.value) == 0)
        {
            Group newGroup;

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The group at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            newGroup.setName(currentToken.value);

            if(isReserved(reservedWords, currentToken.value) == 1){
                cout << "Error: The group at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }

            reservedWords.push_back(currentToken.value);

            groups[newGroup.name] = newGroup;
            currentGroup = newGroup.name;

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The group at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }


            while (strcmp(currentToken.value,  "instance") == 0){
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


                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                instanceName = currentToken.value;

                if(isReserved(reservedWords, currentToken.value) == 1){
                    cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                    return 1;
                }

                reservedWords.push_back(currentToken.value);

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                className = currentToken.value;

                // Check what type of object
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
                            cout << "Error: The instance " + className + " at line " + to_string(currentToken.lineNumber) + " has never been created."  << endl;
                            return 1;
                        }
                    }
                }

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                vector<Transformation> transformations_up;
                while(strcmp(currentToken.value,  "endinstance") != 0)
                {
                    if(strcmp(currentToken.value,  "rotate") == 0)
                    {
                        string xyz;
                        string angle;
                        bool makingXYZ = false;
                        bool makingAngle = false;
                        bool doneXYZ = false;
                        bool inExpression = false;

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }

                        if(strcmp(currentToken.value,  "(") != 0)
                        {
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }


                        while (strcmp(currentToken.value,  ")") != 0){
                            xyz.append(currentToken.value);

                            currentToken = tokens.dequeue();
                            if(currentToken.lineNumber == -1){
                                cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                                return 1;
                            }
                            xyz.push_back(' ');
                        }

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }



                        if(strcmp(currentToken.value,  "(") != 0)
                        {
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }


                        while (strcmp(currentToken.value,  ")") != 0){
                            angle.append(currentToken.value);

                            currentToken = tokens.dequeue();
                            if(currentToken.lineNumber == -1){
                                cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                                return 1;
                            }
                            angle.push_back(' ');
                        }
                        Transformation t(1, &params, xyz, angle);
                        transformations_up.push_back(t);
                    }
                    else if(strcmp(currentToken.value,  "translate") == 0 || strcmp(currentToken.value,  "scale") == 0)
                    {
                        bool isTranslate = false;
                        if(strcmp(currentToken.value,  "translate") == 0)
                        {
                            isTranslate = true;
                        }

                        string xyz = "";
                        bool makingXYZ = false;
                        bool inExpression = false;

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }

                        if(strcmp(currentToken.value,  "(") != 0)
                        {
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }

                        while (strcmp(currentToken.value,  ")") != 0){
                            xyz.append(currentToken.value);

                            currentToken = tokens.dequeue();
                            if(currentToken.lineNumber == -1){
                                cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                                return 1;
                            }
                            xyz.push_back(' ');
                        }

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
                    else if(strcmp(currentToken.value,  "mirror") == 0)
                    {
                        string xyzw = "";
                        bool makingXYZW = false;
                        bool inExpression = false;

                        if(strcmp(currentToken.value,  "(") != 0)
                        {
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }

                        while (strcmp(currentToken.value,  ")") != 0){
                            xyzw.append(currentToken.value);

                            currentToken = tokens.dequeue();
                            if(currentToken.lineNumber == -1){
                                cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                                return 1;
                            }
                            xyzw.push_back(' ');
                        }

                        Transformation t(4, &params, xyzw);
                        transformations_up.push_back(t);
                    }
                    else if(strcmp(currentToken.value,  "surface") == 0)
                    {
                        string color_name;

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }

                        color_name = currentToken.value;
                        colorIt = user_defined_colors.find(color_name);
                        if(colorIt != user_defined_colors.end())
                        {
                            color = colorIt -> second;
                            foundColor = true;
                        }
                        else
                        {
                            cout << "Error: The instance " + color_name + " at line " + to_string(currentToken.lineNumber) + " has never been created."  << endl;
                            return 1;
                        }

                    }
                    else {
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " has the parameter " + currentToken.value + " which is incorrect."  << endl;
                        return 1;
                    }

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
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

                if(strcmp(currentToken.value,  "endinstance") != 0){
                    cout << "Error: Missing endinstance on line " + to_string(currentToken.lineNumber) + "." << endl;
                    return 1;
                }

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

            }
            if(strcmp(currentToken.value,  "endgroup") != 0){
                cout << "Error: Missing endgroup on line " + to_string(currentToken.lineNumber) + "." << endl;
                return 1;
            }
            currentToken = tokens.dequeue();

        }
        else if(strcmp("instance", currentToken.value) == 0)
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

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            instanceName = currentToken.value;

            if(isReserved(reservedWords, currentToken.value) == 1){
                cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }

            reservedWords.push_back(currentToken.value);

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            className = currentToken.value;

            // Check what type of object
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
                        cout << "Error: The instance " + className + " at line " + to_string(currentToken.lineNumber) + " has never been created."  << endl;
                        return 1;
                    }
                }
            }



            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }



            vector<Transformation> transformations_up;
            while(strcmp(currentToken.value,  "endinstance") != 0)
            {
                if(strcmp(currentToken.value,  "rotate") == 0)
                {
                    string xyz;
                    string angle;
                    bool makingXYZ = false;
                    bool makingAngle = false;
                    bool doneXYZ = false;
                    bool inExpression = false;

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    if(strcmp(currentToken.value,  "(") != 0)
                    {
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }


                    while (strcmp(currentToken.value,  ")") != 0){
                        xyz.append(currentToken.value);

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }
                        xyz.push_back(' ');
                    }

                    if(strcmp(currentToken.value,  "(") != 0)
                    {
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    while (strcmp(currentToken.value,  ")") != 0){
                        angle.append(currentToken.value);

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }
                        angle.push_back(' ');
                    }
                    Transformation t(1, &params, xyz, angle);
                    transformations_up.push_back(t);
                }
                else if(strcmp(currentToken.value,  "translate") == 0 || strcmp(currentToken.value,  "scale") == 0)
                {
                    bool isTranslate = false;
                    if(strcmp(currentToken.value,  "translate") == 0)
                    {
                        isTranslate = true;
                    }

                    string xyz = "";
                    bool makingXYZ = false;
                    bool inExpression = false;

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    if(strcmp(currentToken.value,  "(") != 0)
                    {
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    while (strcmp(currentToken.value,  ")") != 0){
                        xyz.append(currentToken.value);

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }
                        xyz.push_back(' ');
                    }

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
                else if(strcmp(currentToken.value,  "mirror") == 0)
                {
                    string xyzw = "";
                    bool makingXYZW = false;
                    bool inExpression = false;

                    if(strcmp(currentToken.value,  "(") != 0)
                    {
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    while (strcmp(currentToken.value,  ")") != 0){
                        xyzw.append(currentToken.value);

                        currentToken = tokens.dequeue();
                        if(currentToken.lineNumber == -1){
                            cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                            return 1;
                        }
                        xyzw.push_back(' ');
                    }

                    Transformation t(4, &params, xyzw);
                    transformations_up.push_back(t);
                }
                else if(strcmp(currentToken.value,  "surface") == 0)
                {
                    string color_name;

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    color_name = currentToken.value;
                    colorIt = user_defined_colors.find(color_name);
                    if(colorIt != user_defined_colors.end())
                    {
                        color = colorIt -> second;
                        foundColor = true;
                    }
                    else
                    {
                        cout << "Error: The instance " + color_name + " at line " + to_string(currentToken.lineNumber) + " has never been created."  << endl;
                        return 1;
                    }

                }
                else {
                    cout << "Error: The instance at line " + to_string(currentToken.lineNumber) + " has the parameter " + currentToken.value + " which is incorrect."  << endl;
                    return 1;
                }

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The point at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
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

            if(strcmp(currentToken.value,  "endinstance") != 0){
                cout << "Error: Missing endinstance on line " + to_string(currentToken.lineNumber) + "." << endl;
                return 1;
            }

            currentToken = tokens.dequeue();


        }
        else if(strcmp("object", currentToken.value) == 0){
            Mesh newMesh(0);
            newMesh.setGlobalParameter(&params);

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The object at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            newMesh.name = currentToken.value;

            if(isReserved(reservedWords, currentToken.value) == 1){
                cout << "Error: The object at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }

            reservedWords.push_back(currentToken.value);

            string faceInside = "";
            bool addingFace = false;

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The object at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "(") != 0)
            {
                cout << "Error: The object at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The object at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }



            while (strcmp(currentToken.value,  ")") != 0){
                //cout << currentToken.value << endl;
                faceIt = global_faces.find(currentToken.value);

                if(faceIt == global_faces.end())
                {
                    cout << "Error: Incorrect face name in object generator on line " + to_string(currentToken.lineNumber) + ". The face " + faceInside + " has never been created." << endl;
                    return 1;
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
                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The object at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }
            }

            if(meshes.find(newMesh.name) == meshes.end())
            {
                meshes[newMesh.name] = newMesh;
            }
            else
            {
                cout << "Error: The object " + newMesh.name + " at line " + to_string(currentToken.lineNumber) + " has already been created."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The object at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            if(strcmp(currentToken.value,  "endobject") != 0){
                cout << "Error: Missing endobject on line " + to_string(currentToken.lineNumber) + "." << endl;
                return 1;
            }

            currentToken = tokens.dequeue();


        }
        else if(strcmp("mesh", currentToken.value) == 0){
            Mesh newMesh(0);
            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            newMesh.name = currentToken.value;
            newMesh.setGlobalParameter(&params);

            if(isReserved(reservedWords, currentToken.value) == 1){
                cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " has already been defined."  << endl;
                return 1;
            }

            reservedWords.push_back(currentToken.value);

            if(meshes.find(newMesh.name) == meshes.end())
            {
                meshes[newMesh.name] = newMesh;
                current_mesh_name = newMesh.name;
            }
            else
            {
                cout << "Error: The mesh " + newMesh.name + " at line " + to_string(lineNumber) + " has already been created."  << endl;
                return 1;
            }

            currentToken = tokens.dequeue();
            if(currentToken.lineNumber == -1){
                cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                return 1;
            }

            while (strcmp("face", currentToken.value) == 0){
                Face * newFace = new Face;

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                faceIt = global_faces.find(currentToken.value);

                if(faceIt == global_faces.end())
                {
                    newFace -> name = currentToken.value;
                    global_faces[currentToken.value] = newFace;
                }
                else
                {
                    cout << "Error: The mesh " << currentToken.value << " at line " << to_string(currentToken.lineNumber) << " has already been created."  << endl;
                    return 1;
                }

                string vertInside = "";
                bool addingVert = false;
                vector<Vertex*> vertices;
                vertices.clear();

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                if(strcmp(currentToken.value,  "(") != 0){
                    cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }

                while (strcmp(currentToken.value,  ")") != 0){
                    vertIt = global_vertices.find(currentToken.value);

                    if(vertIt == global_vertices.end()){
                        cout << "Error: Incorrect vertex name in face generator on line " + to_string(currentToken.lineNumber) + ". The vertex " + currentToken.value + " has never been created." << endl;
                        return 1;
                    }
                    else{
                        vertices.push_back(vertIt -> second);
                    }

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                }

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

                currentToken = tokens.dequeue();
                if(currentToken.lineNumber == -1){
                    cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                    return 1;
                }


                if(strcmp(currentToken.value,  "surface") == 0)
                {
                    string color_name = "";
                    QColor color;
                    bool foundColor = false;

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }

                    color_name = currentToken.value;
                    colorIt = user_defined_colors.find(color_name);

                    if(colorIt != user_defined_colors.end())
                    {
                        foundColor = true;
                        color = colorIt -> second;
                    }
                    else
                    {
                        cout << "Error: The surface " + color_name + " at line " + to_string(currentToken.lineNumber) + " has never been created."  << endl;
                        return 1;
                    }

                    if(foundColor)
                    {
                        meshes[current_mesh_name].faceList[meshes[current_mesh_name].faceList.size() - 1]
                                -> color = color;
                        meshes[current_mesh_name].faceList[meshes[current_mesh_name].faceList.size() - 1]
                                -> user_defined_color = true;
                    }

                    currentToken = tokens.dequeue();
                    if(currentToken.lineNumber == -1){
                        cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }
                }
                if(strcmp(currentToken.value,  "endface") != 0){
                    cout << "Error: The face at line " + to_string(currentToken.lineNumber) + " is missing endface."  << endl;
                    return 1;
                }

                delete newFace;

                currentToken = tokens.dequeue();
            }

            if(strcmp(currentToken.value,  "endmesh") != 0){
                cout << "Error: The mesh at line " + to_string(currentToken.lineNumber) + " is missing endmesh."  << endl;
                return 1;
            }
            currentToken = tokens.dequeue();
        }
        else{
            cout << "Error: The method " << currentToken.value << " at line " << to_string(currentToken.lineNumber) << " is not defined."  << endl;
            return 1;
            currentToken = tokens.dequeue();
        }

    }



    /*while(std::getline(file, nextLine))
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
            }*/
            /*else if(createBank){
                if((*tIt) == "endbank")
                {
                    //banklines.push_back(nextLine);
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
                                    + QString::fromStdString("_" + nextToken);
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
                                goto newLineEnd;
                            }
                        }
                        i++;
                    }

                    //cout << *tIt << endl;
                    pIt = params.find(newParameter.name.toStdString());
                    if(pIt == params.end())
                    {
                        params[banks[banks.size() - 1].name.toStdString() + "_" + name]
                                = newParameter;
                    }
                    else
                    {

                        cout << "Error: The set at line " + to_string(lineNumber) + " with name " + newParameter.name.toStdString() + " has already been defined."  << endl;
                        return 1;
                        goto newLineEnd;
                    }
                    banks[banks.size() - 1].addParameter(
                                &params[banks[banks.size() - 1].name.toStdString() + "_" + name]);


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
            }*/
            /*else if((*tIt) == "bank")
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
            }*/
            /*else if((*tIt) == "surface")
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
                }
                if(++tIt < tokens.end())
                {
                    if((*tIt) != "color")
                    {
                        cout << "Error: The surface " + color_name + " at line " + to_string(lineNumber) + " does not have the correct format."  << endl;
                        return 1;
                    }
                }
                else
                {
                    cout << "Error: The surface " + color_name + " at line " + to_string(lineNumber) + " does not have the correct format."  << endl;
                    return 1;
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
            }*/
            /*else if((*tIt) == "funnel")
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
                }


                //newFunnel.computeNormals();
            }*/
            /*else if((*tIt) == "tunnel")
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

                //*************
                if(meshes.find(newTunnel.name) == meshes.end())
                {
                    meshes[newTunnel.name] = newTunnel;
                }
                else
                {
                    cout << "Error: The tunnel at line " + to_string(lineNumber) + " with name " + newTunnel.name + " has already been created."  << endl;
                    return 1;
                }

                //newTunnel.computeNormals();
            }*/
            /*else if((*tIt) == "object")
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
                }

                if(++tIt == tokens.end() || (*tIt) != "endobject"){
                    cout << "Error: Missing endobject on line " + to_string(lineNumber) + "." << endl;
                    return 1;
                }
            }*/
            /*else if((*tIt) == "face" && (!deletePhase) && (!constructingMesh))
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
                        vertIt = global_vertices.find(vertInside);
                        if(vertIt == global_vertices.end())
                        {
                            cout << "Error: Incorrect vertex name in face generator on line " + to_string(lineNumber) + ". The vertex " + vertInside + " has never been created." << endl;
                            return 1;
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
                        }
                    }
                    else
                    {
                        cout << "Error: The surface at line " + to_string(lineNumber) + "does not have any name."  << endl;
                        return 1;
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
            }*/
            /*else if((*tIt) == "face" && deletePhase)
            {
                postProcessingLines.push_back(lineNumber);

                goto newLineEnd;
            }*/
            /*else if((*tIt) == "face" && constructingMesh)
            {
                if(current_mesh_name == "")
                {
                    cout<<warning(27, lineNumber)<<endl;
                    goto newLineEnd;
                }
                else if(current_mesh_name == "consolidatedmesh")
                {
                    postProcessingLines.push_back(lineNumber);
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
                        }
                        else
                        {
                            vertices.push_back(vertIt -> second);
                        }
                        vertInside = "";
                    }
                }
                endAddingVertInFace1:
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
                        }
                    }
                    else
                    {
                        cout << "Error: The surface at line " + to_string(lineNumber) + " does not have a name."  << endl;
                        return 1;
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
            }*/
            /*else if((*tIt) == "polyline")
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
                    }
                    else
                    {
                        newPolyline.addVertex(vertIt -> second);
                    }
                    vertInside = "";
                }



                if((*tIt) != "endpolyline"){
                    cout << "Error: Missing endpolyline on line " + to_string(lineNumber) + "." << endl;
                    return 1;
                }

                polylines[newPolyline.name] = newPolyline;

            }*/
            /*else if((*tIt) == "point")
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
            }*/
            /*else if((*tIt) == "group")
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
                            }
                        }
                        else
                        {
                            cout << "Error: The surface " + *tIt + " at line " + to_string(lineNumber) + " is missing a name."  << endl;
                            return 1;
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

            }*/
            /*else if(*tIt == "delete")
            {
                postProcessingLines.push_back(lineNumber);
                deletePhase = true;
                goto newLineEnd;
            }
            else if(*tIt == "enddelete")
            {
                postProcessingLines.push_back(lineNumber);
                deletePhase = false;
                goto newLineEnd;
            }*/
            /*else if(*tIt == "mesh")
            {
                constructingMesh = true;
                Mesh newMesh(0);
                if((++tIt) < tokens.end()) {
                    if(!testComments(*tIt))
                    {
                        if(*tIt == "consolidatedmesh")
                        {
                            postProcessingLines.push_back(lineNumber);
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
                }
                goto newLineEnd;
            }
            else if(*tIt == "endmesh")
            {
                constructingMesh = false;
                if(current_mesh_name == "consolidatedmesh")
                {
                    postProcessingLines.push_back(lineNumber);
                }
                else
                {
                    geometrylines.push_back(nextLine);
                }
                current_mesh_name = "";
            }*/
            /*else{
                //cout<< "Error: Method " + *tIt + " at line " + to_string(lineNumber) + " is not defined." << endl;
                //return 1;
            }
        }
        newLineEnd:
        lineNumber++;
    }*/
    group.mapFromParameters();
}

void NomeParser::postProcessingWithNome(unordered_map<string, Parameter> &params,
                                        vector<int> &postProcessingLines,
                                        SlideGLWidget *canvas,
                                        Group &group,
                                        string input)
{
    //cout << global_faces << endl;
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
                        cout << "HI" << endl;
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
                        //className = *tIt;
                        cout << className << endl;
                    }
                }
                else
                {
                    cout<<warning(6, lineNumber)<<endl;
                }
                if(className != "consolidatedmesh")
                {
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
