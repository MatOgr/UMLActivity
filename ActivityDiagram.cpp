/*
    ActivityDiagram.cpp
    UML ActDiag
    Mateusz Ogrodowczyk
*/

#include "ActivityDiagram.hpp"


//////////////////////////////      Mode manip

void ActivityDiagram::figureMode() {
    state.mode = Mode::Node;
    draw();
}

void ActivityDiagram::signalMode() {
    state.mode = Mode::Signal;
    draw();
}


//////////////////////////////      Terminal sizing
void ActivityDiagram::trimDown() {
    if(state.lengthMarg < (doc.signals.size() * SIGLNGTH - getmaxy(stdscr) + 10))
        state.lengthMarg++;
    draw(false);
}

void ActivityDiagram::trimRight() {
    if(state.widthMarg < doc.nodes.size() * NDLNGTH - getmaxx(stdscr) + 2)
        state.widthMarg++;
    draw(false);
}

void ActivityDiagram::trimUp() {
    if(state.lengthMarg > 0)
        state.lengthMarg--;
    draw(false);
}

void ActivityDiagram::trimLeft() {
    if(state.widthMarg > 0)
        state.widthMarg--;
    draw(false);
}



//////////////////////////////      Signals changing
void ActivityDiagram::nextSig() {
    if(doc.signals.size() == 0)
        return;
    state.selectedSig = (state.selectedSig + 1) % doc.signals.size();
    draw();
}

void ActivityDiagram::prevSig() {
    if(doc.signals.size() == 0) 
        return;
    
    if(state.selectedSig == 0) 
        state.selectedSig = (unsigned int)doc.signals.size() - 1;
    else 
        state.selectedSig--;
    draw();
}



//////////////////////////////      Nodes changing
void ActivityDiagram::nextFigure() {
    if(doc.nodes.size() == 0) 
        return;
    state.selectedNode = (state.selectedNode + 1) % doc.nodes.size();
    draw();
}

void ActivityDiagram::prevFigure() {
    if(doc.nodes.size() == 0) 
        return;
    
    if(state.selectedNode == 0) 
        state.selectedNode = (unsigned int)doc.nodes.size() - 1;
    else 
        state.selectedNode--;
    draw();
}



//////////////////////////////      Visualizing
void ActivityDiagram::resetTerminal() {
    delete nodeView;
    delete sigView;
    sigView = new SignalVision(&doc, &state);
    nodeView = new Blocks(&doc, &state);
}

void ActivityDiagram::draw(bool adjusting) {
    if(adjusting) {
        switch (state.mode)
        {
        case Mode::Node:
        case Mode::NewSigSrc:
        case Mode::NewSigDest:
            nodeView->margAdjustBlock(state.selectedNode);
            break;

        case Mode::Signal:        
        default:
            sigView->margAdjustSignal(state.selectedSig);
            if(!doc.signals.empty()) {
                nodeView->margAdjustBlock(doc.signals[state.selectedSig].source);
                nodeView->margAdjustBlock(doc.signals[state.selectedSig].destination);
            }
            break;
        }
    }
    borderView->draw();
    nodeView->draw();
    sigView->draw();
    infoView->draw();
}



//////////////////////////////      Binding
void ActivityDiagram::bindChangeType() {
    infoView->clearInfo();
    switch(state.mode) {
        case Mode::Node:
            control->changeNode(state.selectedNode);
            draw();
            break;
        case Mode::Signal:
            control->changeSignal(state.selectedSig);
            draw();
            break;
        default:
            break;
    }
}

void ActivityDiagram::bindSig() {
    infoView->clearInfo();
    if(state.mode == Mode::Node) 
        signalMode();
}

void ActivityDiagram::bindFigure() {
    infoView->clearInfo();
    if(state.mode == Mode::Signal)
        figureMode();
}

void ActivityDiagram::bindNew() {
    control->newDoc();
    resetTerminal();
    infoView->setInfo("New document has been created");
    draw();
}

void ActivityDiagram::bindOpen() {
    try {
        control->openDoc(entries["FILENAME"]);
        resetTerminal();
        infoView->setInfo("File \"" + entries["FILENAME"] + "\" has been opened");
        draw();
    } catch (...) {
        resetTerminal();
        infoView->setInfo("Opening file error \"" + entries["FILENAME"] + "\"");
        draw();
    }
}

void ActivityDiagram::bindSave() {
    try {
        control->saveDoc(state.docName);
        infoView->setInfo("File \"" + state.docName + "\" has been saved");
        draw();
    } catch(...) {
        infoView->setInfo("Saving file \"" + state.docName + "\" error ");
        draw();
    }
}

