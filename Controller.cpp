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

void Controller::addNode(unsigned int pos, NodeType type, string name) {
    for(auto& s : d->signals) {
        if (s.source >= pos) s.source++;
        if (s.destination >= pos) s.destination++;
    }
    s->hasChanged = true;
    d->nodes.emplace(d->nodes.begin() + pos, Node {name, type});
}

void Controller::removeNode(unsigned int pos) {
    auto i = d->signals.begin();
    while(i != d->signals.end()) {
        if(i->source == pos || i->destination == pos) {
            i = d->signals.erase(i);
        } else {
            if(i->source > pos) 
                i->source--;
            if(i->destination > pos)
                i->destination--;
            i++;
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

bool Controller::moveNode(unsigned int start, unsigned int dest) {
    
    if(dest < 0 || dest >= d->nodes.size()) 
        return false;

    swap(d->nodes[start], d->nodes[dest]);
    for(auto& i : d->signals) {
        i.source = (i.source == start) ? dest : (i.source == dest) ? start : i.source;
        i.destination = (i.destination == start) ? dest : (i.destination == dest) ? start : i.destination;
    }
    s->hasChanged = true;

    return true;
}

void Controller::changeNode(unsigned int pos) {
    if(d->nodes.empty()) 
        return;

    Node& n = d->nodes[pos];
    printf("Choose one of the following types:\n\n");
    printf("Initial - i,\n");
    printf("Activity - a,\n");
    printf("Decision - d,\n");
    printf("Guard - g,\n");
    printf("Fork - f,\n");
    printf("Join - j,\n");
    printf("Merge - m,\n");
    printf("Time - t,\n");
    printf("Final - e\n\n");

    char o;
    bool repeat = true;
    while(repeat) {
                       //  error exception needed
        switch(getchar()) {
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
       /*
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
            */
        case 'e':
            n.type = NodeType::Final;
            repeat = false;
            break;
        default:
            printf("There's no such option - type remains as it was before\n");
            repeat = true;
            break;
        }
    }
    s->hasChanged = false;
}



void Controller::addSignal(unsigned int pos, unsigned int src, unsigned int dest, SigType type, string name) {
    d->signals.emplace(d->signals.begin() + pos, Signal {type, name, src, dest});
    s->hasChanged = true;
}

void Controller::removeSignal(unsigned int pos) {
    d->signals.erase(d->signals.begin() + pos);
    s->hasChanged = true;
}

void Controller::renameSignal(string name) {
    if(d->signals.empty()) 
        return;
    d->signals[s->selectedSig].name = name;
    s->hasChanged = true;
}
 
bool Controller::moveSignal(unsigned int start, unsigned int dest) {
    if(dest >= d->signals.size() || dest < 0) 
        return false;
    
    swap(d->signals[start], d->signals[dest]);
    s->hasChanged = true;
    return true;
}

void Controller::changeSignal(unsigned int pos) {
    if(d->signals.empty()) 
        return;

    Signal& i = d->signals[pos];
    i.type = (i.type == SigType::Continue) ? SigType::Info : SigType::Continue;
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
    ifstream file(fName);
    if(file.fail()) {
        throw FError::OpenErr;
    }
    json j;
    file >> j;
    *d = j.get<Doc>();
    file.close();
    
    s->docName = fName;
    s->lengthMarg = 0;
    s->widthMarg = 0;
    s->selectedNode = 0;
    s->selectedSig = 0;
    s->mode = Mode::Node;
    s->hasChanged = false;
}

void Controller::saveDoc(string fName) {
    ofstream file(fName);
    if(file.fail())   
        throw FError::CloseErr;
    file << json(*d).dump(4) << endl;
    file.close();
    s->docName = fName;
    s->hasChanged = false;
}




SigCreator::SigCreator(Controller* cont, Doc* doc, DocState* state) {
    c = cont;
    d = doc;
    s = state;
}

void SigCreator::begin(unsigned int pos) {
    if(s->mode != Mode::Signal || d->nodes.empty()) 
        return;
    sigPos = pos;
    s->mode = Mode::NewSigSrc;
    currentSlctdNode = s->selectedNode;
    currentSlctdSig = s->selectedSig;
    s->selectedNode = (d->signals.size() > 0) ? min(d->signals[s->selectedSig].source, d->signals[s->selectedSig].destination) : 0;
}

void SigCreator::end() {
    c->addSignal(sigPos, sigSrc, s->selectedNode, SigType::Info, "New Signal");
    s->selectedNode = currentSlctdNode;
    s->selectedSig = currentSlctdSig;
    s->mode = Mode::Signal;
}

void SigCreator::next() {
    s->mode = Mode::NewSigDest;
    sigSrc = s->selectedNode;
}

void SigCreator::cancel() {
    if(s->mode == Mode::NewSigSrc || s->mode == Mode::NewSigDest) {
        s->mode = Mode::Signal;
        s->selectedNode = currentSlctdNode;
        s->selectedSig = currentSlctdSig;
    }
}

//N