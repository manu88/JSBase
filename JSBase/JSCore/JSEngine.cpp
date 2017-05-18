//
//  JMEngine.cpp
//  JSBase
//
//  Created by Manuel Deneu on 07/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//
#include <functional>
#include "JSEngine.hpp"
#include "FileSystem.hpp"


/*static*/ duk_context *JSEngine::_globalCtx = nullptr;

JSEngine::JSEngine()
{
    _delegate = nullptr;

    _ctx = duk_create_heap(alloc_function, realloc_function, free_function, this, fatal_function);
    _globalCtx = _ctx;
    
    if (!_ctx)
    {
        printf("Failed to create a Duktape heap.\n");
    }
}

JSEngine::~JSEngine()
{
    duk_destroy_heap(_ctx);
}

/*static*/ void* JSEngine::alloc_function (void *udata, duk_size_t size)
{
    JSEngine* self = static_cast<JSEngine*>(udata);
    assert(self);
    return malloc(size);
}
/*static*/ void* JSEngine::realloc_function (void *udata, void *ptr, duk_size_t size)
{
    JSEngine* self = static_cast<JSEngine*>(udata);
    assert(self);
    return realloc(ptr, size);
}
/*static*/ void  JSEngine::free_function (void *udata, void *ptr)
{
    JSEngine* self = static_cast<JSEngine*>(udata);
    assert(self);
    
    free(ptr);
}
/*static*/ void  JSEngine::fatal_function (void *udata, const char *msg)
{
    JSEngine* self = static_cast<JSEngine*>(udata);
    assert(self);
    
    printf("Fatal error : '%s' \n" , msg);
}

bool JSEngine::isValid() const
{
    return _ctx != NULL;
}

bool JSEngine::parseScriptFile( const std::string &filename )
{
    //  std::cout << "opening file " << filename << std::endl;
    
    
    if ( !FileSystem::fileExists( filename ) )
    {
        std::cout << "Cannot Open file " << filename << std::endl;
        return false;
    }
    
    const std::string buffer = FileSystem::getFileText( filename );
    

    //push_file_as_string(_ctx, "main.js");
    duk_push_lstring(_ctx, buffer.c_str(), buffer.size());

    if (duk_peval(_ctx) != 0)
    {
        printf("Error: %s\n", duk_safe_to_string( _ctx, -1));
        return false;
    }
    duk_pop(_ctx);  /* ignore result */
    
    
    return true;
}


duk_ret_t JSEngine::native_test(duk_context *ctx)
{
    printf("Test called\n");
    return 0;  /* no return value (= undefined) */
}



