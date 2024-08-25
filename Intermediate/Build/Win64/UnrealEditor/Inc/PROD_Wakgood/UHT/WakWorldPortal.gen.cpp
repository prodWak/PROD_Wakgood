// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PROD_Wakgood/Interaction/WakWorldPortal.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWakWorldPortal() {}
// Cross Module References
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AInteractionBase();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWorldPortal();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWorldPortal_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UWidgetComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_PROD_Wakgood();
// End Cross Module References
	void AWorldPortal::StaticRegisterNativesAWorldPortal()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWorldPortal);
	UClass* Z_Construct_UClass_AWorldPortal_NoRegister()
	{
		return AWorldPortal::StaticClass();
	}
	struct Z_Construct_UClass_AWorldPortal_Statics
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
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WidgetComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_WidgetComponent;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWorldPortal_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AInteractionBase,
		(UObject* (*)())Z_Construct_UPackage__Script_PROD_Wakgood,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldPortal_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWorldPortal_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Interaction/WakWorldPortal.h" },
		{ "ModuleRelativePath", "Interaction/WakWorldPortal.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWorldPortal_Statics::NewProp_PlayerLastLocationIndex_MetaData[] = {
		{ "Category", "Game Instance" },
		{ "ModuleRelativePath", "Interaction/WakWorldPortal.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AWorldPortal_Statics::NewProp_PlayerLastLocationIndex = { "PlayerLastLocationIndex", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWorldPortal, PlayerLastLocationIndex), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldPortal_Statics::NewProp_PlayerLastLocationIndex_MetaData), Z_Construct_UClass_AWorldPortal_Statics::NewProp_PlayerLastLocationIndex_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWorldPortal_Statics::NewProp_LocationName_MetaData[] = {
		{ "Category", "Game Instance" },
		{ "ModuleRelativePath", "Interaction/WakWorldPortal.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_AWorldPortal_Statics::NewProp_LocationName = { "LocationName", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWorldPortal, LocationName), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldPortal_Statics::NewProp_LocationName_MetaData), Z_Construct_UClass_AWorldPortal_Statics::NewProp_LocationName_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWorldPortal_Statics::NewProp_WidgetComponent_MetaData[] = {
		{ "Category", "WorldPortal" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Interaction/WakWorldPortal.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWorldPortal_Statics::NewProp_WidgetComponent = { "WidgetComponent", nullptr, (EPropertyFlags)0x0040000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWorldPortal, WidgetComponent), Z_Construct_UClass_UWidgetComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldPortal_Statics::NewProp_WidgetComponent_MetaData), Z_Construct_UClass_AWorldPortal_Statics::NewProp_WidgetComponent_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWorldPortal_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWorldPortal_Statics::NewProp_PlayerLastLocationIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWorldPortal_Statics::NewProp_LocationName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWorldPortal_Statics::NewProp_WidgetComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWorldPortal_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWorldPortal>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWorldPortal_Statics::ClassParams = {
		&AWorldPortal::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AWorldPortal_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AWorldPortal_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldPortal_Statics::Class_MetaDataParams), Z_Construct_UClass_AWorldPortal_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWorldPortal_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AWorldPortal()
	{
		if (!Z_Registration_Info_UClass_AWorldPortal.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWorldPortal.OuterSingleton, Z_Construct_UClass_AWorldPortal_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWorldPortal.OuterSingleton;
	}
	template<> PROD_WAKGOOD_API UClass* StaticClass<AWorldPortal>()
	{
		return AWorldPortal::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWorldPortal);
	AWorldPortal::~AWorldPortal() {}
	struct Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakWorldPortal_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakWorldPortal_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWorldPortal, AWorldPortal::StaticClass, TEXT("AWorldPortal"), &Z_Registration_Info_UClass_AWorldPortal, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWorldPortal), 700891021U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakWorldPortal_h_236780772(TEXT("/Script/PROD_Wakgood"),
		Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakWorldPortal_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakWorldPortal_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
