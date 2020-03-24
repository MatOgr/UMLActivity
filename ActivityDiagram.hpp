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
#include "Visual.hpp"
#include "obiektowe/shared.hpp"

using namespace std;

class ActivityDiagram : public Tool {

public:
    
    //  Storage
    map<string, string> entries;

    //  Document (and its state), data control, create signal
    Doc doc;
    DocState state;
    Controller* control;
    SigCreator* create;

    //  Point of view
    Blocks* nodeView;
    SignalVision* sigView;
    InfoBar* infoView;
    Border* borderView;

    //  Terminal sizing
    void trimUp();          //  DONE
    void trimDown();          //  DONE
    void trimLeft();          //  DONE
    void trimRight();          //  DONE

    //  Nodes 
    void nextFigure();          //  DONE
    void prevFigure();          //  DONE

    //  Signals
    void nextSig();          //  DONE
    void prevSig();          //  DONE

    //  Changing modes
    void figureMode();          //  DONE
    void signalMode();          //  DONE

    //  Visualizing
    void resetTerminal();          //  DONE
    void draw(bool marginAdjust = true);          //  DONE

    //  Binding objects
    void bindSig();          //  DONE
    void bindFigure();          //  DONE
    void bindDelete();          //  DONE
    void bindChangeType();          //  DONE
    void bindNewU();          //  DONE
    void bindNewD();          //  DONE

    //  file binding
    void bindNew();          //  DONE
    void bindOpen();          //  DONE
    void bindSave();          //  DONE
    void bindSaveAs();          //  DONE
    void bindRename();          //  DONE
    
    //  Nav binding
    void bindMoveD();          //  DONE
    void bindMoveU();          //  DONE
   // void bindUp();
   // void bindDown();
   // void bindLeft();
   // void bindRight();

    //  Key handler
    void keyHandler();          //  DONE 
    void keyHandler(int key);          //  DONE

    //  General
    void bindingSetup();

//public:

    ActivityDiagram();
    void init();          //  DONE
    void redraw();          //  DONE
    void setEntry(string field, string value);
    string getEntry(string field);

};



//N
#endif // !ActivityDiagram_hpp