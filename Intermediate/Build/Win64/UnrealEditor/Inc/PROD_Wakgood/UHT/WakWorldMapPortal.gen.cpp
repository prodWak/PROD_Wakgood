// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PROD_Wakgood/Interaction/WakWorldMapPortal.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWakWorldMapPortal() {}
// Cross Module References
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AInteractionBase();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWorldMapPortal();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWorldMapPortal_NoRegister();
	UPackage* Z_Construct_UPackage__Script_PROD_Wakgood();
// End Cross Module References
	void AWorldMapPortal::StaticRegisterNativesAWorldMapPortal()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWorldMapPortal);
	UClass* Z_Construct_UClass_AWorldMapPortal_NoRegister()
	{
		return AWorldMapPortal::StaticClass();
	}
	struct Z_Construct_UClass_AWorldMapPortal_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlayerLastLocationIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlayerLastLocationIndex;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LocationName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_LocationName;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWorldMapPortal_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AInteractionBase,
		(UObject* (*)())Z_Construct_UPackage__Script_PROD_Wakgood,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldMapPortal_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWorldMapPortal_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Interaction/WakWorldMapPortal.h" },
		{ "ModuleRelativePath", "Interaction/WakWorldMapPortal.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWorldMapPortal_Statics::NewProp_PlayerLastLocationIndex_MetaData[] = {
		{ "Category", "Game Instance" },
		{ "ModuleRelativePath", "Interaction/WakWorldMapPortal.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AWorldMapPortal_Statics::NewProp_PlayerLastLocationIndex = { "PlayerLastLocationIndex", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWorldMapPortal, PlayerLastLocationIndex), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldMapPortal_Statics::NewProp_PlayerLastLocationIndex_MetaData), Z_Construct_UClass_AWorldMapPortal_Statics::NewProp_PlayerLastLocationIndex_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWorldMapPortal_Statics::NewProp_LocationName_MetaData[] = {
		{ "Category", "Game Instance" },
		{ "ModuleRelativePath", "Interaction/WakWorldMapPortal.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_AWorldMapPortal_Statics::NewProp_LocationName = { "LocationName", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWorldMapPortal, LocationName), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldMapPortal_Statics::NewProp_LocationName_MetaData), Z_Construct_UClass_AWorldMapPortal_Statics::NewProp_LocationName_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWorldMapPortal_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWorldMapPortal_Statics::NewProp_PlayerLastLocationIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWorldMapPortal_Statics::NewProp_LocationName,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWorldMapPortal_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWorldMapPortal>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWorldMapPortal_Statics::ClassParams = {
		&AWorldMapPortal::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AWorldMapPortal_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AWorldMapPortal_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldMapPortal_Statics::Class_MetaDataParams), Z_Construct_UClass_AWorldMapPortal_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldMapPortal_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AWorldMapPortal()
	{
		if (!Z_Registration_Info_UClass_AWorldMapPortal.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWorldMapPortal.OuterSingleton, Z_Construct_UClass_AWorldMapPortal_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWorldMapPortal.OuterSingleton;
	}
	template<> PROD_WAKGOOD_API UClass* StaticClass<AWorldMapPortal>()
	{
		return AWorldMapPortal::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWorldMapPortal);
	AWorldMapPortal::~AWorldMapPortal() {}
	struct Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakWorldMapPortal_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakWorldMapPortal_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWorldMapPortal, AWorldMapPortal::StaticClass, TEXT("AWorldMapPortal"), &Z_Registration_Info_UClass_AWorldMapPortal, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWorldMapPortal), 3510040509U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakWorldMapPortal_h_3180067513(TEXT("/Script/PROD_Wakgood"),
		Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakWorldMapPortal_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakWorldMapPortal_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
