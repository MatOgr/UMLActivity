/*
    Visual.hpp
    UML ActDiag
    MatOgr
*/

#ifndef Visual_hpp
#define Visual_hpp

#include <ncurses.h>
#include <stdio.h>
#include "Doc.hpp"

using namespace std;

const int NDLNGTH = 21;
const int SIGLNGTH = 4;

class Vision {
protected:
    WINDOW* w;
    DocState* state;

public:
    virtual void draw() = 0;
};

class Border : public Vision {
public:
    Border(DocState* stat);
    ~Border();

    void draw();
};

class InfoBar : public Vision {
private:
    Doc* doc;
    string info;
    
    void drawInfo();

public:
    InfoBar(Doc* d, DocState* s);
    ~InfoBar();

    void setInfo(string i);
    void clearInfo();
    void draw();
};


class Blocks: public Vision {
private:
    Doc* doc;

public:
    Blocks(Doc* d, DocState* s);
    ~Blocks();

    void draw();
    void margAdjustBlock(int id);
};


class SignalVision: public Vision {
private:
    Doc* doc;

    void refreshLines();
    
public:
    SignalVision(Doc* d, DocState* s);
    ~SignalVision();

    void draw();
    void margAdjustSignal(int id);
};


#endif // !Visual_hpp