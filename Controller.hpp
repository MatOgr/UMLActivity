/*
    Controller.hpp
    UML ActDiag
    MatOgr
*/

#ifndef Controller_hpp
#define Controller_hpp


#include "Doc.hpp"
#include <fstream>

using namespace std;

class Controller {
private:
    Doc* d;
    DocState* s;

public:
    Controller(Doc* doc, DocState state);

    void addNode(int pos, NodeType type, string name);
    void removeNode(int pos);
    void renameNode(string name);
    void moveNode(int pos, int dest);
    void changeNode(int pos);

    void addSignal(int pos);
    void removeSignal(int pos);
    void renameSignal(string name);
    void moveSignal(int pos, int dest);
    void changeSignal(int pos);

    void newDoc();
    void openDoc(string fName);
    void saveDoc(string fName);
};



class SigCreator {
private:
    Controller* c;
    Doc* d;
    DocState* s;
    int sigPos;         //  of new signal
    int sigSrc;         //  of new signal
    

public:
    SigCreator(Controller* cont, Doc* doc, DocState* state);
    void begin(int pos);        //  creating new signal
    void end();                 //  finish creating
    void next();                //  save src, continue
    void cancel();              //  resign of creating new signal
};

//N

#endif // !Controller_hpp