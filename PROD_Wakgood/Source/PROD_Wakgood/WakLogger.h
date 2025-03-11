#pragma once

#include "Logging/LogMacros.h"

void PROD_WAKGOOD_API WakNoLoggingImpl(const ELogVerbosity::Type Verbosity, const FString& Message);
void PROD_WAKGOOD_API WakLogImpl(const FLogCategoryName CategoryName, const ELogVerbosity::Type Verbosity, const FString& Message);

#if NO_LOGGING
#define WAK_LOG(CategoryName, Verbosity, Format, ...) \
{ \
UE_LOG(CategoryName, Verbosity, Format, ##__VA_ARGS__); \
WakNoLoggingImpl(ELogVerbosity::Verbosity, FString::Printf(Format, ##__VA_ARGS__)); \
}
#else
#define WAK_LOG(CategoryName, Verbosity, Format, ...) \
{ \
UE_LOG(CategoryName, Verbosity, Format, ##__VA_ARGS__); \
WakLogImpl(CategoryName.GetCategoryName(), ELogVerbosity::Verbosity, FString::Printf(Format, ##__VA_ARGS__)); \
}
#endif