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
#include "rrlib/finroc_core_utils/definitions.h"

namespace finroc
{
namespace util
{

#ifdef __JC_CREATE_JNI_WRAPPERS__

JavaVM* tJNIHelper::jvm = NULL;

__thread JNIEnv* tJNIHelper::env = NULL;

rrlib::thread::tMutex tJNIWrappable::create_mutex;

JNIEnv* tJNIHelper::AttachThread()
{
  assert(jvm != NULL && "No Java VM set - cannot attach thread and get JNIEnv");
  JNIEnv* result = NULL;
  __attribute__((unused)) // prevents warning in release mode
  jint res = jvm->AttachCurrentThread((void**) & result, NULL);
  assert(res >= 0 && "Java VM Thread Attach failed");
  env = result;
  return result;
}

jobject tJNIWrappable::CreateJavaWrapper()
{
  rrlib::thread::tLock l(create_mutex); // avoid that two threads create wrapper object at the same time
  jobject obj = java_wrapper_object.Get();
  if (obj != NULL)   // "double-checked locking" - should be safe though
  {
    return obj;
  }
  JNIEnv* env = tJNIHelper::GetEnv();
  __attribute__((unused)) // prevents warning in release mode
  const char* class_name = GetJavaClassName();
  assert(class_name != NULL && "Cannot create java class without class name - your class needs to override getJavaClassName()");
  jclass clazz = env->FindClass(GetJavaClassName());
  assert(clazz != NULL && "Class not found");

  /* Get the method ID for the clazz(long) constructor */
  jmethodID cid = env->GetMethodID(clazz, "<init>", "(L)V");
  assert(cid != NULL && "No Constructor taking long argument (pointer) found for Java class");

  obj = env->NewObject(clazz, cid, (jlong)this);
  assert(obj != NULL && "Java object creation failed for whatever reason");
  java_wrapper_object.Set(obj, true);
  env->DeleteLocalRef(clazz);
  return obj;
}

void tJNIWrappable::SetJavaWrapper(jobject obj, bool cpp_responsible_)
{
  rrlib::thread::tLock l(create_mutex); // avoid that two threads create wrapper object at the same time
  if (java_wrapper_object.Get() == obj)
  {
    return;
  }
  assert((java_wrapper_object.Get() == NULL || obj == NULL) && "Java Object already set to a different instance");
  java_wrapper_object.Set(obj, cpp_responsible_);
}

const char* tJNIWrappable::GetJavaClassName() const
{
  return NULL;
}

#endif

} // namespace finroc
} // namespace util

