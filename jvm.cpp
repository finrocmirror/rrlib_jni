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
/*!\file    rrlib/jni/jvm.cpp
 *
 * \author  Max Reichardt
 *
 * \date    2013-05-07
 *
 */
//----------------------------------------------------------------------
#include "rrlib/jni/jvm.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

//----------------------------------------------------------------------
// Namespace usage
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

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

namespace internal
{

/*! Pointer to JavaVM. Set at jvm initialization - needs to be done manually if libraries/jni is not used */
JavaVM* jvm;

/*! (Cached) Pointer to JNIEnv of current thread */
__thread JNIEnv* env;

JNIEnv* AttachThread()
{
  assert(jvm != NULL && "No Java VM set - cannot attach thread and get JNIEnv");
  JNIEnv* result = NULL;
  __attribute__((unused)) // prevents warning in release mode
  jint res = jvm->AttachCurrentThread((void**) & result, NULL);
  assert(res >= 0 && "Java VM Thread Attach failed");
  env = result;
  return result;
}

} // namespace internal

void SetJavaVM(JavaVM* jvm)
{
  if (jvm == internal::jvm)
  {
    return;
  }
  assert(internal::jvm && "Java VM already set to a different instance");
  internal::jvm = jvm;
}
//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
