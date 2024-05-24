#pragma once
#include "KNKernel.h"

#include <string>

class WordShell
{
public:
    WordShell(IKNWordShell* iknWordShell);


    void makeActor();
    void makeSubjectNoActor();
    std::string getIsActor();

    IKNWordShell* getWordShell();

    bool isSubject();
    bool isAnimate();
private:
    std::string isActor;
    IKNWordShell* wordShell;
};

