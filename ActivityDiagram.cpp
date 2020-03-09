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


//N
