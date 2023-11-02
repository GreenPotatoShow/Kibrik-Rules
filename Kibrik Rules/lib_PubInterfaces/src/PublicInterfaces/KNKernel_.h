// Copyright (c) 2005 by RRIAI. All rights reserved.
//===================================================================
// KlaNvoc.h:      Declaration of dll exported funcions.
//===================================================================
// Nov 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef KNKernel_H
#define KNKernel_H
//===================================================================
  #ifdef  __KNKernel
    #define KNKernel_API     __declspec(dllexport)
  #else
    #define KNKernel_API     __declspec(dllimport)
  #endif

#include "IKNManager.h"
//===================================================================
/**
 * @relates IKNManager
 * Создание интерфейса IKNManager.
 */
extern "C" KNKernel_API IKNManager * GenerateAPIManager();

//===================================================================
#endif
