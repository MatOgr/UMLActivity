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


enum class FError { 
    OpenErr,
    CloseErr
};


class Controller {
private:
    Doc* d;
    DocState* s;

public:
    Controller(Doc* doc, DocState state);

    void addNode(int pos, NodeType type, string name);  // Added
    void removeNode(int pos);       // Added
    void renameNode(string name);   // Added
    bool moveNode(int start, int dest);     // Added
    void changeNode(int pos);       // Added

    void addSignal(int pos, int src, int dest, SigType type, string name);  // Added
    void removeSignal(int pos);         // Added
    void renameSignal(string name);         // Added
    bool moveSignal(int start, int dest);           // Added
    void changeSignal(int pos);         // Added

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
    int crSlctdNode = 0;
    int crSlctdSig = 0;
    

public:
    SigCreator(Controller* cont, Doc* doc, DocState* state);
    void begin(int pos);        //  creating new signal
    void end();                 //  finish creating
    void next();                //  save src, continue
    void cancel();              //  resign of creating new signal
};



//N

#endif // !Controller_hpp