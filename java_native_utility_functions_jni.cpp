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
/*!\file    rrlib/jni/java_native_utility_functions_jni.cpp
 *
 * \author  Max Reichardt
 *
 * \date    2013-05-07
 *
 * Native utility functions for java code (e.g. get Pointers to native byte buffers)
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <jni.h>
#include <cstring>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/jni/tJNIWrappable.h"

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

extern "C"
{
  JNIEXPORT void JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_deleteJNIWrappable(JNIEnv* env, jclass class_, jlong pointer)
  {
    rrlib::jni::tJNIWrappable* obj = (rrlib::jni::tJNIWrappable*)pointer;
    obj->SetJavaWrapper(NULL, false); // avoids that Java "destructor" is invoked (again)
    delete obj;
  }
  JNIEXPORT jlong JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_getBufferPointer(JNIEnv* env, jclass class_, jobject buf)
  {
    return (jlong)env->GetDirectBufferAddress(buf);
  }
  JNIEXPORT jbyte JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_getByte(JNIEnv* env, jclass class_, jlong ptr)
  {
    return *((jbyte*)ptr);
  }
  JNIEXPORT jobject JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_getCByteBuffer(JNIEnv* env, jclass class_, jlong ptr, jint size)
  {
    jobject result;
    result = env->NewDirectByteBuffer((void*)ptr, size);
    return result;
  }
  JNIEXPORT jdouble JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_getDouble(JNIEnv* env, jclass class_, jlong ptr)
  {
    return *((jdouble*)ptr);
  }
  JNIEXPORT jfloat JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_getFloat(JNIEnv* env, jclass class_, jlong ptr)
  {
    return *((jfloat*)ptr);
  }
  JNIEXPORT jint JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_getInt(JNIEnv* env, jclass class_, jlong ptr)
  {
    return *((jint*)ptr);
  }
  JNIEXPORT jlong JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_getJavaVM(JNIEnv* env, jclass class_)
  {
    JavaVM* jvm = rrlib::jni::GetJavaVM();
    if (jvm != NULL)
    {
      return (jlong)jvm;
    }
    env->GetJavaVM(&jvm);
    assert(jvm != NULL && "Error initializing JavaVM pointer");
    rrlib::jni::SetJavaVM(jvm);
    return (jlong)jvm;
  }
  JNIEXPORT jlong JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_getLong(JNIEnv* env, jclass class_, jlong ptr)
  {
    return *((jlong*)ptr);
  }
  JNIEXPORT jlong JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_getPointer(JNIEnv* env, jclass class_, jlong address, jint index)
  {
    void** array = (void**)address;
    return (jlong)array[index];
  }
  JNIEXPORT jshort JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_getShort(JNIEnv* env, jclass class_, jlong ptr)
  {
    return *((jshort*)ptr);
  }
  JNIEXPORT void JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_memcpy(JNIEnv* env, jclass class_, jlong dest, jlong src, jint length)
  {
    memcpy((void*)src, (void*)dest, (int)length);
  }
  JNIEXPORT void JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_setByte(JNIEnv* env, jclass class_, jlong ptr, jbyte val)
  {
    *((jbyte*)ptr) = val;
  }
  JNIEXPORT void JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_setDouble(JNIEnv* env, jclass class_, jlong ptr, jdouble val)
  {
    *((jdouble*)ptr) = val;
  }
  JNIEXPORT void JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_setFloat(JNIEnv* env, jclass class_, jlong ptr, jfloat val)
  {
    *((jfloat*)ptr) = val;
  }
  JNIEXPORT void JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_setInt(JNIEnv* env, jclass class_, jlong ptr, jint val)
  {
    *((jint*)ptr) = val;
  }
  JNIEXPORT void JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_setJavaObject(JNIEnv* env, jclass class_, jlong pointer, jobject object, jboolean java_responsible)
  {
    rrlib::jni::tJNIWrappable* obj = (rrlib::jni::tJNIWrappable*)pointer;
    obj->SetJavaWrapper(object, !java_responsible);
  }
  JNIEXPORT void JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_setLong(JNIEnv* env, jclass class_, jlong ptr, jlong val)
  {
    *((jlong*)ptr) = val;
  }
  JNIEXPORT void JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_setPointer(JNIEnv* env, jclass class_, jlong arraypointer, jint index, jlong pointer)
  {
    void** array = (void**)arraypointer;
    array[index] = (void*)pointer;
  }
  JNIEXPORT void JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_setShort(JNIEnv* env, jclass class_, jlong ptr, jshort val)
  {
    *((jshort*)ptr) = val;
  }
  JNIEXPORT jint JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_sizeOfPointer(JNIEnv* env, jclass class_)
  {
    return sizeof(void*);
  }
  JNIEXPORT jint JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_strlen(JNIEnv* env, jclass class_, jlong ptr)
  {
    return strlen((char*)ptr);
  }
  JNIEXPORT jstring JNICALL Java_org_rrlib_finroc_1core_1utils_jc_jni_JNICalls_toString(JNIEnv* env, jclass class_, jlong pointer)
  {
    jstring result;
    result = env->NewStringUTF((char*)pointer);
    return result;
  }

} // extern C

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
