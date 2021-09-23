// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME roothbkDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "cfortran.h"
#include "roothbk.h"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_roothbkDict_Impl() {
    static const char* headers[] = {
"cfortran.h",
"roothbk.h",
0
    };
    static const char* includePaths[] = {
"/home/kobayash/cern/root-6.20.04/include/",
"/home/kobayash/nobukoba/rootminipacklib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "roothbkDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "roothbkDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "cfortran.h"
#include "roothbk.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"hbook1", payloadCode, "@",
"hbook2", payloadCode, "@",
"hcdir", payloadCode, "@",
"hf1", payloadCode, "@",
"hf2", payloadCode, "@",
"hfill", payloadCode, "@",
"hlimap", payloadCode, "@",
"hmdir", payloadCode, "@",
"hrndm", payloadCode, "@",
"hrndm1", payloadCode, "@",
"hrndm2", payloadCode, "@",
"htitle", payloadCode, "@",
"rannor", payloadCode, "@",
"rndm", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("roothbkDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_roothbkDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_roothbkDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_roothbkDict() {
  TriggerDictionaryInitialization_roothbkDict_Impl();
}
