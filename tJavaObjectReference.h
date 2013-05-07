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
/*!\file    rrlib/jni/tJavaObjectReference.h
 *
 * \author  Max Reichardt
 *
 * \date    2013-05-07
 *
 * \brief   Contains tJavaObjectReference
 *
 * \b tJavaObjectReference
 *
 * Maintains a global reference to the specified java object.
 * It releases reference upon destruction or reassignment.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__jni__tJavaObjectReference_h__
#define __rrlib__jni__tJavaObjectReference_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/jni/jvm.h"

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
// Class declaration
//----------------------------------------------------------------------
//! Java object reference
/*!
 * Maintains a global reference to the specified java object (in a JVM).
 * It releases reference upon destruction or reassignment.
 */
class tJavaObjectReference
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  tJavaObjectReference() :
    java_object(NULL),
    cpp_responsible(false)
  {}

  /*! \param java_object_ Java object to hold initially */
  tJavaObjectReference(jobject java_object_, bool cpp_responsible_) :
    java_object(NULL),
    cpp_responsible(false)
  {
    Set(java_object_, cpp_responsible_);
  }

  ~tJavaObjectReference()
  {
    Reset();
  }

  /*!
   * Hold global reference to specified java object. Releases global reference to any old object.
   * AND local reference to specified object
   *
   * \param java_object_ Java object to hold reference to
   */
  void Set(jobject java_object_, bool cpp_responsible_)
  {
    Reset();
    cpp_responsible = cpp_responsible_;
    if (cpp_responsible_)
    {
      java_object = GetEnv()->NewGlobalRef(java_object_);
    }
    else
    {
      java_object = GetEnv()->NewWeakGlobalRef(java_object_);
    }
    GetEnv()->DeleteLocalRef(java_object_);
  }

  /*!
   * Get current java object reference
   */
  jobject Get()
  {
    return java_object;
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  /*! Java Object currently "locked" */
  jobject java_object;

  /*! Is C++ responsible for cleaning up this object and "holding" Java object? */
  bool cpp_responsible;


  tJavaObjectReference(const tJavaObjectReference&) = delete;
  tJavaObjectReference& operator=(const tJavaObjectReference&) = delete;

  /*!  Releases global reference to any old object. */
  void Reset()
  {
    if (java_object != NULL)
    {
      if (cpp_responsible)
      {
        GetEnv()->DeleteGlobalRef(java_object);
      }
      else
      {
        GetEnv()->DeleteWeakGlobalRef(java_object);
      }
      java_object = NULL;
    }
  }
};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
