/**
 * You received this file as part of an advanced experimental
 * robotics framework prototype ('finroc')
 *
 * Copyright (C) 2007-2010 Max Reichardt,
 *   Robotics Research Lab, University of Kaiserslautern
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#ifndef rrlib__finroc_core_utils__tJNIHelper_h__
#define rrlib__finroc_core_utils__tJNIHelper_h__

#include "rrlib/finroc_core_utils/definitions.h"

//#ifdef _LIB_RRLIB_FINROC_CORE_UTILS_JNI_BASE_PRESENT_
//#define __JC_CREATE_JNI_WRAPPERS__
//#endif
//
//#ifdef __JC_CREATE_JNI_WRAPPERS__
#include <jni.h>
#include "rrlib/finroc_core_utils/tCastCache.h"
//#endif

namespace finroc
{
namespace util
{

//#ifdef __JC_CREATE_JNI_WRAPPERS__
class tJNIHelper
{

  /*! Pointer to JavaVM. Set at jvm initialization - needs to be done manually if libraries/jni is not used */
  static JavaVM* jvm;

  /*! (Cached) Pointer to JNIEnv of current thread */
  static __thread JNIEnv* env;

  static JNIEnv* AttachThread();

public:

  /*! Set JVM - once set, may not be changed to a different instance */
  static void SetJavaVM(JavaVM* jvm_)
  {
    if (jvm_ == jvm)
    {
      return;
    }
    assert(jvm == NULL && "Java VM already set to a different instance");
    jvm = jvm_;
  }

  /*! Get JVM instance */
  static JavaVM* GetJavaVM()
  {
    return jvm;
  }

  /*! Get JNI Env for current thread */
  static JNIEnv* GetEnv()
  {
    JNIEnv* result = env;
    if (result != NULL)
    {
      return result;
    }
    return AttachThread();
  }
};

/*!
 * Maintains a global reference to the specified java object.
 * It releases reference upon destruction or reassignment.
 *
 * T can be jobject or volatile jobject (the latter may be required to ensure thread-safety)
 */
template <typename T>
class tJNIObjectRefHolderT : boost::noncopyable
{

  /*! Java Object currently "locked" */
  T java_object;

  /*! Is C++ responsible for cleaning up this object and "holding" Java object? */
  bool cpp_responsible;

public:

  tJNIObjectRefHolderT() :
    java_object(NULL),
    cpp_responsible(false)
  {}

  /*! \param java_object_ Java object to hold initially */
  tJNIObjectRefHolderT(jobject java_object_, bool cpp_responsible_) :
    java_object(NULL),
    cpp_responsible(false)
  {
    Set(java_object_, cpp_responsible_);
  }

  ~tJNIObjectRefHolderT()
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
      java_object = tJNIHelper::GetEnv()->NewGlobalRef(java_object_);
    }
    else
    {
      java_object = tJNIHelper::GetEnv()->NewWeakGlobalRef(java_object_);
    }
    tJNIHelper::GetEnv()->DeleteLocalRef(java_object_);
  }

  /*!
   * Get current java object reference
   */
  jobject Get()
  {
    return java_object;
  }

private:

  /*!  Releases global reference to any old object. */
  void Reset()
  {
    if (java_object != NULL)
    {
      if (cpp_responsible)
      {
        tJNIHelper::GetEnv()->DeleteGlobalRef(java_object);
      }
      else
      {
        tJNIHelper::GetEnv()->DeleteWeakGlobalRef(java_object);
      }
      java_object = NULL;
    }
  }
};

typedef tJNIObjectRefHolderT<jobject> tJNIObjectRefHolder;
typedef tJNIObjectRefHolderT<volatile jobject> tVolatileJNIObjectRefHolder;

class tJNIWrappableBase {};

//#else
//typedef tSafeDestructible tJNIWrappableBase;
//#endif

/*!
 * Base class for classes that can be wrapped from a Java VM via JNI.
 */
class tJNIWrappable : tJNIWrappableBase
{

//#ifdef __JC_CREATE_JNI_WRAPPERS__

private:
  /*! Java Object that wraps this object. Null, if there isn't any wrapper (yet) */
  tVolatileJNIObjectRefHolder java_wrapper_object;

  /*! Mutex for creating Java objects - non-static would be faster at creation, but would consume more memory */
  static rrlib::thread::tMutex create_mutex;

public:
  tJNIWrappable() :
    java_wrapper_object()
  {}

  virtual ~tJNIWrappable() {}

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

protected:

  /*! Returns fully-qualified name of Java-(Wrapper)-Class name */
  virtual const char* GetJavaClassName() const;

  /** Creates Java Wrapper object from c++ side */
  virtual jobject CreateJavaWrapper();

//#endif
};

} // namespace finroc
} // namespace util


#endif // rrlib__finroc_core_utils__tJNIHelper_h__
