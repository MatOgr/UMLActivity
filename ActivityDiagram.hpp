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

    //  Sizing
    void trimUp();
    void trimDown();
    void trimLeft();
    void trimRight();

    //  Nodes and labels

    //  Signals
    void nextSig();
    void prevSig();

    //  Changing modes
    void figureMode();
    void signalMode();

    //  Visual
    void resetTerminal();
    void draw(bool marginAdjust = true);

    //  Binding 
    void bindSig();
    void bindNode();

    void bindNew();
    void bindOpen();
    void bindSave();
    void bindSaveAs();
    void bindRename();

    void bindMoveD();
    void bindMoveU();
    void bindUp();
    void bindDown();
    void bindLeft();
    void bindRight();



public:

    ActivityDiagram();
    void initAll();
    void refresh();
    void setEntry(string what, string value);
    string getEntry(string what);

};




#endif // !Controller_hpp