//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
//----------------------------------------------------------------------
/*!\file    rrlib/jni/tJNIWrappable.h
 *
 * \author  Max Reichardt
 *
 * \date    2013-05-07
 *
 * \brief   Contains tJNIWrappable
 *
 * \b tJNIWrappable
 *
 * Base class for classes that can be wrapped from a Java VM via JNI.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__jni__tJNIWrappable_h__
#define __rrlib__jni__tJNIWrappable_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/thread/tMutex.h"

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/jni/tJavaObjectReference.h"

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
//! Can be wrapped as Java object
/*!
 * Base class for classes that can be wrapped from a Java VM via JNI.
 */
class tJNIWrappable : private rrlib::util::tNoncopyable
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  tJNIWrappable();

  virtual ~tJNIWrappable();

  /*! Get Java Wrapper for this object */
  jobject GetJavaWrapper()
  {
    jobject obj = java_wrapper_object.Get();
    if (obj != NULL)
    {
      return obj;
    }
    return CreateJavaWrapper();
  }

  /*! Set Java Wrapper for this object - once set, may not be changed to a different instance */
  void SetJavaWrapper(jobject obj, bool cpp_responsible_);

//----------------------------------------------------------------------
// Protected methods (TODO: can they be private?)
//----------------------------------------------------------------------
protected:

  /*! Returns fully-qualified name of Java-(Wrapper)-Class name */
  virtual const char* GetJavaClassName() const;

  /** Creates Java Wrapper object from c++ side */
  virtual jobject CreateJavaWrapper();

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  /*! Java Object that wraps this object. Null, if there isn't any wrapper (yet) */
  tJavaObjectReference java_wrapper_object;

  /*! Mutex for creating Java objects - non-static would be faster at creation, but would consume more memory */
  static rrlib::thread::tMutex create_mutex;

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
