//
//  main.cpp
//  JSBase
//
//  Created by Manuel Deneu on 03/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <iostream>
#include <GroundBase.hpp>

#include "GBJS/JSRunLoop.hpp"
#include "GBJS/JSTimer.hpp"

#include "JSEngine.hpp"


void print(const char* text)
{
    printf("%s" , text);
}

int main(int argc, const char *argv[])
{

    (void) argc; (void) argv;
    
    JSEngine eng;

    eng.registerFunction(&print , "print");
    
    eng.registerConstructor<JSTimer >();
    eng.registerDestructor<JSTimer>( );
    
    eng.registerConstructor<InSource ,int >();
    eng.registerDestructor<InSource>();
    
    eng.registerConstructor<JSRunLoop >();
    eng.registerDestructor<JSRunLoop>();
    
    JSRunLoop runLoop;
    eng.registerGlobal( &runLoop, "runLoop");
    
    eng.parseScriptFile("/Users/manueldeneu/Documents/projets/dev/JSBase/JSBase/main.js");

    return 0;
}


