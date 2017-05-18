//
//  JSTimer.cpp
//  JSBase
//
//  Created by Manuel Deneu on 13/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "JSTimer.hpp"

JSTimer::JSTimer()
{
    setCallback( std::bind(&JSTimer::onTime, this , std::placeholders::_1));
}

void JSTimer::onTime(Timer &t)
{
    dukglue_pcall_method<void>( JSEngine::globalContext() , this, "callback" );
}


bool JSTimer::isAct() const
{
    return isActive();
}

void JSTimer::setAct(bool a)
{
    setActive(a);
}

/*static*/ bool JSTimer::init( JSEngine *engine)
{
    dukglue_set_base_class< GB::Timer , JSTimer>(engine->_ctx);
    dukglue_register_property(engine->_ctx, &JSTimer::getInterval, &JSTimer::setInterval, "interval");
    dukglue_register_property(engine->_ctx, &JSTimer::isAct, &JSTimer::setAct, "active");
    
    return true;
}