void ActivityDiagram::bindSaveAs() {
    try {
        if(entries["FILENAME"] == "") {
            control->saveDoc(state.docName);
            infoView->setInfo("File \"" + state.docName + "\" has been saved");
        } else {
            control->saveDoc(entries["FILENAME"]);
            infoView->setInfo("File \"" + entries["FILENAME"] + "\" has been saved");
        }
        draw();
    } catch(...) {
        infoView->setInfo("Saving file \"" + entries["FILENAME"] + "\" error");
        draw();
    }
}

void ActivityDiagram::bindRename() {
    infoView->clearInfo();
    if(state.mode == Mode::Signal) {
        control->renameSignal(entries["RENAME"]);
        draw();
    } else if(state.mode == Mode::Node) {
        control->renameNode(entries["RENAME"]);
        draw();
        draw();
    }
}

void ActivityDiagram::bindDelete() {
    infoView->clearInfo();
    if(state.mode == Mode::Signal) {
        control->removeSignal(state.selectedSig);
        if(doc.signals.size() == state.selectedSig) 
            state.selectedSig--;
        if(doc.signals.empty()) 
            state.selectedSig = 0;
        resetTerminal();
        draw();
    } else if(state.mode == Mode::Node) {
        control->removeNode(state.selectedNode);
        if(doc.nodes.size() == state.selectedNode) 
            state.selectedNode--;
        if(doc.nodes.empty()) 
            state.selectedNode = 0;
        resetTerminal();
        draw();
    }
}

void ActivityDiagram::bindMoveD() {
    infoView->clearInfo();
    if(state.mode == Mode::Signal && control->moveSignal(state.selectedSig, state.selectedSig + 1)) {
        state.selectedSig++;
        draw();
    } else if(state.mode == Mode::Node && control->moveNode(state.selectedNode, state.selectedNode + 1)) {
        state.selectedNode++;
        draw();
    }
}

void ActivityDiagram::bindMoveU() {
    infoView->clearInfo();
    if(state.mode == Mode::Signal && control->moveSignal(state.selectedSig, state.selectedSig - 1)) {
        state.selectedSig--;
        draw();
    } else if(state.mode == Mode::Node && control->moveNode(state.selectedNode, state.selectedNode - 1)) {
        state.selectedNode--;
        draw();
    }
}

void ActivityDiagram::bindNewU() {
    infoView->clearInfo();
    switch(state.mode) {
        case Mode::Node:
            control->addNode(state.selectedNode, NodeType::Activity, "New Node");
            resetTerminal();
            draw();
            break;
        case Mode::Signal:
            create->begin(state.selectedSig);
            draw();
            break;
        default:
            break;
    }
}

void ActivityDiagram::bindNewD() {
    infoView->clearInfo();
    switch(state.mode) {
        case Mode::Node:
            if(!doc.nodes.empty()) 
                state.selectedNode++;
            control->addNode(state.selectedNode, NodeType::Activity, "New Node");
            resetTerminal();
            draw();
            break;
        case Mode::Signal:
            if(!doc.signals.empty()) 
                create->begin(state.selectedSig + 1);
            else 
                create->begin(state.selectedSig);
            draw();
            break;
        case Mode::NewSigSrc:
            create->next();
            draw();
            break;
        case Mode::NewSigDest:
            create->end();
            resetTerminal();
            draw();
            break;
        default:
            break;

    }
}

