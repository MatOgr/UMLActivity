/*
    Doc.cpp
    UML ActDiag
    MatOgr
*/

#include "Doc.hpp"


////////////////////////////        NODES

void to_json(json& j, const Node& n) {
    j = json { {"name", n.name}, {"type", n.type}};
} 

void from_json(const json& j, Node& n) {
    j.at("name").get_to(n.name);
    j.at("type").get_to(n.type);
}


////////////////////////////        SIGNALS         

void to_json(json& j, const Signal& s) {
    j = json {
        {"name", s.name},
        {"type", s.type},
        {"source", s.source},
        {"destination", s.destination}
    };
} 

void from_json(const json& j, Signal& s) {
    j.at("name").get_to(s.name);
    j.at("type").get_to(s.type);
    j.at("source").get_to(s.source);
    j.at("destination").get_to(s.destination);
}


////////////////////////////        DOCUMENTS

void to_json(json& j, const Doc& d) {
    j = json {
        {"nodes", d.nodes},
        {"signals", d.signals}
    };
}

void from_json(const json& j, Doc& d) {
    j.at("nodes").get_to(d.nodes);
    j.at("signals").get_to(d.signals);
}