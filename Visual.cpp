/*
    Visual.cpp
    UML ActDiag
    MatOgr
*/

#include "Visual.hpp"


void visContent(WINDOW* w, char* txt, int length, int X, int Y) {
    int pad;
    pad = (length - strlen(txt)) / 2;
    mvwaddnstr(w, Y, X + pad, txt, len);
}

void makeSpace(WINDOW* w, int X, int Y, int length) {
    for(int i = 0; i < length, i++) 
        mvwaddch(w, Y, X + i, ' ');
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

///////////////////////////         InfoBar

InfoBar::InfoBar(Doc* d, DocState* s) {
    doc = d;
    state = s;
    w = newwin(1, getmaxx(stdscr) - 1, 0);
    wstandout(w);
}

InfoBar::~InfoBar() {
    delwin(w);
}

void InfoBar::setInfo(string inf) {
    this->info = inf;
}

void InfoBar::clearInfo() {
    this->info = "";
}

void InfoBar::draw() {
    wclear(w);
    int wid = getmaxx(stdscr);
    makeSpace(w, 0, 0, wid);    //  something for blank spaces???
    switch (state->mode)
    {
    case Mode::Node:
        if(info != "") 
            mvwprintw(w, 0, 1, info.c_str());
        else if(!doc->nodes.empty()) 
            mvwprintw(w, 0, wid - 16, "[MODE]: Node");
        break;

    case Mode::Signal:
        if(info != "") 
            mvwprintw(w, 0, 1, info.c_str());
        else if(!doc->signals.empty()) {
            Signal& sig = doc->signals[state->selectedSig];
            string n = sig.name;
            n += " (" + doc->nodes[sig.source].name;
            n += (sig.type == SigType::Continue) ? " -> " : " -- ";
            n += doc->nodes[sig.destination].name + ")";
            mvwprintw(w, 0, 1, n.c_str());
        }
        mvwprintw(w, 0, wid - 16, "[MODE]: Signal");
        break;

    case Mode::NewSigDest: 
        mvwprintw(w, 0, 1, (info != "") ? info.c_str() : "Select DESTINATION - press [y] ([q] - cancel)");
        mvwprintw(w, 0, wid -16, "[MODE]:newSignal");
        break;

    case Mode::NewSigSrc:
        mvwprintw(w, 0, 1, (info != "") ? info.c_str() : "Select SOURCE - press [y] ([q] - cancel)");
        mvwprintw(w, 0, wid -16, "[MODE]:newSignal");
        break;

    default:
        break;
    }
    wrefresh(w);
}