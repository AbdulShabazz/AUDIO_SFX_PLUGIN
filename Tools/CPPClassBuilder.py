from string import Template
import re

MyPyClassDeclaration = Template('''
#pragma once

// DO NOT EDIT. This class is auto-generated.
class $Class : $ColonSpacePublicFirstClass$CommaSpaceNextClass
{
$PublicColonNewlineTabReturnTypeClassNameParameterListSemiColonNewline
$PublicColonNewlineTabReturnTypeClassDestructorNameParameterListSemiColonNewline
$TabNextPublicMethodReturnTypeMethodNameParameterListSemiColonNewline
$ProtectedColonNewlineReturnTypeMethodNameParameterListSemiColonNewline
$TabNextProtectedMethodReturnTypeMethodNameParameterListSemiColonNewline
$PrivateColonNewlineReturnTypeMethodNameParameterListSemiColonNewline
$TabNextPrivateMethodReturnTypeMethodNameParameterListSemiColonNewline
};
''')

MyPyClassDefinition = Template('''
#include "$Class.h"
$NextIncludeInQuotesNewline
''')