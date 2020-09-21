/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  07/05/18            */
/*                                                     */
/*               I/O FUNCTIONS HEADER FILE             */
/*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.24: Added the get-char, set-locale, and            */
/*            read-number functions.                         */
/*                                                           */
/*            Modified printing of floats in the format      */
/*            function to use the locale from the set-locale */
/*            function.                                      */
/*                                                           */
/*            Moved IllegalLogicalNameMessage function to    */
/*            argacces.c.                                    */
/*                                                           */
/*      6.30: Changed integer type/precision.                */
/*                                                           */
/*            Support for long long integers.                */
/*                                                           */
/*            Removed the undocumented use of t in the       */
/*            printout command to perform the same function  */
/*            as crlf.                                       */
/*                                                           */
/*            Replaced EXT_IO and BASIC_IO compiler flags    */
/*            with IO_FUNCTIONS compiler flag.               */
/*                                                           */
/*            Added a+, w+, rb, ab, r+b, w+b, and a+b modes  */
/*            for the open function.                         */
/*                                                           */
/*            Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW and       */
/*            MAC_MCW).                                      */
/*                                                           */
/*            Used gensprintf instead of sprintf.            */
/*                                                           */
/*            Added put-char function.                       */
/*                                                           */
/*            Added SetFullCRLF which allows option to       */
/*            specify crlf as \n or \r\n.                    */
/*                                                           */
/*            Added AwaitingInput flag.                      */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*      6.40: Removed LOCALE definition.                     */
/*                                                           */
/*            Pragma once and other inclusion changes.       */
/*                                                           */
/*            Added support for booleans with <stdbool.h>.   */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*            UDF redesign.                                  */
/*                                                           */
/*            Added print and println functions.             */
/*                                                           */
/*            Added unget-char function.                     */
/*                                                           */
/*            Added flush, rewind, tell, seek, and chdir     */
/*            functions.                                     */
/*                                                           */
/*************************************************************/

#ifndef _H_iofun

#pragma once

#define _H_iofun

void IOFunctionDefinitions(Environment *);
#if IO_FUNCTIONS
bool SetFullCRLF(Environment *, bool);
void PrintoutFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void PrintFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void PrintlnFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void ReadFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void OpenFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void CloseFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void FlushFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void RewindFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void TellFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SeekFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void GetCharFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void UngetCharFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void PutCharFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void ReadlineFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void FormatFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void RemoveFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void ChdirFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void RenameFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SetLocaleFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void ReadNumberFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
#endif

#endif /* _H_iofun */






