/*
    main.cpp
    UML Activity Diagram
    Mateusz Ogrodowczyk
*/

#include "ActivityDiagram.hpp"
#include "backend-nano/nano.hpp"
#include "backend-nice/nice-like.hpp"

using namespace std;

int main(int argc, char* argv[]) {


    if (argc < 2) {
        cout << "Choose backend type:\n\n";
        cout << argv[0] << "\to - Nano\n";
        cout << argv[0] << "\te - Nice\n";
        //cout << argv[0] << "\tm - Mcedit\n";
        //cout << argv[0] << "\tv - Vim\n";
        return 0;
    }

    Backend* b;

    switch (argv[1][0]) {
        case 'o':
            b = new Nano();
            break;
        case 'e':
            b = new nice();
            break;
        case 'm':
            //b = new Mcedit;
            break;
        case 'v':
            //b = new Vim;
            break;
        default:
            cout << "Unavailable option\n\n";
            break;
    }

    ActivityDiagram a;

    b->tool = &a;
    a.backend = b;
    cout << "Tool has been connected with the chosen backend\n\n";
    a.init();
    b->start();


    delete b;
    return 0;
}