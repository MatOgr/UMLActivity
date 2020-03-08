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

    

}




#endif // !Controller_hpp