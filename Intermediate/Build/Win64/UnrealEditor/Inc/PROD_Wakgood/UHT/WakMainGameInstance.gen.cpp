// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PROD_Wakgood/Game/WakMainGameInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWakMainGameInstance() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_UMainGameInstance();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_UMainGameInstance_NoRegister();
	UPackage* Z_Construct_UPackage__Script_PROD_Wakgood();
// End Cross Module References
	DEFINE_FUNCTION(UMainGameInstance::execSetPlayerLastLocation)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_LocationIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetPlayerLastLocation(Z_Param_LocationIndex);
		P_NATIVE_END;
	}
	void UMainGameInstance::StaticRegisterNativesUMainGameInstance()
	{
		UClass* Class = UMainGameInstance::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetPlayerLastLocation", &UMainGameInstance::execSetPlayerLastLocation },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics
	{
		struct MainGameInstance_eventSetPlayerLastLocation_Parms
		{
			int32 LocationIndex;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_LocationIndex;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::NewProp_LocationIndex = { "LocationIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MainGameInstance_eventSetPlayerLastLocation_Parms, LocationIndex), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::NewProp_LocationIndex,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "Game Instance" },
		{ "ModuleRelativePath", "Game/WakMainGameInstance.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainGameInstance, nullptr, "SetPlayerLastLocation", nullptr, nullptr, Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::MainGameInstance_eventSetPlayerLastLocation_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::MainGameInstance_eventSetPlayerLastLocation_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMainGameInstance);
	UClass* Z_Construct_UClass_UMainGameInstance_NoRegister()
	{
		return UMainGameInstance::StaticClass();
	}
	struct Z_Construct_UClass_UMainGameInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LastLocationName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_LastLocationName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LastLocationVector_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_LastLocationVector;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMainGameInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_PROD_Wakgood,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainGameInstance_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UMainGameInstance_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UMainGameInstance_SetPlayerLastLocation, "SetPlayerLastLocation" }, // 2574572005
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainGameInstance_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainGameInstance_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Game/WakMainGameInstance.h" },
		{ "ModuleRelativePath", "Game/WakMainGameInstance.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainGameInstance_Statics::NewProp_LastLocationName_MetaData[] = {
		{ "Category", "Game Instance" },
		{ "ModuleRelativePath", "Game/WakMainGameInstance.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UMainGameInstance_Statics::NewProp_LastLocationName = { "LastLocationName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainGameInstance, LastLocationName), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainGameInstance_Statics::NewProp_LastLocationName_MetaData), Z_Construct_UClass_UMainGameInstance_Statics::NewProp_LastLocationName_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainGameInstance_Statics::NewProp_LastLocationVector_MetaData[] = {
		{ "Category", "Game Instance" },
		{ "ModuleRelativePath", "Game/WakMainGameInstance.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UMainGameInstance_Statics::NewProp_LastLocationVector = { "LastLocationVector", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainGameInstance, LastLocationVector), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainGameInstance_Statics::NewProp_LastLocationVector_MetaData), Z_Construct_UClass_UMainGameInstance_Statics::NewProp_LastLocationVector_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMainGameInstance_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainGameInstance_Statics::NewProp_LastLocationName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainGameInstance_Statics::NewProp_LastLocationVector,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMainGameInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMainGameInstance>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UMainGameInstance_Statics::ClassParams = {
		&UMainGameInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UMainGameInstance_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UMainGameInstance_Statics::PropPointers),
		0,
		0x009000A8u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainGameInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UMainGameInstance_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainGameInstance_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UMainGameInstance()
	{
		if (!Z_Registration_Info_UClass_UMainGameInstance.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMainGameInstance.OuterSingleton, Z_Construct_UClass_UMainGameInstance_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UMainGameInstance.OuterSingleton;
	}
	template<> PROD_WAKGOOD_API UClass* StaticClass<UMainGameInstance>()
	{
		return UMainGameInstance::StaticClass();
	}
	UMainGameInstance::UMainGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMainGameInstance);
	UMainGameInstance::~UMainGameInstance() {}
	struct Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakMainGameInstance_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakMainGameInstance_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UMainGameInstance, UMainGameInstance::StaticClass, TEXT("UMainGameInstance"), &Z_Registration_Info_UClass_UMainGameInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMainGameInstance), 2373226364U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakMainGameInstance_h_480230554(TEXT("/Script/PROD_Wakgood"),
		Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakMainGameInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakMainGameInstance_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
