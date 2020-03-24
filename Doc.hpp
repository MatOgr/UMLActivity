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

using namespace std;
using nlohmann::json;

//  Node structure
enum class NodeType {
    Initial, 
    Activity,
    Decision,
    Guard,
    Fork,
    Join,
    Merge,
    Time,
    Final
};

struct Node {
    string name;
    NodeType type;
};

void to_json(json& j, const Node& n);
void from_json(const json& j, Node& n);
bool operator <(const Node& x, const Node& y);

//  Signal structure 
enum class SigType {
    Continue,
    Info
};

struct Signal {
    SigType type;
    string name;
    unsigned int source;
    unsigned int destination;
};

void to_json(json& j, const Signal& s);
void from_json(json& j, const Signal& s);
bool operator <(const Signal& x, const Signal& y);


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
void to_json(json& j, const Doc& d);
void from_json(json& j, Doc& d);

struct DocState {
    string docName;
    Mode mode;
    unsigned int selectedNode = 0;
    unsigned int selectedSig = 0;
    int widthMarg = 0;
    int lengthMarg = 0;
    bool hasChanged = false;
};


const Doc EXAMPLE {
    {
        {NodeType::Initial, "Start"},                       // 0
        {NodeType::Decision, "Which one?"},                 // 1
        {NodeType::Activity, "Add 5 to the number"},        // 2
        {NodeType::Activity, "Multiply it by 5"},           // 3
        {NodeType::Activity, "Add 7 to the number"},        // 4
        {NodeType::Activity, "Multiply it by 7"},           // 5
        {NodeType::Activity, "Display the number"},         // 6
        {NodeType::Final, "Dead"}                           // 7
    },
    {
        {SigType::Info, "Is the number odd?", 0, 1},
        {SigType::Info, "YES", 1, 2},
        {SigType::Continue, "", 2, 3},
        {SigType::Continue, "", 3, 6},
        {SigType::Info, "NO", 1, 4},
        {SigType::Continue, "", 4, 5},
        {SigType::Continue, "", 5, 6},
        {SigType::Continue, "", 6, 7},
    }
};



//N
#endif // !Doc_hpp
