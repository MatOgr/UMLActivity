/*
    Visual.cpp
    UML ActDiag
    MatOgr
*/

#include "Visual.hpp"


void visContent(WINDOW* w, char* txt, int length, int Y, int X) {
    int pad;
    pad = (length - strlen(txt)) / 2;
    mvwaddnstr(w, Y, X + pad, txt, len);
}



///////////////////////////          Border

Border::Border(DocState* s) {
    state = s;
    w = newwin(getmaxx(stdscr) - 5, getmaxy(stdscr), 1, 0); //  ???
}

Border::~Border() {
    delwin(w);
}

void Border::draw() {
    wclear(w);
    box(w, 0, 0);
    mvwhline(w, 5, 1, '=', getmaxx(w) - 1); //  ???
    string windowName = state->docName;
    if(state->hasChanged) windowName += "*";
    visContent(w, windowName.c_str(), 0, 0, getmaxx(stdscr) - 1);   //  ???          //  ???
    wrefresh(w);
}