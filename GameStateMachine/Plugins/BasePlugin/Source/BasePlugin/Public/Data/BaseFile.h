// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace BaseFiles
{
	BASEPLUGIN_API int32 IncGlobalCfgVersion();
	BASEPLUGIN_API int32 GetGlobalCfgVersion();
	BASEPLUGIN_API void ResetGlobalCfgVersion();

	enum class EFileType : int8
	{
		UnKnown,
		Asset,           //�ļ��� '*/(name).(name)'
		Text,            //�ļ��� '*/(name).text'
		TextCSV,         //�ļ��� '*/(name).csv'
		TextJson,        //�ļ��� '*/(name).json'
	};

	enum class EFileAssetType :int8
	{
		UnKnown,
		Asset,            //UE ��Դ
		Package,        //����������Դ
	};
	
	struct FileDescription 
	{
		EFileAssetType AssetType{};
		EFileType      GuessType{};
		FString Directory;
		FString Name;
		FString ExtensionName;
	};

	BASEPLUGIN_API bool ParseFilePath(const FString& FilePath, FileDescription& OutDescription);

	/*
	 *��Patch��Դ�м����ı�
	 */
	BASEPLUGIN_API bool LoadStringContentFromPatchs(const FString &FilePath,FString &OutString);

	/*
		�����ı�
		����˳��Patch-> Asset Package
	*/
	BASEPLUGIN_API bool LoadStringContent(const FString &FilePath,FString &OutString);

	FORCEINLINE static bool LoadStringContent(const FileDescription& Description, FString& OutString)
	{
		FString Path = FString::Printf(TEXT("%s/%s.%s"),*Description.Directory,*Description.Name,*Description.ExtensionName);

		return LoadStringContent(Path, OutString);
	}

	//������µ����ñ���Ϣ
	BASEPLUGIN_API void AddNewConfig(FString Path,FString Content);

	//���ñ�������ñ���Ϣ
	BASEPLUGIN_API  void RestNewConfigMap();

	//����·��/���� ��ȡ���µ����ñ�����
	BASEPLUGIN_API  FString* GetNewConfig(FString Path);
}
