//------------------------------------------------
//--- 010 Editor v10.0.2 Binary Template
//
//      File: common.h
//   Authors: SutandoTsukai181
//   Version: 1.0
//   Purpose: Common include for Kurohyo templates
//  Category: 
// File Mask: 
//  ID Bytes: 
//   History: 
//------------------------------------------------

#ifndef KUROHYO_COMMON
#define KUROHYO_COMMON

#include "../Common/includes/include.h"

typedef struct
{
    char Magic[4];
    Assert(Magic == "end ", "Unexpected magic.");
} TEnd;

typedef struct
{
    u16 Length;
    char Data[Length];
} TKString <read=ReadTKString>;

string ReadTKString(TKString& value)
{
    return (value.Length == 0) ? "" : value.Data;
}

#endif
