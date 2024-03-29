#pragma once

namespace RegexPatterns
{
constexpr const char* SZ_RGX_FUNCTION_HEADER_INFORMATION =
R"((?:^[ \t]*\/\/\s*\^\^x\n[ \t]*\/\/.*\n[ \t]*\/\/\s*3([a-zA-Z_]{2,3})\s+([a-zA-Z0-9\_\-\. \t]+)\n(?:[\/\/a-zA-Z0-9\_\-\.\(\) \t\n]+)?)?)";

constexpr const char* SZ_RGX_GLOBAL_FUNCTION_HEADER =
R"(^[ \t]*(?:static\s+)?(?:inline\s+)?(?:constexpr\s+)?([\w\:\<\>\:\,\*\&]{1,})(?:[\s\*\&]+)?\s+([\w]{3,})\s*\(\s*([\w\t \.\-\:\<\>\,\*\&\/'\"\;\[\]\n]+)?\s*\)[\t ]*$)";

constexpr const char* SZ_RGX_MEMBER_FUNCTION_HEADER =
R"(^[ \t]*(?:inline\s+)?(?:([\w\:\<\>\,\*\&]{3,})(?:[\s\*\&]+)?\s+)?([\w\:\<\>\,\t ]+)::(\~)?([\w]+(?:[\t \W]{0,4})?)\s*\(\s*([\w\t \.\-\:\<\>\,\*\&\/\=\'\"\;\n]+)?\s*\)\s*(?:const)?(?:\:)?[ \t]*$)";

constexpr const char* SZ_RGX_COMMENT_SINGLELINE_DOTS =
R"(\/{2,}\*+$)";

constexpr const char* SZ_RGX_COMMENT_SINGLELINE =
R"((?:\/\/.*))";

constexpr const char* SZ_RGX_DIRECTIVE_INCLUDE =
R"(^[\t ]*#include\s+(?:\"|\<)[\w\.]+(?:\"|\>)$)";

constexpr const char* SZ_RGX_MACRO_IMPLEMENT_DYNAMIC =
R"(^[\t ]*IMPLEMENT_DYNAMIC\s*\(.*\)$)";

constexpr const char* SZ_RGX_MACRO_IMPLEMENT_DYNCREATE =
R"(^[\t ]*IMPLEMENT_DYNCREATE\s*\(.*\)$)";

constexpr const char* SZ_RGX_STRUCT_TYPE_DECLARATION =
R"((?:const)?\s+struct\s+\w+[*]+)";

constexpr const char* SZ_RGX_MEMBER_DATA_LIST_INITIALIZATION =
R"(^[\t ]*(?:\:\s*)?(?:\w{3,}[\{\(].*[\}\)](?:\,)?)$)";

constexpr const char* SZ_RGX_VARIABLE =
R"(^[\t ]*((?:static\s+)?(?:constexpr\s+)?(?:const\s+)?(?:\w+::)*(?!(?:return|delete|using|enum|friend|extern|struct|class))(?:unsigned\s+|signed\s+)?\w{3,}(?: \w{3,}){0,1}(?:\<.*\>)?)([*&]+)?\s+(\w+)\s*(\[.*\])?(?:\s*(?:=\s*.*?)|(?:\{.*\}|\(.*\)|(?:\[.*\])))?;[\t ]*$)";

constexpr const char* SZ_RGX_MEMBER_VARIABLE =
R"(^[\t ]*((?:static\s+)?(?:constexpr\s+)?(?:const\s+)?(?:\w+::)*(?!(?:return|delete|using|enum|friend|extern|struct|class))(?:unsigned\s+|signed\s+)?\w{3,}(?: \w{3,}){0,1}(?:\<.*\>)?)([*&]+)?\s+(\w+)\s*(\[.*\])?(\{.*\})?;[\t ]*$)";

constexpr const char* SZ_RGX_OPTIONAL_ARG_SHORT =
R"(\-(\w{0,3})\s+(\w+))";

constexpr const char* SZ_RGX_OPTIONAL_ARG_EXTENDED =
R"(\-\-(\w+(?:\-\w+)*)\s+(\w+))";
};
