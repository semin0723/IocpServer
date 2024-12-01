// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

// Author: jasonh@google.com (Jason Hsueh)
//
// This header is logically internal, but is made public because it is used
// from protocol-compiler-generated code, which may reside in other components.
// It provides reflection support for generated enums, and is included in
// generated .pb.h files and should have minimal dependencies. The methods are
// implemented in generated_message_reflection.cc.

#ifndef GOOGLE_PROTOBUF_GENERATED_ENUM_REFLECTION_H__
#define GOOGLE_PROTOBUF_GENERATED_ENUM_REFLECTION_H__

#include <string>

#include "absl/strings/string_view.h"
#include "google/protobuf/generated_enum_util.h"
#include "google/protobuf/port.h"

#ifdef SWIG
#error "You cannot SWIG proto headers"
#endif

// Must be included last.
#include "google/protobuf/port_def.inc"

namespace google {
namespace protobuf {
class EnumDescriptor;
}  // namespace protobuf
}  // namespace google

namespace google {
namespace protobuf {

// Returns the EnumDescriptor for enum type E, which must be a
// proto-declared enum type.  Code generated by the protocol compiler
// will include specializations of this template for each enum type declared.
template <typename E>
const EnumDescriptor* GetEnumDescriptor();

namespace internal {

// Helper for EnumType_Parse functions: try to parse the string 'name' as
// an enum name of the given type, returning true and filling in value on
// success, or returning false and leaving value unchanged on failure.
PROTOBUF_EXPORT bool ParseNamedEnum(const EnumDescriptor* descriptor,
                                    absl::string_view name, int* value);

template <typename EnumType>
bool ParseNamedEnum(const EnumDescriptor* descriptor, absl::string_view name,
                    EnumType* value) {
  int tmp;
  if (!ParseNamedEnum(descriptor, name, &tmp)) return false;
  *value = static_cast<EnumType>(tmp);
  return true;
}

// Just a wrapper around printing the name of a value. The main point of this
// function is not to be inlined, so that you can do this without including
// descriptor.h.
PROTOBUF_EXPORT const std::string& NameOfEnum(const EnumDescriptor* descriptor,
                                              int value);

}  // namespace internal
}  // namespace protobuf
}  // namespace google

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_GENERATED_ENUM_REFLECTION_H__