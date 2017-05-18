//
//  JSTimer.hpp
//  JSBase
//
//  Created by Manuel Deneu on 13/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef JSTimer_hpp
#define JSTimer_hpp

#include <GBRunLoop.hpp>
#include "JSEngine.hpp"
#include "JSClass.hpp"

class JSTimer : public GB::Timer , public JSClass<JSTimer>
{
public:
    JSTimer();
    void onTime(Timer &t);
    

    
    bool isAct() const;
    
    void setAct(bool a);
    
    static bool init( JSEngine *engine);
    
    static constexpr const char* className = "Timer";
    
};

class InSource : GB::FDSource , public JSClass<InSource>
{
public:
    InSource(int fd) : GB::FDSource(fd)
    {
        notification = [this](GBRunLoopSourceNotification notif)
        {
            //printf("Notif %i\n" , notif);
            if( notif == GBRunLoopSourceCanRead)
            {
                char buf[128];
                
                GBSize readSize = GB::RunLoopSource::read(buf, 128);
                if( readSize)
                {
                    buf[readSize -1] = 0 ;
                    
                    const char* arg =  buf;
                    dukglue_pcall_method<void>( JSEngine::globalContext() , this, "onRead" ,arg );
                }
            }
        };
    }
    
    static bool init( JSEngine *engine)
    {
        dukglue_set_base_class< GB::RunLoopSource , InSource>(engine->_ctx);
        return true;
    }
    
    static constexpr const char* className = "InSource";
};

#endif /* JSTimer_hpp */
