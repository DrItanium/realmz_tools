// maya
// Copyright (c) 2012-2019, Joshua Scoggins
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
extern "C" {
#include "clips.h"
}
#include "MayaSetup.h"
#include "BoostExtensions.h"
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/math/common_factor.hpp>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include <boost/algorithm/clamp.hpp>

#if BOOST_EXTENSIONS
using Path = boost::filesystem::path;
using DirectoryIterator = boost::filesystem::directory_iterator;
using FilesystemError = boost::filesystem::filesystem_error;
using boost::filesystem::is_regular_file;
using boost::filesystem::is_directory;
using boost::starts_with;
using boost::ends_with;
void HasPrefix(Environment *theEnv, UDFContext *context, UDFValue *ret);
void HasSuffix(Environment *theEnv, UDFContext *context, UDFValue *ret);
void TrimString(Environment *theEnv, UDFContext *context, UDFValue *ret);
void TrimStringFront(Environment *theEnv, UDFContext *context, UDFValue *ret);
void TrimStringBack(Environment *theEnv, UDFContext *context, UDFValue *ret);
void NewUUID(Environment *theEnv, UDFContext *context, UDFValue *ret);
void gcdFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void lcmFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void FileExists(Environment *theEnv, UDFContext *context, UDFValue *ret);
void IsDirectory(Environment *theEnv, UDFContext *context, UDFValue *ret);
void IsRegularFile(Environment *theEnv, UDFContext *context, UDFValue *ret);
void ClampValue(Environment *theEnv, UDFContext *context, UDFValue *ret);
void GetDirectoryContents(Environment *theEnv, UDFContext *context, UDFValue *ret);
void GetFileExtension(Environment *theEnv, UDFContext *context, UDFValue *ret);
#endif

extern "C" void InstallBoostExtensions(Environment *theEnv) {
#if BOOST_EXTENSIONS
    AddUDF(theEnv, "has-prefix", "b", 2, 2, "sy;sy;sy", HasPrefix, nullptr);
    AddUDF(theEnv, "has-suffix", "b", 2, 2, "sy;sy;sy", HasSuffix, nullptr);
    AddUDF(theEnv, "string-trim", "y", 1, 1, "s", TrimString, nullptr);
    AddUDF(theEnv, "string-trim-front", "y", 1, 1, "s", TrimStringFront, nullptr);
    AddUDF(theEnv, "string-trim-back", "y", 1, 1, "s", TrimStringBack, nullptr);
    AddUDF(theEnv, "new-uuid", "s", 0, 0, "", NewUUID, nullptr);
    AddUDF(theEnv, "gcd", "l", 2, 2, "l;l;l", gcdFunction, nullptr);
    AddUDF(theEnv, "lcm", "l", 2, 2, "l;l;l", lcmFunction, nullptr);
    AddUDF(theEnv, "path-exists", "b", 1, 1, "sy", FileExists, nullptr);
    AddUDF(theEnv, "directoryp", "b", 1, 1, "sy", IsDirectory, nullptr);
    AddUDF(theEnv, "regular-filep", "b", 1, 1, "sy", IsRegularFile, nullptr);
    AddUDF(theEnv, "clamp", "l", 3, 3, "l;l;l;l", ClampValue, nullptr);
    AddUDF(theEnv, "get-directory-contents", "m", 1, 1, "sy", GetDirectoryContents, nullptr);
    AddUDF(theEnv, "get-file-extension", "sy", 1, 1, "sy", GetFileExtension, nullptr);
#endif
}

