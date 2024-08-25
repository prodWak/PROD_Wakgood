// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PROD_Wakgood/Game/WakGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWakGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWakGameModeBase();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWakGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_PROD_Wakgood();
// End Cross Module References
	void AWakGameModeBase::StaticRegisterNativesAWakGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWakGameModeBase);
	UClass* Z_Construct_UClass_AWakGameModeBase_NoRegister()
	{
		return AWakGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AWakGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWakGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_PROD_Wakgood,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWakGameModeBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWakGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Game/WakGameModeBase.h" },
		{ "ModuleRelativePath", "Game/WakGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWakGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWakGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWakGameModeBase_Statics::ClassParams = {
		&AWakGameModeBase::StaticClass,
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
		0x009002ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWakGameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AWakGameModeBase_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AWakGameModeBase()
	{
		if (!Z_Registration_Info_UClass_AWakGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWakGameModeBase.OuterSingleton, Z_Construct_UClass_AWakGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWakGameModeBase.OuterSingleton;
	}
	template<> PROD_WAKGOOD_API UClass* StaticClass<AWakGameModeBase>()
	{
		return AWakGameModeBase::StaticClass();
	}
	AWakGameModeBase::AWakGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWakGameModeBase);
	AWakGameModeBase::~AWakGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWakGameModeBase, AWakGameModeBase::StaticClass, TEXT("AWakGameModeBase"), &Z_Registration_Info_UClass_AWakGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWakGameModeBase), 4287198304U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakGameModeBase_h_4150751198(TEXT("/Script/PROD_Wakgood"),
		Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
