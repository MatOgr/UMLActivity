/*
    main.cpp
    UML Activity Diagram
    Mateusz Ogrodowczyk
*/

#include "Controller.hpp"




Controller::Controller(Doc* doc, DocState* state) {
    d = doc;
    s = state;
}


void Controller::addNode(int pos, NodeType type, string name) {

    for(auto& s : d->signals) {
        if (s.source >= pos) ++s.source;
        if (s.destination >= pos) ++s.destination;
    }
    s->hasChanged = true;
    d->nodes.emplace(d->nodes.begin() + pos, Node {type, name});
}

void Controller::removeNode(int pos) {
    
    for(auto& i : d->signals) {
        if(i->source == pos || i->destination == pos)
            i = d->signals.erase(i);
            break;      // HMM??
        else {
            if(i->source > pos) 
                i->source--;
            if(i->destination > pos)
                i->destination--;
        }
    }

    s->hasChanged = true;
    d->nodes.erase(d->nodes.begin() + pos);
}

void Controller::renameNode(string name) {
    d->nodes[s->selectedNode].name = name;
    s->hasChanged = true;
}

bool Controller::moveNode(int start, int dest) {
    
    if(dest < 0 || dest >= d->nodes.size()) 
        return false;

    swap(d->nodes[start], d->nodes[dest]);
    for(auto& i : d->signals) {
        (i.source == start) ? i.source = dest : (i.source == dest) ? i.source = start : ;
        (i.destination == start) ? i.source = dest : (i.source == dest) ? i.source = start : ;
    }
    s->hasChanged = true;

    return true;
}

bool Controller::changeNode(int pos) {
    if(d->nodes.empty()) 
        return false;

    Node& n = d->nodes[pos];
    cout << "Actual type is: " << n.type << endl;
    cout << "Choose one of the following types:\n\n
             Initial - i,
             Activity - a,
             Decision - d,
             Guard - g,
             Fork - f,
             Join - j,
             Merge - m,
             Time - t,
             Final - e\n\n";
    char o;
    cin >> o;       //  error exception needed
    switch(o) {
    case 'i':
        n.type = NodeType::Initial;
        break;
    case 'a':
        n.type = NodeType::Activity;
        break;
    case 'd':
        n.type = NodeType::Decision;
        break;
    case 'g':
        n.type = NodeType::Guard;
        break;
    case 'f':
        n.type = NodeType::Fork;
        break;
    case 'j':
        n.type = NodeType::Join;
        break;
    case 'm':
        n.type = NodeType::Merge;
        break;
    case 't':
        n.type = NodeType::Time;
        break;
    case 'e':
        n.type = NodeType::Final;
        break;
    default:
        cout << "There's no such option\n";
        break;
    }
    s->hasChanged = true;
    return true;
}
 
//N