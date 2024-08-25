// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PROD_Wakgood/Game/WakPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWakPlayerController() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWakPlayerController();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWakPlayerController_NoRegister();
	UPackage* Z_Construct_UPackage__Script_PROD_Wakgood();
// End Cross Module References
	void AWakPlayerController::StaticRegisterNativesAWakPlayerController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWakPlayerController);
	UClass* Z_Construct_UClass_AWakPlayerController_NoRegister()
	{
		return AWakPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_AWakPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWakPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_PROD_Wakgood,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWakPlayerController_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWakPlayerController_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Game/WakPlayerController.h" },
		{ "ModuleRelativePath", "Game/WakPlayerController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWakPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWakPlayerController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWakPlayerController_Statics::ClassParams = {
		&AWakPlayerController::StaticClass,
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWakPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AWakPlayerController_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AWakPlayerController()
	{
		if (!Z_Registration_Info_UClass_AWakPlayerController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWakPlayerController.OuterSingleton, Z_Construct_UClass_AWakPlayerController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWakPlayerController.OuterSingleton;
	}
	template<> PROD_WAKGOOD_API UClass* StaticClass<AWakPlayerController>()
	{
		return AWakPlayerController::StaticClass();
	}
	AWakPlayerController::AWakPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWakPlayerController);
	AWakPlayerController::~AWakPlayerController() {}
	struct Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakPlayerController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakPlayerController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWakPlayerController, AWakPlayerController::StaticClass, TEXT("AWakPlayerController"), &Z_Registration_Info_UClass_AWakPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWakPlayerController), 456233560U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakPlayerController_h_461492129(TEXT("/Script/PROD_Wakgood"),
		Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Game_WakPlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
