// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PROD_Wakgood/Game/WakLevelScript.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWakLevelScript() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_ALevelScript();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_ALevelScript_NoRegister();
	UPackage* Z_Construct_UPackage__Script_PROD_Wakgood();
// End Cross Module References
	void ALevelScript::StaticRegisterNativesALevelScript()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ALevelScript);
	UClass* Z_Construct_UClass_ALevelScript_NoRegister()
	{
		return ALevelScript::StaticClass();
	}
	struct Z_Construct_UClass_ALevelScript_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALevelScript_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_PROD_Wakgood,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALevelScript_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALevelScript_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Game/WakLevelScript.h" },
		{ "ModuleRelativePath", "Game/WakLevelScript.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALevelScript_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALevelScript>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ALevelScript_Statics::ClassParams = {
		&ALevelScript::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALevelScript_Statics::Class_MetaDataParams), Z_Construct_UClass_ALevelScript_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ALevelScript()
	{
		if (!Z_Registration_Info_UClass_ALevelScript.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALevelScript.OuterSingleton, Z_Construct_UClass_ALevelScript_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ALevelScript.OuterSingleton;
	}
	template<> PROD_WAKGOOD_API UClass* StaticClass<ALevelScript>()
	{
		return ALevelScript::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALevelScript);
	ALevelScript::~ALevelScript() {}
	struct Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakLevelScript_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakLevelScript_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ALevelScript, ALevelScript::StaticClass, TEXT("ALevelScript"), &Z_Registration_Info_UClass_ALevelScript, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALevelScript), 3655835930U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakLevelScript_h_4126427771(TEXT("/Script/PROD_Wakgood"),
		Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakLevelScript_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakLevelScript_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
