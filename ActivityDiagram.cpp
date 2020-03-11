/*
    ActivityDiagram.cpp
    UML ActDiag
    Mateusz Ogrodowczyk
*/

#include "ActivityDiagram.hpp"


// Mode manip
void ActivityDiagram::nodeMode() {
    state.mode = Mode::Node;
    draw();
}

void ActivityDiagram::signalMode() {
    state.mode = Mode::Signal;
    draw();
}


//  Window sizes
void ActivityDiagram::trimDown() {
    if(state.lengthMarg < (doc.nodes.size() * )
}


//N
