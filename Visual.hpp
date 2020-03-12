/*
    Visual.hpp
    UML ActDiag
    MatOgr
*/

#include <ncurses.h>
#include "Doc.hpp"
#include <stdio.h>

const int NDLNGTH = 20;
const int SIGLNGTH = 3;

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
    //  positioning???
}
// what about nodes, signals?