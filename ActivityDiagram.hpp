/*
    ActivityDiagram.hpp
    UML Activity Diagram
    Mateusz Ogrodowczyk
*/

#ifndef Controller_hpp
#define Controller_hpp

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <map>
#include "Controller.hpp"
#include "Document.hpp"

using namespace std;

class ActivityDiagram : public Tool {

private:
    
    //  Storage
    map<string, string> entries;

    //  Document (and its state), data control, create signal
    Document doc;
    DocumentState state;
    DataControl* control;
    SignalCreate* create;

    //  Terminal sizing
    void trimUp();
    void trimDown();
    void trimLeft();
    void trimRight();

    //  Nodes 
    void nextNode();
    void prevNode();

    //  Signals
    void nextSig();
    void prevSig();

    //  Changing modes
    void figureMode();
    void signalMode();

    //  Visualizing
    void resetTerminal();
    void draw(bool marginAdjust = true);

    //  Binding objects
    void bindSig();
    void bindNode();

    //  file binding
    void bindNew();
    void bindOpen();
    void bindSave();
    void bindSaveAs();
    void bindRename();

    //  Nav binding
    void bindMoveD();
    void bindMoveU();
    void bindUp();
    void bindDown();
    void bindLeft();
    void bindRight();

    //  Key handler
    void keyHandler();
    void keyHandler(int key);

    //  General
    void bindingSetup();

public:

    ActivityDiagram();
    void initAll();
    void refresh();
    void setEntry(string what, string value);
    string getEntry(string what);

};




#endif // !Controller_hpp