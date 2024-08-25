// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PROD_Wakgood/Interaction/WakItemBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWakItemBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AInteractionBase();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWakItemBase();
	PROD_WAKGOOD_API UClass* Z_Construct_UClass_AWakItemBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_PROD_Wakgood();
// End Cross Module References
	void AWakItemBase::StaticRegisterNativesAWakItemBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWakItemBase);
	UClass* Z_Construct_UClass_AWakItemBase_NoRegister()
	{
		return AWakItemBase::StaticClass();
	}
	struct Z_Construct_UClass_AWakItemBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ItemTexture_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemTexture;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWakItemBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AInteractionBase,
		(UObject* (*)())Z_Construct_UPackage__Script_PROD_Wakgood,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWakItemBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWakItemBase_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Interaction/WakItemBase.h" },
		{ "ModuleRelativePath", "Interaction/WakItemBase.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWakItemBase_Statics::NewProp_ItemTexture_MetaData[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Interaction/WakItemBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWakItemBase_Statics::NewProp_ItemTexture = { "ItemTexture", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWakItemBase, ItemTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWakItemBase_Statics::NewProp_ItemTexture_MetaData), Z_Construct_UClass_AWakItemBase_Statics::NewProp_ItemTexture_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWakItemBase_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWakItemBase_Statics::NewProp_ItemTexture,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWakItemBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWakItemBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWakItemBase_Statics::ClassParams = {
		&AWakItemBase::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AWakItemBase_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AWakItemBase_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWakItemBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AWakItemBase_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWakItemBase_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AWakItemBase()
	{
		if (!Z_Registration_Info_UClass_AWakItemBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWakItemBase.OuterSingleton, Z_Construct_UClass_AWakItemBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWakItemBase.OuterSingleton;
	}
	template<> PROD_WAKGOOD_API UClass* StaticClass<AWakItemBase>()
	{
		return AWakItemBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWakItemBase);
	AWakItemBase::~AWakItemBase() {}
	struct Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakItemBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakItemBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWakItemBase, AWakItemBase::StaticClass, TEXT("AWakItemBase"), &Z_Registration_Info_UClass_AWakItemBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWakItemBase), 3052951845U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakItemBase_h_28195244(TEXT("/Script/PROD_Wakgood"),
		Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakItemBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakItemBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
