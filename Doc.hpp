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



enum class Mode { 
    Node,
    Signal,
    NewSigSrc,
    NewSigDest
};



#endif // !Doc_hpp
