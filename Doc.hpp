/*
    Doc.hpp
    UML ActDiag
    MatOgr
*/

#ifndef Doc_hpp
#define Doc_hpp

#include "json.hpp"
#include <vector>
#include <string>

using nlohmann::json;
using namespace std;


//  Node structure
struct Node {
    NodeType type;
    string name;
};

enum NodeType {
    Initial, 
    Activity,
    Decision,
    Guard,
    Fork,
    Join,
    Merge,
    //Time,
    Final
};

void toJson(json& j, const Node& n);
void fromJson(const json& j, Node& n);


//  Signal structure 
struct Signal {
    SigType type;
    string name;
    int source;
    int destination;
};

enum class SigType {
    Change,
    Info
};

void toJson(json& j, const Signal& s);
void fromJson(json& j, const Signal& s);


//  Document structure
enum class Mode { 
    Node,
    Signal,
    NewSigSrc,
    NewSigDest
};

struct Doc {
    vector<Node> nodes;
    vector<Signal> signals;
};
void toJson(json& j, const Doc& d);
void fromJson(json& j, Doc& d);

struct DocState {
    string docName;
    Mode mode;
    int selectedNode;
    int selectedSig;
    int widthMarg = 0;
    int lengthMarg = 0;
    bool hasChanged = false;
};


//N
#endif // !Doc_hpp
