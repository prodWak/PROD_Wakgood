#include "WakLogger.h"

void WakLogImpl(const ELogVerbosity::Type Verbosity, const FString& Message)
{
	if (Verbosity > ELogVerbosity::Warning)
	{
		return;
	}

	if (!GEngine)
	{
		return;
	}

	if (Verbosity == ELogVerbosity::Warning)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Message);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message);
	}
}

void PROD_WAKGOOD_API WakNoLoggingImpl(const ELogVerbosity::Type Verbosity, const FString& Message)
{
	WakLogImpl(Verbosity, Message);
}

void PROD_WAKGOOD_API WakLogImpl(const FLogCategoryName CategoryName, const ELogVerbosity::Type Verbosity, const FString& Message)
{
	const FString DebugMessage = FString::Printf( TEXT("%s : %s"), *CategoryName.ToString(), *Message);
	WakLogImpl(Verbosity, DebugMessage);
}

