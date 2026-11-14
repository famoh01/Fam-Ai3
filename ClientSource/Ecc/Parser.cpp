/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "Parser.y"

// rcg10042001 Changed to specify Ecc directory...
#include "Ecc/StdH.h"
#include "Ecc/Main.h"
#define YYINITDEPTH 10000
#define YYMAXDEPTH 500000

static char *_strCurrentClass;
static int _iCurrentClassID;
static char *_strCurrentBase;
static char *_strCurrentDescription;
static char *_strCurrentThumbnail;
static char *_strCurrentEnum;
static int _bClassIsExported = 0;

static char *_strCurrentPropertyID;         
static char *_strCurrentPropertyIdentifier; 
static char *_strCurrentPropertyPropertyType;
static char *_strCurrentPropertyEnumType;   
static char *_strCurrentPropertyDataType;
static char *_strCurrentPropertyName;       
static char *_strCurrentPropertyShortcut;
static char *_strCurrentPropertyColor;
static char *_strCurrentPropertyFlags;
static char *_strCurrentPropertyDefaultCode;

static char *_strCurrentEventList;
static char *_strCurrentEventCheck;

static char *_strCurrentComponentIdentifier;
static char *_strCurrentComponentType;
static char *_strCurrentComponentID;     
static char *_strCurrentComponentFileName;
static unsigned long _ulCurrentComponentFlags = 0;

static int _ctInProcedureHandler = 0;
static char _strLastProcedureName[256];

static char _strInWaitName[256];
static char _strAfterWaitName[256];
static char _strInWaitID[256];
static char _strAfterWaitID[256];

static char _strInLoopName[256];
static char _strAfterLoopName[256];
static char _strInLoopID[256];
static char _strAfterLoopID[256];
static char _strCurrentStateID[256];

static int _bInProcedure;   // set if currently compiling a procedure
static int _bInHandler;
static int _bHasOtherwise;  // set if current 'wait' block has an 'otherwise' statement

static char *_strCurrentEvent;
static int _bFeature_AbstractBaseClass;
static int _bFeature_ImplementsOnInitClass;
static int _bFeature_ImplementsOnEndClass;
static int _bFeature_ImplementsOnPrecache;
static int _bFeature_ImplementsOnWorldInit;
static int _bFeature_ImplementsOnWorldEnd;
static int _bFeature_ImplementsOnWorldTick;
static int _bFeature_ImplementsOnWorldRender;
static int _bFeature_CanBePredictable;

static int _iNextFreeID;
inline int CreateID(void) {
  return _iNextFreeID++;
}

static int _ctBraces = 0;
void OpenBrace(void) {
  _ctBraces++;
}
void CloseBrace(void) {
  _ctBraces--;
}
SType Braces(int iBraces) {
  static char strBraces[50];
  memset(strBraces, '}', sizeof(strBraces));
  strBraces[iBraces] = 0;
  return SType(strBraces);
}
char *RemoveLineDirective(char *str) 
{
  if (str[0]=='\n' && str[1]=='#') {
    return strchr(str+2, '\n')+1;
  } else {
    return str;
  }
}
char *GetLineDirective(SType &st) 
{
  char *str = st.strString;
  if (str[0]=='\n' && str[1]=='#' && str[2]=='l') {
    char *strResult = strdup(str);
    strchr(strResult+3,'\n')[1] = 0;
    return strResult;
  } else {
    return "";
  }
}
void AddHandlerFunction(char *strProcedureName, int iStateID)
{
  fprintf(_fDeclaration, "\tBOOL %s(const CEntityEvent &__eeInput);\n", strProcedureName);
  fprintf(_fTables, " {0x%08x, -1, CEntity::pEventHandler(&%s::%s), "
    "DEBUGSTRING(\"%s::%s\")},\n",
    iStateID, _strCurrentClass, strProcedureName, _strCurrentClass, strProcedureName);
}


void AddHandlerFunction(char *strProcedureName, char *strStateID, char *strBaseStateID)
{
  fprintf(_fDeclaration, "\tBOOL %s(const CEntityEvent &__eeInput);\n", strProcedureName);
  fprintf(_fTables, " {%s, %s, CEntity::pEventHandler(&%s::%s),"
    "DEBUGSTRING(\"%s::%s\")},\n",
    strStateID, strBaseStateID, _strCurrentClass, strProcedureName,
    _strCurrentClass, RemoveLineDirective(strProcedureName));
  strcpy(_strLastProcedureName, RemoveLineDirective(strProcedureName));
  _ctInProcedureHandler = 0;
}

void CreateInternalHandlerFunction(char *strFunctionName, char *strID)
{
  int iID = CreateID();
  _ctInProcedureHandler++;
  sprintf(strID, "0x%08x", iID);
  sprintf(strFunctionName, "H0x%08x_%s_%02d", iID, _strLastProcedureName, _ctInProcedureHandler);
  AddHandlerFunction(strFunctionName, iID);
}

void DeclareFeatureProperties(void)
{
  if (_bFeature_CanBePredictable) {
    fprintf(_fTables, " CEntityProperty(CEntityProperty::EPT_ENTITYPTR, NULL, (0x%08x<<8)+%s, offsetof(%s, %s), %s, %s, %s, %s),\n",
      _iCurrentClassID,
      "255",
      _strCurrentClass,
      "m_penPrediction",
      "\"\"",
      "0",
      "0",
      "0");
    fprintf(_fDeclaration, "\t%s %s;\n",
      "CEntityPointer",
      "m_penPrediction"
      );
    fprintf(_fImplementation, "\tm_penPrediction = NULL;\n");
  }
}

#define YYERROR_VERBOSE 1


