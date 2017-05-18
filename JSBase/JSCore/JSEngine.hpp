//
//  JMEngine.hpp
//  JSBase
//
//  Created by Manuel Deneu on 07/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef JMEngine_hpp
#define JMEngine_hpp

#include <string>
#include <stdio.h>
#include <GBVariant.hpp>
#include "Ducktape/duktape.h"
#include "dukglue/dukglue.h"



/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** */


class JSEngineDelegate
{
public:
    virtual ~JSEngineDelegate(){}
protected:
    JSEngineDelegate(){}
    
};


class JSEngine
{
public:
    JSEngine();
    ~JSEngine();
    
    bool parseScriptFile( const std::string &filename );

    template<typename RetType, typename... Ts>
    void registerFunction( RetType(*funcToCall)(Ts...), const char* name)
    {
        dukglue_register_function(_ctx , funcToCall , name);
    }

    template<class Cls, typename... Ts>
    void registerConstructor()
    {
        dukglue_register_constructor<Cls, Ts...>(_ctx,  Cls::className );
        Cls::init(this);
    }
    
    template<typename Cls>
    void registerDestructor()
    {
        dukglue_register_delete<Cls>(_ctx);
    }
    
    template <typename T>
    inline void registerGlobal( const T& obj, const std::string& name)
    {
        dukglue_push(_ctx, obj);
        duk_put_global_string(_ctx, name.c_str() );
    }
    
    
    template<class Cls, typename RetType, typename... Ts>
    void registerMethod( RetType(Cls::*method)(Ts...), const std::string &name)
    {
        dukglue_register_method(_ctx, method, name.c_str());
    }
    
    template<class Cls, typename RetType, typename... Ts>
    void registerMethod( RetType(Cls::*method)(Ts...) const , const std::string &name)
    {
        dukglue_register_method(_ctx, method, name.c_str());
    }

    template <typename RetT, typename ObjT, typename... ArgTs>
    typename std::enable_if<std::is_void<RetT>::value, RetT>::type callMethod( const ObjT& obj, const std::string &methodName, ArgTs... args)
    {
        dukglue_pcall_method(_ctx, obj , methodName.c_str() , /*std::forward<ArgTs>(args)...*/ args...);
    }
    
    
    static duk_context * globalContext()
    {
        return _globalCtx;
    }
    
    
    duk_context *_ctx;
private:
    
    static duk_context *_globalCtx;
    
    JSEngineDelegate* _delegate;
    static void *alloc_function (void *udata, duk_size_t size);
    static void *realloc_function (void *udata, void *ptr, duk_size_t size);
    static void free_function (void *udata, void *ptr);
    static void fatal_function (void *udata, const char *msg);
    
    static duk_ret_t native_test(duk_context *ctx);
    bool isValid() const;
    
    
    
};

#endif /* JMEngine_hpp */
