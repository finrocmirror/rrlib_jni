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
#ifndef RRLIB__FINROC_CORE_UTILS_JNI__TJNICONVERT_H
#define RRLIB__FINROC_CORE_UTILS_JNI__TJNICONVERT_H

#include "rrlib/finroc_core_utils/tJCBase.h"

#ifdef __JC_CREATE_JNI_WRAPPERS__

namespace finroc
{
namespace util
{
namespace jni
{

///////////////////////////////////////////////////////////////////////////////
// conversion methods C++ to Java
///////////////////////////////////////////////////////////////////////////////

template <typename T>
jbyte ToJbyte(T v)
{
  return static_cast<jbyte>(v);
}

template <typename T>
jshort ToJshort(T v)
{
  return static_cast<jshort>(v);
}

template <typename T>
jint ToJint(T v)
{
  return static_cast<jint>(v);
}

jlong ToJlong(int64 v)
{
  return static_cast<jlong>(v);
}
jlong ToJlong(float v)
{
  return static_cast<jlong>(v);
}
jlong ToJlong(double v)
{
  return static_cast<jlong>(v);
}
jlong ToJlong(tJNIWrappable* v)
{
  return (jlong)v;  // Pointer conversion
}
jlong ToJlong(const tJNIWrappable& v)
{
  return (jlong)&v;  // Pointer conversion
}

template <typename T>
jchar ToJchar(T v)
{
  return static_cast<jchar>(v);
}

template <typename T>
jfloat ToJfloat(T v)
{
  return static_cast<jfloat>(v);
}

template <typename T>
jdouble ToJdouble(T v)
{
  return static_cast<jdouble>(v);
}

jstring ToJstring(const char* c)
{
  jstring js = tJNIHelper::GetEnv()->NewStringUTF(c);
  return js;
}
jstring ToJstring(const finroc::util::tAbstractString& d)
{
  return ToJstring(d.GetCString());
}
jstring ToJstring(const std::string& d)
{
  return ToJstring(d.c_str());
}

jobject ToJobject(tJNIWrappable* ptr)
{
  return ptr->GetJavaWrapper();
}
jobject ToJobject(tJNIWrappable& ref)
{
  return ref.GetJavaWrapper();
}
template<typename T>
jobject ToJobject(T* ptr)
{
  return tCastCache::DynamicCast<tJNIWrappable>(ptr)->GetJavaWrapper();
}
template<typename T>
jobject ToJobject(T& ref)
{
  return tCastCache::DynamicCast<tJNIWrappable>(&ref)->GetJavaWrapper();
}


///////////////////////////////////////////////////////////////////////////////
// conversion methods Java to C++
///////////////////////////////////////////////////////////////////////////////

int ToInt(jint v)
{
  return static_cast<int>(v);
}
int ToInt(jlong v)
{
  return static_cast<int>(v);
}
int ToInt(jbyte v)
{
  return static_cast<int>(v);
}
int ToInt(jshort v)
{
  return static_cast<int>(v);
}

int16 ToInt16(jint v)
{
  return static_cast<int16>(v);
}
int16 ToInt16(jlong v)
{
  return static_cast<int16>(v);
}
int16 ToInt16(jbyte v)
{
  return static_cast<int16>(v);
}
int16 ToInt16(jshort v)
{
  return static_cast<int16>(v);
}

int8 ToInt8(jint v)
{
  return static_cast<int8>(v);
}
int8 ToInt8(jlong v)
{
  return static_cast<int8>(v);
}
int8 ToInt8(jbyte v)
{
  return static_cast<int8>(v);
}
int8 ToInt8(jshort v)
{
  return static_cast<int8>(v);
}

int64 ToInt64(jint v)
{
  return static_cast<int64>(v);
}
int64 ToInt64(jlong v)
{
  return static_cast<int64>(v);
}
int64 ToInt64(jbyte v)
{
  return static_cast<int64>(v);
}
int64 ToInt64(jshort v)
{
  return static_cast<int64>(v);
}

double ToDouble(jdouble v)
{
  return static_cast<jdouble>(v);
}
float ToFloat(jfloat v)
{
  return static_cast<jfloat>(v);
}

template <typename T>
T* StaticCast(jlong ptr)
{
  tJNIWrappable* jw = (tJNIWrappable*)ptr;
  return static_cast<T>(jw);
}

template <typename T>
T* DynamicCast(jlong ptr)
{
  tJNIWrappable* jw = (tJNIWrappable*)ptr;
  return tCastCache::DynamicCast<T>(jw);
}

} // namespace jni
} // namespace util
} // namespace finroc

#endif

#endif // RRLIB__FINROC_CORE_UTILS_JNI__TJNICONVERT_H
