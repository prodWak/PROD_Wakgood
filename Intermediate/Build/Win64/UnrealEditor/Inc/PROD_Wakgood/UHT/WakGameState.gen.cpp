// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PROD_Wakgood/Game/WakGameState.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWakGameState() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameState();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWakGameState();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWakGameState_NoRegister();
	UPackage* Z_Construct_UPackage__Script_PROD_Wakgood();
// End Cross Module References
	void AWakGameState::StaticRegisterNativesAWakGameState()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWakGameState);
	UClass* Z_Construct_UClass_AWakGameState_NoRegister()
	{
		return AWakGameState::StaticClass();
	}
	struct Z_Construct_UClass_AWakGameState_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWakGameState_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameState,
		(UObject* (*)())Z_Construct_UPackage__Script_PROD_Wakgood,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWakGameState_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWakGameState_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Game/WakGameState.h" },
		{ "ModuleRelativePath", "Game/WakGameState.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWakGameState_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWakGameState>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWakGameState_Statics::ClassParams = {
		&AWakGameState::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWakGameState_Statics::Class_MetaDataParams), Z_Construct_UClass_AWakGameState_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AWakGameState()
	{
		if (!Z_Registration_Info_UClass_AWakGameState.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWakGameState.OuterSingleton, Z_Construct_UClass_AWakGameState_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWakGameState.OuterSingleton;
	}
	template<> PROD_WAKGOOD_API UClass* StaticClass<AWakGameState>()
	{
		return AWakGameState::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWakGameState);
	AWakGameState::~AWakGameState() {}
	struct Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakGameState_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakGameState_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWakGameState, AWakGameState::StaticClass, TEXT("AWakGameState"), &Z_Registration_Info_UClass_AWakGameState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWakGameState), 2278013983U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakGameState_h_994924050(TEXT("/Script/PROD_Wakgood"),
		Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakGameState_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakGameState_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
