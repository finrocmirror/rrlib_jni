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
/*!\file    rrlib/jni/type_conversion.h
 *
 * \author  Max Reichardt
 *
 * \date    2013-05-07
 *
 * Functions that convert native C++ types to JNI types and vice versa.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__jni__jni_type_conversion_h__
#define __rrlib__jni__jni_type_conversion_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <jni.h>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/jni/jvm.h"
#include "rrlib/jni/tJNIWrappable.h"

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
// Function declarations
//----------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// conversion methods C++ to Java
///////////////////////////////////////////////////////////////////////////////

template <typename T>
inline jbyte ToJbyte(T v)
{
  return static_cast<jbyte>(v);
}

template <typename T>
inline jshort ToJshort(T v)
{
  return static_cast<jshort>(v);
}

template <typename T>
inline jint ToJint(T v)
{
  return static_cast<jint>(v);
}

inline jlong ToJlong(int64_t v)
{
  return static_cast<jlong>(v);
}
inline jlong ToJlong(float v)
{
  return static_cast<jlong>(v);
}
inline jlong ToJlong(double v)
{
  return static_cast<jlong>(v);
}
inline jlong ToJlong(tJNIWrappable* v)
{
  return (jlong)v;  // Pointer conversion
}
inline jlong ToJlong(const tJNIWrappable& v)
{
  return (jlong)&v;  // Pointer conversion
}

template <typename T>
inline jchar ToJchar(T v)
{
  return static_cast<jchar>(v);
}

template <typename T>
inline jfloat ToJfloat(T v)
{
  return static_cast<jfloat>(v);
}

template <typename T>
inline jdouble ToJdouble(T v)
{
  return static_cast<jdouble>(v);
}

inline jstring ToJstring(const char* c)
{
  jstring js = GetEnv()->NewStringUTF(c);
  return js;
}
inline jstring ToJstring(const std::string& d)
{
  return ToJstring(d.c_str());
}

//inline jobject ToJobject(tJNIWrappable* ptr)
//{
//  return ptr->GetJavaWrapper();
//}
inline jobject ToJobject(tJNIWrappable& ref)
{
  return ref.GetJavaWrapper();
}
//template<typename T>
//inline jobject ToJobject(T& ref)
//{
//  return dynamic_cast<tJNIWrappable&>(ref)->GetJavaWrapper();
//}


///////////////////////////////////////////////////////////////////////////////
// conversion methods Java to C++
///////////////////////////////////////////////////////////////////////////////

inline int ToInt(jint v)
{
  return static_cast<int>(v);
}
inline int ToInt(jlong v)
{
  return static_cast<int>(v);
}
inline int ToInt(jbyte v)
{
  return static_cast<int>(v);
}
inline int ToInt(jshort v)
{
  return static_cast<int>(v);
}

inline int16_t ToInt16(jint v)
{
  return static_cast<int16_t>(v);
}
inline int16_t ToInt16(jlong v)
{
  return static_cast<int16_t>(v);
}
inline int16_t ToInt16(jbyte v)
{
  return static_cast<int16_t>(v);
}
inline int16_t ToInt16(jshort v)
{
  return static_cast<int16_t>(v);
}

inline int8_t ToInt8(jint v)
{
  return static_cast<int8_t>(v);
}
inline int8_t ToInt8(jlong v)
{
  return static_cast<int8_t>(v);
}
inline int8_t ToInt8(jbyte v)
{
  return static_cast<int8_t>(v);
}
inline int8_t ToInt8(jshort v)
{
  return static_cast<int8_t>(v);
}

inline int64_t ToInt64(jint v)
{
  return static_cast<int64_t>(v);
}
inline int64_t ToInt64(jlong v)
{
  return static_cast<int64_t>(v);
}
inline int64_t ToInt64(jbyte v)
{
  return static_cast<int64_t>(v);
}
inline int64_t ToInt64(jshort v)
{
  return static_cast<int64_t>(v);
}

inline double ToDouble(jdouble v)
{
  return static_cast<jdouble>(v);
}
inline float ToFloat(jfloat v)
{
  return static_cast<jfloat>(v);
}

inline std::string ToString(jstring js)
{
  const char* str = GetEnv()->GetStringUTFChars(js, NULL);
  assert(str != NULL && "OutOfMemoryError");
  std::string s(str);
  GetEnv()->ReleaseStringUTFChars(js, str);
  return s;
}

template <typename T>
inline T* StaticCast(jlong ptr)
{
  tJNIWrappable* jw = (tJNIWrappable*)ptr;
  return static_cast<T>(jw);
}

//template <typename T>
//inline T* DynamicCast(jlong ptr)
//{
//  tJNIWrappable* jw = (tJNIWrappable*)ptr;
//  return tCastCache::DynamicCast<T>(jw);
//}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
