/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2018 NoahFrame(NoahGameFrame)

   File creator: lvsheng.huang
   
   NoahFrame is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#ifndef NFC_LUA_SCRIPT_MODULE_H
#define NFC_LUA_SCRIPT_MODULE_H

//just define it as 0 if you want to use luaintf with C
//#define LUAINTF_LINK_LUA_COMPILED_IN_CXX 0

#include "Dependencies/LuaIntf/LuaIntf.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIClassModule.h"
#include "NFComm/NFPluginModule/NFILuaScriptModule.h"
#include "NFComm/NFPluginModule/NFIEventModule.h"
#include "NFComm/NFPluginModule/NFIScheduleModule.h"
#include "NFComm/NFPluginModule/NFIElementModule.h"
#include "NFComm/NFPluginModule/NFINetClientModule.h"
#include "NFComm/NFPluginModule/NFINetModule.h"
#include "NFComm/NFPluginModule/NFILogModule.h"

class NFCLuaScriptModule
    : public NFILuaScriptModule
{
public:
    NFCLuaScriptModule(NFIPluginManager* p)
    {
        pPluginManager = p;
    }

	virtual bool Awake();
	virtual bool Init();
    virtual bool Shut();
	virtual bool ReadyExecute();
	virtual bool Execute();

    virtual bool AfterInit();
    virtual bool BeforeShut();


protected:

	//FOR KERNEL MODULE
	NFGUID CreateObject(const NFGUID& self, const int nSceneID, const int nGroupID, const std::string& strClassName, const std::string& strIndex, const NFDataList& arg);
	bool ExistObject(const NFGUID& self);
	bool DestroyObject(const NFGUID & self);

	//return the group id
	bool EnterScene(const int nSceneID, const int nGroupID);
	bool DoEvent(const NFGUID& self, const int nEventID, const NFDataList& arg);

	bool FindProperty(const NFGUID& self, const std::string& strPropertyName);

	bool SetPropertyInt(const NFGUID& self, const std::string& strPropertyName, const NFINT64 nValue);
	bool SetPropertyFloat(const NFGUID& self, const std::string& strPropertyName, const double dValue);
	bool SetPropertyString(const NFGUID& self, const std::string& strPropertyName, const std::string& strValue);
	bool SetPropertyObject(const NFGUID& self, const std::string& strPropertyName, const NFGUID& objectValue);
	bool SetPropertyVector2(const NFGUID& self, const std::string& strPropertyName, const NFVector2& value);
	bool SetPropertyVector3(const NFGUID& self, const std::string& strPropertyName, const NFVector3& value);

	NFINT64 GetPropertyInt(const NFGUID& self, const std::string& strPropertyName);
	int GetPropertyInt32(const NFGUID& self, const std::string& strPropertyName);	//equal to (int)GetPropertyInt(...), to remove C4244 warning
	double GetPropertyFloat(const NFGUID& self, const std::string& strPropertyName);
	std::string GetPropertyString(const NFGUID& self, const std::string& strPropertyName);
	NFGUID GetPropertyObject(const NFGUID& self, const std::string& strPropertyName);
	NFVector2 GetPropertyVector2(const NFGUID& self, const std::string& strPropertyName);
	NFVector3 GetPropertyVector3(const NFGUID& self, const std::string& strPropertyName);

	bool AddPropertyCallBack(const NFGUID& self, std::string& strPropertyName, std::string& luaFunc);
    bool AddRecordCallBack(const NFGUID& self, std::string& strRecordName, std::string& luaFunc);
    bool AddEventCallBack(const NFGUID& self, const NFEventDefine nEventID, std::string& luaFunc);
	bool AddSchedule(const NFGUID& self, std::string& strHeartBeatName, std::string& luaFunc, const float fTime, const int nCount);
	bool AddModuleSchedule(std::string& strHeartBeatName, std::string& luaFunc, const float fTime, const int nCount);

	int AddRow(const NFGUID& self, std::string& strRecordName, const NFDataList& var);
	bool RemRow(const NFGUID& self, std::string& strRecordName, const int nRow);

	bool SetRecordInt(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const NFINT64 value);
	bool SetRecordFloat(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const double value);
	bool SetRecordString(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const std::string& value);
	bool SetRecordObject(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const NFGUID& value);
	bool SetRecordVector2(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const NFVector2& value);
	bool SetRecordVector3(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const NFVector3& value);

	NFINT64 GetRecordInt(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag);
	double GetRecordFloat(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag);
	std::string GetRecordString(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag);
	NFGUID GetRecordObject(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag);
	NFVector2 GetRecordVector2(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag);
	NFVector3 GetRecordVector3(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag);

	NFINT64 GetNowTime();
	NFGUID CreateID();
	NFINT64 APPID();
	NFINT64 APPType();

	//FOR ELEMENT MODULE
	bool ExistElementObject(const std::string& strConfigName);
	std::vector<std::string> GetEleList(const std::string& strClassName);

	NFINT64 GetElePropertyInt(const std::string& strConfigName, const std::string& strPropertyName);
	double GetElePropertyFloat(const std::string& strConfigName, const std::string& strPropertyName);
	std::string GetElePropertyString(const std::string& strConfigName, const std::string& strPropertyName);
	NFVector2 GetElePropertyVector2(const std::string& strConfigName, const std::string& strPropertyName);
	NFVector3 GetElePropertyVector3(const std::string& strConfigName, const std::string& strPropertyName);

	//FOR NET MODULE
    //for client module

    void AddReceiveCallBack(const int nMsgID, const std::string& luaFunc);

	void SendByServerFD(const NFSOCK nFD, const uint16_t nMsgID, const std::string& strData);
	void SendByServerID(const int nServerID, const uint16_t nMsgID, const std::string& strData);
    void SendByServerType(const NF_SERVER_TYPES eType, const uint16_t nMsgID, const std::string& strData);

    //for net module
    void SendMsgToGate(const NFGUID player, const uint16_t nMsgID, const std::string& strData);
    void SendGroupMsgToGate(const uint16_t nMsgID, const std::string& strData);
    void SendToAllPlayer(const uint16_t nMsgID, const std::string& strData);

	//for log
	void LogInfo(const std::string& strData);
	void LogError(const std::string& strData);
	void LogWarning(const std::string& strData);
	void LogDebug(const std::string& strData);

    //hot fix
	void SetVersionCode(const std::string& strData);
	const std::string& GetVersionCode();

	//FOR CLASS MDOULE



    bool AddClassCallBack(std::string& className, std::string& funcName);

protected:
    template<typename T>
    bool AddLuaFuncToMap(NFMap<T, NFMap<NFGUID, NFList<string>>>& funcMap, const NFGUID& self, T key, std::string& luaFunc);

    template<typename T>
    bool AddLuaFuncToMap(NFMap<T, NFMap<NFGUID, NFList<string>>>& funcMap, T key, std::string& luaFunc);

    template<typename T1, typename... T2>
    bool CallLuaFuncFromMap(NFMap<T1, NFMap<NFGUID, NFList<string>>>& funcMap, T1 key, const NFGUID& self, T2... arg);

    template<typename T1, typename... T2>
    bool CallLuaFuncFromMap(NFMap<T1, NFMap<NFGUID, NFList<string>>>& funcMap, T1 key, T2... arg);

    int OnLuaPropertyCB(const NFGUID& self, const std::string& strPropertyName, const NFData& oldVar, const NFData& newVar);
    int OnLuaRecordCB(const NFGUID& self, const RECORD_EVENT_DATA& xEventData, const NFData& oldVar, const NFData& newVar);
    int OnLuaHeartBeatCB(const NFGUID& self, const std::string& strHeartBeatName, const float fTime, const int nCount);

	int OnLuaHeartBeatCB(const std::string& strHeartBeatName, const float fTime, const int nCount);

    int OnLuaEventCB(const NFGUID& self, const NFEventDefine nEventID, const NFDataList& argVar);

    int OnClassEventCB(const NFGUID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT eClassEvent, const NFDataList& var);
    
	void OnScriptReload();

protected:
    bool Register();

protected:
    NFIElementModule* m_pElementModule;
    NFIKernelModule* m_pKernelModule;
    NFIClassModule* m_pClassModule;
	NFIEventModule* m_pEventModule;
    NFIScheduleModule* m_pScheduleModule;
    NFINetClientModule* m_pNetClientModule;
    NFINetModule* m_pNetModule;
    NFILogModule* m_pLogModule;

protected:
    int64_t mnTime;
    std::string strVersionCode;
    LuaIntf::LuaContext mLuaContext;

    NFMap<std::string, NFMap<NFGUID, NFList<std::string>>> m_luaPropertyCallBackFuncMap;
    NFMap<std::string, NFMap<NFGUID, NFList<std::string>>> m_luaRecordCallBackFuncMap;
    NFMap<int, NFMap<NFGUID, NFList<std::string>>> m_luaEventCallBackFuncMap;
    NFMap<std::string, NFMap<NFGUID, NFList<std::string>>> m_luaHeartBeatCallBackFuncMap;

    NFMap<std::string, std::string> m_ClassEventFuncMap;
};

#endif
