//
//  JSRunLoop.hpp
//  JSBase
//
//  Created by Manuel Deneu on 11/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef JSRunLoop_hpp
#define JSRunLoop_hpp

#include <stdio.h>
#include <GBRunLoop.hpp>
#include "JSEngine.hpp"
#include "JSClass.hpp"


class JSRunLoop : public GB::RunLoop , public JSClass<JSRunLoop>
{
public:
    
    
    static bool init( JSEngine *engine);
    
    static constexpr const char* className = "RunLoop";
    
protected:
    
    bool addTimer( GB::Timer& timer);
    
    bool addInput( GB::RunLoopSource& source);
    
    bool removeTimer( GB::Timer& timer);
    
    
    void async( DukValue callback );
    
    void after( int timeout , DukValue  callback);
    
    
};


#endif /* JSRunLoop_hpp */
