// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseFile.h"

/*
�������ñ�ʵ�֣�Ŀǰ֧�� DataTable �� CSV ���ָ�ʽ�������͸������͵�Key��֧��BinarySearchByKey()����

�ṹ����̳��� FTableRowBase �����£�

USTRUCT(BlueprintType)
struct FSampleTableRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;
};

1�ṹ�� VS 1���ñ�����ʹ�����º��ݣ����ٶ��壺
MAKE_DH_DATATABLE_WITH_STRING_KEY(FSampleTable, FSampleTableRow, TEXT("/Game/DataTables/SampleTable.SampleTable"), ID);

1�ṹ�� VS N���ñ�����ͨ���ֶ������������
class FMultiSampleTable : public DHDataTable<FMultiSampleTable, FSampleTableRow, FString, true>
{
public:
    FMultiSampleTable(int32 TagID)
    {
        switch (TagID) {
            case 0:
                Initialize(TEXT("/Game/DataTables/SampleTable0.SampleTable0"));
                return;
            case 1:
                Initialize(TEXT("/Game/DataTables/SampleTable1.SampleTable1"));
                return;
        }
    }
    static const FString &GenerateKey(TableRowTypePtr Row)
    {
        return Row->KeyField;
    }
};

���ʹ�ã�
    auto SampleTable = FSampleTable::GetInstance();
    auto Row = SampleTable->GetRowByKey(TEXT("123"));

    auto MultiSampleTable = FMultiSampleTable::GetInstance(0);
    auto Row = MultiSampleTable->GetRowByKey(TEXT("123"));
*/

#include "BaseCommon.h"
#include "Engine/DataTable.h"

/*
 TableClassName         �����
 TableRowStructType     ���нṹ�壬�̳���FTableRowBase
 FilePath               ���ݱ�·��
 KeyType                ΨһKey�ֶ����ͣ������ integer ���� float ����֧��BinarySearch����
 KeyField               TableRowStructType����ΪΨһKey���ֶ�
 */
#define MAKE_DH_DATATABLE(TableClassName, TableRowStructType, FilePath, KeyType, KeyField)                      \
class TableClassName : public DHDataTable<TableClassName, TableRowStructType, KeyType>	                        \
{																								                \
public:																							                \
	TableClassName()																		                    \
	{																							                \
		Initialize(FilePath);								                                                    \
	}																							                \
	static const KeyType &GenerateKey(const TableRowTypePtr Row)							                    \
	{																							                \
		return Row->KeyField;																                    \
	}																							                \
};

#define MAKE_DH_DATATABLE_WITH_INT32_KEY(TableClassName, TableRowStructType, FilePath, KeyField)                \
    MAKE_DH_DATATABLE(TableClassName, TableRowStructType, FilePath, int32, KeyField)

#define MAKE_DH_DATATABLE_WITH_STRING_KEY(TableClassName, TableRowStructType, FilePath, KeyField)               \
    MAKE_DH_DATATABLE(TableClassName, TableRowStructType, FilePath, FString, KeyField)

#define MAKE_DH_DATATABLE_WITH_INT32(TableClassName, TableRowStructType, FilePath)                              \
    MAKE_DH_DATATABLE_WITH_INT32_KEY(TableClassName, TableRowStructType, FilePath, ItemID)

#define MAKE_DH_DATATABLE_WITH_STRING(TableClassName, TableRowStructType, FilePath)                             \
    MAKE_DH_DATATABLE_WITH_STRING_KEY(TableClassName, TableRowStructType, FilePath, ItemID)

#define MAKE_DH_DATATABLE_WITH_FLOAT_KEY(TableClassName, TableRowStructType, FilePath, KeyField)                \
    MAKE_DH_DATATABLE(TableClassName, TableRowStructType, FilePath, float, KeyField)

enum class EDHFileType : int8
{
    Asset,      // �ļ��� `*/(name).(name)`
    Text,       // �ļ��� `*/(name).txt`
    TextCSV,    // �ļ��� `*/(name).csv`
    TextJson    // �ļ��� `*/(name).json`
};

template <
    typename TableRowType,
    typename KeyType
>
class DHDataTable_DataEntity
{
public:
    typedef const TableRowType* TableRowTypePtr;
protected:
    TMap<KeyType, TableRowTypePtr> _Table;
    TArray<TableRowTypePtr> _TableRows;
    UDataTable* _RawTable = nullptr;
    bool _Sorted = false;
};

template <
    typename TableRowType,
    typename KeyType,
    typename InternalDataType = DHDataTable_DataEntity<TableRowType, KeyType>
>
class DHDataTable_Operation : public DHDataTable_DataEntity<TableRowType, KeyType>
{
    typedef DHDataTable_DataEntity<TableRowType, KeyType> Super;
public:
    // Nullable
    typename Super::TableRowTypePtr GetRowByKey(const KeyType Key)
    {
        return_null_if_null(Super::_RawTable);

        return Super::_Table.FindRef(Key);
    }
};

/*
 * FString��������
 * ֧�� GetRowByKey(const FString &Key) �� GetRowByKey(const TCHAR *Key) ��������
 */
template <
    typename TableRowType
>
class DHDataTable_Operation<TableRowType, FString> : public DHDataTable_DataEntity<TableRowType, FString>
{
    typedef DHDataTable_DataEntity<TableRowType, FString> Super;
public:
    // Nullable
    typename Super::TableRowTypePtr GetRowByKey(const FString& Key)
    {
        return_null_if_null(Super::_RawTable);

        return Super::_Table.FindRef(Key);
    }

