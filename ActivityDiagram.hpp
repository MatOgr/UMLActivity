/*
    ActivityDiagram.hpp
    UML Activity Diagram
    Mateusz Ogrodowczyk
*/

#ifndef ActivityDiagram_hpp
#define ActivityDiagram_hpp

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <map>
#include "Controller.hpp"
#include "Doc.hpp"

using namespace std;

class ActivityDiagram : public Tool {

private:
    
    //  Storage
    map<string, string> entries;

    //  Document (and its state), data control, create signal
    Doc doc;
    DocState state;
    Controller* control;
    SigCreator* create;

    //  Terminal sizing
    void trimUp();
    void trimDown();
    void trimLeft();
    void trimRight();

    //  Nodes 
    void nextFigure();
    void prevFigure();

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
    void bindFigure();

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



//N
#endif // !ActivityDiagram_hpp