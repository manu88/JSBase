//
//  JSRunLoop.cpp
//  JSBase
//
//  Created by Manuel Deneu on 11/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "JSRunLoop.hpp"

bool JSRunLoop::addTimer( GB::Timer& timer)
{
    return addSource( timer);
}

bool JSRunLoop::addInput( GB::RunLoopSource& source)
{
    return addSource( source);
}

bool JSRunLoop::removeTimer( GB::Timer& timer)
{
    return removeSource( timer );
}

void JSRunLoop::async( DukValue callback )
{
    dispatchAsync([ callback ]() // pass
                  {
                      dukglue_pcall<void>( JSEngine::globalContext(), callback  );
                  });
}

void JSRunLoop::after( int timeout , DukValue  callback)
{
    dispatchAfter([ callback]()
                  {
                      dukglue_pcall<void>(JSEngine::globalContext(), callback  );
                  }, timeout);
}

/*static*/ bool JSRunLoop::init( JSEngine *engine)
{    
    dukglue_set_base_class< GB::RunLoop , JSRunLoop>(engine->_ctx);
    
    dukglue_register_method(engine->_ctx, &JSRunLoop::run , "run");
    dukglue_register_method(engine->_ctx, &JSRunLoop::stop , "stop");
    dukglue_register_method(engine->_ctx, &JSRunLoop::addTimer, "addTimer");
    dukglue_register_method(engine->_ctx, &JSRunLoop::addInput, "addSource");
    dukglue_register_method(engine->_ctx, &JSRunLoop::removeTimer, "removeTimer");
    dukglue_register_method(engine->_ctx, &JSRunLoop::async, "async");
    dukglue_register_method(engine->_ctx, &JSRunLoop::after, "after");
    
    return true;
}