#line 225 "Parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "Parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_c_char = 3,                     /* c_char  */
  YYSYMBOL_c_int = 4,                      /* c_int  */
  YYSYMBOL_c_float = 5,                    /* c_float  */
  YYSYMBOL_c_bool = 6,                     /* c_bool  */
  YYSYMBOL_c_string = 7,                   /* c_string  */
  YYSYMBOL_identifier = 8,                 /* identifier  */
  YYSYMBOL_cppblock = 9,                   /* cppblock  */
  YYSYMBOL_k_while = 10,                   /* k_while  */
  YYSYMBOL_k_for = 11,                     /* k_for  */
  YYSYMBOL_k_if = 12,                      /* k_if  */
  YYSYMBOL_k_else = 13,                    /* k_else  */
  YYSYMBOL_k_enum = 14,                    /* k_enum  */
  YYSYMBOL_k_switch = 15,                  /* k_switch  */
  YYSYMBOL_k_case = 16,                    /* k_case  */
  YYSYMBOL_k_class = 17,                   /* k_class  */
  YYSYMBOL_k_do = 18,                      /* k_do  */
  YYSYMBOL_k_void = 19,                    /* k_void  */
  YYSYMBOL_k_const = 20,                   /* k_const  */
  YYSYMBOL_k_inline = 21,                  /* k_inline  */
  YYSYMBOL_k_static = 22,                  /* k_static  */
  YYSYMBOL_k_virtual = 23,                 /* k_virtual  */
  YYSYMBOL_k_return = 24,                  /* k_return  */
  YYSYMBOL_k_autowait = 25,                /* k_autowait  */
  YYSYMBOL_k_autocall = 26,                /* k_autocall  */
  YYSYMBOL_k_waitevent = 27,               /* k_waitevent  */
  YYSYMBOL_k_event = 28,                   /* k_event  */
  YYSYMBOL_k_name = 29,                    /* k_name  */
  YYSYMBOL_k_thumbnail = 30,               /* k_thumbnail  */
  YYSYMBOL_k_features = 31,                /* k_features  */
  YYSYMBOL_k_uses = 32,                    /* k_uses  */
  YYSYMBOL_k_export = 33,                  /* k_export  */
  YYSYMBOL_k_texture = 34,                 /* k_texture  */
  YYSYMBOL_k_sound = 35,                   /* k_sound  */
  YYSYMBOL_k_model = 36,                   /* k_model  */
  YYSYMBOL_k_skamodel = 37,                /* k_skamodel  */
  YYSYMBOL_k_editor = 38,                  /* k_editor  */
  YYSYMBOL_k_properties = 39,              /* k_properties  */
  YYSYMBOL_k_components = 40,              /* k_components  */
  YYSYMBOL_k_functions = 41,               /* k_functions  */
  YYSYMBOL_k_procedures = 42,              /* k_procedures  */
  YYSYMBOL_k_wait = 43,                    /* k_wait  */
  YYSYMBOL_k_on = 44,                      /* k_on  */
  YYSYMBOL_k_otherwise = 45,               /* k_otherwise  */
  YYSYMBOL_k_call = 46,                    /* k_call  */
  YYSYMBOL_k_jump = 47,                    /* k_jump  */
  YYSYMBOL_k_stop = 48,                    /* k_stop  */
  YYSYMBOL_k_resume = 49,                  /* k_resume  */
  YYSYMBOL_k_pass = 50,                    /* k_pass  */
  YYSYMBOL_k_CTString = 51,                /* k_CTString  */
  YYSYMBOL_k_CTStringTrans = 52,           /* k_CTStringTrans  */
  YYSYMBOL_k_CTFileName = 53,              /* k_CTFileName  */
  YYSYMBOL_k_CTFileNameNoDep = 54,         /* k_CTFileNameNoDep  */
  YYSYMBOL_k_BOOL = 55,                    /* k_BOOL  */
  YYSYMBOL_k_COLOR = 56,                   /* k_COLOR  */
  YYSYMBOL_k_FLOAT = 57,                   /* k_FLOAT  */
  YYSYMBOL_k_INDEX = 58,                   /* k_INDEX  */
  YYSYMBOL_k_RANGE = 59,                   /* k_RANGE  */
  YYSYMBOL_k_CEntityPointer = 60,          /* k_CEntityPointer  */
  YYSYMBOL_k_CModelObject = 61,            /* k_CModelObject  */
  YYSYMBOL_k_CModelInstance = 62,          /* k_CModelInstance  */
  YYSYMBOL_k_CAnimObject = 63,             /* k_CAnimObject  */
  YYSYMBOL_k_CSoundObject = 64,            /* k_CSoundObject  */
  YYSYMBOL_k_CPlacement3D = 65,            /* k_CPlacement3D  */
  YYSYMBOL_k_FLOATaabbox3D = 66,           /* k_FLOATaabbox3D  */
  YYSYMBOL_k_FLOATmatrix3D = 67,           /* k_FLOATmatrix3D  */
  YYSYMBOL_k_FLOATquat3D = 68,             /* k_FLOATquat3D  */
  YYSYMBOL_k_ANGLE = 69,                   /* k_ANGLE  */
  YYSYMBOL_k_FLOAT3D = 70,                 /* k_FLOAT3D  */
  YYSYMBOL_k_ANGLE3D = 71,                 /* k_ANGLE3D  */
  YYSYMBOL_k_FLOATplane3D = 72,            /* k_FLOATplane3D  */
  YYSYMBOL_k_ANIMATION = 73,               /* k_ANIMATION  */
  YYSYMBOL_k_ILLUMINATIONTYPE = 74,        /* k_ILLUMINATIONTYPE  */
  YYSYMBOL_k_FLAGS = 75,                   /* k_FLAGS  */
  YYSYMBOL_k_ZONEFLAGS = 76,               /* k_ZONEFLAGS  */
  YYSYMBOL_k_ZONEFLAGS_EX = 77,            /* k_ZONEFLAGS_EX  */
  YYSYMBOL_78_ = 78,                       /* ';'  */
  YYSYMBOL_79_ = 79,                       /* '{'  */
  YYSYMBOL_80_ = 80,                       /* '}'  */
  YYSYMBOL_81_ = 81,                       /* ','  */
  YYSYMBOL_82_ = 82,                       /* ':'  */
  YYSYMBOL_83_ = 83,                       /* '('  */
  YYSYMBOL_84_ = 84,                       /* ')'  */
  YYSYMBOL_85_ = 85,                       /* '='  */
  YYSYMBOL_86_ = 86,                       /* '-'  */
  YYSYMBOL_87_ = 87,                       /* '~'  */
  YYSYMBOL_88_ = 88,                       /* '*'  */
  YYSYMBOL_89_ = 89,                       /* '&'  */
  YYSYMBOL_90_ = 90,                       /* '<'  */
  YYSYMBOL_91_ = 91,                       /* '>'  */
  YYSYMBOL_92_ = 92,                       /* '+'  */
  YYSYMBOL_93_ = 93,                       /* '!'  */
  YYSYMBOL_94_ = 94,                       /* '|'  */
  YYSYMBOL_95_ = 95,                       /* '/'  */
  YYSYMBOL_96_ = 96,                       /* '%'  */
  YYSYMBOL_97_ = 97,                       /* '^'  */
  YYSYMBOL_98_ = 98,                       /* '['  */
  YYSYMBOL_99_ = 99,                       /* ']'  */
  YYSYMBOL_100_ = 100,                     /* '.'  */
  YYSYMBOL_101_ = 101,                     /* '?'  */
  YYSYMBOL_YYACCEPT = 102,                 /* $accept  */
  YYSYMBOL_program = 103,                  /* program  */
  YYSYMBOL_104_1 = 104,                    /* $@1  */
  YYSYMBOL_105_2 = 105,                    /* $@2  */
  YYSYMBOL_106_3 = 106,                    /* $@3  */
  YYSYMBOL_107_4 = 107,                    /* $@4  */
  YYSYMBOL_108_5 = 108,                    /* $@5  */
  YYSYMBOL_opt_global_cppblock = 109,      /* opt_global_cppblock  */
  YYSYMBOL_uses_list = 110,                /* uses_list  */
  YYSYMBOL_uses_statement = 111,           /* uses_statement  */
  YYSYMBOL_enum_and_event_declarations_list = 112, /* enum_and_event_declarations_list  */
  YYSYMBOL_enum_declaration = 113,         /* enum_declaration  */
  YYSYMBOL_114_6 = 114,                    /* $@6  */
  YYSYMBOL_opt_comma = 115,                /* opt_comma  */
  YYSYMBOL_enum_values_list = 116,         /* enum_values_list  */
  YYSYMBOL_enum_value = 117,               /* enum_value  */
  YYSYMBOL_event_declaration = 118,        /* event_declaration  */
  YYSYMBOL_119_7 = 119,                    /* $@7  */
  YYSYMBOL_event_members_list = 120,       /* event_members_list  */
  YYSYMBOL_non_empty_event_members_list = 121, /* non_empty_event_members_list  */
  YYSYMBOL_event_member = 122,             /* event_member  */
  YYSYMBOL_opt_class_declaration = 123,    /* opt_class_declaration  */
  YYSYMBOL_class_declaration = 124,        /* class_declaration  */
  YYSYMBOL_125_8 = 125,                    /* $@8  */
  YYSYMBOL_126_9 = 126,                    /* $@9  */
  YYSYMBOL_127_10 = 127,                   /* $@10  */
  YYSYMBOL_128_11 = 128,                   /* $@11  */
  YYSYMBOL_129_12 = 129,                   /* $@12  */
  YYSYMBOL_130_13 = 130,                   /* $@13  */
  YYSYMBOL_131_14 = 131,                   /* $@14  */
  YYSYMBOL_class_optexport = 132,          /* class_optexport  */
  YYSYMBOL_opt_features = 133,             /* opt_features  */
  YYSYMBOL_134_15 = 134,                   /* $@15  */
  YYSYMBOL_features_list = 135,            /* features_list  */
  YYSYMBOL_feature = 136,                  /* feature  */
  YYSYMBOL_opt_internal_properties = 137,  /* opt_internal_properties  */
  YYSYMBOL_internal_property_list = 138,   /* internal_property_list  */
  YYSYMBOL_internal_property = 139,        /* internal_property  */
  YYSYMBOL_property_declaration_list = 140, /* property_declaration_list  */
  YYSYMBOL_nonempty_property_declaration_list = 141, /* nonempty_property_declaration_list  */
  YYSYMBOL_empty_property_declaration_list = 142, /* empty_property_declaration_list  */
  YYSYMBOL_property_declaration = 143,     /* property_declaration  */
  YYSYMBOL_property_id = 144,              /* property_id  */
  YYSYMBOL_property_identifier = 145,      /* property_identifier  */
  YYSYMBOL_property_type = 146,            /* property_type  */
  YYSYMBOL_property_wed_name_opt = 147,    /* property_wed_name_opt  */
  YYSYMBOL_property_shortcut_opt = 148,    /* property_shortcut_opt  */
  YYSYMBOL_property_color_opt = 149,       /* property_color_opt  */
  YYSYMBOL_property_flags_opt = 150,       /* property_flags_opt  */
  YYSYMBOL_property_default_opt = 151,     /* property_default_opt  */
  YYSYMBOL_property_default_expression = 152, /* property_default_expression  */
  YYSYMBOL_component_declaration_list = 153, /* component_declaration_list  */
  YYSYMBOL_nonempty_component_declaration_list = 154, /* nonempty_component_declaration_list  */
  YYSYMBOL_empty_component_declaration_list = 155, /* empty_component_declaration_list  */
  YYSYMBOL_component_declaration = 156,    /* component_declaration  */
  YYSYMBOL_component_id = 157,             /* component_id  */
  YYSYMBOL_component_identifier = 158,     /* component_identifier  */
  YYSYMBOL_component_filename = 159,       /* component_filename  */
  YYSYMBOL_component_type = 160,           /* component_type  */
  YYSYMBOL_opt_component_flags = 161,      /* opt_component_flags  */
  YYSYMBOL_undefined_component_flags = 162, /* undefined_component_flags  */
  YYSYMBOL_component_flags_list = 163,     /* component_flags_list  */
  YYSYMBOL_component_flags = 164,          /* component_flags  */
  YYSYMBOL_function_list = 165,            /* function_list  */
  YYSYMBOL_function_implementation = 166,  /* function_implementation  */
  YYSYMBOL_opt_tilde = 167,                /* opt_tilde  */
  YYSYMBOL_opt_export = 168,               /* opt_export  */
  YYSYMBOL_opt_const = 169,                /* opt_const  */
  YYSYMBOL_opt_virtual = 170,              /* opt_virtual  */
  YYSYMBOL_opt_semicolon = 171,            /* opt_semicolon  */
  YYSYMBOL_parameters_list = 172,          /* parameters_list  */
  YYSYMBOL_non_void_parameters_list = 173, /* non_void_parameters_list  */
  YYSYMBOL_parameter_declaration = 174,    /* parameter_declaration  */
  YYSYMBOL_return_type = 175,              /* return_type  */
  YYSYMBOL_any_type = 176,                 /* any_type  */
  YYSYMBOL_procedure_list = 177,           /* procedure_list  */
  YYSYMBOL_opt_override = 178,             /* opt_override  */
  YYSYMBOL_procedure_implementation = 179, /* procedure_implementation  */
  YYSYMBOL_180_16 = 180,                   /* $@16  */
  YYSYMBOL_event_specification = 181,      /* event_specification  */
  YYSYMBOL_expression = 182,               /* expression  */
  YYSYMBOL_type_keyword = 183,             /* type_keyword  */
  YYSYMBOL_case_constant_expression = 184, /* case_constant_expression  */
  YYSYMBOL_statements = 185,               /* statements  */
  YYSYMBOL_statement = 186,                /* statement  */
  YYSYMBOL_statement_if = 187,             /* statement_if  */
  YYSYMBOL_statement_if_else = 188,        /* statement_if_else  */
  YYSYMBOL_statement_while = 189,          /* statement_while  */
  YYSYMBOL_190_17 = 190,                   /* $@17  */
  YYSYMBOL_statement_dowhile = 191,        /* statement_dowhile  */
  YYSYMBOL_192_18 = 192,                   /* $@18  */
  YYSYMBOL_statement_for = 193,            /* statement_for  */
  YYSYMBOL_194_19 = 194,                   /* $@19  */
  YYSYMBOL_statement_wait = 195,           /* statement_wait  */
  YYSYMBOL_196_20 = 196,                   /* $@20  */
  YYSYMBOL_statement_autowait = 197,       /* statement_autowait  */
  YYSYMBOL_statement_waitevent = 198,      /* statement_waitevent  */
  YYSYMBOL_opt_eventvar = 199,             /* opt_eventvar  */
  YYSYMBOL_statement_autocall = 200,       /* statement_autocall  */
  YYSYMBOL_wait_expression = 201,          /* wait_expression  */
  YYSYMBOL_statement_jump = 202,           /* statement_jump  */
  YYSYMBOL_statement_call = 203,           /* statement_call  */
  YYSYMBOL_event_expression = 204,         /* event_expression  */
  YYSYMBOL_jumptarget = 205,               /* jumptarget  */
  YYSYMBOL_statement_stop = 206,           /* statement_stop  */
  YYSYMBOL_statement_resume = 207,         /* statement_resume  */
  YYSYMBOL_statement_pass = 208,           /* statement_pass  */
  YYSYMBOL_statement_return = 209,         /* statement_return  */
  YYSYMBOL_opt_expression = 210,           /* opt_expression  */
  YYSYMBOL_handler = 211,                  /* handler  */
  YYSYMBOL_handlers_list = 212             /* handlers_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3503

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  111
/* YYNRULES -- Number of rules.  */
#define YYNRULES  310
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  501

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   332


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,     2,     2,     2,    96,    89,     2,
      83,    84,    88,    92,    81,    86,   100,    95,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    82,    78,
      90,    85,    91,   101,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    98,     2,    99,    97,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    79,    94,    80,    87,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   256,   256,   266,   269,   275,   276,   256,   287,   288,
     292,   293,   296,   305,   306,   307,   313,   313,   324,   324,
     326,   327,   331,   341,   341,   388,   389,   393,   394,   398,
     414,   415,   419,   422,   442,   447,   451,   452,   458,   461,
     420,   527,   528,   532,   533,   533,   546,   547,   550,   601,
     602,   605,   606,   609,   619,   626,   635,   636,   639,   643,
     671,   672,   675,   680,   685,   690,   695,   700,   705,   710,
     715,   720,   725,   730,   735,   740,   745,   750,   755,   760,
     765,   770,   775,   780,   785,   790,   795,   800,   805,   810,
     818,   823,   828,   831,   836,   839,   843,   846,   851,   873,
     883,   883,   883,   883,   883,   884,   885,   886,   887,   888,
     895,   901,   909,   910,   913,   917,   931,   932,   933,   936,
     937,   938,   939,   940,   944,   945,   949,   953,   954,   958,
     965,   966,   970,   989,   990,   994,   995,  1005,  1006,  1009,
    1010,  1013,  1014,  1017,  1018,  1019,  1022,  1023,  1026,  1030,
    1031,  1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,
    1044,  1045,  1053,  1054,  1058,  1059,  1065,  1065,  1103,  1106,
    1109,  1115,  1115,  1115,  1115,  1115,  1116,  1117,  1118,  1118,
    1118,  1118,  1118,  1118,  1118,  1118,  1118,  1118,  1118,  1118,
    1118,  1118,  1118,  1118,  1118,  1118,  1118,  1119,  1120,  1121,
    1122,  1123,  1124,  1125,  1126,  1127,  1128,  1129,  1130,  1131,
    1132,  1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,
    1142,  1143,  1144,  1147,  1147,  1147,  1147,  1148,  1148,  1148,
    1148,  1148,  1149,  1149,  1149,  1149,  1149,  1150,  1150,  1150,
    1150,  1150,  1150,  1150,  1151,  1151,  1151,  1152,  1153,  1156,
    1156,  1156,  1156,  1156,  1157,  1164,  1165,  1168,  1169,  1170,
    1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,  1179,  1180,
    1181,  1182,  1183,  1184,  1185,  1186,  1187,  1188,  1193,  1209,
    1231,  1231,  1256,  1256,  1282,  1282,  1299,  1299,  1333,  1357,
    1382,  1385,  1390,  1414,  1417,  1423,  1432,  1444,  1447,  1453,
    1456,  1462,  1468,  1473,  1478,  1492,  1493,  1497,  1506,  1516,
    1517
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "c_char", "c_int",
  "c_float", "c_bool", "c_string", "identifier", "cppblock", "k_while",
  "k_for", "k_if", "k_else", "k_enum", "k_switch", "k_case", "k_class",
  "k_do", "k_void", "k_const", "k_inline", "k_static", "k_virtual",
  "k_return", "k_autowait", "k_autocall", "k_waitevent", "k_event",
  "k_name", "k_thumbnail", "k_features", "k_uses", "k_export", "k_texture",
  "k_sound", "k_model", "k_skamodel", "k_editor", "k_properties",
  "k_components", "k_functions", "k_procedures", "k_wait", "k_on",
  "k_otherwise", "k_call", "k_jump", "k_stop", "k_resume", "k_pass",
  "k_CTString", "k_CTStringTrans", "k_CTFileName", "k_CTFileNameNoDep",
  "k_BOOL", "k_COLOR", "k_FLOAT", "k_INDEX", "k_RANGE", "k_CEntityPointer",
  "k_CModelObject", "k_CModelInstance", "k_CAnimObject", "k_CSoundObject",
  "k_CPlacement3D", "k_FLOATaabbox3D", "k_FLOATmatrix3D", "k_FLOATquat3D",
  "k_ANGLE", "k_FLOAT3D", "k_ANGLE3D", "k_FLOATplane3D", "k_ANIMATION",
  "k_ILLUMINATIONTYPE", "k_FLAGS", "k_ZONEFLAGS", "k_ZONEFLAGS_EX", "';'",
  "'{'", "'}'", "','", "':'", "'('", "')'", "'='", "'-'", "'~'", "'*'",
  "'&'", "'<'", "'>'", "'+'", "'!'", "'|'", "'/'", "'%'", "'^'", "'['",
  "']'", "'.'", "'?'", "$accept", "program", "$@1", "$@2", "$@3", "$@4",
  "$@5", "opt_global_cppblock", "uses_list", "uses_statement",
  "enum_and_event_declarations_list", "enum_declaration", "$@6",
  "opt_comma", "enum_values_list", "enum_value", "event_declaration",
  "$@7", "event_members_list", "non_empty_event_members_list",
  "event_member", "opt_class_declaration", "class_declaration", "$@8",
  "$@9", "$@10", "$@11", "$@12", "$@13", "$@14", "class_optexport",
  "opt_features", "$@15", "features_list", "feature",
  "opt_internal_properties", "internal_property_list", "internal_property",
  "property_declaration_list", "nonempty_property_declaration_list",
  "empty_property_declaration_list", "property_declaration", "property_id",
  "property_identifier", "property_type", "property_wed_name_opt",
  "property_shortcut_opt", "property_color_opt", "property_flags_opt",
  "property_default_opt", "property_default_expression",
  "component_declaration_list", "nonempty_component_declaration_list",
  "empty_component_declaration_list", "component_declaration",
  "component_id", "component_identifier", "component_filename",
  "component_type", "opt_component_flags", "undefined_component_flags",
  "component_flags_list", "component_flags", "function_list",
  "function_implementation", "opt_tilde", "opt_export", "opt_const",
  "opt_virtual", "opt_semicolon", "parameters_list",
  "non_void_parameters_list", "parameter_declaration", "return_type",
  "any_type", "procedure_list", "opt_override", "procedure_implementation",
  "$@16", "event_specification", "expression", "type_keyword",
  "case_constant_expression", "statements", "statement", "statement_if",
  "statement_if_else", "statement_while", "$@17", "statement_dowhile",
  "$@18", "statement_for", "$@19", "statement_wait", "$@20",
  "statement_autowait", "statement_waitevent", "opt_eventvar",
  "statement_autocall", "wait_expression", "statement_jump",
  "statement_call", "event_expression", "jumptarget", "statement_stop",
  "statement_resume", "statement_pass", "statement_return",
  "opt_expression", "handler", "handlers_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-378)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-39)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,  -378,    48,    47,  -378,  -378,  -378,  -378,    29,    56,
    -378,  -378,    -6,     1,  -378,   114,   120,    47,  -378,  -378,
    -378,  -378,  -378,    50,    52,   115,   129,  3338,   101,  -378,
    -378,   127,   128,    57,  -378,    49,   133,  3338,    54,  3338,
    3338,  3338,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,    63,  -378,  -378,    16,
    -378,  -378,    55,   136,   129,    65,  3338,  -378,    14,  -378,
      14,    14,    14,  3338,    66,  -378,  -378,  -378,   140,  -378,
    -378,    72,   -15,  -378,    74,    75,  -378,  -378,  -378,   124,
     149,    81,   132,   156,    86,  -378,   134,  -378,  -378,   159,
     130,  -378,    38,  -378,    85,  -378,   159,   164,  -378,  -378,
    -378,    89,  -378,  -378,  3243,    92,   164,  -378,   165,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,   166,   167,   168,   169,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,   171,  3271,   139,   177,    96,
    -378,  -378,    18,   100,  -378,   131,    27,   152,   106,   181,
     103,  -378,  -378,  -378,  -378,  -378,  -378,   105,  -378,  -378,
    3177,    27,  -378,   111,   112,  -378,  -378,  -378,  -378,   108,
    -378,  -378,   158,  3177,  3177,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,   116,  1593,   117,   -31,  -378,   118,   -14,   -73,
     -33,   -42,   121,   -69,   122,   123,   -44,  -378,  -378,  -378,
    -378,  1692,  -378,  -378,  3177,  3177,   160,   181,  -378,  -378,
       2,  -378,  -378,   158,  1791,  1890,  -378,  -378,  1989,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,   125,  -378,   126,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    3177,  2088,  2187,   135,  -378,  -378,  -378,  -378,  -378,  -378,
     189,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,   192,     9,  -378,  -378,  -378,   163,  -378,   186,   137,
    -378,  3362,  -378,    54,   113,    14,   204,  -378,   205,   138,
     142,  -378,   141,   206,   145,  3429,   208,   143,  -378,    54,
     144,   148,  -378,    20,  -378,   151,   198,  3338,  -378,   212,
    -378,  -378,   146,  -378,   155,   162,  -378,   157,  -378,   306,
     222,   405,   161,   170,   172,   173,    62,   175,  3177,   174,
     223,   174,   174,   223,   223,   180,   182,   183,  -378,  -378,
     184,  1494,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,   184,
    3177,  3177,  3177,  3177,  -378,  -378,  -378,  -378,  -378,  -378,
     187,  -378,  3177,   185,  2286,   193,   188,   176,   226,  -378,
     190,   191,  -378,  -378,  -378,   504,  -378,  -378,  -378,  -378,
    -378,  2385,  2484,  2583,  2682,  -378,   603,  -378,  -378,  2781,
    -378,   194,  3177,   234,   196,  3177,  3177,  -378,   702,  -378,
    3177,   199,   201,  -378,  -378,   235,  3177,   200,  -378,   207,
    -378,   202,   209,  -378,   210,  2880,  -378,  -378,   236,  -378,
     237,  -378,   -34,   214,   216,  -378,  3177,   801,   900,   215,
     234,   217,   219,  -378,  -378,  -378,  -378,   999,  2979,   238,
    -378,  3177,   221,   206,   206,  -378,  -378,  1395,  3078,  -378,
     211,   213,   224,  -378,   229,   233,   241,  -378,  -378,   225,
     240,  1098,  -378,  -378,  -378,  1197,  1296,   184,   184,  -378,
    -378
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     2,     0,     8,     1,     9,     3,    10,     4,     0,
      13,    11,     0,     5,    12,     0,     0,     8,    14,    15,
      16,    23,     6,     0,     0,    30,     0,    25,    41,     7,
      31,     0,     0,    18,    20,   152,     0,     0,     0,   247,
       0,   248,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   245,   244,   246,   242,   243,    18,    26,    27,     0,
     151,    42,     0,     0,    19,     0,     0,   153,   160,   156,
     157,   158,   159,    19,     0,    29,   154,   155,     0,    22,
      21,     0,     0,    28,     0,     0,    17,   161,    24,     0,
       0,     0,     0,     0,     0,    33,    43,    44,    34,     0,
       0,    48,     0,    46,     0,    45,     0,    58,    47,    60,
      35,    18,    54,    56,     0,    49,    19,    55,     0,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    84,    83,
      85,    87,    86,     0,     0,     0,     0,    51,    36,    57,
      62,    63,    88,    89,    61,    90,     0,     0,    92,    98,
      50,    52,     0,     0,    93,    94,     0,    96,     0,   114,
       0,    91,   103,   100,   101,   102,   104,   105,   247,   248,
       0,     0,    99,     0,     0,    59,    53,   116,    37,    18,
     110,   112,   126,     0,     0,   174,   171,   172,   173,   175,
     176,   193,   192,     0,   178,   180,   196,   186,   185,   181,
     182,   179,   183,   184,   187,   188,   189,   190,   191,   194,
     195,     0,   177,   108,     0,     0,     0,    19,   111,   129,
       0,   124,   125,   128,     0,     0,   201,   197,     0,   207,
     215,   199,   200,   218,   211,   202,   210,   206,   209,   205,
     214,   198,   208,   212,   203,   216,   217,   213,   204,   109,
     222,     0,     0,     0,   113,   122,   120,   121,   119,   123,
       0,   127,    95,   106,   221,   220,   219,   107,    97,   130,
     117,     0,   135,   118,   115,   136,     0,   131,   139,     0,
     140,     0,   162,   150,   133,   149,    39,   134,     0,     0,
       0,   163,     0,   168,     0,   143,   169,     0,    40,   144,
       0,   145,   146,     0,   170,   164,   137,     0,   148,     0,
     166,   138,     0,   147,     0,     0,   255,     0,   255,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   305,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   277,   255,
     141,     0,   256,   265,   266,   262,   263,   264,   267,   268,
     269,   271,   276,   270,   272,   273,   274,   275,   165,   141,
       0,     0,     0,     0,   252,   249,   250,   251,   253,   254,
       0,   255,   306,     0,     0,     0,   299,     0,     0,   286,
       0,     0,   301,   302,   303,     0,   142,   132,   257,   255,
     167,     0,     0,     0,     0,   259,     0,   304,   293,     0,
     288,     0,   298,   290,     0,   298,   298,   260,     0,   280,
       0,     0,     0,   282,   294,     0,   297,     0,   291,     0,
     309,     0,     0,   261,     0,     0,   255,   255,     0,   300,
       0,   289,     0,     0,     0,   255,     0,     0,     0,     0,
     290,     0,     0,   287,   310,   296,   295,     0,     0,   278,
     258,     0,     0,   168,   168,   281,   284,     0,     0,   292,
       0,     0,     0,   279,     0,     0,     0,   255,   283,     0,
       0,     0,   255,   255,   285,     0,     0,   141,   141,   307,
     308
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -378,  -378,  -378,  -378,  -378,  -378,  -378,   230,  -378,  -378,
    -378,  -378,  -378,   -59,  -378,   178,  -378,  -378,  -378,  -378,
     242,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,   218,  -378,  -378,  -378,  -378,  -378,
    -378,   203,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,
      58,  -378,  -378,  -378,    11,  -378,  -378,  -378,  -378,  -378,
    -378,     7,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -377,
    -378,  -378,   -63,  -378,   -36,  -378,  -378,  -378,  -378,  -362,
    -190,   -19,  -378,  -332,  -205,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -177,  -378,  -234,
    -378,  -378,  -301,  -227,  -378,  -378,  -378,  -378,  -378,  -378,
    -378
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,     7,    10,    17,    25,     6,     8,    11,
      13,    18,    23,    75,    33,    34,    19,    24,    66,    67,
      68,    29,    30,   106,   110,   125,   167,   236,   296,   310,
      31,   108,   109,   112,   113,   158,   166,   171,   120,   121,
     122,   123,   124,   165,   156,   169,   175,   181,   195,   177,
     192,   198,   199,   200,   201,   202,   291,   294,   280,   240,
     241,   242,   243,   292,   297,   308,   298,   332,   301,   407,
     320,   321,   322,   304,    69,   306,   330,   311,   335,   317,
     270,   232,   390,   339,   362,   363,   364,   365,   444,   366,
     448,   367,   482,   368,   424,   369,   370,   439,   371,   395,
     372,   373,   437,   397,   374,   375,   376,   377,   393,   464,
     452
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     231,    78,   410,    80,    81,    82,   341,    84,    70,     1,
     461,   462,   256,   244,   245,    15,   263,   257,    70,   275,
      70,    70,    70,   248,    85,   264,   178,   405,   328,    16,
     182,   183,   184,   185,   186,   187,   276,   277,   278,   279,
      92,   267,   295,   260,   271,   272,   463,   188,     4,   189,
     261,   -38,   258,   268,   250,   251,     5,    70,   259,   416,
     252,     9,   127,    12,    70,   384,   385,   386,   387,   388,
     389,   254,    14,    86,    87,   255,    97,   428,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    86,    87,    86,    87,    86,    87,    86,    87,
     190,   480,   481,   191,   457,   458,   115,   398,   399,   116,
     499,   500,    20,   467,   441,   442,   400,   401,    21,    26,
     172,    27,    28,    32,    71,    72,    73,    88,    74,    76,
     238,    77,    79,    89,    83,    91,    94,    70,    95,   361,
      96,   361,    98,   100,    99,   491,   101,   193,   392,   102,
     495,   496,   103,   104,   105,   107,   111,   117,   119,   114,
     126,   157,   193,   160,   161,   162,   163,   164,   168,   173,
     174,   176,   179,   194,   196,   197,   203,   180,   204,   237,
     411,   412,   413,   414,   234,   235,   239,   290,   246,   293,
     307,   273,   249,   253,   419,   299,   262,   265,   266,   300,
     285,   286,   309,   312,   316,   361,   324,   289,   331,   302,
     334,   313,   314,   318,   315,   336,   361,   325,   326,   327,
     378,   396,   436,   329,   423,   436,   436,   337,   361,   340,
     445,   338,   438,   449,   380,   460,   459,    22,   274,   233,
     281,   477,    90,   381,   391,   382,   383,   394,   402,   422,
     403,   404,   406,   417,   333,   305,   468,   361,   361,   415,
     421,   420,   483,   425,   426,   440,   435,   361,   446,   323,
     447,   478,    70,   472,   450,   451,   453,   361,     0,   455,
       0,   323,   465,   454,   466,   485,    70,   486,   471,   479,
     473,   361,   474,   487,   492,   361,   361,   488,    70,   205,
     206,   207,   208,   209,   210,   489,   342,   343,   344,   493,
       0,   345,   346,   490,   347,    93,   188,     0,   189,   159,
     348,   349,   350,   351,   118,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   352,
       0,     0,   353,   354,   355,   356,   357,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,     0,     0,     0,   358,   359,   360,   211,   212,   213,
       0,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   205,   206,
     207,   208,   209,   210,     0,   342,   343,   344,     0,     0,
     345,   346,     0,   347,     0,   188,     0,   189,     0,   348,
     349,   350,   351,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   352,     0,
       0,   353,   354,   355,   356,   357,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
       0,     0,     0,   358,   359,   379,   211,   212,   213,     0,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   205,   206,   207,
     208,   209,   210,     0,   342,   343,   344,     0,     0,   345,
     346,     0,   347,     0,   188,     0,   189,     0,   348,   349,
     350,   351,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   352,     0,     0,
     353,   354,   355,   356,   357,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,     0,
       0,     0,   358,   359,   427,   211,   212,   213,     0,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   205,   206,   207,   208,
     209,   210,     0,   342,   343,   344,     0,     0,   345,   346,
       0,   347,     0,   188,     0,   189,     0,   348,   349,   350,
     351,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   352,     0,     0,   353,
     354,   355,   356,   357,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,     0,     0,
       0,   358,   359,   433,   211,   212,   213,     0,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   205,   206,   207,   208,   209,
     210,     0,   342,   343,   344,     0,     0,   345,   346,     0,
     347,     0,   188,     0,   189,     0,   348,   349,   350,   351,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   352,     0,     0,   353,   354,
     355,   356,   357,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,     0,     0,     0,
     358,   359,   443,   211,   212,   213,     0,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   205,   206,   207,   208,   209,   210,
       0,   342,   343,   344,     0,     0,   345,   346,     0,   347,
       0,   188,     0,   189,     0,   348,   349,   350,   351,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   352,     0,     0,   353,   354,   355,
     356,   357,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,     0,     0,     0,   358,
     359,   469,   211,   212,   213,     0,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   205,   206,   207,   208,   209,   210,     0,
     342,   343,   344,     0,     0,   345,   346,     0,   347,     0,
     188,     0,   189,     0,   348,   349,   350,   351,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   352,     0,     0,   353,   354,   355,   356,
     357,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,     0,     0,     0,   358,   359,
     470,   211,   212,   213,     0,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   205,   206,   207,   208,   209,   210,     0,   342,
     343,   344,     0,     0,   345,   346,     0,   347,     0,   188,
       0,   189,     0,   348,   349,   350,   351,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   352,     0,     0,   353,   354,   355,   356,   357,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,     0,     0,     0,   358,   359,   475,
     211,   212,   213,     0,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   205,   206,   207,   208,   209,   210,     0,   342,   343,
     344,     0,     0,   345,   346,     0,   347,     0,   188,     0,
     189,     0,   348,   349,   350,   351,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   352,     0,     0,   353,   354,   355,   356,   357,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,     0,     0,     0,   358,   359,   494,   211,
     212,   213,     0,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     205,   206,   207,   208,   209,   210,     0,   342,   343,   344,
       0,     0,   345,   346,     0,   347,     0,   188,     0,   189,
       0,   348,   349,   350,   351,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     352,     0,     0,   353,   354,   355,   356,   357,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,     0,     0,     0,   358,   359,   497,   211,   212,
     213,     0,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   205,
     206,   207,   208,   209,   210,     0,   342,   343,   344,     0,
       0,   345,   346,     0,   347,     0,   188,     0,   189,     0,
     348,   349,   350,   351,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   352,
       0,     0,   353,   354,   355,   356,   357,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,     0,     0,     0,   358,   359,   498,   211,   212,   213,
       0,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   205,   206,
     207,   208,   209,   210,     0,   342,   343,   344,     0,     0,
     345,   346,     0,   347,     0,   188,     0,   189,     0,   348,
     349,   350,   351,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   352,     0,
       0,   353,   354,   355,   356,   357,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
       0,     0,     0,   358,   359,     0,   211,   212,   213,     0,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   205,   206,   207,
     208,   209,   210,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,     0,   189,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,     0,
       0,     0,   408,   409,     0,   211,   212,   213,     0,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   205,   206,   207,   208,
     209,   210,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   188,     0,   189,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,     0,     0,
       0,     0,     0,     0,   211,   212,   213,   247,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   205,   206,   207,   208,   209,
     210,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,     0,   189,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,     0,     0,     0,
       0,     0,     0,   211,   212,   213,   269,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   205,   206,   207,   208,   209,   210,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   188,     0,   189,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,     0,     0,     0,     0,
       0,     0,   211,   212,   213,   282,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   205,   206,   207,   208,   209,   210,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     188,     0,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,     0,     0,     0,     0,     0,
       0,   211,   212,   213,   283,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   205,   206,   207,   208,   209,   210,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   188,
       0,   189,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,     0,     0,     0,     0,     0,     0,
     211,   212,   213,   284,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   205,   206,   207,   208,   209,   210,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,     0,
     189,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,     0,     0,     0,     0,     0,     0,   211,
     212,   213,   287,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     205,   206,   207,   208,   209,   210,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   188,     0,   189,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,     0,     0,     0,     0,     0,     0,   211,   212,
     213,   288,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   205,
     206,   207,   208,   209,   210,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   188,     0,   189,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,     0,     0,     0,     0,     0,     0,   211,   212,   213,
     418,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   205,   206,
     207,   208,   209,   210,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   188,     0,   189,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
       0,     0,     0,     0,     0,     0,   211,   212,   213,   429,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   205,   206,   207,
     208,   209,   210,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,     0,   189,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,     0,
       0,     0,   430,     0,     0,   211,   212,   213,     0,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   205,   206,   207,   208,
     209,   210,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   188,     0,   189,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,     0,     0,
       0,     0,     0,     0,   211,   212,   213,   431,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   205,   206,   207,   208,   209,
     210,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,     0,   189,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,     0,     0,     0,
       0,     0,     0,   211,   212,   213,   432,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   205,   206,   207,   208,   209,   210,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   188,     0,   189,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,     0,     0,     0,     0,
       0,     0,   211,   212,   213,   434,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   205,   206,   207,   208,   209,   210,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     188,     0,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,     0,     0,     0,   456,     0,
       0,   211,   212,   213,     0,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   205,   206,   207,   208,   209,   210,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   188,
       0,   189,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,     0,     0,     0,     0,     0,     0,
     211,   212,   213,   476,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   205,   206,   207,   208,   209,   210,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,     0,
     189,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,     0,     0,     0,     0,     0,     0,   211,
     212,   213,   484,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     205,   206,   207,   208,   209,   210,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   188,     0,   189,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,     0,     0,     0,     0,     0,   128,   211,   212,
     213,     0,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,    35,
       0,     0,     0,     0,     0,    36,     0,     0,    37,     0,
      38,    39,    40,    41,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,     0,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    35,     0,     0,     0,
       0,   170,    36,     0,     0,    37,     0,    38,    39,    40,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,     0,     0,     0,     0,     0,    36,     0,     0,    37,
       0,   303,    39,    40,    41,     0,     0,     0,     0,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    35,     0,     0,
       0,     0,     0,    36,     0,     0,    37,     0,   319,    39,
      40,    41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65
};

