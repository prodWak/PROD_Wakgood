// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PROD_Wakgood/TP_ThirdPerson/TP_ThirdPersonGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTP_ThirdPersonGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_ATP_ThirdPersonGameMode();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_ATP_ThirdPersonGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_PROD_Wakgood();
// End Cross Module References
	void ATP_ThirdPersonGameMode::StaticRegisterNativesATP_ThirdPersonGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATP_ThirdPersonGameMode);
	UClass* Z_Construct_UClass_ATP_ThirdPersonGameMode_NoRegister()
	{
		return ATP_ThirdPersonGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ATP_ThirdPersonGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATP_ThirdPersonGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_PROD_Wakgood,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATP_ThirdPersonGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATP_ThirdPersonGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "TP_ThirdPerson/TP_ThirdPersonGameMode.h" },
		{ "ModuleRelativePath", "TP_ThirdPerson/TP_ThirdPersonGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATP_ThirdPersonGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATP_ThirdPersonGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATP_ThirdPersonGameMode_Statics::ClassParams = {
		&ATP_ThirdPersonGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATP_ThirdPersonGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ATP_ThirdPersonGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ATP_ThirdPersonGameMode()
	{
		if (!Z_Registration_Info_UClass_ATP_ThirdPersonGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATP_ThirdPersonGameMode.OuterSingleton, Z_Construct_UClass_ATP_ThirdPersonGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATP_ThirdPersonGameMode.OuterSingleton;
	}
	template<> PROD_WAKGOOD_API UClass* StaticClass<ATP_ThirdPersonGameMode>()
	{
		return ATP_ThirdPersonGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATP_ThirdPersonGameMode);
	ATP_ThirdPersonGameMode::~ATP_ThirdPersonGameMode() {}
	struct Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_TP_ThirdPerson_TP_ThirdPersonGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_TP_ThirdPerson_TP_ThirdPersonGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATP_ThirdPersonGameMode, ATP_ThirdPersonGameMode::StaticClass, TEXT("ATP_ThirdPersonGameMode"), &Z_Registration_Info_UClass_ATP_ThirdPersonGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATP_ThirdPersonGameMode), 2533510780U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_TP_ThirdPerson_TP_ThirdPersonGameMode_h_1253347546(TEXT("/Script/PROD_Wakgood"),
		Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_TP_ThirdPerson_TP_ThirdPersonGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_TP_ThirdPerson_TP_ThirdPersonGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
