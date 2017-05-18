//
//  JSClass.hpp
//  JSBase
//
//  Created by Manuel Deneu on 03/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef JSClass_hpp
#define JSClass_hpp


#include <string>
class JSEngine;

template <class T>
class JSClass
{
    friend class JSEngine;
public:
    virtual ~JSClass()
    {}
    
    const std::string &getClassName() const noexcept
    {
        return T::className;
    }
    
    static bool init( JSEngine *eng)
    {
        T::initClass(  eng);
    }
    
    void setEngine(JSEngine* eng)
    {
        engine = eng;
    }
    JSEngine* engine;
    
    
protected:
    
    JSClass() : engine(nullptr)
    {}
    
};

#endif /* JSClass_hpp */
