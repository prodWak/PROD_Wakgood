// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Interaction/WakInteractionBase.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
#ifdef PROD_WAKGOOD_WakInteractionBase_generated_h
#error "WakInteractionBase.generated.h already included, missing '#pragma once' in WakInteractionBase.h"
#endif
#define PROD_WAKGOOD_WakInteractionBase_generated_h

#define FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_SPARSE_DATA
#define FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execInteraction); \
	DECLARE_FUNCTION(execOnEndOverlap); \
	DECLARE_FUNCTION(execOnBeginOverlap);


#define FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_ACCESSORS
#define FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAInteractionBase(); \
	friend struct Z_Construct_UClass_AInteractionBase_Statics; \
public: \
	DECLARE_CLASS(AInteractionBase, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/PROD_Wakgood"), NO_API) \
	DECLARE_SERIALIZER(AInteractionBase) \
	virtual UObject* _getUObject() const override { return const_cast<AInteractionBase*>(this); }


#define FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AInteractionBase(AInteractionBase&&); \
	NO_API AInteractionBase(const AInteractionBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AInteractionBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AInteractionBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AInteractionBase) \
	NO_API virtual ~AInteractionBase();


#define FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_10_PROLOG
#define FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_SPARSE_DATA \
	FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_ACCESSORS \
	FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_INCLASS_NO_PURE_DECLS \
	FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROD_WAKGOOD_API UClass* StaticClass<class AInteractionBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_pc10_Documents_GitHub_Unr_PROD_Wakgood2_Source_PROD_Wakgood_Interaction_WakInteractionBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
