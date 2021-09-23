// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME convertfuncDict
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
#include "convertfunc.h"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_convertfuncDict_Impl() {
    static const char* headers[] = {
"cfortran.h",
"convertfunc.h",
0
    };
    static const char* includePaths[] = {
"/home/kobayash/cern/root-6.20.04/include/",
"/home/kobayash/nobukoba/rootminipacklib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "convertfuncDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "convertfuncDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "cfortran.h"
#include "convertfunc.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"dir2hbk", payloadCode, "@",
"dir2root", payloadCode, "@",
"dir2shm", payloadCode, "@",
"dir2srv", payloadCode, "@",
"dshm", payloadCode, "@",
"hbk2dir", payloadCode, "@",
"hbk2root", payloadCode, "@",
"hbk2shm", payloadCode, "@",
"hbk_id_title", payloadCode, "@",
"lshm", payloadCode, "@",
"root2dir", payloadCode, "@",
"root2hbk", payloadCode, "@",
"root2shm", payloadCode, "@",
"root2srv", payloadCode, "@",
"shm2dir", payloadCode, "@",
"shm2hbk", payloadCode, "@",
"shm2root", payloadCode, "@",
"shm2srv", payloadCode, "@",
"shms2dir", payloadCode, "@",
"shms2hbk", payloadCode, "@",
"shms2root", payloadCode, "@",
"shms2srv", payloadCode, "@",
"shms2srv_sync", payloadCode, "@",
"srv2dir", payloadCode, "@",
"srv2hbk", payloadCode, "@",
"srv2root", payloadCode, "@",
"srv2shm", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("convertfuncDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_convertfuncDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_convertfuncDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_convertfuncDict() {
  TriggerDictionaryInitialization_convertfuncDict_Impl();
}