#if BOOST_EXTENSIONS
void GetFileExtension(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    if (UDFValue path; !UDFFirstArgument(context, LEXEME_BITS, &path)) {
        ret->lexemeValue = CreateString(theEnv, "");
    } else {
        if (Path p(path.lexemeValue->contents); is_regular_file(p)) {
            ret->lexemeValue = CreateString(theEnv, p.has_extension() ? p.extension().string().c_str() : "");
        } else {
            ret->lexemeValue = CreateString(theEnv, "");
        }
    }
}
void GetDirectoryContents(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    if (UDFValue path; !UDFFirstArgument(context, LEXEME_BITS, &path)) {
        ret->multifieldValue = EmptyMultifield(theEnv);
    } else {
        if (Path p(path.lexemeValue->contents); is_directory(p)) {
            auto mb = CreateMultifieldBuilder(theEnv, 10);
            try {
                DirectoryIterator it(p);
                for (const auto &path : it) {
                    MBAppendString(mb, path.path().string().c_str());
                }
                ret->multifieldValue = MBCreate(mb);
                MBDispose(mb);
            } catch (FilesystemError &) {
                // probably permission denied or something similar so just
                // emit empty
                ret->multifieldValue = EmptyMultifield(theEnv);
            }
        } else {
            ret->multifieldValue = EmptyMultifield(theEnv);
        }
    }
}
void ClampValue(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue v, lo, hi;
    if (!UDFFirstArgument(context, INTEGER_BIT, &v)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else if (!UDFNextArgument(context, INTEGER_BIT, &lo)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else if (!UDFNextArgument(context, INTEGER_BIT, &hi)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else {
        ret->integerValue = CreateInteger(theEnv,
                                          boost::algorithm::clamp(CVCoerceToInteger(&v), CVCoerceToInteger(&lo), CVCoerceToInteger(&hi)));
    }
}

void FileExists(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue path;
    if (!UDFFirstArgument(context, LEXEME_BITS, &path)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else {
        std::string p(path.lexemeValue->contents);
        ret->lexemeValue = CreateBoolean(theEnv, boost::filesystem::exists(p));
    }
}

void IsDirectory(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue path;
    if (!UDFFirstArgument(context, LEXEME_BITS, &path)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else {
        std::string p(path.lexemeValue->contents);
        ret->lexemeValue = CreateBoolean(theEnv, is_directory(p));
    }
}

void IsRegularFile(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue path;
    if (!UDFFirstArgument(context, LEXEME_BITS, &path)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else {
        std::string p(path.lexemeValue->contents);
        ret->lexemeValue = CreateBoolean(theEnv, is_regular_file(p));
    }
}

void gcdFunction(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue first, second;
    if (!UDFFirstArgument(context, INTEGER_BIT, &first)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else if (!UDFNextArgument(context, INTEGER_BIT, &second)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else {
        ret->integerValue = CreateInteger(theEnv, boost::math::gcd(CVCoerceToInteger(&first), CVCoerceToInteger(&second)));
    }
}
void lcmFunction(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue first, second;
    if (!UDFFirstArgument(context, INTEGER_BIT, &first)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else if (!UDFNextArgument(context, INTEGER_BIT, &second)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else {
        ret->integerValue = CreateInteger(theEnv, boost::math::lcm(CVCoerceToInteger(&first), CVCoerceToInteger(&second)));
    }
}
void NewUUID(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    boost::uuids::random_generator rgen;
    boost::uuids::uuid theUUID(rgen());
    const std::string tmp = boost::lexical_cast<std::string>(theUUID);
    ret->value = CreateSymbol(theEnv, tmp.c_str());
}
void HasPrefix(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue data, prefix;
    if (!UDFFirstArgument(context, LEXEME_BITS, &data)) {
        ret->lexemeValue = FalseSymbol(theEnv);
        return;
    } else if (!UDFNextArgument(context, LEXEME_BITS, &prefix)) {
        ret->lexemeValue = FalseSymbol(theEnv);
        return;
    }
    std::string dataStr(data.lexemeValue->contents);
    std::string prefixStr(prefix.lexemeValue->contents);
    ret->lexemeValue = CreateBoolean(theEnv, starts_with(dataStr, prefixStr));
}

void HasSuffix(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue data, suffix;
    if (!UDFFirstArgument(context, LEXEME_BITS, &data)) {
        ret->lexemeValue = FalseSymbol(theEnv);
        return;
    } else if (!UDFNextArgument(context, LEXEME_BITS, &suffix)) {
        ret->lexemeValue = FalseSymbol(theEnv);
        return;
    }
    std::string dataStr(data.lexemeValue->contents);
    std::string suffixStr(suffix.lexemeValue->contents);
    ret->lexemeValue = CreateBoolean(theEnv, ends_with(dataStr, suffixStr));
}
void TrimString(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue str;
    if (!UDFFirstArgument(context, STRING_BIT, &str)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else {
        std::string tmp(str.lexemeValue->contents);
        boost::algorithm::trim(tmp);
        ret->value = CreateString(theEnv, tmp.c_str());
    }
}
void TrimStringFront(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue str;
    if (!UDFFirstArgument(context, STRING_BIT, &str)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else {
        std::string tmp(str.lexemeValue->contents);
        boost::algorithm::trim_left(tmp);
        ret->value = CreateString(theEnv, tmp.c_str());
    }
}
void TrimStringBack(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue str;
    if (!UDFFirstArgument(context, STRING_BIT, &str)) {
        ret->lexemeValue = FalseSymbol(theEnv);
    } else {
        std::string tmp(str.lexemeValue->contents);
        boost::algorithm::trim_right(tmp);
        ret->value = CreateString(theEnv, tmp.c_str());
    }
}
#endif



