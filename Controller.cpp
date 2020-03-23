/*
    main.cpp
    UML Activity Diagram
    Mateusz Ogrodowczyk
*/

#include "Controller.hpp"
#include <fstream>
#include "Doc.hpp"

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
    if(d->signals.empty()) 
        return;
    d->nodes[s->selectedNode].name = name;
    s->hasChanged = true;
}

bool Controller::moveNode(int start, int dest) {
    
    if(dest < 0 || dest >= d->nodes.size()) 
        return false;

    swap(d->nodes[start], d->nodes[dest]);
    for(auto& i : d->signals) {
        i.source = (i.source == start) ? dest : (i.source == dest) ? start : ;
        i.source = (i.destination == start) ? dest : (i.source == dest) ? start : ;
    }
    s->hasChanged = true;

    return true;
}

void Controller::changeNode(int pos) {
    if(d->nodes.empty()) 
        return;

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
    bool repeat = true;
    while(repeat) {
        cin >> o;       //  error exception needed
        switch(o) {
        case 'i':
            n.type = NodeType::Initial;
            repeat = false;
            break;
        case 'a':
            n.type = NodeType::Activity;
            repeat = false;
            break;
        case 'd':
            n.type = NodeType::Decision;
            repeat = false;
            break;
        case 'g':
            n.type = NodeType::Guard;
            repeat = false;
            break;
        case 'f':
            n.type = NodeType::Fork;
            repeat = false;
            break;
        case 'j':
            n.type = NodeType::Join;
            repeat = false;
            break;
        case 'm':
            n.type = NodeType::Merge;
            repeat = false;
            break;
        case 't':
            n.type = NodeType::Time;
            repeat = false;
            break;
        case 'e':
            n.type = NodeType::Final;
            repeat = false;
            break;
        default:
            cout << "There's no such option - type remains as it was before\n";
            repeat = true;
            break;
        }
    }
    s->hasChanged = false;
}



void Controller::addSignal(int pos, int src, int dest, SigType type, string name) {
    d->signals.emplace(d->signals.begin() + pos, Signal {type, name, src, dest});
    s->hasChanged = true;
}

void Controller::removeSignal(int pos) {
    d->signals.erase(d->signals.begin() + pos);
    s->hasChanged = true;
}

void Controller::renameSignal(string name) {
    if(d->signals.empty()) 
        return;
    d->signals[s->selectedSig].name = name;
    s->hasChanged = true;
}
 
bool Controller::moveSignal(int start, int dest) {
    if(dest >= d->signals.size() || dest < 0) 
        return false;
    
    swap(d->signals[start], d->signals[dest]);
    s->hasChanged = true;
    return true;
}

void Controller::changeSignal(int pos) {
    if(d->signals.empty()) 
        return false;

    Signal& i = d->signals[pos];
    i.type = (i.type == SigType::Change) ? SigType::Info : SigType::Change;
    s->hasChanged = true;
}



void Controller::newDoc() {
    *d = Doc();
    s->docName = "newOne.json";
    s->lengthMarg = 0;
    s->widthMarg = 0;
    s->selectedNode = 0;
    s->selectedSig = 0;
    s->mode = Mode::Node;
    s->hasChanged = true;
}

void Controller::openDoc(string fName) {
    ifstream fp(fName);
    if(fp.fail())   throw cout << "Error opening\n";
    json j;
    fp >> j;
    *d = j.get<Doc>();
    fp.close();
    s->docName = fName;
    s->lengthMarg = 0;
    s->widthMarg = 0;
    s->selectedNode = 0;
    s->selectedSig = 0;
    s->mode = Mode::Node;
    s->hasChanged = false;
}

void Controller::saveDoc(string fName) {
    ofstream fp(fName);
    if(fp.fail())   throw cout << "Error saving\n\n";
    fp << json(*d).dump(4) << endl;
    fp.close();
    s->docName = fName;
    s->hasChanged = false;
}




void SigCreator::SigCreator(Controller* cont, Doc* doc, DocState* state) {
    c = cont;
    d = doc;
    s = state;
}

void SigCreator::begin(int pos) {
    if(s->mode != Mode::Signal || d->nodes.empty()) 
        return;
    sigPos = pos;
    s->mode = Mode::NewSigSrc;
    crSlctdNode = s->selectedNode;
    crSlctdSig = s->selectedSig
    s->crSlctdNode = (d->signals.size() > 0) ? min(d->signals[s->selectedSig].source, d->signals[s->selectedSignal].destination) : 0;
}

void SigCreator::end() {
    c->addSignal(sigPos, sigSrc, s->selectedNode, SigType::Info, "New Signal");
    s->selectedNode = crSlctdNode;
    s->selectedSig = crSlctdSig;
    s->mode = Mode::Signal;
}

void SigCreator::next() {
    s->mode = Mode::NewSigDest;
    siSrc = s->selectedNode;
}

void SigCreator::cancel() {
    if(s->mode == Mode::NewSigSrc || s->mode == Mode::NewSigDest) {
        s->mode = Mode::Signal;
        s->selectedNode = crSlctdNode;
        s->selectedSig = crSlctdSig;
    }
}

//N