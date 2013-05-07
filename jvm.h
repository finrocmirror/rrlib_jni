//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//----------------------------------------------------------------------
/*!\file    rrlib/jni/jvm.h
 *
 * \author  Max Reichardt
 *
 * \date    2013-05-07
 *
 * Functions to set/obtain the current Java virtual machnine.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__jni__jvm_h__
#define __rrlib__jni__jvm_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <jni.h>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace jni
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

namespace internal
{

/*! Pointer to JavaVM. Set at jvm initialization - needs to be done manually if libraries/jni is not used */
extern JavaVM* jvm;

/*! (Cached) Pointer to JNIEnv of current thread */
extern __thread JNIEnv* env;

JNIEnv* AttachThread();

}

//----------------------------------------------------------------------
// Function declarations
//----------------------------------------------------------------------

/*! Set JVM - once set, may not be changed to a different instance */
void SetJavaVM(JavaVM* jvm);

/*! Get JVM instance */
inline JavaVM* GetJavaVM()
{
  return internal::jvm;
}

/*! Get JNI Env for current thread */
inline JNIEnv* GetEnv()
{
  JNIEnv* result = internal::env;
  if (result != NULL)
  {
    return result;
  }
  return internal::AttachThread();
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