    // Nullable
    typename Super::TableRowTypePtr GetRowByKey(const TCHAR* Key)
    {
        return_null_if_null(Super::_RawTable);

        return Super::_Table.FindRef(Key);
    }
};

/*
 * �����ݱȽ��������� TableType::GenerateKey ��̬����
 */
template <
    typename TableType,
    typename TableRowType
>
struct DHDataTable_DataRowComparer
{
    bool operator() (const TableRowType& Left, const TableRowType& Right) const
    {
        return TableType::GenerateKey(&Left) < TableType::GenerateKey(&Right);
    }
};

/*
 * ֧�� Key ֵ ��Ԫ����
 */
template <
    typename TableType,
    typename TableRowType,
    typename KeyType
>
class DHDataTable_BinarySearch : public DHDataTable_Operation<TableRowType, KeyType>
{
    typedef DHDataTable_DataEntity<TableRowType, KeyType> Super;

    void SortOnce()
    {
        return_if_true(Super::_Sorted);
        Super::_Sorted = true;
        Super::_TableRows.Sort(DHDataTable_DataRowComparer<TableType, TableRowType>());
    }
public:
    /*
     * ��Ԫ����
     * @param ClosedKey �ٽ� Key ��ֵ
     * @param UseClosedRange �Ƿ�ʹ�ñպ����䣬Ч���磺�� [1, 3, 6, 7] �У����� -2 ���� 1������ 10 ���� 7��
     * @return TableRowType*  Nullable
     */
    typename Super::TableRowTypePtr BinarySearchByClosedKey(KeyType ClosedKey, bool UseClosedRange = true)
    {
        auto& Rows = Super::_TableRows;

        int32 Num = Rows.Num();
        return_null_if_true(Num == 0);

        SortOnce();

        int32 Index = 0;
        SIZE_T Size = Num;

        while (Size > 0) {
            const SIZE_T LeftoverSize = Size % 2;
            Size = Size / 2;

            const SIZE_T CheckIndex = Index + Size;
            const SIZE_T StartIfLess = CheckIndex + LeftoverSize;

            auto&& CheckValue = TableType::GenerateKey(Rows[CheckIndex]);
            Index = CheckValue < ClosedKey ? StartIfLess : Index;
        }

        if (Index == INDEX_NONE || Index >= Num) {
            return_null_if_true(!UseClosedRange);

            Index = (ClosedKey < TableType::GenerateKey(Super::_TableRows[0])) ? 0 : (Num - 1);
        }

        return Super::_TableRows[Index];
    }
};

/*
 * ���ݱ���
 * @TableType ��
 * @TableRowType ���нṹ�壬�̳���FTableRowBase
 * @KeyType ���г䵱 Key ����������
 * @Multiple �Ƿ�Ҫ֧�ֶ����ļ��ؼ�ʵ����ȡ��ͨ�� TagID ������
 */
template <
    typename TableType,
    typename TableRowType,
    typename KeyType,
    bool Multiple = false,
    typename = typename std::enable_if<std::is_base_of<FTableRowBase, TableRowType>::value>::type
>
class DHDataTable :
    public std::conditional<
    (std::is_integral<KeyType>::value || std::is_floating_point<KeyType>::value),
    DHDataTable_BinarySearch<TableType, TableRowType, KeyType>,
    DHDataTable_Operation<TableRowType, KeyType>
    >::type,
    public DHInstance<TableType, Multiple>
{
    typedef DHDataTable_DataEntity<TableRowType, KeyType> Super;
    int32 CurVersion = 0;
    FString FilePath;
public:
    DHDataTable() = default;

    virtual ~DHDataTable()
    {
        Reset();
    }

    void Initialize(const FString& InFilePath)
    {
        return_if_true(Super::_RawTable != nullptr && CurVersion == DHFiles::GetGlobalCfgVersion());

        return_if_true(!DHLoadDataTable(InFilePath, TableRowType::StaticStruct(), Super::_RawTable));

        Super::_RawTable->AddToRoot();

        FString ContextString;

        Super::_TableRows.Empty(Super::_RawTable->GetRowMap().Num());
        Super::_RawTable->template ForeachRow<TableRowType>(ContextString, [this](const FName&, const TableRowType& Row) {
            Super::_Table.Add(TableType::GenerateKey(&Row), &Row);
            Super::_TableRows.Add(&Row);
            });

        FilePath = InFilePath;
        CurVersion = DHFiles::GetGlobalCfgVersion();
    }

    const TArray<typename Super::TableRowTypePtr>& GetRows()
    {
        Initialize(FilePath); // ȷ�����£���ͬ
        return Super::_TableRows;
    }

    FORCEINLINE bool IsEmpty()
    {
        Initialize(FilePath);
        return Super::_TableRows.Num() == 0;
    }

    FORCEINLINE int32 RowsNum()
    {
        Initialize(FilePath);
        return Super::_TableRows.Num();
    }

    void Reset()
    {
        return_if_true(!IsValid(Super::_RawTable));

        Super::_RawTable->RemoveFromRoot();
        Super::_RawTable = nullptr;
        Super::_Table.Empty();
        Super::_TableRows.Empty();
        Super::_Sorted = false;

        CurVersion = 0;
    }
};

bool BASEPLUGIN_API DHLoadDataTable(const FString& FilePath, UScriptStruct* ScriptStruct, UDataTable*& Table);

void BASEPLUGIN_API DHScanAssetPaths(const TArray<FString>& Paths);