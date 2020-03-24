/*
    Visual.cpp
    UML ActDiag
    MatOgr
*/

#include "Visual.hpp"


void visContent(WINDOW* w, const char* txt, int length, int X, int Y) {
    int pad;
    pad = (length - strlen(txt)) / 2;
    mvwaddnstr(w, Y, X + pad, txt, length);
}

void makeSpace(WINDOW* w, int X, int Y, int length) {
    for(int i = 0; i < length; i++) 
        mvwaddch(w, Y, X + i, ' ');
}



///////////////////////////          Border

Border::Border(DocState* s) {
    state = s;
    w = newwin(getmaxy(stdscr) - 3, getmaxx(stdscr), 1, 0); //  ???
}

Border::~Border() {
    delwin(w);
}

void Border::draw() {
    wclear(w);
    box(w, 0, 0);
    mvwhline(w, 6, 1, '=', getmaxx(w) - 2); //  ???
    string windowName = state->docName;
    if(state->hasChanged) windowName += "*";
    visContent(w, windowName.c_str(), getmaxx(stdscr) - 2, 0, 0);   //  ???          //  ???
    wrefresh(w);
}

///////////////////////////         InfoBar

InfoBar::InfoBar(Doc* d, DocState* s) {
    doc = d;
    state = s;
    w = newwin(1, getmaxx(stdscr), getmaxy(stdscr) - 2, 0);
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


//////////////////////////         Nodes / Blocks

Blocks::Blocks(Doc* d, DocState* s) {
    doc = d;
    state = s;
    w = newpad(6, doc->nodes.size() * NDLNGTH);
    draw();
}

Blocks::~Blocks() {
    delwin(w);
}

void Blocks::draw() {
    for(int i = 0; i < doc->nodes.size(); i++) {
        if(i == state->selectedNode && (state->mode == Mode::Node || state->mode == Mode::NewSigSrc || state->mode == Mode::NewSigDest))
            wattron(w, A_STANDOUT);
        makeSpace(w, 0, NDLNGTH * i, NDLNGTH);
        makeSpace(w, 1, NDLNGTH * i, NDLNGTH);
        makeSpace(w, 2, NDLNGTH * i, NDLNGTH);
        makeSpace(w, 3, NDLNGTH * i, NDLNGTH);
        makeSpace(w, 4, NDLNGTH * i, NDLNGTH);

        if(doc->nodes[i].type == NodeType::Initial) {
            visContent(w, "  -----", 0, NDLNGTH * i, NDLNGTH);
            visContent(w, " /     \\", 1, NDLNGTH * i, NDLNGTH);
            visContent(w, "|       |", 2, NDLNGTH * i, NDLNGTH);
            visContent(w, " \\    /", 3, NDLNGTH * i, NDLNGTH);
            visContent(w, "  -----", 4, NDLNGTH * i, NDLNGTH);
        } else if(doc->nodes[i].type == NodeType::Final) {
            visContent(w, "  -----", 0, NDLNGTH * i, NDLNGTH);
            visContent(w, " /@@@@@\\", 1, NDLNGTH * i, NDLNGTH);
            visContent(w, "|@@@@@@@|", 2, NDLNGTH * i, NDLNGTH);
            visContent(w, " \\@@@@@/", 3, NDLNGTH * i, NDLNGTH);
            visContent(w, "  -----", 4, NDLNGTH * i, NDLNGTH);
        } else if (doc->nodes[i].type == NodeType::Decision) {
            visContent(w, " /\\", 0, NDLNGTH * i, NDLNGTH);
            visContent(w, "/  \\", 1, NDLNGTH * i, NDLNGTH);
            visContent(w, "\\  /", 2, NDLNGTH * i, NDLNGTH);
            visContent(w, " \\/", 3, NDLNGTH * i, NDLNGTH);
            visContent(w, "  ", 4, NDLNGTH * i, NDLNGTH);
        }

        ////////////////////////    NEED ALSO SOME OTHER TYPES - LATERRRRRRRRRRRRRRERERERR

        visContent(w, doc->nodes[i].name.c_str(), 4, NDLNGTH * i, NDLNGTH);
        if(i == state->selectedNode && (state->mode == Mode::Node || state->mode == Mode::NewSigSrc || state->mode == Mode::NewSigDest))
            wattron(w, A_STANDOUT);    
    }
    prefresh(w, 0, state->widthMarg, 2, 1, 6, getmaxx(stdscr) - 2);

}

void Blocks::margAdjustBlock(int id) {
    if(NDLNGTH * (id + 1) - state->widthMarg > getmaxx(stdscr) - 2) 
        state->widthMarg = NDLNGTH * (id + 1) - getmaxx(stdscr) - 2;
    else if(state->widthMarg >= NDLNGTH * id)
        state->widthMarg = NDLNGTH * id;
}


/////////////////////////           Signals

void SignalVision::refreshLines() {
    for(int i = 0; i < doc->nodes.size(); i++) 
        mvwvline(w, 0, NDLNGTH * i + NDLNGTH / 2, '|', SIGLNGTH * doc->signals.size());
}

SignalVision::SignalVision(Doc* d, DocState* s) {
    doc = d;
    state = s;
    w = newpad(doc->signals.size() * SIGLNGTH, doc->nodes.size() * NDLNGTH);
    draw();
}

void SignalVision::draw() {
    wclear(w);
    refreshLines();
    int source, dest;
    Signal* s;

    for(int i = 0; i < doc->signals.size(); i++) {
        s = &doc->signals[i];
        if(state->mode == Mode::Signal && state->selectedSig == i)
            wattron(w, A_STANDOUT);
        //  to the left
        if(s->destination < s->source) {
            dest = (s->source - s->destination) * NDLNGTH - 1;
            source = (s->destination * NDLNGTH) + NDLNGTH / 2 + 1;
            makeSpace(w, SIGLNGTH * i + 1, source, dest);
            visContent(w, s->name.c_str(), SIGLNGTH * i + 1, source, dest);    
            switch (s->type)
            {
            case SigType::Continue:
                mvwhline(w, SIGLNGTH * i + 2, source, '=', dest);
                break;            
            default:
                mvwhline(w, SIGLNGTH * i + 2, source, '-', dest);
                break;
            }
            mvwaddch(w, SIGLNGTH * i + 2, source, '<');
        }
        //  to the right
        else if(s->destination > s->source) {
            dest = (s->destination - s->source) * NDLNGTH - 1;
            source = (s->source * NDLNGTH) + NDLNGTH / 2 + 1;
            makeSpace(w, SIGLNGTH * i + 1, source, dest);
            visContent(w, s->name.c_str(), SIGLNGTH * i + 1, source, dest);

            switch(s->type) {
                case SigType::Continue:
                    mvwhline(w, SIGLNGTH * i + 2, source, '=',dest);
                    break;
                default:
                    mvwhline(w, SIGLNGTH * i + 2, source, '-', dest);
                    break;
            }
            mvwaddch(w, SIGLNGTH * i + 2, source + dest - 1, '>');
        }
        // to selffffffffyfyf
        else {
            dest = NDLNGTH / 2;
            source = (s->source * NDLNGTH);
            makeSpace(w, SIGLNGTH * i, source, NDLNGTH);
            makeSpace(w, SIGLNGTH * i + 1, source, NDLNGTH);
            makeSpace(w, SIGLNGTH * i + 2, source, NDLNGTH);
            visContent(w, s->name.c_str(), SIGLNGTH * i, source, NDLNGTH);

            char ch = (s->type == SigType::Continue) ? '=' : '-';
            mvwhline(w, SIGLNGTH * i + 1, source + dest + 1, ch, dest - 2);
            mvwhline(w, SIGLNGTH * i + 2, source + dest + 1, ch, dest - 2);
            mvwaddch(w, SIGLNGTH * i + 1, source + dest, '|');
            mvwaddch(w, SIGLNGTH * i + 2, source + dest, '|');
            mvwaddch(w, SIGLNGTH * i + 2, source + dest + 1, '<');
            mvwaddch(w, SIGLNGTH * i + 1, source + dest * 2 - 1, '*');
            mvwaddch(w, SIGLNGTH * i + 2, source + dest * 2 - 1, '*');

        }
        if(state->mode == Mode::Signal && i == state->selectedSig) 
            wattroff(w, A_STANDOUT);
    }
    prefresh(w, state->lengthMarg, state->widthMarg, 8, 1, getmaxy(stdscr) - 4, getmaxx(stdscr) - 2);
}

void SignalVision::margAdjustSignal(int id) {
    if(SIGLNGTH * (id + 1) - state->lengthMarg > getmaxy(stdscr) - 10) 
        state->lengthMarg = SIGLNGTH * (id + 1) - getmaxy(stdscr) - 10;
    else if(state->lengthMarg >= SIGLNGTH * id)
        state->lengthMarg = SIGLNGTH * id;
}