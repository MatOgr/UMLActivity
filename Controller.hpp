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
    Controller(Doc* doc, DocState* state);

    void addNode(unsigned int pos, NodeType type, string name);  // Added
    void removeNode(unsigned int pos);       // Added
    void renameNode(string name);   // Added
    bool moveNode(unsigned int start, unsigned int dest);     // Added
    void changeNode(unsigned int pos);       // Added

    void addSignal(unsigned int pos, unsigned int src, unsigned int dest, SigType type, string name);  // Added
    void removeSignal(unsigned int pos);         // Added
    void renameSignal(string name);         // Added
    bool moveSignal(unsigned int start, unsigned int dest);           // Added
    void changeSignal(unsigned int pos);         // Added

    void newDoc();
    void openDoc(string fName);
    void saveDoc(string fName);
};



class SigCreator {
private:
    Controller* c;
    Doc* d;
    DocState* s;
    unsigned int sigPos;         //  of new signal
    unsigned int sigSrc;         //  of new signal
    unsigned int currentSlctdNode = 0;
    unsigned int currentSlctdSig = 0;
    

public:
    SigCreator(Controller* cont, Doc* doc, DocState* state);
    void begin(unsigned int pos);        //  creating new signal
    void end();                 //  finish creating
    void next();                //  save src, continue
    void cancel();              //  resign of creating new signal

};



//N

#endif // !Controller_hpp