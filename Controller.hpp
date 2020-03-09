/*
    Controller.hpp
    UML ActDiag
    MatOgr
*/

#ifndef Controller_hpp
#define Controller_hpp


#include "Doc.hpp"
#include <fstream>

using namespace std;

class Controller {
private:
    Doc* d;
    DocState* s;

public:
    Controller(Doc* doc, DocState state);

    void addNode(int pos, NodeType type, string name);
    void removeNode(int pos);
    void renameNode(string name);
    void moveNode(int pos, int dest);
    void changeNode(int pos);

    void addSignal(int pos);
    void removeSignal(int pos);
    void renameSignal(string name);
    void moveSignal(int pos, int dest);
    void changeSignal(int pos);

    void newDoc();
    void openDoc();
    void saveDoc();
}




#endif // !Controller_hpp