void ActivityDiagram::bindingSetup() {
    // Key handler
    backend->bind("<EDITION>", [this]() { keyHandler(); }, "---");

    // Change type  -   CTRL + T
    backend->bind("#nano#<CTRL>t%Toggle", [&]() { bindChangeType(); }, "Change Node/Signal type");
    backend->bind("#nice#.Edit.Toggle type", [&]() { bindChangeType(); }, "Change Node/Signal type");

    //  Rename  -   CTRL + R
    backend->bind("#nano#<CTRL>r%Rename!New name${RENAME}", [this]() { bindRename(); }, "Rename Node/Signal");
    backend->bind("#nice#.Edit.Rename${New name: |RENAME}", [this]() { bindRename(); }, "Rename Node/Signal");

    //  Delete  -   CTRL X
    backend->bind("#nano#<CTRL>x%Delete", [this]() { bindDelete(); }, "Delete Node/Signal");
    backend->bind("#nice#.Edit.Delete", [this]() { bindDelete(); }, "Delete Node/Signal");

    //  Signal Mode -   CTRL + L
    backend->bind("#nano#<CTRL>l%Signals", [&]() { bindSig(); }, "Signals mode");
    backend->bind("#nice#.Mode.Signals", [&]() { bindSig(); }, "Signals mode");

    //  Node Mode   -   CTRL + K
    backend->bind("#nano#<CTRL>k%Nodes", [&]() { bindFigure(); }, "Nodes mode");
    backend->bind("#nice#.Mode.Nodes", [&]() { bindFigure(); }, "Nodes mode");

    //  New up  -   CTRL + W
    backend->bind("#nano#<CTRL>w%New before", [&]() { bindNewU(); }, "Create Node/Signal before this one");
    backend->bind("#nice#.New.Before", [&]() { bindNewU(); }, "Create Node/Signal before this one");

    //  New down    -   CTRL + E
    backend->bind("#nano#<CTRL>w%New down here", [&]() { bindNewD(); }, "Create Node/Signal down here");
    backend->bind("#nice#.New.Down.Here", [&]() { bindNewD(); }, "Create Node/Signal down here");

    // Move down    -   CTRL + M
    backend->bind("#nano#<CTRL>m%Move down", [&]() { bindMoveD(); }, "Move Node/Signal forward");
    backend->bind("#nice#.Move.Down", [&]() { bindMoveD(); }, "Move Node/Signal forward");

    // Move up  -   CTRL + B
    backend->bind("#nano#<CTRL>b%Move up", [&]() { bindMoveU(); }, "Move Node/Signal backwards");
    backend->bind("#nice#.Move.Up", [&]() { bindMoveU(); }, "Move Node/Signal backwards");

    // Open file    -   CTRL + O
    backend->bind("#nano#<CTRL>o%Open!Filename${FILENAME}", [&]() { bindOpen(); }, "Open the file");
    backend->bind("#nice#.File.Open${Filename: |FILENAME}", [&]() { bindOpen(); }, "Open the file");

    // New file -   CTRL + N
    backend->bind("#nano#<CTRL>n%New", [&]() { bindNew(); }, "Create new file");
    backend->bind("#nice#.File.New", [&]() { bindNew(); }, "Create new file");

    // Save file    -   CTRL + S
    backend->bind("#nano#<CTRL>s%Save", [&]() { bindSave(); }, "Save to existing file");
    backend->bind("#nice#.File.Save", [&]() { bindSave(); }, "Save to existing file");

    // Save file as -   CTRL + Z
    backend->bind("#nano#<CTRL>z%Save as!Filename${FILENAME}", [&]() { bindSaveAs(); }, "Save to a new file");
    backend->bind("#nice#.File.Save as${Filename: |FILENAME}", [&]() { bindSaveAs(); }, "Save to a new file");
}


/////////////////////////////       Key handle
void ActivityDiagram::keyHandler() {
    string k = getEntry("KEY");
    infoView->clearInfo();

    // Arrow up
    if(k == "<UARROW>") {
        if(state.mode == Mode::Signal)
            prevSig();
        else 
            trimUp();
    }

    // Arrow down
    if(k == "<DARROW>") {
        if(state.mode == Mode::Signal)
            nextSig();
        else 
            trimDown();
    }

    // Arrow left
    if(k == "<LARROW>") {
        if(state.mode == Mode::Node || state.mode == Mode::NewSigDest || state.mode == Mode::NewSigSrc) 
            prevFigure();
        else
            trimLeft();
    }

    // Arrow left
    if(k == "<RARROW>") {
        if(state.mode == Mode::Node || state.mode == Mode::NewSigDest || state.mode == Mode::NewSigSrc) 
            nextFigure();
        else
            trimRight();
    }

    //  Signal mode
    else if(k == "s") 
        bindSig();

    //  Node mode
    else if(k == "d")
        bindFigure();

    ////////////////  Sig creator
    //  Next
    else if(k == "y") {
        switch (state.mode)
        {
        case Mode::NewSigSrc:
            create->next();
            draw();
            break;
        case Mode::NewSigDest:
            create->end();
            resetTerminal();
            draw();
            break;
        
        default:
            break;
        }
    }

    //  Cancel
    else if(k == "c") {
        if(state.mode == Mode::NewSigSrc || state.mode == Mode::NewSigDest) {
            create->cancel();
            draw();
        }
    }
}


/////////////////////////////       Public things
ActivityDiagram::ActivityDiagram() {
    doc = EXAMPLE;
    state = {Mode::Node, "example.json"};
    control = new Controller(&doc, &state);
    create = new SigCreator(control, &doc, &state);

    borderView = new Border(&state);
    nodeView = new Blocks(&doc, &state);
    sigView = new SignalVision(&doc, &state);
    infoView = new InfoBar(&doc, &state);

    draw();
}

void ActivityDiagram::init() {
    bindingSetup();
    draw();
}

void ActivityDiagram::redraw() {
    draw(false);
}

void ActivityDiagram::setEntry(string field, string value) {
    entries[field] = value;
}

string ActivityDiagram::getEntry(string field) {
    if(field == "IS_SAVED") 
        return state.hasChanged ? "NO" : "YES";
    else 
        return entries[field];
}

//N