static const yytype_int16 yycheck[] =
{
     190,    37,   379,    39,    40,    41,   338,    66,    27,     4,
      44,    45,    85,   203,   204,    14,    85,    90,    37,    17,
      39,    40,    41,   213,     8,    94,     8,   359,     8,    28,
       3,     4,     5,     6,     7,     8,    34,    35,    36,    37,
      76,    85,    33,    85,   234,   235,    80,    20,     0,    22,
      92,    42,    85,    97,    85,    86,     9,    76,    91,   391,
      91,    32,   121,     7,    83,     3,     4,     5,     6,     7,
       8,    85,    78,    88,    89,    89,    91,   409,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    88,    89,    88,    89,    88,    89,    88,    89,
      83,   473,   474,    86,   446,   447,    78,   351,   352,    81,
     497,   498,     8,   455,   425,   426,   353,   354,     8,    79,
     166,    79,    17,     4,    33,     8,     8,    82,    81,    90,
     199,     8,    88,     7,    81,    80,    80,   166,     8,   339,
      78,   341,    78,    29,    79,   487,     7,   176,   348,    78,
     492,   493,    30,     7,    78,    31,     7,    82,     4,    39,
      81,    79,   191,     8,     8,     8,     8,     8,     7,    40,
       3,    85,    82,    31,    78,     4,    83,    56,    83,    81,
     380,   381,   382,   383,    83,    83,    38,     8,    82,     7,
      87,    41,    85,    85,   394,    42,    85,    85,    85,    23,
      85,    85,     8,     8,     8,   405,     8,    82,    20,    82,
       8,    83,    80,    78,    83,    79,   416,    84,    84,    81,
       8,     8,   422,    82,     8,   425,   426,    82,   428,    82,
     430,    79,     8,     8,    83,     8,    10,    17,   237,   191,
     243,    13,    74,    83,    79,    83,    83,    83,    78,    83,
      78,    78,    78,    78,   327,   301,   456,   457,   458,    82,
      82,    78,   477,    83,    83,    79,    82,   467,    79,   315,
      79,   471,   301,   460,    84,    78,    84,   477,    -1,    79,
      -1,   327,    78,    84,    78,    84,   315,    84,    83,    78,
      83,   491,    83,    79,    79,   495,   496,    78,   327,     3,
       4,     5,     6,     7,     8,    82,    10,    11,    12,    79,
      -1,    15,    16,    82,    18,    83,    20,    -1,    22,   126,
      24,    25,    26,    27,   116,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    -1,    78,    79,    80,    81,    82,    83,
      -1,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    -1,    -1,
      15,    16,    -1,    18,    -1,    20,    -1,    22,    -1,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    78,    79,    80,    81,    82,    83,    -1,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    -1,    -1,    15,
      16,    -1,    18,    -1,    20,    -1,    22,    -1,    24,    25,
      26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    -1,    78,    79,    80,    81,    82,    83,    -1,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,     3,     4,     5,     6,
       7,     8,    -1,    10,    11,    12,    -1,    -1,    15,    16,
      -1,    18,    -1,    20,    -1,    22,    -1,    24,    25,    26,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    78,    79,    80,    81,    82,    83,    -1,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,     3,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    -1,    -1,    15,    16,    -1,
      18,    -1,    20,    -1,    22,    -1,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    83,    -1,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,     3,     4,     5,     6,     7,     8,
      -1,    10,    11,    12,    -1,    -1,    15,    16,    -1,    18,
      -1,    20,    -1,    22,    -1,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    78,
      79,    80,    81,    82,    83,    -1,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    12,    -1,    -1,    15,    16,    -1,    18,    -1,
      20,    -1,    22,    -1,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    -1,    78,    79,
      80,    81,    82,    83,    -1,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,     3,     4,     5,     6,     7,     8,    -1,    10,
      11,    12,    -1,    -1,    15,    16,    -1,    18,    -1,    20,
      -1,    22,    -1,    24,    25,    26,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    78,    79,    80,
      81,    82,    83,    -1,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    -1,    -1,    15,    16,    -1,    18,    -1,    20,    -1,
      22,    -1,    24,    25,    26,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    78,    79,    80,    81,
      82,    83,    -1,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      -1,    -1,    15,    16,    -1,    18,    -1,    20,    -1,    22,
      -1,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    -1,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    78,    79,    80,    81,    82,
      83,    -1,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    12,    -1,
      -1,    15,    16,    -1,    18,    -1,    20,    -1,    22,    -1,
      24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    -1,    78,    79,    80,    81,    82,    83,
      -1,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    -1,    -1,
      15,    16,    -1,    18,    -1,    20,    -1,    22,    -1,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    78,    79,    -1,    81,    82,    83,    -1,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    -1,    78,    79,    -1,    81,    82,    83,    -1,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    -1,    78,    -1,    -1,    81,    82,    83,    -1,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    -1,    78,    -1,
      -1,    81,    82,    83,    -1,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    14,    81,    82,
      83,    -1,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,     8,
      -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,    17,    -1,
      19,    20,    21,    22,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,     8,    -1,    -1,    -1,
      -1,    80,    14,    -1,    -1,    17,    -1,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,    17,
      -1,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,     8,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    17,    -1,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,   103,   104,     0,     9,   109,   105,   110,    32,
     106,   111,     7,   112,    78,    14,    28,   107,   113,   118,
       8,     8,   109,   114,   119,   108,    79,    79,    17,   123,
     124,   132,     4,   116,   117,     8,    14,    17,    19,    20,
      21,    22,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,   120,   121,   122,   176,
     183,    33,     8,     8,    81,   115,    90,     8,   176,    88,
     176,   176,   176,    81,   115,     8,    88,    89,    82,     7,
     117,    80,   176,   122,    80,     8,    78,    91,    78,    79,
      29,     7,    78,    30,     7,    78,   125,    31,   133,   134,
     126,     7,   135,   136,    39,    78,    81,    82,   136,     4,
     140,   141,   142,   143,   144,   127,    81,   115,    14,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,   146,    79,   137,   143,
       8,     8,     8,     8,     8,   145,   138,   128,     7,   147,
      80,   139,   176,    40,     3,   148,    85,   151,     8,    82,
      56,   149,     3,     4,     5,     6,     7,     8,    20,    22,
      83,    86,   152,   183,    31,   150,    78,     4,   153,   154,
     155,   156,   157,    83,    83,     3,     4,     5,     6,     7,
       8,    81,    82,    83,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   182,   183,   152,    83,    83,   129,    81,   115,    38,
     161,   162,   163,   164,   182,   182,    82,    84,   182,    85,
      85,    86,    91,    85,    85,    89,    85,    90,    85,    91,
      85,    92,    85,    85,    94,    85,    85,    85,    97,    84,
     182,   182,   182,    41,   156,    17,    34,    35,    36,    37,
     160,   163,    84,    84,    84,    85,    85,    84,    84,    82,
       8,   158,   165,     7,   159,    33,   130,   166,   168,    42,
      23,   170,    82,    19,   175,   176,   177,    87,   167,     8,
     131,   179,     8,    83,    80,    83,     8,   181,    78,    19,
     172,   173,   174,   176,     8,    84,    84,    81,     8,    82,
     178,    20,   169,   174,     8,   180,    79,    82,    79,   185,
      82,   185,    10,    11,    12,    15,    16,    18,    24,    25,
      26,    27,    43,    46,    47,    48,    49,    50,    78,    79,
      80,   182,   186,   187,   188,   189,   191,   193,   195,   197,
     198,   200,   202,   203,   206,   207,   208,   209,     8,    80,
      83,    83,    83,    83,     3,     4,     5,     6,     7,     8,
     184,    79,   182,   210,    83,   201,     8,   205,   201,   201,
     205,   205,    78,    78,    78,   185,    78,   171,    78,    79,
     171,   182,   182,   182,   182,    82,   185,    78,    84,   182,
      78,    82,    83,     8,   196,    83,    83,    80,   185,    84,
      78,    84,    84,    80,    84,    82,   182,   204,     8,   199,
      79,   204,   204,    80,   190,   182,    79,    79,   192,     8,
      84,    78,   212,    84,    84,    79,    78,   185,   185,    10,
       8,    44,    45,    80,   211,    78,    78,   185,   182,    80,
      80,    83,   199,    83,    83,    80,    84,    13,   182,    78,
     181,   181,   194,   186,    84,    84,    84,    79,    78,    82,
      82,   185,    79,    79,    80,   185,   185,    80,    80,   171,
     171
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   102,   104,   105,   106,   107,   108,   103,   109,   109,
     110,   110,   111,   112,   112,   112,   114,   113,   115,   115,
     116,   116,   117,   119,   118,   120,   120,   121,   121,   122,
     123,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     124,   132,   132,   133,   134,   133,   135,   135,   136,   137,
     137,   138,   138,   139,   140,   140,   141,   141,   142,   143,
     144,   145,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     147,   147,   148,   148,   149,   149,   150,   150,   151,   151,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     153,   153,   154,   154,   155,   156,   157,   158,   159,   160,
     160,   160,   160,   160,   161,   161,   162,   163,   163,   164,
     165,   165,   166,   167,   167,   168,   168,   169,   169,   170,
     170,   171,   171,   172,   172,   172,   173,   173,   174,   175,
     175,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   177,   177,   178,   178,   180,   179,   181,   181,
     181,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   184,
     184,   184,   184,   184,   184,   185,   185,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   187,   188,
     190,   189,   192,   191,   194,   193,   196,   195,   197,   198,
     199,   199,   200,   201,   201,   202,   203,   204,   204,   205,
     205,   206,   207,   208,   209,   210,   210,   211,   211,   212,
     212
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,     0,     0,     0,    11,     0,     1,
       0,     2,     3,     0,     2,     2,     0,     8,     0,     1,
       1,     3,     3,     0,     8,     0,     1,     1,     3,     2,
       0,     1,     0,     0,     0,     0,     0,     0,     0,     0,
      34,     1,     2,     0,     0,     4,     1,     3,     1,     0,
       3,     0,     2,     3,     1,     2,     1,     3,     0,     6,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       0,     3,     0,     1,     0,     4,     0,     4,     0,     2,
       1,     1,     1,     1,     1,     1,     4,     4,     2,     3,
       1,     2,     1,     3,     0,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     2,     1,     1,
       0,     2,    13,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     1,     1,     3,     2,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     4,     0,     2,     0,     5,     0,    10,     0,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     2,     7,     3,
       3,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     7,     9,
       0,     8,     0,    10,     0,    12,     0,     6,     3,     5,
       0,     1,     8,     2,     3,     6,     6,     1,     0,     1,
       4,     2,     2,     2,     3,     0,     1,     9,     9,     0,
       2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 256 "Parser.y"
          {
    int iID = atoi(yyvsp[0].strString);
    if(iID>32767) {
      yyerror("Maximum allowed id for entity source file is 32767");
    }
    _iCurrentClassID = iID;
    _iNextFreeID = iID<<16;
    fprintf(_fDeclaration, "#ifndef _%s_INCLUDED\n", _strFileNameBaseIdentifier);
    fprintf(_fDeclaration, "#define _%s_INCLUDED 1\n", _strFileNameBaseIdentifier);

  }
#line 2440 "Parser.cpp"
    break;

  case 3: /* $@2: %empty  */
#line 266 "Parser.y"
                        {

    //fprintf(_fImplementation, "\n#undef DECL_DLL\n#define DECL_DLL _declspec(dllimport)\n");
  }
#line 2449 "Parser.cpp"
    break;

  case 4: /* $@3: %empty  */
#line 269 "Parser.y"
              {
    //fprintf(_fImplementation, "\n#undef DECL_DLL\n#define DECL_DLL _declspec(dllexport)\n");

    fprintf(_fImplementation, "#include <%s.h>\n", _strFileNameBase);
    fprintf(_fImplementation, "#include <%s_tables.h>\n", _strFileNameBase);
    _strCurrentEventList = strdup("");
  }
#line 2461 "Parser.cpp"
    break;

  case 5: /* $@4: %empty  */
#line 275 "Parser.y"
                                     {
  }
#line 2468 "Parser.cpp"
    break;

  case 6: /* $@5: %empty  */
#line 276 "Parser.y"
                        {
  }
#line 2475 "Parser.cpp"
    break;

  case 7: /* program: c_int $@1 opt_global_cppblock $@2 uses_list $@3 enum_and_event_declarations_list $@4 opt_global_cppblock $@5 opt_class_declaration  */
#line 277 "Parser.y"
                          {
    fprintf(_fDeclaration, "#endif // _%s_INCLUDED\n", _strFileNameBaseIdentifier);
  }
#line 2483 "Parser.cpp"
    break;

  case 9: /* opt_global_cppblock: cppblock  */
#line 288 "Parser.y"
             { fprintf(_fImplementation, "%s\n", yyvsp[0].strString); }
#line 2489 "Parser.cpp"
    break;

  case 12: /* uses_statement: k_uses c_string ';'  */
#line 296 "Parser.y"
                        {
    char *strUsedFileName = strdup(yyvsp[-1].strString);
    strUsedFileName[strlen(strUsedFileName)-1] = 0;
    fprintf(_fDeclaration, "#include <%s.h>\n", strUsedFileName+1);
  }
#line 2499 "Parser.cpp"
    break;

  case 16: /* $@6: %empty  */
#line 313 "Parser.y"
                      { 
    _strCurrentEnum = yyvsp[0].strString;
    fprintf(_fTables, "EP_ENUMBEG(%s)\n", _strCurrentEnum );
    fprintf(_fDeclaration, "extern DECL_DLL CEntityPropertyEnumType %s_enum;\n", _strCurrentEnum );
    fprintf(_fDeclaration, "enum %s {\n", _strCurrentEnum );
  }
#line 2510 "Parser.cpp"
    break;

  case 17: /* enum_declaration: k_enum identifier $@6 '{' enum_values_list opt_comma '}' ';'  */
#line 318 "Parser.y"
                                           {
    fprintf(_fTables, "EP_ENUMEND(%s);\n\n", _strCurrentEnum);
    fprintf(_fDeclaration, "};\n");
    fprintf(_fDeclaration, "DECL_DLL inline void ClearToDefault(%s &e) { e = (%s)0; } ;\n", _strCurrentEnum, _strCurrentEnum);
  }
#line 2520 "Parser.cpp"
    break;

  case 22: /* enum_value: c_int identifier c_string  */
#line 331 "Parser.y"
                              {
    fprintf(_fTables, "\tEP_ENUMVALUE(%s, %s),\n", yyvsp[-1].strString, yyvsp[0].strString);
    fprintf(_fDeclaration, "\t%s = %s,\n", yyvsp[-1].strString, yyvsp[-2].strString);
  }
#line 2529 "Parser.cpp"
    break;

  case 23: /* $@7: %empty  */
#line 341 "Parser.y"
                       { 
    _strCurrentEvent = yyvsp[0].strString;
    int iID = CreateID();
    fprintf(_fDeclaration, "#define EVENTCODE_%s 0x%08x\n", _strCurrentEvent, iID);
    fprintf(_fDeclaration, "class DECL_DLL %s : public CEntityEvent {\npublic:\n",
      _strCurrentEvent);
    fprintf(_fDeclaration, "\t%s();\n", _strCurrentEvent );
    fprintf(_fDeclaration, "\tCEntityEvent *MakeCopy(void);\n");
    fprintf(_fDeclaration, "\tBOOL CheckIDs(void);\n");
    fprintf(_fImplementation, 
      "CEntityEvent *%s::MakeCopy(void) { "
      "\tCEntityEvent *peeCopy = new %s(*this); "
      "\treturn peeCopy;}\n",
      _strCurrentEvent, _strCurrentEvent);
    fprintf(_fDeclaration, "\tSLONG GetSizeOf(void);\n");
    fprintf(_fImplementation, 
      "SLONG %s::GetSizeOf(void) { "
      "\treturn sizeof(*this);}\n",
      _strCurrentEvent);

    fprintf(_fImplementation, "%s::%s() : CEntityEvent(EVENTCODE_%s) {\n",
      _strCurrentEvent, _strCurrentEvent, _strCurrentEvent);

    fprintf(_fTables, "CEntityEvent *%s_New(void) { return new %s; };\n", _strCurrentEvent, _strCurrentEvent);
    fprintf(_fTables, 
      "CDLLEntityEvent DLLEvent_%s = {\n"
      "\t0x%08x, &%s_New\n"
      "};\n",
      _strCurrentEvent, iID, _strCurrentEvent);

    char strBuffer[256];
    sprintf(strBuffer, "\t&DLLEvent_%s,\n", _strCurrentEvent);
    extern char *stradd(char *str1, char *str2);
    _strCurrentEventList = stradd(strBuffer, _strCurrentEventList);
    _strCurrentEventCheck = strdup("");


  }
#line 2572 "Parser.cpp"
    break;

  case 24: /* event_declaration: k_event identifier $@7 '{' event_members_list opt_comma '}' ';'  */
#line 378 "Parser.y"
                                             {
    fprintf(_fImplementation, "}\n");
    fprintf(_fDeclaration, "};\n");
    fprintf(_fDeclaration, "DECL_DLL inline void ClearToDefault(%s &e) { e = %s(); } ;\n", _strCurrentEvent, _strCurrentEvent);

    fprintf(_fImplementation, "BOOL %s::CheckIDs(void) {\treturn TRUE %s; }\n\n", _strCurrentEvent, _strCurrentEventCheck);
  }
#line 2584 "Parser.cpp"
    break;

  case 29: /* event_member: any_type identifier  */
#line 398 "Parser.y"
                        {
    fprintf(_fDeclaration, "\t%s %s;\n", yyvsp[-1].strString, yyvsp[0].strString);
    fprintf(_fImplementation, "\tClearToDefault(%s);\n", yyvsp[0].strString);
    if (strcmp(yyvsp[-1].strString, "CEntityID")==0) {
      char strBuffer[256];
      sprintf(strBuffer, "&& %s.IsValid()", yyvsp[0].strString);
      extern char *stradd(char *str1, char *str2);
      _strCurrentEventCheck = stradd(_strCurrentEventCheck, strBuffer);
    }
  }
#line 2599 "Parser.cpp"
    break;

  case 33: /* $@8: %empty  */
#line 422 "Parser.y"
                           {
    _strCurrentClass = yyvsp[-9].strString;
    _strCurrentBase = yyvsp[-7].strString;
    _strCurrentDescription = yyvsp[-4].strString;
    _strCurrentThumbnail = yyvsp[-1].strString;

    if (strlen(_strCurrentEventList)>0) {
      fprintf(_fTables, "CDLLEntityEvent *%s_events[] = {\n%s};\n", _strCurrentClass, _strCurrentEventList);
      fprintf(_fTables, "#define %s_eventsct ARRAYCOUNT(%s_events)\n", _strCurrentClass, _strCurrentClass);
    } else {
      fprintf(_fTables, "CDLLEntityEvent *%s_events[] = {NULL};\n", _strCurrentClass);
      fprintf(_fTables, "#define %s_eventsct 0\n", _strCurrentClass);
    }

    fprintf(_fTables, "#define ENTITYCLASS %s\n\n", _strCurrentClass);
    fprintf(_fDeclaration, "extern \"C\" DECL_DLL CDLLEntityClass %s_DLLClass;\n",
      _strCurrentClass);
    fprintf(_fDeclaration, "%s %s : public %s {\npublic:\n",
      yyvsp[-10].strString, _strCurrentClass, _strCurrentBase);

  }
#line 2625 "Parser.cpp"
    break;

  case 34: /* $@9: %empty  */
#line 442 "Parser.y"
                 {
    fprintf(_fDeclaration, "\t%s virtual void SetDefaultProperties(void);\n", _bClassIsExported?"":"DECL_DLL");
    fprintf(_fImplementation, "void %s::SetDefaultProperties(void) {\n", _strCurrentClass);
    fprintf(_fTables, "CEntityProperty %s_properties[] = {\n", _strCurrentClass);

  }
#line 2636 "Parser.cpp"
    break;

  case 35: /* $@10: %empty  */
#line 447 "Parser.y"
                                               {
    fprintf(_fImplementation, "\t%s::SetDefaultProperties();\n}\n", _strCurrentBase);

    fprintf(_fTables, "CEntityComponent %s_components[] = {\n", _strCurrentClass);
  }
#line 2646 "Parser.cpp"
    break;

  case 36: /* $@11: %empty  */
#line 451 "Parser.y"
                            {
  }
#line 2653 "Parser.cpp"
    break;

  case 37: /* $@12: %empty  */
#line 452 "Parser.y"
                                                {
    _bTrackLineInformation = 1;
    fprintf(_fTables, "CEventHandlerEntry %s_handlers[] = {\n", _strCurrentClass);

    _bInProcedure = 0;
    _bInHandler = 0;
  }
#line 2665 "Parser.cpp"
    break;

  case 38: /* $@13: %empty  */
#line 458 "Parser.y"
                                  {

    _bInProcedure = 1;
  }
#line 2674 "Parser.cpp"
    break;

  case 39: /* $@14: %empty  */
#line 461 "Parser.y"
                                    {
  }
#line 2681 "Parser.cpp"
    break;

  case 40: /* class_declaration: class_optexport identifier ':' identifier '{' k_name c_string ';' k_thumbnail c_string ';' $@8 opt_features $@9 k_properties ':' property_declaration_list $@10 opt_internal_properties $@11 k_components ':' component_declaration_list $@12 k_functions ':' function_list $@13 k_procedures ':' procedure_list $@14 '}' ';'  */
#line 462 "Parser.y"
            {
    fprintf(_fTables, "};\n#define %s_handlersct ARRAYCOUNT(%s_handlers)\n", 
      _strCurrentClass, _strCurrentClass);
    fprintf(_fTables, "\n");

    if (_bFeature_AbstractBaseClass) {
      fprintf(_fTables, "CEntity *%s_New(void) { return NULL; };\n",
        _strCurrentClass);
    } else {
      fprintf(_fTables, "CEntity *%s_New(void) { return new %s; };\n",
        _strCurrentClass, _strCurrentClass);
    }

    if (!_bFeature_ImplementsOnInitClass) {
      fprintf(_fTables, "void %s_OnInitClass(void) {};\n", _strCurrentClass);
    } else {
      fprintf(_fTables, "void %s_OnInitClass(void);\n", _strCurrentClass);
    }

    if (!_bFeature_ImplementsOnEndClass) {
      fprintf(_fTables, "void %s_OnEndClass(void) {};\n", _strCurrentClass);
    } else {
      fprintf(_fTables, "void %s_OnEndClass(void);\n", _strCurrentClass);
    }

    if (!_bFeature_ImplementsOnPrecache) {
      fprintf(_fTables, "void %s_OnPrecache(CDLLEntityClass *pdec, INDEX iUser) {};\n", _strCurrentClass);
    } else {
      fprintf(_fTables, "void %s_OnPrecache(CDLLEntityClass *pdec, INDEX iUser);\n", _strCurrentClass);
    }

    if (!_bFeature_ImplementsOnWorldEnd) {
      fprintf(_fTables, "void %s_OnWorldEnd(CWorld *pwo) {};\n", _strCurrentClass);
    } else {
      fprintf(_fTables, "void %s_OnWorldEnd(CWorld *pwo);\n", _strCurrentClass);
    }

    if (!_bFeature_ImplementsOnWorldInit) {
      fprintf(_fTables, "void %s_OnWorldInit(CWorld *pwo) {};\n", _strCurrentClass);
    } else {
      fprintf(_fTables, "void %s_OnWorldInit(CWorld *pwo);\n", _strCurrentClass);
    }

    if (!_bFeature_ImplementsOnWorldTick) {
      fprintf(_fTables, "void %s_OnWorldTick(CWorld *pwo) {};\n", _strCurrentClass);
    } else {
      fprintf(_fTables, "void %s_OnWorldTick(CWorld *pwo);\n", _strCurrentClass);
    }

    if (!_bFeature_ImplementsOnWorldRender) {
      fprintf(_fTables, "void %s_OnWorldRender(CWorld *pwo) {};\n", _strCurrentClass);
    } else {
      fprintf(_fTables, "void %s_OnWorldRender(CWorld *pwo);\n", _strCurrentClass);
    }

    fprintf(_fTables, "ENTITY_CLASSDEFINITION(%s, %s, %s, %s, 0x%08x);\n",
      _strCurrentClass, _strCurrentBase, 
      _strCurrentDescription, _strCurrentThumbnail, _iCurrentClassID);
    fprintf(_fTables, "DECLARE_CTFILENAME(_fnm%s_tbn, %s);\n", _strCurrentClass, _strCurrentThumbnail);

    fprintf(_fDeclaration, "};\n");
  }
#line 2748 "Parser.cpp"
    break;

  case 41: /* class_optexport: k_class  */
#line 527 "Parser.y"
            { yyval = yyvsp[0]; _bClassIsExported = 0; }
#line 2754 "Parser.cpp"
    break;

  case 42: /* class_optexport: k_class k_export  */
#line 528 "Parser.y"
                     { yyval = yyvsp[-1]+" DECL_DLL "; _bClassIsExported = 1; }
#line 2760 "Parser.cpp"
    break;

  case 44: /* $@15: %empty  */
#line 533 "Parser.y"
               {
    _bFeature_ImplementsOnWorldInit = 0;
    _bFeature_ImplementsOnWorldEnd = 0;
    _bFeature_ImplementsOnWorldTick = 0;
    _bFeature_ImplementsOnWorldRender = 0;
    _bFeature_ImplementsOnInitClass = 0;
    _bFeature_ImplementsOnEndClass = 0;
    _bFeature_ImplementsOnPrecache = 0;
    _bFeature_AbstractBaseClass = 0;
    _bFeature_CanBePredictable = 0;
  }
#line 2776 "Parser.cpp"
    break;

  case 48: /* feature: c_string  */
#line 550 "Parser.y"
             {
    if (strcmp(yyvsp[0].strString, "\"AbstractBaseClass\"")==0) {
      _bFeature_AbstractBaseClass = 1;
    } else if (strcmp(yyvsp[0].strString, "\"IsTargetable\"")==0) {
      fprintf(_fDeclaration, "virtual BOOL IsTargetable(void) const { return TRUE; };\n");
    } else if (strcmp(yyvsp[0].strString, "\"NotSentOverNet\"")==0) {
      fprintf(_fDeclaration, "virtual BOOL IsSentOverNet(void) const { return FALSE; };\n");
    } else if (strcmp(yyvsp[0].strString, "\"IsImportant\"")==0) {
      fprintf(_fDeclaration, "virtual BOOL IsImportant(void) const { return TRUE; };\n");
    } else if (strcmp(yyvsp[0].strString, "\"HasName\"")==0) {
      fprintf(_fDeclaration, 
        "virtual const CTString &GetName(void) const { return m_strName; };\n");
    } else if (strcmp(yyvsp[0].strString, "\"CanBePredictable\"")==0) {
      fprintf(_fDeclaration, 
        "virtual CEntity *GetPredictionPair(void) { return m_penPrediction; };\n");
      fprintf(_fDeclaration, 
        "virtual void SetPredictionPair(CEntity *penPair) { m_penPrediction = penPair; };\n");
      _bFeature_CanBePredictable = 1;
    } else if (strcmp(yyvsp[0].strString, "\"HasDescription\"")==0) {
      fprintf(_fDeclaration, 
        "virtual const CTString &GetDescription(void) const { return m_strDescription; };\n");
    } else if (strcmp(yyvsp[0].strString, "\"HasTarget\"")==0) {
      fprintf(_fDeclaration, 
        "virtual CEntity *GetTarget(void) const { return m_penTarget; };\n");
    } else if (strcmp(yyvsp[0].strString, "\"ImplementsOnInitClass\"")==0) {
      _bFeature_ImplementsOnInitClass = 1;
    } else if (strcmp(yyvsp[0].strString, "\"ImplementsOnEndClass\"")==0) {
      _bFeature_ImplementsOnEndClass = 1;
    } else if (strcmp(yyvsp[0].strString, "\"ImplementsOnPrecache\"")==0) {
      _bFeature_ImplementsOnPrecache = 1;
    } else if (strcmp(yyvsp[0].strString, "\"ImplementsOnWorldInit\"")==0) {
      _bFeature_ImplementsOnWorldInit = 1;
    } else if (strcmp(yyvsp[0].strString, "\"ImplementsOnWorldEnd\"")==0) {
      _bFeature_ImplementsOnWorldEnd = 1;
    } else if (strcmp(yyvsp[0].strString, "\"ImplementsOnWorldTick\"")==0) {
      _bFeature_ImplementsOnWorldTick = 1;
    } else if (strcmp(yyvsp[0].strString, "\"ImplementsOnWorldRender\"")==0) {
      _bFeature_ImplementsOnWorldRender = 1;
    } else if (strcmp(yyvsp[0].strString, "\"HasRaidObject\"")==0) {
      fprintf(_fDeclaration, "virtual BOOL GetRaidObject(void) const { return m_bRaidObject; };\n");
	} else if (strcmp(yyvsp[0].strString, "\"RaidEvent\"")==0) {
		fprintf(_fDeclaration, "virtual INDEX GetRaidEvent(void) const { return m_RaidEventType; };\n");
	} else if (strcmp(yyvsp[0].strString, "\"AlignBackground\"")==0) {
		fprintf(_fDeclaration, "virtual BOOL GetAlBackground(void) const { return m_AlignBackground; };\n");
	} else {
      yyerror((SType("Unknown feature: ")+yyvsp[0]).strString);
    }
  }
#line 2829 "Parser.cpp"
    break;

  case 53: /* internal_property: any_type identifier ';'  */
#line 609 "Parser.y"
                            { 
    fprintf(_fDeclaration, "%s %s;\n", yyvsp[-2].strString, yyvsp[-1].strString);
  }
#line 2837 "Parser.cpp"
    break;

  case 54: /* property_declaration_list: empty_property_declaration_list  */
#line 619 "Parser.y"
                                    {
    DeclareFeatureProperties(); // this won't work, but at least it will generate an error!!!!
    fprintf(_fTables, "\tCEntityProperty()\n};\n");
    fprintf(_fTables, "#define %s_propertiesct 0\n", _strCurrentClass);
    fprintf(_fTables, "\n");
    fprintf(_fTables, "\n");
  }
#line 2849 "Parser.cpp"
    break;

  case 55: /* property_declaration_list: nonempty_property_declaration_list opt_comma  */
#line 626 "Parser.y"
                                                 {
    DeclareFeatureProperties();
    fprintf(_fTables, "};\n");
    fprintf(_fTables, "#define %s_propertiesct ARRAYCOUNT(%s_properties)\n", 
      _strCurrentClass, _strCurrentClass);
    fprintf(_fTables, "\n");
  }
#line 2861 "Parser.cpp"
    break;

  case 59: /* property_declaration: property_id property_type property_identifier property_wed_name_opt property_default_opt property_flags_opt  */
#line 643 "Parser.y"
                                                                                                                {
    int iPropertyID = atoi(_strCurrentPropertyID);
    if (iPropertyID > 255) {     
      yyerror((SType("property id greater then 255, property: ")+yyvsp[-3]).strString);
    }
    
    fprintf(_fTables, " CEntityProperty(%s, %s, (0x%08x<<8)+%s, offsetof(%s, %s), %s, %s, %s, %s),\n",
      _strCurrentPropertyPropertyType,
      _strCurrentPropertyEnumType,
      _iCurrentClassID,
      _strCurrentPropertyID,
      _strCurrentClass,
      _strCurrentPropertyIdentifier,
      _strCurrentPropertyName,
      _strCurrentPropertyShortcut,
      _strCurrentPropertyColor,
      _strCurrentPropertyFlags);
    fprintf(_fDeclaration, "\t%s %s;\n",
      _strCurrentPropertyDataType,
      _strCurrentPropertyIdentifier
      );

    if (strlen(_strCurrentPropertyDefaultCode)>0) {
      fprintf(_fImplementation, "\t%s\n", _strCurrentPropertyDefaultCode);
    }
  }
#line 2892 "Parser.cpp"
    break;

  case 60: /* property_id: c_int  */
#line 671 "Parser.y"
                    { _strCurrentPropertyID = yyvsp[0].strString; }
#line 2898 "Parser.cpp"
    break;

  case 61: /* property_identifier: identifier  */
#line 672 "Parser.y"
                                 { _strCurrentPropertyIdentifier = yyvsp[0].strString; }
#line 2904 "Parser.cpp"
    break;

  case 62: /* property_type: k_enum identifier  */
#line 675 "Parser.y"
                      {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_ENUM"; 
    _strCurrentPropertyEnumType = (SType("&")+yyvsp[0]+"_enum").strString; 
    _strCurrentPropertyDataType = (SType("enum ")+yyvsp[0].strString).strString;
  }
#line 2914 "Parser.cpp"
    break;

  case 63: /* property_type: k_FLAGS identifier  */
#line 680 "Parser.y"
                       {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_FLAGS"; 
    _strCurrentPropertyEnumType = (SType("&")+yyvsp[0]+"_enum").strString; 
    _strCurrentPropertyDataType = "ULONG";
  }
#line 2924 "Parser.cpp"
    break;

  case 64: /* property_type: k_CTString  */
#line 685 "Parser.y"
               {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_STRING"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "CTString";
  }
#line 2934 "Parser.cpp"
    break;

  case 65: /* property_type: k_CTStringTrans  */
#line 690 "Parser.y"
                    {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_STRINGTRANS"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "CTStringTrans";
  }
#line 2944 "Parser.cpp"
    break;

  case 66: /* property_type: k_CTFileName  */
#line 695 "Parser.y"
                 {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_FILENAME"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "CTFileName";
  }
#line 2954 "Parser.cpp"
    break;

  case 67: /* property_type: k_CTFileNameNoDep  */
#line 700 "Parser.y"
                      {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_FILENAMENODEP"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "CTFileNameNoDep";
  }
#line 2964 "Parser.cpp"
    break;

  case 68: /* property_type: k_BOOL  */
#line 705 "Parser.y"
           {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_BOOL"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "BOOL";
  }
#line 2974 "Parser.cpp"
    break;

  case 69: /* property_type: k_COLOR  */
#line 710 "Parser.y"
            {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_COLOR"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "COLOR";
  }
#line 2984 "Parser.cpp"
    break;

  case 70: /* property_type: k_FLOAT  */
#line 715 "Parser.y"
            {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_FLOAT"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "FLOAT";
  }
#line 2994 "Parser.cpp"
    break;

  case 71: /* property_type: k_INDEX  */
#line 720 "Parser.y"
            {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_INDEX"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "INDEX";
  }
#line 3004 "Parser.cpp"
    break;

  case 72: /* property_type: k_RANGE  */
#line 725 "Parser.y"
            {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_RANGE"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "RANGE";
  }
#line 3014 "Parser.cpp"
    break;

  case 73: /* property_type: k_CEntityPointer  */
#line 730 "Parser.y"
                     {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_ENTITYPTR"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "CEntityPointer";
  }
#line 3024 "Parser.cpp"
    break;

  case 74: /* property_type: k_CModelObject  */
#line 735 "Parser.y"
                   {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_MODELOBJECT"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "CModelObject";
  }
#line 3034 "Parser.cpp"
    break;

  case 75: /* property_type: k_CModelInstance  */
#line 740 "Parser.y"
                     {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_MODELINSTANCE"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "CModelInstance";
  }
#line 3044 "Parser.cpp"
    break;

  case 76: /* property_type: k_CAnimObject  */
#line 745 "Parser.y"
                  {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_ANIMOBJECT"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "CAnimObject";
  }
#line 3054 "Parser.cpp"
    break;

  case 77: /* property_type: k_CSoundObject  */
#line 750 "Parser.y"
                   {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_SOUNDOBJECT"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "CSoundObject";
  }
#line 3064 "Parser.cpp"
    break;

  case 78: /* property_type: k_CPlacement3D  */
#line 755 "Parser.y"
                   {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_PLACEMENT3D"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "CPlacement3D";
  }
#line 3074 "Parser.cpp"
    break;

  case 79: /* property_type: k_FLOATaabbox3D  */
#line 760 "Parser.y"
                    {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_FLOATAABBOX3D"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "FLOATaabbox3D";
  }
#line 3084 "Parser.cpp"
    break;

  case 80: /* property_type: k_FLOATmatrix3D  */
#line 765 "Parser.y"
                    {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_FLOATMATRIX3D"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "FLOATmatrix3D";
  }
#line 3094 "Parser.cpp"
    break;

  case 81: /* property_type: k_FLOATquat3D  */
#line 770 "Parser.y"
                  {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_FLOATQUAT3D"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "FLOATquat3D";
  }
#line 3104 "Parser.cpp"
    break;

  case 82: /* property_type: k_ANGLE  */
#line 775 "Parser.y"
            {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_ANGLE"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "ANGLE";
  }
#line 3114 "Parser.cpp"
    break;

  case 83: /* property_type: k_ANGLE3D  */
#line 780 "Parser.y"
              {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_ANGLE3D"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "ANGLE3D";
  }
#line 3124 "Parser.cpp"
    break;

  case 84: /* property_type: k_FLOAT3D  */
#line 785 "Parser.y"
              {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_FLOAT3D"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "FLOAT3D";
  }
#line 3134 "Parser.cpp"
    break;

  case 85: /* property_type: k_FLOATplane3D  */
#line 790 "Parser.y"
                   {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_FLOATplane3D"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "FLOATplane3D";
  }
#line 3144 "Parser.cpp"
    break;

  case 86: /* property_type: k_ILLUMINATIONTYPE  */
#line 795 "Parser.y"
                       {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_ILLUMINATIONTYPE"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "ILLUMINATIONTYPE";
  }
#line 3154 "Parser.cpp"
    break;

  case 87: /* property_type: k_ANIMATION  */
#line 800 "Parser.y"
                {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_ANIMATION"; 
    _strCurrentPropertyEnumType = "NULL"; 
    _strCurrentPropertyDataType = "ANIMATION";
  }
#line 3164 "Parser.cpp"
    break;

  case 88: /* property_type: k_ZONEFLAGS identifier  */
#line 805 "Parser.y"
                           {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_ZONEFLAGS"; 
    _strCurrentPropertyEnumType = (SType("&")+yyvsp[0]+"_enum").strString; 
    _strCurrentPropertyDataType = "ULONG";
  }
#line 3174 "Parser.cpp"
    break;

  case 89: /* property_type: k_ZONEFLAGS_EX identifier  */
#line 810 "Parser.y"
                              {
    _strCurrentPropertyPropertyType = "CEntityProperty::EPT_ZONEFLAGS_EX"; 
    _strCurrentPropertyEnumType = (SType("&")+yyvsp[0]+"_enum").strString; 
    _strCurrentPropertyDataType = "ULONG64";
  }
#line 3184 "Parser.cpp"
    break;

  case 90: /* property_wed_name_opt: %empty  */
#line 818 "Parser.y"
               {
    _strCurrentPropertyName = "\"\""; 
    _strCurrentPropertyShortcut = "0"; 
    _strCurrentPropertyColor = "0"; // this won't be rendered anyway
  }
#line 3194 "Parser.cpp"
    break;

  case 91: /* property_wed_name_opt: c_string property_shortcut_opt property_color_opt  */
#line 823 "Parser.y"
                                                      {
    _strCurrentPropertyName = yyvsp[-2].strString; 
  }
#line 3202 "Parser.cpp"
    break;

  case 92: /* property_shortcut_opt: %empty  */
#line 828 "Parser.y"
               {
    _strCurrentPropertyShortcut = "0"; 
  }
#line 3210 "Parser.cpp"
    break;

  case 93: /* property_shortcut_opt: c_char  */
#line 831 "Parser.y"
           {
    _strCurrentPropertyShortcut = yyvsp[0].strString; 
  }
#line 3218 "Parser.cpp"
    break;

  case 94: /* property_color_opt: %empty  */
#line 836 "Parser.y"
               {
    _strCurrentPropertyColor = "0x7F0000FFUL"; // dark red
  }
#line 3226 "Parser.cpp"
    break;

  case 95: /* property_color_opt: k_COLOR '(' expression ')'  */
#line 839 "Parser.y"
                               {
    _strCurrentPropertyColor = yyvsp[-1].strString; 
  }
#line 3234 "Parser.cpp"
    break;

  case 96: /* property_flags_opt: %empty  */
#line 843 "Parser.y"
               {
    _strCurrentPropertyFlags = "0"; // dark red
  }
#line 3242 "Parser.cpp"
    break;

  case 97: /* property_flags_opt: k_features '(' expression ')'  */
#line 846 "Parser.y"
                                  {
    _strCurrentPropertyFlags = yyvsp[-1].strString; 
  }
#line 3250 "Parser.cpp"
    break;

  case 98: /* property_default_opt: %empty  */
#line 851 "Parser.y"
               {
    if (strcmp(_strCurrentPropertyDataType,"CEntityPointer")==0)  {
      _strCurrentPropertyDefaultCode = (SType(_strCurrentPropertyIdentifier)+" = NULL;").strString;
    } else if (strcmp(_strCurrentPropertyDataType,"CModelObject")==0)  {
      _strCurrentPropertyDefaultCode = 
        (SType(_strCurrentPropertyIdentifier)+".SetData(NULL);\n"+
        _strCurrentPropertyIdentifier+".mo_toTexture.SetData(NULL);").strString;
    } else if (strcmp(_strCurrentPropertyDataType,"CModelInstance")==0)  {
      _strCurrentPropertyDefaultCode = 
        (SType(_strCurrentPropertyIdentifier)+".Clear();\n").strString;
    } else if (strcmp(_strCurrentPropertyDataType,"CAnimObject")==0)  {
      _strCurrentPropertyDefaultCode = 
        (SType(_strCurrentPropertyIdentifier)+".SetData(NULL);\n").strString;
    } else if (strcmp(_strCurrentPropertyDataType,"CSoundObject")==0)  {
      _strCurrentPropertyDefaultCode = 
        (SType(_strCurrentPropertyIdentifier)+".SetOwner(this);\n\t"+
         _strCurrentPropertyIdentifier+".Stop(FALSE);").strString;
    } else {
      yyerror("this kind of property must have default value");
      _strCurrentPropertyDefaultCode = "";
    }
  }
#line 3277 "Parser.cpp"
    break;

  case 99: /* property_default_opt: '=' property_default_expression  */
#line 873 "Parser.y"
                                    {
    if (strcmp(_strCurrentPropertyDataType,"CEntityPointer")==0)  {
      _strCurrentPropertyDefaultCode = (SType(_strCurrentPropertyIdentifier)+" = NULL;").strString;
      yyerror("CEntityPointer type properties always default to NULL");
    } else {
      _strCurrentPropertyDefaultCode = (SType(_strCurrentPropertyIdentifier)+" = "+yyvsp[0].strString+";").strString;
    }
  }
#line 3290 "Parser.cpp"
    break;

  case 105: /* property_default_expression: identifier  */
#line 884 "Parser.y"
               {yyval = yyvsp[0] + " ";}
#line 3296 "Parser.cpp"
    break;

  case 106: /* property_default_expression: identifier '(' expression ')'  */
#line 885 "Parser.y"
                                  {yyval = yyvsp[-3]+yyvsp[-2]+yyvsp[-1]+yyvsp[0];}
#line 3302 "Parser.cpp"
    break;

  case 107: /* property_default_expression: type_keyword '(' expression ')'  */
#line 886 "Parser.y"
                                    {yyval = yyvsp[-3]+yyvsp[-2]+yyvsp[-1]+yyvsp[0];}
#line 3308 "Parser.cpp"
    break;

  case 108: /* property_default_expression: '-' property_default_expression  */
#line 887 "Parser.y"
                                    {yyval = yyvsp[-1]+yyvsp[0];}
#line 3314 "Parser.cpp"
    break;

  case 109: /* property_default_expression: '(' expression ')'  */
#line 888 "Parser.y"
                       {yyval = yyvsp[-2]+yyvsp[-1]+yyvsp[0];}
#line 3320 "Parser.cpp"
    break;

  case 110: /* component_declaration_list: empty_component_declaration_list  */
#line 895 "Parser.y"
                                     {
    fprintf(_fTables, "\tCEntityComponent()\n};\n");
    fprintf(_fTables, "#define %s_componentsct 0\n", _strCurrentClass);
    fprintf(_fTables, "\n");
    fprintf(_fTables, "\n");
  }
#line 3331 "Parser.cpp"
    break;

  case 111: /* component_declaration_list: nonempty_component_declaration_list opt_comma  */
#line 901 "Parser.y"
                                                  {
    fprintf(_fTables, "};\n");
    fprintf(_fTables, "#define %s_componentsct ARRAYCOUNT(%s_components)\n", 
      _strCurrentClass, _strCurrentClass);
    fprintf(_fTables, "\n");
  }
#line 3342 "Parser.cpp"
    break;

  case 115: /* component_declaration: component_id opt_component_flags component_type component_identifier component_filename  */
#line 917 "Parser.y"
                                                                                            {
  fprintf(_fTables, "#define %s ((0x%08x<<8)+%s)\n",
      _strCurrentComponentIdentifier,
      _iCurrentClassID,
      _strCurrentComponentID);
    fprintf(_fTables, " CEntityComponent(%s, %s, %d, \"%s%s\" %s),\n",
      _strCurrentComponentType,
      _strCurrentComponentIdentifier,
      _ulCurrentComponentFlags,
      "EF","NM",
      _strCurrentComponentFileName);
  }
#line 3359 "Parser.cpp"
    break;

  case 116: /* component_id: c_int  */
#line 931 "Parser.y"
                     { _strCurrentComponentID = yyvsp[0].strString; }
#line 3365 "Parser.cpp"
    break;

  case 117: /* component_identifier: identifier  */
#line 932 "Parser.y"
                                  { _strCurrentComponentIdentifier = yyvsp[0].strString; }
#line 3371 "Parser.cpp"
    break;

  case 118: /* component_filename: c_string  */
#line 933 "Parser.y"
                              { _strCurrentComponentFileName = yyvsp[0].strString; }
#line 3377 "Parser.cpp"
    break;

  case 119: /* component_type: k_model  */
#line 936 "Parser.y"
               { _strCurrentComponentType = "ECT_MODEL"; }
#line 3383 "Parser.cpp"
    break;

  case 120: /* component_type: k_texture  */
#line 937 "Parser.y"
               { _strCurrentComponentType = "ECT_TEXTURE"; }
#line 3389 "Parser.cpp"
    break;

  case 121: /* component_type: k_sound  */
#line 938 "Parser.y"
               { _strCurrentComponentType = "ECT_SOUND"; }
#line 3395 "Parser.cpp"
    break;

  case 122: /* component_type: k_class  */
#line 939 "Parser.y"
               { _strCurrentComponentType = "ECT_CLASS"; }
#line 3401 "Parser.cpp"
    break;

  case 123: /* component_type: k_skamodel  */
#line 940 "Parser.y"
               { _strCurrentComponentType = "ECT_SKAMODEL";}
#line 3407 "Parser.cpp"
    break;

  case 126: /* undefined_component_flags: %empty  */
#line 949 "Parser.y"
               { _ulCurrentComponentFlags = 0; }
#line 3413 "Parser.cpp"
    break;

  case 129: /* component_flags: k_editor  */
#line 958 "Parser.y"
               { _ulCurrentComponentFlags |= CF_EDITOR; }
#line 3419 "Parser.cpp"
    break;

  case 130: /* function_list: %empty  */
#line 965 "Parser.y"
    { yyval = "";}
#line 3425 "Parser.cpp"
    break;

  case 131: /* function_list: function_list function_implementation  */
#line 966 "Parser.y"
                                          {yyval = yyvsp[-1]+yyvsp[0];}
#line 3431 "Parser.cpp"
    break;

  case 132: /* function_implementation: opt_export opt_virtual return_type opt_tilde identifier '(' parameters_list ')' opt_const '{' statements '}' opt_semicolon  */
#line 971 "Parser.y"
                                   {
    char *strReturnType = yyvsp[-10].strString;
    char *strFunctionHeader = (yyvsp[-9]+yyvsp[-8]+yyvsp[-7]+yyvsp[-6]+yyvsp[-5]+yyvsp[-4]).strString;
    char *strFunctionBody = (yyvsp[-3]+yyvsp[-2]+yyvsp[-1]).strString;
    if (strcmp(yyvsp[-8].strString, _strCurrentClass)==0) {
      if (strcmp(strReturnType+strlen(strReturnType)-4, "void")==0 ) {
        strReturnType = "";
      } else {
        yyerror("use 'void' as return type for constructors");
      }
    }
    fprintf(_fDeclaration, " %s %s %s %s;\n", 
      yyvsp[-12].strString, yyvsp[-11].strString, strReturnType, strFunctionHeader);
    fprintf(_fImplementation, "%s %s::%s %s\n", 
      strReturnType, _strCurrentClass, strFunctionHeader, strFunctionBody);
  }
#line 3452 "Parser.cpp"
    break;

  case 133: /* opt_tilde: %empty  */
#line 989 "Parser.y"
    { yyval = "";}
#line 3458 "Parser.cpp"
    break;

  case 134: /* opt_tilde: '~'  */
#line 990 "Parser.y"
        { yyval = " ~ "; }
#line 3464 "Parser.cpp"
    break;

  case 135: /* opt_export: %empty  */
#line 994 "Parser.y"
    { yyval = "";}
#line 3470 "Parser.cpp"
    break;

  case 136: /* opt_export: k_export  */
#line 995 "Parser.y"
             { 
    if (_bClassIsExported) {
      yyval = ""; 
    } else {
      yyval = " DECL_DLL "; 
    }
  }
#line 3482 "Parser.cpp"
    break;

  case 137: /* opt_const: %empty  */
#line 1005 "Parser.y"
    { yyval = "";}
#line 3488 "Parser.cpp"
    break;

  case 138: /* opt_const: k_const  */
#line 1006 "Parser.y"
            { yyval = yyvsp[0]; }
#line 3494 "Parser.cpp"
    break;

  case 139: /* opt_virtual: %empty  */
#line 1009 "Parser.y"
    { yyval = "";}
#line 3500 "Parser.cpp"
    break;

  case 140: /* opt_virtual: k_virtual  */
#line 1010 "Parser.y"
              { yyval = yyvsp[0]; }
#line 3506 "Parser.cpp"
    break;

  case 143: /* parameters_list: %empty  */
#line 1017 "Parser.y"
    { yyval = "";}
#line 3512 "Parser.cpp"
    break;

  case 147: /* non_void_parameters_list: non_void_parameters_list ',' parameter_declaration  */
#line 1023 "Parser.y"
                                                       {yyval = yyvsp[-2]+yyvsp[-1]+yyvsp[0];}
#line 3518 "Parser.cpp"
    break;

  case 148: /* parameter_declaration: any_type identifier  */
#line 1026 "Parser.y"
                        { yyval=yyvsp[-1]+" "+yyvsp[0]; }
#line 3524 "Parser.cpp"
    break;

  case 153: /* any_type: k_enum identifier  */
#line 1037 "Parser.y"
                      { yyval=yyvsp[-1]+" "+yyvsp[0]; }
#line 3530 "Parser.cpp"
    break;

  case 154: /* any_type: any_type '*'  */
#line 1038 "Parser.y"
                 { yyval=yyvsp[-1]+" "+yyvsp[0]; }
#line 3536 "Parser.cpp"
    break;

  case 155: /* any_type: any_type '&'  */
#line 1039 "Parser.y"
                 { yyval=yyvsp[-1]+" "+yyvsp[0]; }
#line 3542 "Parser.cpp"
    break;

  case 156: /* any_type: k_void '*'  */
#line 1040 "Parser.y"
               { yyval=yyvsp[-1]+" "+yyvsp[0]; }
#line 3548 "Parser.cpp"
    break;

  case 157: /* any_type: k_const any_type  */
#line 1041 "Parser.y"
                     { yyval=yyvsp[-1]+" "+yyvsp[0]; }
#line 3554 "Parser.cpp"
    break;

  case 158: /* any_type: k_inline any_type  */
#line 1042 "Parser.y"
                      { yyval=yyvsp[-1]+" "+yyvsp[0]; }
#line 3560 "Parser.cpp"
    break;

  case 159: /* any_type: k_static any_type  */
#line 1043 "Parser.y"
                      { yyval=yyvsp[-1]+" "+yyvsp[0]; }
#line 3566 "Parser.cpp"
    break;

  case 160: /* any_type: k_class any_type  */
#line 1044 "Parser.y"
                     { yyval=yyvsp[-1]+" "+yyvsp[0]; }
#line 3572 "Parser.cpp"
    break;

  case 161: /* any_type: identifier '<' any_type '>'  */
#line 1045 "Parser.y"
                                { yyval=yyvsp[-3]+" "+yyvsp[-2]+" "+yyvsp[-1]+" "+yyvsp[0]; }
#line 3578 "Parser.cpp"
    break;

  case 162: /* procedure_list: %empty  */
#line 1053 "Parser.y"
    { yyval = "";}
#line 3584 "Parser.cpp"
    break;

  case 163: /* procedure_list: procedure_list procedure_implementation  */
#line 1054 "Parser.y"
                                            {yyval = yyvsp[-1]+yyvsp[0];}
#line 3590 "Parser.cpp"
    break;

  case 164: /* opt_override: %empty  */
#line 1058 "Parser.y"
    { yyval = "-1"; }
#line 3596 "Parser.cpp"
    break;

  case 165: /* opt_override: ':' identifier ':' ':' identifier  */
#line 1059 "Parser.y"
                                      {
    yyval = SType("STATE_")+yyvsp[-3]+"_"+yyvsp[0];
  }
#line 3604 "Parser.cpp"
    break;

  case 166: /* $@16: %empty  */
#line 1065 "Parser.y"
                                                        {
    char *strProcedureName = yyvsp[-4].strString;
    char strInputEventType[80];
    char strInputEventName[80];
    sscanf(yyvsp[-2].strString, "%s %s", strInputEventType, strInputEventName);

    char strStateID[256];
    char *strBaseStateID = "-1";
    if(strcmp(RemoveLineDirective(strProcedureName), "Main")==0){
      strcpy(strStateID, "1");
      if(strncmp(strInputEventType, "EVoid", 4)!=0 && _strCurrentThumbnail[2]!=0) {
        yyerror("procedure 'Main' can take input parameters only in classes without thumbnails");
      }
    } else {
      sprintf(strStateID, "0x%08x", CreateID());
    }

    sprintf(_strCurrentStateID, "STATE_%s_%s", 
      _strCurrentClass, RemoveLineDirective(strProcedureName));
    fprintf(_fDeclaration, "#define  %s %s\n", _strCurrentStateID, strStateID);
    AddHandlerFunction(strProcedureName, strStateID, yyvsp[0].strString);
    fprintf(_fImplementation, 
      "BOOL %s::%s(const CEntityEvent &__eeInput) {\n#undef STATE_CURRENT\n#define STATE_CURRENT %s\n", 
      _strCurrentClass, strProcedureName, _strCurrentStateID);
    fprintf(_fImplementation, 
      "\tASSERTMSG(__eeInput.ee_slEvent==EVENTCODE_%s, \"%s::%s expects '%s' as input!\");",
      strInputEventType, _strCurrentClass, RemoveLineDirective(strProcedureName), 
      strInputEventType);
    fprintf(_fImplementation, "\tconst %s &%s = (const %s &)__eeInput;",
      strInputEventType, strInputEventName, strInputEventType);

  }
#line 3641 "Parser.cpp"
    break;

  case 167: /* procedure_implementation: identifier '(' event_specification ')' opt_override $@16 '{' statements '}' opt_semicolon  */
#line 1096 "Parser.y"
                                     {
    char *strFunctionBody = yyvsp[-2].strString;
    fprintf(_fImplementation, "%s ASSERT(FALSE); return TRUE;};", strFunctionBody);
  }
#line 3650 "Parser.cpp"
    break;

  case 168: /* event_specification: %empty  */
#line 1103 "Parser.y"
    {
    yyval="EVoid e";
  }
#line 3658 "Parser.cpp"
    break;

  case 169: /* event_specification: identifier  */
#line 1106 "Parser.y"
               {
    yyval=yyvsp[0]+" e";
  }
#line 3666 "Parser.cpp"
    break;

  case 170: /* event_specification: identifier identifier  */
#line 1109 "Parser.y"
                          {
    yyval=yyvsp[-1]+" "+yyvsp[0];
  }
#line 3674 "Parser.cpp"
    break;

  case 176: /* expression: identifier  */
#line 1116 "Parser.y"
               {yyval = yyvsp[0] + " ";}
#line 3680 "Parser.cpp"
    break;

  case 197: /* expression: '(' ')'  */
#line 1119 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3686 "Parser.cpp"
    break;

  case 198: /* expression: '+' '+'  */
#line 1120 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3692 "Parser.cpp"
    break;

  case 199: /* expression: '-' '-'  */
#line 1121 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3698 "Parser.cpp"
    break;

  case 200: /* expression: '-' '>'  */
#line 1122 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3704 "Parser.cpp"
    break;

  case 201: /* expression: ':' ':'  */
#line 1123 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3710 "Parser.cpp"
    break;

  case 202: /* expression: '&' '&'  */
#line 1124 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3716 "Parser.cpp"
    break;

  case 203: /* expression: '|' '|'  */
#line 1125 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3722 "Parser.cpp"
    break;

  case 204: /* expression: '^' '^'  */
#line 1126 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3728 "Parser.cpp"
    break;

  case 205: /* expression: '>' '>'  */
#line 1127 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3734 "Parser.cpp"
    break;

  case 206: /* expression: '<' '<'  */
#line 1128 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3740 "Parser.cpp"
    break;

  case 207: /* expression: '=' '='  */
#line 1129 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3746 "Parser.cpp"
    break;

  case 208: /* expression: '!' '='  */
#line 1130 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3752 "Parser.cpp"
    break;

  case 209: /* expression: '>' '='  */
#line 1131 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3758 "Parser.cpp"
    break;

  case 210: /* expression: '<' '='  */
#line 1132 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3764 "Parser.cpp"
    break;

  case 211: /* expression: '&' '='  */
#line 1133 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3770 "Parser.cpp"
    break;

  case 212: /* expression: '|' '='  */
#line 1134 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3776 "Parser.cpp"
    break;

  case 213: /* expression: '^' '='  */
#line 1135 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3782 "Parser.cpp"
    break;

  case 214: /* expression: '+' '='  */
#line 1136 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3788 "Parser.cpp"
    break;

  case 215: /* expression: '-' '='  */
#line 1137 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3794 "Parser.cpp"
    break;

  case 216: /* expression: '/' '='  */
#line 1138 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3800 "Parser.cpp"
    break;

  case 217: /* expression: '%' '='  */
#line 1139 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3806 "Parser.cpp"
    break;

  case 218: /* expression: '*' '='  */
#line 1140 "Parser.y"
            {yyval=yyvsp[-1]+yyvsp[0];}
#line 3812 "Parser.cpp"
    break;

  case 219: /* expression: '>' '>' '='  */
#line 1141 "Parser.y"
                {yyval=yyvsp[-2]+yyvsp[-1]+yyvsp[0];}
#line 3818 "Parser.cpp"
    break;

  case 220: /* expression: '<' '<' '='  */
#line 1142 "Parser.y"
                {yyval=yyvsp[-2]+yyvsp[-1]+yyvsp[0];}
#line 3824 "Parser.cpp"
    break;

  case 221: /* expression: '(' expression ')'  */
#line 1143 "Parser.y"
                       {yyval = yyvsp[-2]+yyvsp[-1]+yyvsp[0];}
#line 3830 "Parser.cpp"
    break;

  case 222: /* expression: expression expression  */
#line 1144 "Parser.y"
                          {yyval = yyvsp[-1]+" "+yyvsp[0];}
#line 3836 "Parser.cpp"
    break;

  case 254: /* case_constant_expression: identifier  */
#line 1157 "Parser.y"
               {yyval = yyvsp[0] + " ";}
#line 3842 "Parser.cpp"
    break;

  case 255: /* statements: %empty  */
#line 1164 "Parser.y"
    { yyval = "";}
#line 3848 "Parser.cpp"
    break;

  case 256: /* statements: statements statement  */
#line 1165 "Parser.y"
                         { yyval = yyvsp[-1]+yyvsp[0]; }
#line 3854 "Parser.cpp"
    break;

  case 257: /* statement: expression ';'  */
#line 1168 "Parser.y"
                   {yyval=yyvsp[-1]+yyvsp[0];}
#line 3860 "Parser.cpp"
    break;

  case 258: /* statement: k_switch '(' expression ')' '{' statements '}'  */
#line 1169 "Parser.y"
                                                   {yyval=yyvsp[-6]+yyvsp[-5]+yyvsp[-4]+yyvsp[-3]+yyvsp[-2]+yyvsp[-1]+yyvsp[0];}
#line 3866 "Parser.cpp"
    break;

  case 259: /* statement: k_case case_constant_expression ':'  */
#line 1170 "Parser.y"
                                        {yyval=yyvsp[-2]+" "+yyvsp[-1]+yyvsp[0]+" ";}
#line 3872 "Parser.cpp"
    break;

  case 260: /* statement: '{' statements '}'  */
#line 1171 "Parser.y"
                       {yyval=yyvsp[-2]+yyvsp[-1]+yyvsp[0];}
#line 3878 "Parser.cpp"
    break;

  case 261: /* statement: expression '{' statements '}'  */
#line 1172 "Parser.y"
                                  {yyval=yyvsp[-3]+yyvsp[-2]+yyvsp[-1]+yyvsp[0];}
#line 3884 "Parser.cpp"
    break;

  case 278: /* statement_if: k_if '(' expression ')' '{' statements '}'  */
#line 1193 "Parser.y"
                                               {
    if (yyvsp[-1].bCrossesStates) {
      char strAfterIfName[80], strAfterIfID[11];
      CreateInternalHandlerFunction(strAfterIfName, strAfterIfID);
      yyval = yyvsp[-6]+"(!"+yyvsp[-5]+yyvsp[-4]+yyvsp[-3]+"){ Jump(STATE_CURRENT,"+strAfterIfID+", FALSE, EInternal());return TRUE;}"+yyvsp[-1]+
        "Jump(STATE_CURRENT,"+strAfterIfID+", FALSE, EInternal());return TRUE;}"+
        "BOOL "+_strCurrentClass+"::"+strAfterIfName+"(const CEntityEvent &__eeInput){"+
        "\nASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);"+
        "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+strAfterIfID+"\n";
    } else {
      yyval = yyvsp[-6]+yyvsp[-5]+yyvsp[-4]+yyvsp[-3]+yyvsp[-2]+yyvsp[-1]+yyvsp[0];
    }
  }
#line 3902 "Parser.cpp"
    break;

  case 279: /* statement_if_else: k_if '(' expression ')' '{' statements '}' k_else statement  */
#line 1209 "Parser.y"
                                                                {
    if (yyvsp[-3].bCrossesStates || yyvsp[0].bCrossesStates) {
      char strAfterIfName[80], strAfterIfID[11];
      char strElseName[80], strElseID[11];
      CreateInternalHandlerFunction(strAfterIfName, strAfterIfID);
      CreateInternalHandlerFunction(strElseName, strElseID);
      yyval = yyvsp[-8]+"(!"+yyvsp[-7]+yyvsp[-6]+yyvsp[-5]+"){ Jump(STATE_CURRENT,"+strElseID+", FALSE, EInternal());return TRUE;}"+
        yyvsp[-3]+"Jump(STATE_CURRENT,"+strAfterIfID+", FALSE, EInternal());return TRUE;}"+
        "BOOL "+_strCurrentClass+"::"+strElseName+"(const CEntityEvent &__eeInput){"+
        "\nASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);"+
        "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+strElseID+"\n"+
        yyvsp[0]+"Jump(STATE_CURRENT,"+strAfterIfID+", FALSE, EInternal());return TRUE;}\n"+
        "BOOL "+_strCurrentClass+"::"+strAfterIfName+"(const CEntityEvent &__eeInput){"+
        "\nASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);"+
        "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+strAfterIfID+"\n";
    } else {
      yyval = yyvsp[-8]+yyvsp[-7]+yyvsp[-6]+yyvsp[-5]+yyvsp[-4]+yyvsp[-3]+yyvsp[-2]+yyvsp[-1]+" "+yyvsp[0];
    }
  }
#line 3926 "Parser.cpp"
    break;

  case 280: /* $@17: %empty  */
#line 1231 "Parser.y"
                               {
    if (strlen(_strInLoopName)>0) {
      yyerror("Nested loops are not implemented yet");
    }
  }
#line 3936 "Parser.cpp"
    break;

  case 281: /* statement_while: k_while '(' expression ')' $@17 '{' statements '}'  */
#line 1235 "Parser.y"
                       {
    if (yyvsp[-1].bCrossesStates) {
      CreateInternalHandlerFunction(_strInLoopName, _strInLoopID);
      CreateInternalHandlerFunction(_strAfterLoopName, _strAfterLoopID);
      yyval = SType(GetLineDirective(yyvsp[-7]))+"Jump(STATE_CURRENT,"+_strInLoopID+", FALSE, EInternal());return TRUE;}"+
        "BOOL "+_strCurrentClass+"::"+_strInLoopName+"(const CEntityEvent &__eeInput)"+yyvsp[-2]+
        "\nASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);"+
        "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strInLoopID+"\n"+
        "if(!"+yyvsp[-6]+yyvsp[-5]+yyvsp[-4]+"){ Jump(STATE_CURRENT,"+_strAfterLoopID+", FALSE, EInternal());return TRUE;}"+
        yyvsp[-1]+"Jump(STATE_CURRENT,"+_strInLoopID+", FALSE, EInternal());return TRUE;"+yyvsp[0]+
        "BOOL "+_strCurrentClass+"::"+_strAfterLoopName+"(const CEntityEvent &__eeInput) {"+
        "\nASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);"+
        "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strAfterLoopID+"\n";
    } else {
      yyval = yyvsp[-7]+yyvsp[-6]+yyvsp[-5]+yyvsp[-4]+yyvsp[-2]+yyvsp[-1]+yyvsp[0];
    } 
    _strInLoopName[0] = 0;
  }
#line 3959 "Parser.cpp"
    break;

  case 282: /* $@18: %empty  */
#line 1256 "Parser.y"
                            {
    if (strlen(_strInLoopName)>0) {
      yyerror("Nested loops are not implemented yet");
    }
    _strInLoopName[0] = 0;
  }
#line 3970 "Parser.cpp"
    break;

  case 283: /* statement_dowhile: k_do '{' statements '}' $@18 k_while '(' expression ')' ';'  */
#line 1261 "Parser.y"
                                   {
    if (yyvsp[-7].bCrossesStates) {
      CreateInternalHandlerFunction(_strInLoopName, _strInLoopID);
      CreateInternalHandlerFunction(_strAfterLoopName, _strAfterLoopID);
      yyval = SType(GetLineDirective(yyvsp[-9]))+"Jump(STATE_CURRENT,"+_strInLoopID+", FALSE, EInternal());return TRUE;}"+
        "BOOL "+_strCurrentClass+"::"+_strInLoopName+"(const CEntityEvent &__eeInput)"+yyvsp[-8]+
        "\nASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);"+
        "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strInLoopID+"\n"+yyvsp[-7]+
        "if(!"+yyvsp[-3]+yyvsp[-2]+yyvsp[-1]+"){ Jump(STATE_CURRENT,"+_strAfterLoopID+", FALSE, EInternal());return TRUE;}"+
        "Jump(STATE_CURRENT,"+_strInLoopID+", FALSE, EInternal());return TRUE;"+yyvsp[-6]+
        "BOOL "+_strCurrentClass+"::"+_strAfterLoopName+"(const CEntityEvent &__eeInput) {"+
        "\nASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);"+
        "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strAfterLoopID+"\n";
    } else {
      yyval = yyvsp[-9]+yyvsp[-8]+yyvsp[-7]+yyvsp[-6]+yyvsp[-4]+yyvsp[-3]+yyvsp[-2]+yyvsp[-1]+yyvsp[0];
    } 
    _strInLoopName[0] = 0;
  }
#line 3993 "Parser.cpp"
    break;

  case 284: /* $@19: %empty  */
#line 1282 "Parser.y"
                                                           {
    if (strlen(_strInLoopName)>0) {
      yyerror("Nested loops are not implemented yet");
    }
  }
#line 4003 "Parser.cpp"
    break;

  case 285: /* statement_for: k_for '(' expression ';' expression ';' expression ')' $@19 '{' statements '}'  */
#line 1286 "Parser.y"
                       {
    if (yyvsp[-1].bCrossesStates) {
      CreateInternalHandlerFunction(_strInLoopName, _strInLoopID);
      CreateInternalHandlerFunction(_strAfterLoopName, _strAfterLoopID);
      yyerror("For loops across states are not supported");
    } else {
      yyval = yyvsp[-11]+yyvsp[-10]+yyvsp[-9]+yyvsp[-8]+yyvsp[-7]+yyvsp[-6]+yyvsp[-5]+yyvsp[-4]+yyvsp[-2]+yyvsp[-1]+yyvsp[0];
    } 
    _strInLoopName[0] = 0;
  }
#line 4018 "Parser.cpp"
    break;

  case 286: /* $@20: %empty  */
#line 1299 "Parser.y"
                           {
      if (!_bInProcedure) {
        yyerror("Cannot have 'wait' in functions");
      }
      CreateInternalHandlerFunction(_strInWaitName, _strInWaitID);
      CreateInternalHandlerFunction(_strAfterWaitName, _strAfterWaitID);
      _bHasOtherwise = 0;
      _bInHandler = 1;
  }
#line 4032 "Parser.cpp"
    break;

  case 287: /* statement_wait: k_wait wait_expression $@20 '{' handlers_list '}'  */
#line 1307 "Parser.y"
                          {
    if (yyvsp[-1].bCrossesStates) {
      yyerror("'wait' statements must not be nested");
      yyval = "";
    } else {
      SType stDefault;
      if (!_bHasOtherwise) {
        stDefault = SType("default: return FALSE; break;");
      } else {
        stDefault = SType("");
      }

      yyval = SType(GetLineDirective(yyvsp[-5]))+yyvsp[-4]+";\n"+
        "Jump(STATE_CURRENT, "+_strInWaitID+", FALSE, EBegin());return TRUE;}"+
        "BOOL "+_strCurrentClass+"::"+_strInWaitName+"(const CEntityEvent &__eeInput) {"+
        "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strInWaitID+"\n"+
        "switch(__eeInput.ee_slEvent)"+yyvsp[-2]+yyvsp[-1]+stDefault+yyvsp[0]+
        "return TRUE;}BOOL "+_strCurrentClass+"::"+_strAfterWaitName+"(const CEntityEvent &__eeInput){"+
        "\nASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);"+
        "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strAfterWaitID+"\n";
      yyval.bCrossesStates = 1;
      _bInHandler = 0;
    }
  }
#line 4061 "Parser.cpp"
    break;

  case 288: /* statement_autowait: k_autowait wait_expression ';'  */
#line 1333 "Parser.y"
                                   {
    if (!_bInProcedure) {
      yyerror("Cannot have 'autowait' in functions");
    }
    CreateInternalHandlerFunction(_strInWaitName, _strInWaitID);
    CreateInternalHandlerFunction(_strAfterWaitName, _strAfterWaitID);
    _bHasOtherwise = 0;

    yyval = SType(GetLineDirective(yyvsp[-2]))+yyvsp[-1]+";\n"+
      "Jump(STATE_CURRENT, "+_strInWaitID+", FALSE, EBegin());return TRUE;}"+
      "BOOL "+_strCurrentClass+"::"+_strInWaitName+"(const CEntityEvent &__eeInput) {"+
      "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strInWaitID+"\n"+
      "switch(__eeInput.ee_slEvent) {"+
      "case EVENTCODE_EBegin: return TRUE;"+
      "case EVENTCODE_ETimer: Jump(STATE_CURRENT,"+_strAfterWaitID+", FALSE, EInternal()); return TRUE;"+
      "default: return FALSE; }}"+
      "BOOL "+_strCurrentClass+"::"+_strAfterWaitName+"(const CEntityEvent &__eeInput){"+
      "\nASSERT(__eeInput.ee_slEvent==EVENTCODE_EInternal);"+
      "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strAfterWaitID+"\n"+yyvsp[0];
    yyval.bCrossesStates = 1;
  }
#line 4087 "Parser.cpp"
    break;

  case 289: /* statement_waitevent: k_waitevent wait_expression identifier opt_eventvar ';'  */
#line 1357 "Parser.y"
                                                            {
    if (!_bInProcedure) {
      yyerror("Cannot have 'autocall' in functions");
    }
    CreateInternalHandlerFunction(_strInWaitName, _strInWaitID);
    CreateInternalHandlerFunction(_strAfterWaitName, _strAfterWaitID);
    _bHasOtherwise = 0;

    yyval = SType(GetLineDirective(yyvsp[-4]))+yyvsp[-3]+";\n"+
      "Jump(STATE_CURRENT, "+_strInWaitID+", FALSE, EBegin());return TRUE;}"+
      "BOOL "+_strCurrentClass+"::"+_strInWaitName+"(const CEntityEvent &__eeInput) {"+
      "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strInWaitID+"\n"+
      "switch(__eeInput.ee_slEvent) {"+
      "case EVENTCODE_EBegin: return TRUE;"+
      "case EVENTCODE_"+yyvsp[-2]+": Jump(STATE_CURRENT,"+_strAfterWaitID+", FALSE, __eeInput); return TRUE;"+
      "default: return FALSE; }}"+
      "BOOL "+_strCurrentClass+"::"+_strAfterWaitName+"(const CEntityEvent &__eeInput){"+
      "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strAfterWaitID+"\n"+
      "const "+yyvsp[-2]+"&"+yyvsp[-1]+"= ("+yyvsp[-2]+"&)__eeInput;\n"+yyvsp[0];
    yyval.bCrossesStates = 1;
  }
#line 4113 "Parser.cpp"
    break;

  case 290: /* opt_eventvar: %empty  */
#line 1382 "Parser.y"
    {
    yyval = SType("__e");
  }
#line 4121 "Parser.cpp"
    break;

  case 291: /* opt_eventvar: identifier  */
#line 1385 "Parser.y"
               {
    yyval = yyvsp[0];
  }
#line 4129 "Parser.cpp"
    break;

  case 292: /* statement_autocall: k_autocall jumptarget '(' event_expression ')' identifier opt_eventvar ';'  */
#line 1390 "Parser.y"
                                                                               {
    if (!_bInProcedure) {
      yyerror("Cannot have 'autocall' in functions");
    }
    CreateInternalHandlerFunction(_strInWaitName, _strInWaitID);
    CreateInternalHandlerFunction(_strAfterWaitName, _strAfterWaitID);
    _bHasOtherwise = 0;

    yyval = SType(GetLineDirective(yyvsp[-7]))+yyvsp[-6]+";\n"+
      "Jump(STATE_CURRENT, "+_strInWaitID+", FALSE, EBegin());return TRUE;}"+
      "BOOL "+_strCurrentClass+"::"+_strInWaitName+"(const CEntityEvent &__eeInput) {"+
      "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strInWaitID+"\n"+
      "switch(__eeInput.ee_slEvent) {"+
      "case EVENTCODE_EBegin: Call"+yyvsp[-5]+"STATE_CURRENT, "+yyvsp[-6]+", "+yyvsp[-4]+yyvsp[-3]+";return TRUE;"+
      "case EVENTCODE_"+yyvsp[-2]+": Jump(STATE_CURRENT,"+_strAfterWaitID+", FALSE, __eeInput); return TRUE;"+
      "default: return FALSE; }}"+
      "BOOL "+_strCurrentClass+"::"+_strAfterWaitName+"(const CEntityEvent &__eeInput){"+
      "\n#undef STATE_CURRENT\n#define STATE_CURRENT "+_strAfterWaitID+"\n"+
      "const "+yyvsp[-2]+"&"+yyvsp[-1]+"= ("+yyvsp[-2]+"&)__eeInput;\n"+yyvsp[0];
    yyval.bCrossesStates = 1;
  }
#line 4155 "Parser.cpp"
    break;

  case 293: /* wait_expression: '(' ')'  */
#line 1414 "Parser.y"
            {
    yyval = SType("SetTimerAt(THINKTIME_NEVER)"); 
  }
#line 4163 "Parser.cpp"
    break;

  case 294: /* wait_expression: '(' expression ')'  */
#line 1417 "Parser.y"
                       {
    yyval = SType("SetTimerAfter")+yyvsp[-2]+yyvsp[-1]+yyvsp[0]; 
  }
#line 4171 "Parser.cpp"
    break;

  case 295: /* statement_jump: k_jump jumptarget '(' event_expression ')' ';'  */
#line 1423 "Parser.y"
                                                   {
    if (!_bInProcedure) {
      yyerror("Cannot have 'jump' in functions");
    }
    yyval = SType(GetLineDirective(yyvsp[-5]))+"Jump"+yyvsp[-3]+"STATE_CURRENT, "+yyvsp[-4]+", "+yyvsp[-2]+yyvsp[-1]+";return TRUE;";
  }
#line 4182 "Parser.cpp"
    break;

  case 296: /* statement_call: k_call jumptarget '(' event_expression ')' ';'  */
#line 1432 "Parser.y"
                                                  {
    if (!_bInProcedure) {
      yyerror("Cannot have 'call' in functions");
    }
    if (!_bInHandler) {
      yyerror("'call' must be inside a 'wait' statement");
    }
    yyval = SType(GetLineDirective(yyvsp[-5]))+"Call"+yyvsp[-3]+"STATE_CURRENT, "+yyvsp[-4]+", "+yyvsp[-2]+yyvsp[-1]+";return TRUE;";
  }
#line 4196 "Parser.cpp"
    break;

  case 297: /* event_expression: expression  */
#line 1444 "Parser.y"
               { 
    yyval = yyvsp[0];
  }
#line 4204 "Parser.cpp"
    break;

  case 298: /* event_expression: %empty  */
#line 1447 "Parser.y"
    {
    yyval = SType("EVoid()");
  }
#line 4212 "Parser.cpp"
    break;

  case 299: /* jumptarget: identifier  */
#line 1453 "Parser.y"
               {
    yyval = SType("STATE_")+_strCurrentClass+"_"+yyvsp[0]+", TRUE";
  }
#line 4220 "Parser.cpp"
    break;

  case 300: /* jumptarget: identifier ':' ':' identifier  */
#line 1456 "Parser.y"
                                  {
    yyval = SType("STATE_")+yyvsp[-3]+"_"+yyvsp[0]+", FALSE";
  }
#line 4228 "Parser.cpp"
    break;

  case 301: /* statement_stop: k_stop ';'  */
#line 1462 "Parser.y"
               {
    yyval = SType(GetLineDirective(yyvsp[-1]))+"UnsetTimer();Jump(STATE_CURRENT,"
      +_strAfterWaitID+", FALSE, EInternal());"+"return TRUE"+yyvsp[0];
  }
#line 4237 "Parser.cpp"
    break;

  case 302: /* statement_resume: k_resume ';'  */
#line 1468 "Parser.y"
                 {
    yyval = SType(GetLineDirective(yyvsp[-1]))+"return TRUE"+yyvsp[0];
  }
#line 4245 "Parser.cpp"
    break;

  case 303: /* statement_pass: k_pass ';'  */
#line 1473 "Parser.y"
               {
    yyval = SType(GetLineDirective(yyvsp[-1]))+"return FALSE"+yyvsp[0];
  }
#line 4253 "Parser.cpp"
    break;

  case 304: /* statement_return: k_return opt_expression ';'  */
#line 1478 "Parser.y"
                                {
    if (!_bInProcedure) {
      yyval = yyvsp[-2]+" "+yyvsp[-1]+yyvsp[0];
    } else {
      if (strlen(yyvsp[-1].strString)==0) {
        yyvsp[-1] = SType("EVoid()");
      }
      yyval = SType(GetLineDirective(yyvsp[-2]))
        +"Return(STATE_CURRENT,"+yyvsp[-1]+");"
        +yyvsp[-2]+" TRUE"+yyvsp[0];
    }
  }
#line 4270 "Parser.cpp"
    break;

  case 305: /* opt_expression: %empty  */
#line 1492 "Parser.y"
    {yyval = "";}
#line 4276 "Parser.cpp"
    break;

  case 307: /* handler: k_on '(' event_specification ')' ':' '{' statements '}' opt_semicolon  */
#line 1497 "Parser.y"
                                                                          {
    char strInputEventType[80];
    char strInputEventName[80];
    sscanf(yyvsp[-6].strString, "%s %s", strInputEventType, strInputEventName);

    yyval = SType("case")+yyvsp[-7]+"EVENTCODE_"+strInputEventType+yyvsp[-5]+yyvsp[-4]+yyvsp[-3]+
      "const "+strInputEventType+"&"+strInputEventName+"= ("+
      strInputEventType+"&)__eeInput;\n"+yyvsp[-2]+yyvsp[-1]+"ASSERT(FALSE);break;";
  }
#line 4290 "Parser.cpp"
    break;

  case 308: /* handler: k_otherwise '(' event_specification ')' ':' '{' statements '}' opt_semicolon  */
#line 1506 "Parser.y"
                                                                                 {
    char strInputEventType[80];
    char strInputEventName[80];
    sscanf(yyvsp[-6].strString, "%s %s", strInputEventType, strInputEventName);

    yyval = SType("default")+yyvsp[-4]+yyvsp[-3]+yyvsp[-2]+yyvsp[-1]+"ASSERT(FALSE);break;";
    _bHasOtherwise = 1;
  }
#line 4303 "Parser.cpp"
    break;

  case 309: /* handlers_list: %empty  */
#line 1516 "Parser.y"
    { yyval = "";}
#line 4309 "Parser.cpp"
    break;

  case 310: /* handlers_list: handlers_list handler  */
#line 1517 "Parser.y"
                          { yyval = yyvsp[-1]+yyvsp[0]; }
#line 4315 "Parser.cpp"
    break;


#line 4319 "Parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1520 "Parser.y"

