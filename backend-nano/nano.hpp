#ifndef NANO_HPP_INCLUDED_
#define NANO_HPP_INCLUDED_

#include "shared.hpp"

class Nano : public Backend
{
    private:
    std::vector<int> GetBindTab();
    std::vector<BindingString> bindings;
    bool exit = false;
    void quit();
    void help();
    void draw_bottom_line();
    bool changes = false;
    
    public:
    Nano();
    void bind(std::string str, std::function<void()> func, std::string help);
    void re_bind(std::string old_bind, std::string new_bind);
    void start();

};

#endif