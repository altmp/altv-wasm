#pragma once

#include <altv-capi-client.h>
#include "WasmPtr.hpp"

namespace Wasm
{
    struct alt_Array_unsignedint 
    {
        WasmPtr<unsigned int> data;
        unsigned long long size;
        unsigned long long capacity;
    };

    struct alt_CConnectionCompleteEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
    };

    struct alt_CDisconnectEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
    };

    struct alt_CEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
    };

    struct alt_CKeyboardEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        unsigned int keyCode;
        alt_CKeyboardEvent_KeyState keyState;
    };

    struct alt_CRefCountable 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IBaseObject 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IBlip 
    {
        WasmPtr<void> vtable;
    };

    struct alt_ICheckpoint 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IColShape 
    {
        WasmPtr<void> vtable;
    };

    struct alt_ICore 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IEntity 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValue 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueBaseObject 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueBool 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueByteArray 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueDict 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueDict_Iterator 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueDouble 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueFunction 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueFunction_Impl 
    {
        WasmPtr<void> vtable;
        unsigned long long refCount;
    };

    struct alt_IMValueInt 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueList 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueNil 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueNone 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueRGBA 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueString 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueUInt 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IMValueVector3 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IPackage 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IPackage_File 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IPlayer 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IResource 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IResource_Impl 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IScriptRuntime 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IVehicle 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IVoiceChannel 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IWeakRef 
    {
        WasmPtr<void> vtable;
    };

    struct alt_IWorldObject 
    {
        WasmPtr<void> vtable;
    };

    struct alt_KeyState 
    {
        bool down;
        bool toggled;
    };

    struct alt_PointLayout 
    {
        float x;
        float y;
        float z;
    };

    struct alt_PointPaddedLayout 
    {
        float x;
        float y;
        float z;
        float pad;
    };

    struct alt_RGBA 
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    struct alt_RefBase_RefStore_IBaseObject 
    {
        WasmPtr<alt_IBaseObject> ptr;
    };

    struct alt_RefBase_RefStore_IColShape 
    {
        WasmPtr<alt_IColShape> ptr;
    };

    struct alt_RefBase_RefStore_IEntity 
    {
        WasmPtr<alt_IEntity> ptr;
    };

    struct alt_RefBase_RefStore_IMValue 
    {
        WasmPtr<alt_IMValue> ptr;
    };

    struct alt_RefBase_RefStore_IMValueBaseObject 
    {
        WasmPtr<alt_IMValueBaseObject> ptr;
    };

    struct alt_RefBase_RefStore_IMValueBool 
    {
        WasmPtr<alt_IMValueBool> ptr;
    };

    struct alt_RefBase_RefStore_IMValueByteArray 
    {
        WasmPtr<alt_IMValueByteArray> ptr;
    };

    struct alt_RefBase_RefStore_IMValueDict 
    {
        WasmPtr<alt_IMValueDict> ptr;
    };

    struct alt_RefBase_RefStore_IMValueDouble 
    {
        WasmPtr<alt_IMValueDouble> ptr;
    };

    struct alt_RefBase_RefStore_IMValueFunction 
    {
        WasmPtr<alt_IMValueFunction> ptr;
    };

    struct alt_RefBase_RefStore_IMValueInt 
    {
        WasmPtr<alt_IMValueInt> ptr;
    };

    struct alt_RefBase_RefStore_IMValueList 
    {
        WasmPtr<alt_IMValueList> ptr;
    };

    struct alt_RefBase_RefStore_IMValueNil 
    {
        WasmPtr<alt_IMValueNil> ptr;
    };

    struct alt_RefBase_RefStore_IMValueNone 
    {
        WasmPtr<alt_IMValueNone> ptr;
    };

    struct alt_RefBase_RefStore_IMValueRGBA 
    {
        WasmPtr<alt_IMValueRGBA> ptr;
    };

    struct alt_RefBase_RefStore_IMValueString 
    {
        WasmPtr<alt_IMValueString> ptr;
    };

    struct alt_RefBase_RefStore_IMValueUInt 
    {
        WasmPtr<alt_IMValueUInt> ptr;
    };

    struct alt_RefBase_RefStore_IMValueVector3 
    {
        WasmPtr<alt_IMValueVector3> ptr;
    };

    struct alt_RefBase_RefStore_IPlayer 
    {
        WasmPtr<alt_IPlayer> ptr;
    };

    struct alt_RefBase_RefStore_IVehicle 
    {
        WasmPtr<alt_IVehicle> ptr;
    };

    struct alt_RefBase_RefStore_constIMValue 
    {
        WasmPtr<alt_IMValue> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueBaseObject 
    {
        WasmPtr<alt_IMValueBaseObject> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueBool 
    {
        WasmPtr<alt_IMValueBool> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueByteArray 
    {
        WasmPtr<alt_IMValueByteArray> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueDict 
    {
        WasmPtr<alt_IMValueDict> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueDouble 
    {
        WasmPtr<alt_IMValueDouble> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueFunction 
    {
        WasmPtr<alt_IMValueFunction> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueInt 
    {
        WasmPtr<alt_IMValueInt> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueList 
    {
        WasmPtr<alt_IMValueList> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueNil 
    {
        WasmPtr<alt_IMValueNil> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueNone 
    {
        WasmPtr<alt_IMValueNone> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueRGBA 
    {
        WasmPtr<alt_IMValueRGBA> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueString 
    {
        WasmPtr<alt_IMValueString> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueUInt 
    {
        WasmPtr<alt_IMValueUInt> ptr;
    };

    struct alt_RefBase_RefStore_constIMValueVector3 
    {
        WasmPtr<alt_IMValueVector3> ptr;
    };

    struct alt_RefStore_IBaseObject 
    {
        WasmPtr<alt_IBaseObject> ptr;
    };

    struct alt_RefStore_IColShape 
    {
        WasmPtr<alt_IColShape> ptr;
    };

    struct alt_RefStore_IEntity 
    {
        WasmPtr<alt_IEntity> ptr;
    };

    struct alt_RefStore_IMValue 
    {
        WasmPtr<alt_IMValue> ptr;
    };

    struct alt_RefStore_IMValueBaseObject 
    {
        WasmPtr<alt_IMValueBaseObject> ptr;
    };

    struct alt_RefStore_IMValueBool 
    {
        WasmPtr<alt_IMValueBool> ptr;
    };

    struct alt_RefStore_IMValueByteArray 
    {
        WasmPtr<alt_IMValueByteArray> ptr;
    };

    struct alt_RefStore_IMValueDict 
    {
        WasmPtr<alt_IMValueDict> ptr;
    };

    struct alt_RefStore_IMValueDouble 
    {
        WasmPtr<alt_IMValueDouble> ptr;
    };

    struct alt_RefStore_IMValueFunction 
    {
        WasmPtr<alt_IMValueFunction> ptr;
    };

    struct alt_RefStore_IMValueInt 
    {
        WasmPtr<alt_IMValueInt> ptr;
    };

    struct alt_RefStore_IMValueList 
    {
        WasmPtr<alt_IMValueList> ptr;
    };

    struct alt_RefStore_IMValueNil 
    {
        WasmPtr<alt_IMValueNil> ptr;
    };

    struct alt_RefStore_IMValueNone 
    {
        WasmPtr<alt_IMValueNone> ptr;
    };

    struct alt_RefStore_IMValueRGBA 
    {
        WasmPtr<alt_IMValueRGBA> ptr;
    };

    struct alt_RefStore_IMValueString 
    {
        WasmPtr<alt_IMValueString> ptr;
    };

    struct alt_RefStore_IMValueUInt 
    {
        WasmPtr<alt_IMValueUInt> ptr;
    };

    struct alt_RefStore_IMValueVector3 
    {
        WasmPtr<alt_IMValueVector3> ptr;
    };

    struct alt_RefStore_IPlayer 
    {
        WasmPtr<alt_IPlayer> ptr;
    };

    struct alt_RefStore_IVehicle 
    {
        WasmPtr<alt_IVehicle> ptr;
    };

    struct alt_RefStore_constIMValue 
    {
        WasmPtr<alt_IMValue> ptr;
    };

    struct alt_RefStore_constIMValueBaseObject 
    {
        WasmPtr<alt_IMValueBaseObject> ptr;
    };

    struct alt_RefStore_constIMValueBool 
    {
        WasmPtr<alt_IMValueBool> ptr;
    };

    struct alt_RefStore_constIMValueByteArray 
    {
        WasmPtr<alt_IMValueByteArray> ptr;
    };

    struct alt_RefStore_constIMValueDict 
    {
        WasmPtr<alt_IMValueDict> ptr;
    };

    struct alt_RefStore_constIMValueDouble 
    {
        WasmPtr<alt_IMValueDouble> ptr;
    };

    struct alt_RefStore_constIMValueFunction 
    {
        WasmPtr<alt_IMValueFunction> ptr;
    };

    struct alt_RefStore_constIMValueInt 
    {
        WasmPtr<alt_IMValueInt> ptr;
    };

    struct alt_RefStore_constIMValueList 
    {
        WasmPtr<alt_IMValueList> ptr;
    };

    struct alt_RefStore_constIMValueNil 
    {
        WasmPtr<alt_IMValueNil> ptr;
    };

    struct alt_RefStore_constIMValueNone 
    {
        WasmPtr<alt_IMValueNone> ptr;
    };

    struct alt_RefStore_constIMValueRGBA 
    {
        WasmPtr<alt_IMValueRGBA> ptr;
    };

    struct alt_RefStore_constIMValueString 
    {
        WasmPtr<alt_IMValueString> ptr;
    };

    struct alt_RefStore_constIMValueUInt 
    {
        WasmPtr<alt_IMValueUInt> ptr;
    };

    struct alt_RefStore_constIMValueVector3 
    {
        WasmPtr<alt_IMValueVector3> ptr;
    };

    struct alt_RotationLayout 
    {
        float roll;
        float pitch;
        float yaw;
    };

    struct alt_RotationPaddedLayout 
    {
        float roll;
        float pitch;
        float yaw;
        float pad;
    };

    struct alt_String 
    {
        WasmPtr<char> data;
        unsigned long long size;
    };

    struct alt_StringView 
    {
        WasmPtr<char> data;
        unsigned long long size;
    };

    struct alt_VectorLayout_float_2 
    {
        WasmPtr<float> elements;
    };

    struct alt_VectorLayout_float_3 
    {
        WasmPtr<float> elements;
    };

    struct alt_VectorLayout_float_4 
    {
        WasmPtr<float> elements;
    };

    struct alt_VectorLayout_int_2 
    {
        WasmPtr<int> elements;
    };

    struct alt_VectorLayout_int_3 
    {
        WasmPtr<int> elements;
    };

    struct alt_VectorLayout_int_4 
    {
        WasmPtr<int> elements;
    };

    struct alt_Vector_float_2_VectorLayout_float_2 
    {
        WasmPtr<float> elements;
    };

    struct alt_Vector_float_3_PointLayout 
    {
        float x;
        float y;
        float z;
    };

    struct alt_Vector_float_3_PointPaddedLayout 
    {
        float x;
        float y;
        float z;
        float pad;
    };

    struct alt_Vector_float_3_RotationLayout 
    {
        float roll;
        float pitch;
        float yaw;
    };

    struct alt_Vector_float_3_RotationPaddedLayout 
    {
        float roll;
        float pitch;
        float yaw;
        float pad;
    };

    struct alt_Vector_float_3_VectorLayout_float_3 
    {
        WasmPtr<float> elements;
    };

    struct alt_Vector_float_4_VectorLayout_float_4 
    {
        WasmPtr<float> elements;
    };

    struct alt_Vector_int_2_VectorLayout_int_2 
    {
        WasmPtr<int> elements;
    };

    struct alt_Vector_int_3_VectorLayout_int_3 
    {
        WasmPtr<int> elements;
    };

    struct alt_Vector_int_4_VectorLayout_int_4 
    {
        WasmPtr<int> elements;
    };

    struct alt_ViewMatrixLayout 
    {
        WasmPtr<alt_Vector_float_4_VectorLayout_float_4> right;
        WasmPtr<alt_Vector_float_4_VectorLayout_float_4> up;
        WasmPtr<alt_Vector_float_4_VectorLayout_float_4> forward;
        WasmPtr<alt_Vector_float_4_VectorLayout_float_4> pos;
    };

    struct alt_Array_RefBase_RefStore_IEntity 
    {
        WasmPtr<alt_RefBase_RefStore_IEntity> data;
        unsigned long long size;
        unsigned long long capacity;
    };

    struct alt_Array_RefBase_RefStore_IVehicle 
    {
        WasmPtr<alt_RefBase_RefStore_IVehicle> data;
        unsigned long long size;
        unsigned long long capacity;
    };

    struct alt_Array_StringView 
    {
        WasmPtr<alt_StringView> data;
        unsigned long long size;
        unsigned long long capacity;
    };

    struct alt_CColShapeEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IColShape> target;
        WasmPtr<alt_RefBase_RefStore_IEntity> entity;
        bool state;
    };

    struct alt_CDataNodeReceivedEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_String> name;
        WasmPtr<alt_String> json;
    };

    struct alt_CGameEntityCreateEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IEntity> target;
    };

    struct alt_CGlobalMetaDataChangeEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_String> key;
        WasmPtr<alt_RefBase_RefStore_constIMValue> val;
        WasmPtr<alt_RefBase_RefStore_constIMValue> oldVal;
    };

    struct alt_CPlayerChangeVehicleSeatEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IVehicle> target;
        WasmPtr<alt_RefBase_RefStore_IPlayer> player;
        unsigned char oldSeat;
        unsigned char newSeat;
    };

    struct alt_CPlayerDamageEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IPlayer> target;
        WasmPtr<alt_RefBase_RefStore_IEntity> attacker;
        unsigned short damage;
        unsigned int weapon;
    };

    struct alt_CPlayerDisconnectEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IPlayer> target;
        WasmPtr<alt_String> reason;
    };

    struct alt_CPlayerLeaveVehicleEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IVehicle> target;
        WasmPtr<alt_RefBase_RefStore_IPlayer> player;
        unsigned char seat;
    };

    struct alt_CResourceErrorEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_IResource> resource;
    };

    struct alt_CResourceStopEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_IResource> resource;
    };

    struct alt_CStreamSyncedMetaDataChangeEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IEntity> target;
        WasmPtr<alt_String> key;
        WasmPtr<alt_RefBase_RefStore_constIMValue> val;
        WasmPtr<alt_RefBase_RefStore_constIMValue> oldVal;
    };

    struct alt_CVehicleDestroyEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IVehicle> target;
    };

    struct alt_CWebViewEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_CWebView> target;
        WasmPtr<alt_String> name;
        WasmPtr<alt_Array_RefBase_RefStore_constIMValue> args;
    };

    struct alt_MatrixLayout_float_4_4 
    {
        WasmPtr<alt_Vector_float_4_VectorLayout_float_4> rows;
    };

    struct alt_Matrix_float_4_4_ViewMatrixLayout 
    {
        WasmPtr<alt_Vector_float_4_VectorLayout_float_4> right;
        WasmPtr<alt_Vector_float_4_VectorLayout_float_4> up;
        WasmPtr<alt_Vector_float_4_VectorLayout_float_4> forward;
        WasmPtr<alt_Vector_float_4_VectorLayout_float_4> pos;
    };

    struct alt_Array_RefBase_RefStore_IPlayer 
    {
        WasmPtr<alt_RefBase_RefStore_IPlayer> data;
        unsigned long long size;
        unsigned long long capacity;
    };

    struct alt_CClientScriptEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_String> name;
        WasmPtr<alt_Array_RefBase_RefStore_constIMValue> args;
    };

    struct alt_CExplosionEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IPlayer> source;
        WasmPtr<alt_RefBase_RefStore_IEntity> target;
        alt_CExplosionEvent_ExplosionType explosionType;
        WasmPtr<alt_Vector_float_3_PointLayout> position;
        unsigned int explosionFX;
    };

    struct alt_CGlobalSyncedMetaDataChangeEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_String> key;
        WasmPtr<alt_RefBase_RefStore_constIMValue> val;
        WasmPtr<alt_RefBase_RefStore_constIMValue> oldVal;
    };

    struct alt_CPlayerDeathEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IPlayer> target;
        WasmPtr<alt_RefBase_RefStore_IEntity> killer;
        unsigned int weapon;
    };

    struct alt_CRemoveEntityEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IEntity> target;
    };

    struct alt_CServerScriptEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_String> name;
        WasmPtr<alt_Array_RefBase_RefStore_constIMValue> args;
    };

    struct alt_CWeaponDamageEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IPlayer> source;
        WasmPtr<alt_RefBase_RefStore_IEntity> target;
        unsigned int weaponHash;
        unsigned short damageValue;
        WasmPtr<alt_Vector_float_3_VectorLayout_float_3> shotOffset;
        alt_CWeaponDamageEvent_BodyPart bodyPart;
    };

    struct alt_Matrix_float_4_4_MatrixLayout_float_4_4 
    {
        WasmPtr<alt_Vector_float_4_VectorLayout_float_4> rows;
    };

    struct alt_Array_RefBase_RefStore_constIMValue 
    {
        WasmPtr<alt_RefBase_RefStore_constIMValue> data;
        unsigned long long size;
        unsigned long long capacity;
    };

    struct alt_CGameEntityDestroyEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IEntity> target;
    };

    struct alt_CPlayerEnterVehicleEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IVehicle> target;
        WasmPtr<alt_RefBase_RefStore_IPlayer> player;
        unsigned char seat;
    };

    struct alt_CSyncedMetaDataChangeEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IEntity> target;
        WasmPtr<alt_String> key;
        WasmPtr<alt_RefBase_RefStore_constIMValue> val;
        WasmPtr<alt_RefBase_RefStore_constIMValue> oldVal;
    };

    struct alt_CConsoleCommandEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_StringView> name;
        WasmPtr<alt_Array_StringView> args;
    };

    struct alt_CResourceStartEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_IResource> resource;
    };

    struct alt_CPlayerConnectEvent 
    {
        WasmPtr<void> vtable;
        alt_CEvent_Type type;
        bool cancelled;
        WasmPtr<alt_RefBase_RefStore_IPlayer> target;
        WasmPtr<alt_String> reason;
    };

}