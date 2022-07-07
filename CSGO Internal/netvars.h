#pragma once


#ifndef NETVARS_H_
#define NETVARS_H_

#include "interfaces.h"

class RecvTable;

class RecvProp
{
public:

	char* m_pVarName;
	void*			m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;

	bool					m_bInsideArray;		// Set to true by the engine if this property sits inside an array.

	// Extra data that certain special property types bind to the property here.
	const void* m_pExtraData;

	// If this is an array (DPT_Array).
	RecvProp* m_pArrayProp;
	void*	m_ArrayLengthProxy;

	void*			m_ProxyFn;
	void*	m_DataTableProxyFn;	// For RDT_DataTable.

	RecvTable* m_pDataTable;		// For RDT_DataTable.
	int						m_Offset;

	int						m_ElementStride;
	int						m_nElements;

	// If it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char* m_pParentArrayPropName;
};


class RecvTable
{
public:

	// Properties described in a table.
	RecvProp* m_pProps;
	int				m_nProps;

	// The decoder. NOTE: this covers each RecvTable AND all its children (ie: its children
	// will have their own decoders that include props for all their children).
	void* m_pDecoder;

	char* m_pNetTableName;	// The name matched between client and server.



	bool			m_bInitialized;
	bool			m_bInMainList;
};




class ClientClass
{
public:

	const char* GetName()
	{
		return m_pNetworkName;
	}

	void*		m_pCreateFn;
	void*			m_pCreateEventFn;	// Only called for event objects.
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int						m_ClassID;	// Managed by the engine.
	const char* m_pMapClassname;
};

namespace DT
{
	static uintptr_t GetOffset(RecvTable* table, const char* szClass, const char* szNetVar)
	{
		for (int i = 0; i < table->m_nProps; i++)
		{
			RecvProp prop = table->m_pProps[i];
			if (strcmp(prop.m_pVarName, szNetVar) == 0)
			{
				return prop.m_Offset;
			}

			if (prop.m_pDataTable)
			{
				unsigned int offset = GetOffset(prop.m_pDataTable, szClass, szNetVar);
				if (offset)
				{
					return offset + prop.m_Offset;
				}
			}
		}
		return 0;
	}

	static uintptr_t GetNetVar(const char* szClass, const char* szNetVar)
	{
		static ClientClass* classes = I::CHLClient->GetAllClasses();
		for (ClientClass* pCur = classes; pCur; pCur = pCur->m_pNext)
		{
			if (strcmp(szClass, pCur->m_pRecvTable->m_pNetTableName) == 0)
			{
				unsigned int offset = GetOffset(pCur->m_pRecvTable, szClass, szNetVar);
				if (offset)
					return offset;
			}
		}

		return 0;
	}

	// all of these were dumped & parsed
	// many of which are useless

	namespace _ST_m_hActorList_16
	{
		static uintptr_t lengthproxy = GetNetVar("_ST_m_hActorList_16", "lengthproxy");
	}

	namespace _ST_m_Attributes_32
	{
		static uintptr_t lengthproxy = GetNetVar("_ST_m_Attributes_32", "lengthproxy");
	}

	namespace _ST_m_AnimOverlay_15
	{
		static uintptr_t lengthproxy = GetNetVar("_ST_m_AnimOverlay_15", "lengthproxy");
	}

	namespace _LPT_m_hActorList_16
	{
		static uintptr_t lengthprop16 = GetNetVar("_LPT_m_hActorList_16", "lengthprop16");
	}

	namespace _LPT_m_Attributes_32
	{
		static uintptr_t lengthprop32 = GetNetVar("_LPT_m_Attributes_32", "lengthprop32");
	}

	namespace _LPT_m_AnimOverlay_15
	{
		static uintptr_t lengthprop15 = GetNetVar("_LPT_m_AnimOverlay_15", "lengthprop15");
	}

	namespace DT_WorldVguiText
	{
		static uintptr_t baseclass = GetNetVar("DT_WorldVguiText", "baseclass");
		static uintptr_t m_bEnabled = GetNetVar("DT_WorldVguiText", "m_bEnabled");
		static uintptr_t m_szDisplayText = GetNetVar("DT_WorldVguiText", "m_szDisplayText");
		static uintptr_t m_szDisplayTextOption = GetNetVar("DT_WorldVguiText", "m_szDisplayTextOption");
		static uintptr_t m_szFont = GetNetVar("DT_WorldVguiText", "m_szFont");
		static uintptr_t m_iTextPanelWidth = GetNetVar("DT_WorldVguiText", "m_iTextPanelWidth");
		static uintptr_t m_clrText = GetNetVar("DT_WorldVguiText", "m_clrText");
	}

	namespace DT_World
	{
		static uintptr_t baseclass = GetNetVar("DT_World", "baseclass");
		static uintptr_t m_flWaveHeight = GetNetVar("DT_World", "m_flWaveHeight");
		static uintptr_t m_WorldMins = GetNetVar("DT_World", "m_WorldMins");
		static uintptr_t m_WorldMaxs = GetNetVar("DT_World", "m_WorldMaxs");
		static uintptr_t m_bStartDark = GetNetVar("DT_World", "m_bStartDark");
		static uintptr_t m_flMaxOccludeeArea = GetNetVar("DT_World", "m_flMaxOccludeeArea");
		static uintptr_t m_flMinOccluderArea = GetNetVar("DT_World", "m_flMinOccluderArea");
		static uintptr_t m_flMaxPropScreenSpaceWidth = GetNetVar("DT_World", "m_flMaxPropScreenSpaceWidth");
		static uintptr_t m_flMinPropScreenSpaceWidth = GetNetVar("DT_World", "m_flMinPropScreenSpaceWidth");
		static uintptr_t m_iszDetailSpriteMaterial = GetNetVar("DT_World", "m_iszDetailSpriteMaterial");
		static uintptr_t m_bColdWorld = GetNetVar("DT_World", "m_bColdWorld");
		static uintptr_t m_iTimeOfDay = GetNetVar("DT_World", "m_iTimeOfDay");
	}

	namespace DT_WearableItem
	{
		static uintptr_t baseclass = GetNetVar("DT_WearableItem", "baseclass");
	}

	namespace DT_WeaponZoneRepulsor
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponZoneRepulsor", "baseclass");
	}

	namespace DT_WeaponXM1014
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponXM1014", "baseclass");
		static uintptr_t m_reloadState = GetNetVar("DT_WeaponXM1014", "m_reloadState");
	}

	namespace DT_WeaponUSP
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponUSP", "baseclass");
	}

	namespace DT_WeaponUMP45
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponUMP45", "baseclass");
	}

	namespace DT_WeaponTec9
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponTec9", "baseclass");
	}

	namespace DT_WeaponTaser
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponTaser", "baseclass");
		static uintptr_t m_fFireTime = GetNetVar("DT_WeaponTaser", "m_fFireTime");
	}

	namespace DT_WeaponTablet
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponTablet", "baseclass");
		static uintptr_t m_flUpgradeExpirationTime_0_ = GetNetVar("DT_WeaponTablet", "m_flUpgradeExpirationTime[0]");
		static uintptr_t m_flUpgradeExpirationTime = GetNetVar("DT_WeaponTablet", "m_flUpgradeExpirationTime");
		static uintptr_t m_vecLocalHexFlags_0_ = GetNetVar("DT_WeaponTablet", "m_vecLocalHexFlags[0]");
		static uintptr_t m_vecLocalHexFlags = GetNetVar("DT_WeaponTablet", "m_vecLocalHexFlags");
		static uintptr_t m_nContractKillGridIndex = GetNetVar("DT_WeaponTablet", "m_nContractKillGridIndex");
		static uintptr_t m_nContractKillGridHighResIndex = GetNetVar("DT_WeaponTablet", "m_nContractKillGridHighResIndex");
		static uintptr_t m_bTabletReceptionIsBlocked = GetNetVar("DT_WeaponTablet", "m_bTabletReceptionIsBlocked");
		static uintptr_t m_flScanProgress = GetNetVar("DT_WeaponTablet", "m_flScanProgress");
		static uintptr_t m_flBootTime = GetNetVar("DT_WeaponTablet", "m_flBootTime");
		static uintptr_t m_flShowMapTime = GetNetVar("DT_WeaponTablet", "m_flShowMapTime");
		static uintptr_t m_vecNotificationIds_0_ = GetNetVar("DT_WeaponTablet", "m_vecNotificationIds[0]");
		static uintptr_t m_vecNotificationIds = GetNetVar("DT_WeaponTablet", "m_vecNotificationIds");
		static uintptr_t m_vecNotificationTimestamps_0_ = GetNetVar("DT_WeaponTablet", "m_vecNotificationTimestamps[0]");
		static uintptr_t m_vecNotificationTimestamps = GetNetVar("DT_WeaponTablet", "m_vecNotificationTimestamps");
		static uintptr_t m_vecPlayerPositionHistory_0_ = GetNetVar("DT_WeaponTablet", "m_vecPlayerPositionHistory[0]");
		static uintptr_t m_vecPlayerPositionHistory = GetNetVar("DT_WeaponTablet", "m_vecPlayerPositionHistory");
		static uintptr_t m_nLastPurchaseIndex = GetNetVar("DT_WeaponTablet", "m_nLastPurchaseIndex");
		static uintptr_t m_vecNearestMetalCratePos = GetNetVar("DT_WeaponTablet", "m_vecNearestMetalCratePos");
	}

	namespace DT_WeaponTMP
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponTMP", "baseclass");
	}

	namespace DT_WeaponShield
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponShield", "baseclass");
		static uintptr_t m_flDisplayHealth = GetNetVar("DT_WeaponShield", "m_flDisplayHealth");
	}

	namespace DT_WeaponScout
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponScout", "baseclass");
	}

	namespace DT_WeaponSawedoff
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponSawedoff", "baseclass");
		static uintptr_t m_reloadState = GetNetVar("DT_WeaponSawedoff", "m_reloadState");
	}

	namespace DT_WeaponSSG08
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponSSG08", "baseclass");
	}

	namespace DT_WeaponSG556
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponSG556", "baseclass");
	}

	namespace DT_WeaponSG552
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponSG552", "baseclass");
	}

	namespace DT_WeaponSG550
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponSG550", "baseclass");
	}

	namespace DT_WeaponSCAR20
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponSCAR20", "baseclass");
	}

	namespace DT_WeaponSCAR17
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponSCAR17", "baseclass");
	}

	namespace DT_WeaponP90
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponP90", "baseclass");
	}

	namespace DT_WeaponP250
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponP250", "baseclass");
	}

	namespace DT_WeaponP228
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponP228", "baseclass");
	}

	namespace DT_WeaponNegev
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponNegev", "baseclass");
	}

	namespace DT_WeaponNOVA
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponNOVA", "baseclass");
		static uintptr_t m_reloadState = GetNetVar("DT_WeaponNOVA", "m_reloadState");
	}

	namespace DT_WeaponMelee
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponMelee", "baseclass");
		static uintptr_t m_flThrowAt = GetNetVar("DT_WeaponMelee", "m_flThrowAt");
	}

	namespace DT_WeaponMag7
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponMag7", "baseclass");
	}

	namespace DT_WeaponMP9
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponMP9", "baseclass");
	}

	namespace DT_WeaponMP7
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponMP7", "baseclass");
	}

	namespace DT_WeaponMP5Navy
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponMP5Navy", "baseclass");
	}

	namespace DT_WeaponMAC10
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponMAC10", "baseclass");
	}

	namespace DT_WeaponM4A1
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponM4A1", "baseclass");
	}

	namespace DT_WeaponM3
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponM3", "baseclass");
		static uintptr_t m_reloadState = GetNetVar("DT_WeaponM3", "m_reloadState");
	}

	namespace DT_WeaponM249
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponM249", "baseclass");
	}

	namespace DT_WeaponKnifeGG
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponKnifeGG", "baseclass");
	}

	namespace DT_WeaponKnife
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponKnife", "baseclass");
	}

	namespace DT_WeaponHKP2000
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponHKP2000", "baseclass");
	}

	namespace DT_WeaponGlock
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponGlock", "baseclass");
	}

	namespace DT_WeaponGalilAR
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponGalilAR", "baseclass");
	}

	namespace DT_WeaponGalil
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponGalil", "baseclass");
	}

	namespace DT_WeaponG3SG1
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponG3SG1", "baseclass");
	}

	namespace DT_WeaponFiveSeven
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponFiveSeven", "baseclass");
	}

	namespace DT_WeaponFists
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponFists", "baseclass");
		static uintptr_t m_bPlayingUninterruptableAct = GetNetVar("DT_WeaponFists", "m_bPlayingUninterruptableAct");
	}

	namespace DT_WeaponFamas
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponFamas", "baseclass");
	}

	namespace DT_WeaponElite
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponElite", "baseclass");
	}

	namespace DT_WeaponDEagle
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponDEagle", "baseclass");
	}

	namespace DT_WeaponCycler
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponCycler", "baseclass");
	}

	namespace DT_WeaponCubemap
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponCubemap", "baseclass");
	}

	namespace DT_WeaponCSBaseGun
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponCSBaseGun", "baseclass");
		static uintptr_t m_zoomLevel = GetNetVar("DT_WeaponCSBaseGun", "m_zoomLevel");
		static uintptr_t m_iBurstShotsRemaining = GetNetVar("DT_WeaponCSBaseGun", "m_iBurstShotsRemaining");
	}

	namespace DT_WeaponCSBase
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponCSBase", "baseclass");
		static uintptr_t m_weaponMode = GetNetVar("DT_WeaponCSBase", "m_weaponMode");
		static uintptr_t m_fAccuracyPenalty = GetNetVar("DT_WeaponCSBase", "m_fAccuracyPenalty");
		static uintptr_t m_fLastShotTime = GetNetVar("DT_WeaponCSBase", "m_fLastShotTime");
		static uintptr_t m_iRecoilIndex = GetNetVar("DT_WeaponCSBase", "m_iRecoilIndex");
		static uintptr_t m_flRecoilIndex = GetNetVar("DT_WeaponCSBase", "m_flRecoilIndex");
		static uintptr_t m_hPrevOwner = GetNetVar("DT_WeaponCSBase", "m_hPrevOwner");
		static uintptr_t m_bBurstMode = GetNetVar("DT_WeaponCSBase", "m_bBurstMode");
		static uintptr_t m_flPostponeFireReadyTime = GetNetVar("DT_WeaponCSBase", "m_flPostponeFireReadyTime");
		static uintptr_t m_bReloadVisuallyComplete = GetNetVar("DT_WeaponCSBase", "m_bReloadVisuallyComplete");
		static uintptr_t m_bSilencerOn = GetNetVar("DT_WeaponCSBase", "m_bSilencerOn");
		static uintptr_t m_flDoneSwitchingSilencer = GetNetVar("DT_WeaponCSBase", "m_flDoneSwitchingSilencer");
		static uintptr_t m_iOriginalTeamNumber = GetNetVar("DT_WeaponCSBase", "m_iOriginalTeamNumber");
		static uintptr_t m_iIronSightMode = GetNetVar("DT_WeaponCSBase", "m_iIronSightMode");
	}

	namespace DT_WeaponC4
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponC4", "baseclass");
		static uintptr_t m_bStartedArming = GetNetVar("DT_WeaponC4", "m_bStartedArming");
		static uintptr_t m_bBombPlacedAnimation = GetNetVar("DT_WeaponC4", "m_bBombPlacedAnimation");
		static uintptr_t m_fArmedTime = GetNetVar("DT_WeaponC4", "m_fArmedTime");
		static uintptr_t m_bShowC4LED = GetNetVar("DT_WeaponC4", "m_bShowC4LED");
		static uintptr_t m_bIsPlantingViaUse = GetNetVar("DT_WeaponC4", "m_bIsPlantingViaUse");
	}

	namespace DT_WeaponBumpMine
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponBumpMine", "baseclass");
	}

	namespace DT_WeaponBreachCharge
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponBreachCharge", "baseclass");
	}

	namespace DT_WeaponBizon
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponBizon", "baseclass");
	}

	namespace DT_WeaponBaseItem
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponBaseItem", "baseclass");
		static uintptr_t m_bRedraw = GetNetVar("DT_WeaponBaseItem", "m_bRedraw");
	}

	namespace DT_WeaponAug
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponAug", "baseclass");
	}

	namespace DT_WeaponAWP
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponAWP", "baseclass");
	}

	namespace DT_WeaponAK47
	{
		static uintptr_t baseclass = GetNetVar("DT_WeaponAK47", "baseclass");
	}

	namespace DT_WaterLODControl
	{
		static uintptr_t baseclass = GetNetVar("DT_WaterLODControl", "baseclass");
		static uintptr_t m_flCheapWaterStartDistance = GetNetVar("DT_WaterLODControl", "m_flCheapWaterStartDistance");
		static uintptr_t m_flCheapWaterEndDistance = GetNetVar("DT_WaterLODControl", "m_flCheapWaterEndDistance");
	}

	namespace DT_WaterBullet
	{
		static uintptr_t baseclass = GetNetVar("DT_WaterBullet", "baseclass");
	}

	namespace DT_VoteController
	{
		static uintptr_t baseclass = GetNetVar("DT_VoteController", "baseclass");
		static uintptr_t m_iActiveIssueIndex = GetNetVar("DT_VoteController", "m_iActiveIssueIndex");
		static uintptr_t m_iOnlyTeamToVote = GetNetVar("DT_VoteController", "m_iOnlyTeamToVote");
		static uintptr_t m_nVoteOptionCount = GetNetVar("DT_VoteController", "m_nVoteOptionCount");
		static uintptr_t m_nPotentialVotes = GetNetVar("DT_VoteController", "m_nPotentialVotes");
		static uintptr_t m_bIsYesNoVote = GetNetVar("DT_VoteController", "m_bIsYesNoVote");
	}

	namespace DT_VGuiScreen
	{
		static uintptr_t baseclass = GetNetVar("DT_VGuiScreen", "baseclass");
		static uintptr_t m_flWidth = GetNetVar("DT_VGuiScreen", "m_flWidth");
		static uintptr_t m_flHeight = GetNetVar("DT_VGuiScreen", "m_flHeight");
		static uintptr_t m_fScreenFlags = GetNetVar("DT_VGuiScreen", "m_fScreenFlags");
		static uintptr_t m_nPanelName = GetNetVar("DT_VGuiScreen", "m_nPanelName");
		static uintptr_t m_nAttachmentIndex = GetNetVar("DT_VGuiScreen", "m_nAttachmentIndex");
		static uintptr_t m_nOverlayMaterial = GetNetVar("DT_VGuiScreen", "m_nOverlayMaterial");
		static uintptr_t m_hPlayerOwner = GetNetVar("DT_VGuiScreen", "m_hPlayerOwner");
	}

	namespace DT_TriggerSoundOperator
	{
		static uintptr_t baseclass = GetNetVar("DT_TriggerSoundOperator", "baseclass");
		static uintptr_t m_nSoundOperator = GetNetVar("DT_TriggerSoundOperator", "m_nSoundOperator");
	}

	namespace DT_TriggerPlayerMovement
	{
		static uintptr_t baseclass = GetNetVar("DT_TriggerPlayerMovement", "baseclass");
	}

	namespace DT_TestTraceline
	{
		static uintptr_t m_clrRender = GetNetVar("DT_TestTraceline", "m_clrRender");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TestTraceline", "m_vecOrigin");
		static uintptr_t m_angRotation_0_ = GetNetVar("DT_TestTraceline", "m_angRotation[0]");
		static uintptr_t m_angRotation_1_ = GetNetVar("DT_TestTraceline", "m_angRotation[1]");
		static uintptr_t m_angRotation_2_ = GetNetVar("DT_TestTraceline", "m_angRotation[2]");
		static uintptr_t moveparent = GetNetVar("DT_TestTraceline", "moveparent");
	}

	namespace DT_Tesla
	{
		static uintptr_t baseclass = GetNetVar("DT_Tesla", "baseclass");
		static uintptr_t m_SoundName = GetNetVar("DT_Tesla", "m_SoundName");
		static uintptr_t m_iszSpriteName = GetNetVar("DT_Tesla", "m_iszSpriteName");
	}

	namespace DT_TeamplayRoundBasedRulesProxy
	{
		static uintptr_t baseclass = GetNetVar("DT_TeamplayRoundBasedRulesProxy", "baseclass");
		static uintptr_t teamplayroundbased_gamerules_data = GetNetVar("DT_TeamplayRoundBasedRulesProxy", "teamplayroundbased_gamerules_data");
	}

	namespace DT_TeamplayRoundBasedRules
	{
		static uintptr_t m_iRoundState = GetNetVar("DT_TeamplayRoundBasedRules", "m_iRoundState");
		static uintptr_t m_bInWaitingForPlayers = GetNetVar("DT_TeamplayRoundBasedRules", "m_bInWaitingForPlayers");
		static uintptr_t m_iWinningTeam = GetNetVar("DT_TeamplayRoundBasedRules", "m_iWinningTeam");
		static uintptr_t m_bInOvertime = GetNetVar("DT_TeamplayRoundBasedRules", "m_bInOvertime");
		static uintptr_t m_bInSetup = GetNetVar("DT_TeamplayRoundBasedRules", "m_bInSetup");
		static uintptr_t m_bSwitchedTeamsThisRound = GetNetVar("DT_TeamplayRoundBasedRules", "m_bSwitchedTeamsThisRound");
		static uintptr_t m_bAwaitingReadyRestart = GetNetVar("DT_TeamplayRoundBasedRules", "m_bAwaitingReadyRestart");
		static uintptr_t m_flRestartRoundTime = GetNetVar("DT_TeamplayRoundBasedRules", "m_flRestartRoundTime");
		static uintptr_t m_flMapResetTime = GetNetVar("DT_TeamplayRoundBasedRules", "m_flMapResetTime");
		static uintptr_t m_flNextRespawnWave = GetNetVar("DT_TeamplayRoundBasedRules", "m_flNextRespawnWave");
		static uintptr_t m_TeamRespawnWaveTimes = GetNetVar("DT_TeamplayRoundBasedRules", "m_TeamRespawnWaveTimes");
		static uintptr_t m_bTeamReady = GetNetVar("DT_TeamplayRoundBasedRules", "m_bTeamReady");
		static uintptr_t m_bStopWatch = GetNetVar("DT_TeamplayRoundBasedRules", "m_bStopWatch");
	}

	namespace DT_Team
	{
		static uintptr_t m_iTeamNum = GetNetVar("DT_Team", "m_iTeamNum");
		static uintptr_t m_bSurrendered = GetNetVar("DT_Team", "m_bSurrendered");
		static uintptr_t m_scoreTotal = GetNetVar("DT_Team", "m_scoreTotal");
		static uintptr_t m_scoreFirstHalf = GetNetVar("DT_Team", "m_scoreFirstHalf");
		static uintptr_t m_scoreSecondHalf = GetNetVar("DT_Team", "m_scoreSecondHalf");
		static uintptr_t m_scoreOvertime = GetNetVar("DT_Team", "m_scoreOvertime");
		static uintptr_t m_iClanID = GetNetVar("DT_Team", "m_iClanID");
		static uintptr_t m_szTeamname = GetNetVar("DT_Team", "m_szTeamname");
		static uintptr_t m_szClanTeamname = GetNetVar("DT_Team", "m_szClanTeamname");
		static uintptr_t m_szTeamFlagImage = GetNetVar("DT_Team", "m_szTeamFlagImage");
		static uintptr_t m_szTeamLogoImage = GetNetVar("DT_Team", "m_szTeamLogoImage");
		static uintptr_t m_szTeamMatchStat = GetNetVar("DT_Team", "m_szTeamMatchStat");
		static uintptr_t m_nGGLeaderEntIndex_CT = GetNetVar("DT_Team", "m_nGGLeaderEntIndex_CT");
		static uintptr_t m_nGGLeaderEntIndex_T = GetNetVar("DT_Team", "m_nGGLeaderEntIndex_T");
		static uintptr_t m_numMapVictories = GetNetVar("DT_Team", "m_numMapVictories");
		static uintptr_t player_array_element = GetNetVar("DT_Team", "player_array_element");
		static uintptr_t player_array = GetNetVar("DT_Team", "player_array");
	}

	namespace DT_TEWorldDecal
	{
		static uintptr_t baseclass = GetNetVar("DT_TEWorldDecal", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEWorldDecal", "m_vecOrigin");
		static uintptr_t m_nIndex = GetNetVar("DT_TEWorldDecal", "m_nIndex");
	}
	namespace DT_TESpriteSpray
	{
		static uintptr_t baseclass = GetNetVar("DT_TESpriteSpray", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TESpriteSpray", "m_vecOrigin");
		static uintptr_t m_vecDirection = GetNetVar("DT_TESpriteSpray", "m_vecDirection");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TESpriteSpray", "m_nModelIndex");
		static uintptr_t m_fNoise = GetNetVar("DT_TESpriteSpray", "m_fNoise");
		static uintptr_t m_nCount = GetNetVar("DT_TESpriteSpray", "m_nCount");
		static uintptr_t m_nSpeed = GetNetVar("DT_TESpriteSpray", "m_nSpeed");
	}

	namespace DT_TESprite
	{
		static uintptr_t baseclass = GetNetVar("DT_TESprite", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TESprite", "m_vecOrigin");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TESprite", "m_nModelIndex");
		static uintptr_t m_fScale = GetNetVar("DT_TESprite", "m_fScale");
		static uintptr_t m_nBrightness = GetNetVar("DT_TESprite", "m_nBrightness");
	}

	namespace DT_TESparks
	{
		static uintptr_t baseclass = GetNetVar("DT_TESparks", "baseclass");
		static uintptr_t m_nMagnitude = GetNetVar("DT_TESparks", "m_nMagnitude");
		static uintptr_t m_nTrailLength = GetNetVar("DT_TESparks", "m_nTrailLength");
		static uintptr_t m_vecDir = GetNetVar("DT_TESparks", "m_vecDir");
	}

	namespace DT_TESmoke
	{
		static uintptr_t baseclass = GetNetVar("DT_TESmoke", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TESmoke", "m_vecOrigin");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TESmoke", "m_nModelIndex");
		static uintptr_t m_fScale = GetNetVar("DT_TESmoke", "m_fScale");
		static uintptr_t m_nFrameRate = GetNetVar("DT_TESmoke", "m_nFrameRate");
	}

	namespace DT_TEShowLine
	{
		static uintptr_t baseclass = GetNetVar("DT_TEShowLine", "baseclass");
		static uintptr_t m_vecEnd = GetNetVar("DT_TEShowLine", "m_vecEnd");
	}

	namespace DT_TEShatterSurface
	{
		static uintptr_t baseclass = GetNetVar("DT_TEShatterSurface", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEShatterSurface", "m_vecOrigin");
		static uintptr_t m_vecAngles = GetNetVar("DT_TEShatterSurface", "m_vecAngles");
		static uintptr_t m_vecForce = GetNetVar("DT_TEShatterSurface", "m_vecForce");
		static uintptr_t m_vecForcePos = GetNetVar("DT_TEShatterSurface", "m_vecForcePos");
		static uintptr_t m_flWidth = GetNetVar("DT_TEShatterSurface", "m_flWidth");
		static uintptr_t m_flHeight = GetNetVar("DT_TEShatterSurface", "m_flHeight");
		static uintptr_t m_flShardSize = GetNetVar("DT_TEShatterSurface", "m_flShardSize");
		static uintptr_t m_nSurfaceType = GetNetVar("DT_TEShatterSurface", "m_nSurfaceType");
		static uintptr_t m_uchFrontColor_0_ = GetNetVar("DT_TEShatterSurface", "m_uchFrontColor[0]");
		static uintptr_t m_uchFrontColor_1_ = GetNetVar("DT_TEShatterSurface", "m_uchFrontColor[1]");
		static uintptr_t m_uchFrontColor_2_ = GetNetVar("DT_TEShatterSurface", "m_uchFrontColor[2]");
		static uintptr_t m_uchBackColor_0_ = GetNetVar("DT_TEShatterSurface", "m_uchBackColor[0]");
		static uintptr_t m_uchBackColor_1_ = GetNetVar("DT_TEShatterSurface", "m_uchBackColor[1]");
		static uintptr_t m_uchBackColor_2_ = GetNetVar("DT_TEShatterSurface", "m_uchBackColor[2]");
	}

	namespace DT_TERadioIcon
	{
		static uintptr_t baseclass = GetNetVar("DT_TERadioIcon", "baseclass");
		static uintptr_t m_iAttachToClient = GetNetVar("DT_TERadioIcon", "m_iAttachToClient");
	}

	namespace DT_TEProjectedDecal
	{
		static uintptr_t baseclass = GetNetVar("DT_TEProjectedDecal", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEProjectedDecal", "m_vecOrigin");
		static uintptr_t m_angRotation = GetNetVar("DT_TEProjectedDecal", "m_angRotation");
		static uintptr_t m_flDistance = GetNetVar("DT_TEProjectedDecal", "m_flDistance");
		static uintptr_t m_nIndex = GetNetVar("DT_TEProjectedDecal", "m_nIndex");
	}

	namespace DT_TEPlayerDecal
	{
		static uintptr_t baseclass = GetNetVar("DT_TEPlayerDecal", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEPlayerDecal", "m_vecOrigin");
		static uintptr_t m_vecStart = GetNetVar("DT_TEPlayerDecal", "m_vecStart");
		static uintptr_t m_vecRight = GetNetVar("DT_TEPlayerDecal", "m_vecRight");
		static uintptr_t m_nEntity = GetNetVar("DT_TEPlayerDecal", "m_nEntity");
		static uintptr_t m_nPlayer = GetNetVar("DT_TEPlayerDecal", "m_nPlayer");
		static uintptr_t m_nHitbox = GetNetVar("DT_TEPlayerDecal", "m_nHitbox");
	}

	namespace DT_TEPlayerAnimEvent
	{
		static uintptr_t m_hPlayer = GetNetVar("DT_TEPlayerAnimEvent", "m_hPlayer");
		static uintptr_t m_iEvent = GetNetVar("DT_TEPlayerAnimEvent", "m_iEvent");
		static uintptr_t m_nData = GetNetVar("DT_TEPlayerAnimEvent", "m_nData");
	}

	namespace DT_TEPlantBomb
	{
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEPlantBomb", "m_vecOrigin");
		static uintptr_t m_iPlayer = GetNetVar("DT_TEPlantBomb", "m_iPlayer");
		static uintptr_t m_option = GetNetVar("DT_TEPlantBomb", "m_option");
	}

	namespace DT_TEPhysicsProp
	{
		static uintptr_t baseclass = GetNetVar("DT_TEPhysicsProp", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEPhysicsProp", "m_vecOrigin");
		static uintptr_t m_angRotation_0_ = GetNetVar("DT_TEPhysicsProp", "m_angRotation[0]");
		static uintptr_t m_angRotation_1_ = GetNetVar("DT_TEPhysicsProp", "m_angRotation[1]");
		static uintptr_t m_angRotation_2_ = GetNetVar("DT_TEPhysicsProp", "m_angRotation[2]");
		static uintptr_t m_vecVelocity = GetNetVar("DT_TEPhysicsProp", "m_vecVelocity");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TEPhysicsProp", "m_nModelIndex");
		static uintptr_t m_nFlags = GetNetVar("DT_TEPhysicsProp", "m_nFlags");
		static uintptr_t m_nSkin = GetNetVar("DT_TEPhysicsProp", "m_nSkin");
		static uintptr_t m_nEffects = GetNetVar("DT_TEPhysicsProp", "m_nEffects");
		static uintptr_t m_clrRender = GetNetVar("DT_TEPhysicsProp", "m_clrRender");
	}

	namespace DT_TEParticleSystem
	{
		static uintptr_t baseclass = GetNetVar("DT_TEParticleSystem", "baseclass");
		static uintptr_t m_vecOrigin_0_ = GetNetVar("DT_TEParticleSystem", "m_vecOrigin[0]");
		static uintptr_t m_vecOrigin_1_ = GetNetVar("DT_TEParticleSystem", "m_vecOrigin[1]");
		static uintptr_t m_vecOrigin_2_ = GetNetVar("DT_TEParticleSystem", "m_vecOrigin[2]");
	}

	namespace DT_TEMuzzleFlash
	{
		static uintptr_t baseclass = GetNetVar("DT_TEMuzzleFlash", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEMuzzleFlash", "m_vecOrigin");
		static uintptr_t m_vecAngles = GetNetVar("DT_TEMuzzleFlash", "m_vecAngles");
		static uintptr_t m_flScale = GetNetVar("DT_TEMuzzleFlash", "m_flScale");
		static uintptr_t m_nType = GetNetVar("DT_TEMuzzleFlash", "m_nType");
	}

	namespace DT_TEMetalSparks
	{
		static uintptr_t m_vecPos = GetNetVar("DT_TEMetalSparks", "m_vecPos");
		static uintptr_t m_vecDir = GetNetVar("DT_TEMetalSparks", "m_vecDir");
	}

	namespace DT_TELargeFunnel
	{
		static uintptr_t baseclass = GetNetVar("DT_TELargeFunnel", "baseclass");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TELargeFunnel", "m_nModelIndex");
		static uintptr_t m_nReversed = GetNetVar("DT_TELargeFunnel", "m_nReversed");
	}

	namespace DT_TEKillPlayerAttachments
	{
		static uintptr_t baseclass = GetNetVar("DT_TEKillPlayerAttachments", "baseclass");
		static uintptr_t m_nPlayer = GetNetVar("DT_TEKillPlayerAttachments", "m_nPlayer");
	}

	namespace DT_TEImpact
	{
		static uintptr_t baseclass = GetNetVar("DT_TEImpact", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEImpact", "m_vecOrigin");
		static uintptr_t m_vecNormal = GetNetVar("DT_TEImpact", "m_vecNormal");
		static uintptr_t m_iType = GetNetVar("DT_TEImpact", "m_iType");
		static uintptr_t m_ucFlags = GetNetVar("DT_TEImpact", "m_ucFlags");
	}

	namespace DT_TEGlowSprite
	{
		static uintptr_t baseclass = GetNetVar("DT_TEGlowSprite", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEGlowSprite", "m_vecOrigin");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TEGlowSprite", "m_nModelIndex");
		static uintptr_t m_fScale = GetNetVar("DT_TEGlowSprite", "m_fScale");
		static uintptr_t m_fLife = GetNetVar("DT_TEGlowSprite", "m_fLife");
		static uintptr_t m_nBrightness = GetNetVar("DT_TEGlowSprite", "m_nBrightness");
	}

	namespace DT_TEGaussExplosion
	{
		static uintptr_t baseclass = GetNetVar("DT_TEGaussExplosion", "baseclass");
		static uintptr_t m_nType = GetNetVar("DT_TEGaussExplosion", "m_nType");
		static uintptr_t m_vecDirection = GetNetVar("DT_TEGaussExplosion", "m_vecDirection");
	}

	namespace DT_TEFoundryHelpers
	{
		static uintptr_t baseclass = GetNetVar("DT_TEFoundryHelpers", "baseclass");
		static uintptr_t m_iEntity = GetNetVar("DT_TEFoundryHelpers", "m_iEntity");
	}

	namespace DT_TEFootprintDecal
	{
		static uintptr_t baseclass = GetNetVar("DT_TEFootprintDecal", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEFootprintDecal", "m_vecOrigin");
		static uintptr_t m_vecDirection = GetNetVar("DT_TEFootprintDecal", "m_vecDirection");
		static uintptr_t m_nEntity = GetNetVar("DT_TEFootprintDecal", "m_nEntity");
		static uintptr_t m_nIndex = GetNetVar("DT_TEFootprintDecal", "m_nIndex");
		static uintptr_t m_chMaterialType = GetNetVar("DT_TEFootprintDecal", "m_chMaterialType");
	}

	namespace DT_TEFizz
	{
		static uintptr_t baseclass = GetNetVar("DT_TEFizz", "baseclass");
		static uintptr_t m_nEntity = GetNetVar("DT_TEFizz", "m_nEntity");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TEFizz", "m_nModelIndex");
		static uintptr_t m_nDensity = GetNetVar("DT_TEFizz", "m_nDensity");
		static uintptr_t m_nCurrent = GetNetVar("DT_TEFizz", "m_nCurrent");
	}

	namespace DT_TEFireBullets
	{
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEFireBullets", "m_vecOrigin");
		static uintptr_t m_vecAngles_0_ = GetNetVar("DT_TEFireBullets", "m_vecAngles[0]");
		static uintptr_t m_vecAngles_1_ = GetNetVar("DT_TEFireBullets", "m_vecAngles[1]");
		static uintptr_t m_iWeaponID = GetNetVar("DT_TEFireBullets", "m_iWeaponID");
		static uintptr_t m_weapon = GetNetVar("DT_TEFireBullets", "m_weapon");
		static uintptr_t m_iMode = GetNetVar("DT_TEFireBullets", "m_iMode");
		static uintptr_t m_iSeed = GetNetVar("DT_TEFireBullets", "m_iSeed");
		static uintptr_t m_iPlayer = GetNetVar("DT_TEFireBullets", "m_iPlayer");
		static uintptr_t m_fInaccuracy = GetNetVar("DT_TEFireBullets", "m_fInaccuracy");
		static uintptr_t m_fSpread = GetNetVar("DT_TEFireBullets", "m_fSpread");
		static uintptr_t m_nItemDefIndex = GetNetVar("DT_TEFireBullets", "m_nItemDefIndex");
		static uintptr_t m_iSoundType = GetNetVar("DT_TEFireBullets", "m_iSoundType");
		static uintptr_t m_flRecoilIndex = GetNetVar("DT_TEFireBullets", "m_flRecoilIndex");
	}

	namespace DT_TEExplosion
	{
		static uintptr_t baseclass = GetNetVar("DT_TEExplosion", "baseclass");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TEExplosion", "m_nModelIndex");
		static uintptr_t m_fScale = GetNetVar("DT_TEExplosion", "m_fScale");
		static uintptr_t m_nFrameRate = GetNetVar("DT_TEExplosion", "m_nFrameRate");
		static uintptr_t m_nFlags = GetNetVar("DT_TEExplosion", "m_nFlags");
		static uintptr_t m_vecNormal = GetNetVar("DT_TEExplosion", "m_vecNormal");
		static uintptr_t m_chMaterialType = GetNetVar("DT_TEExplosion", "m_chMaterialType");
		static uintptr_t m_nRadius = GetNetVar("DT_TEExplosion", "m_nRadius");
		static uintptr_t m_nMagnitude = GetNetVar("DT_TEExplosion", "m_nMagnitude");
	}

	namespace DT_TEEnergySplash
	{
		static uintptr_t m_vecPos = GetNetVar("DT_TEEnergySplash", "m_vecPos");
		static uintptr_t m_vecDir = GetNetVar("DT_TEEnergySplash", "m_vecDir");
		static uintptr_t m_bExplosive = GetNetVar("DT_TEEnergySplash", "m_bExplosive");
	}

	namespace DT_TEEffectDispatch
	{
		static uintptr_t baseclass = GetNetVar("DT_TEEffectDispatch", "baseclass");
		static uintptr_t m_EffectData = GetNetVar("DT_TEEffectDispatch", "m_EffectData");
	}

	namespace DT_TEDynamicLight
	{
		static uintptr_t baseclass = GetNetVar("DT_TEDynamicLight", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEDynamicLight", "m_vecOrigin");
		static uintptr_t r = GetNetVar("DT_TEDynamicLight", "r");
		static uintptr_t g = GetNetVar("DT_TEDynamicLight", "g");
		static uintptr_t b = GetNetVar("DT_TEDynamicLight", "b");
		static uintptr_t exponent = GetNetVar("DT_TEDynamicLight", "exponent");
		static uintptr_t m_fRadius = GetNetVar("DT_TEDynamicLight", "m_fRadius");
		static uintptr_t m_fTime = GetNetVar("DT_TEDynamicLight", "m_fTime");
		static uintptr_t m_fDecay = GetNetVar("DT_TEDynamicLight", "m_fDecay");
	}

	namespace DT_TEDust
	{
		static uintptr_t baseclass = GetNetVar("DT_TEDust", "baseclass");
		static uintptr_t m_flSize = GetNetVar("DT_TEDust", "m_flSize");
		static uintptr_t m_flSpeed = GetNetVar("DT_TEDust", "m_flSpeed");
		static uintptr_t m_vecDirection = GetNetVar("DT_TEDust", "m_vecDirection");
	}

	namespace DT_TEDecal
	{
		static uintptr_t baseclass = GetNetVar("DT_TEDecal", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEDecal", "m_vecOrigin");
		static uintptr_t m_vecStart = GetNetVar("DT_TEDecal", "m_vecStart");
		static uintptr_t m_nEntity = GetNetVar("DT_TEDecal", "m_nEntity");
		static uintptr_t m_nHitbox = GetNetVar("DT_TEDecal", "m_nHitbox");
		static uintptr_t m_nIndex = GetNetVar("DT_TEDecal", "m_nIndex");
	}

	namespace DT_TEClientProjectile
	{
		static uintptr_t baseclass = GetNetVar("DT_TEClientProjectile", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEClientProjectile", "m_vecOrigin");
		static uintptr_t m_vecVelocity = GetNetVar("DT_TEClientProjectile", "m_vecVelocity");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TEClientProjectile", "m_nModelIndex");
		static uintptr_t m_nLifeTime = GetNetVar("DT_TEClientProjectile", "m_nLifeTime");
		static uintptr_t m_hOwner = GetNetVar("DT_TEClientProjectile", "m_hOwner");
	}

	namespace DT_TEBubbles
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBubbles", "baseclass");
		static uintptr_t m_vecMins = GetNetVar("DT_TEBubbles", "m_vecMins");
		static uintptr_t m_vecMaxs = GetNetVar("DT_TEBubbles", "m_vecMaxs");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TEBubbles", "m_nModelIndex");
		static uintptr_t m_fHeight = GetNetVar("DT_TEBubbles", "m_fHeight");
		static uintptr_t m_nCount = GetNetVar("DT_TEBubbles", "m_nCount");
		static uintptr_t m_fSpeed = GetNetVar("DT_TEBubbles", "m_fSpeed");
	}

	namespace DT_TEBubbleTrail
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBubbleTrail", "baseclass");
		static uintptr_t m_vecMins = GetNetVar("DT_TEBubbleTrail", "m_vecMins");
		static uintptr_t m_vecMaxs = GetNetVar("DT_TEBubbleTrail", "m_vecMaxs");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TEBubbleTrail", "m_nModelIndex");
		static uintptr_t m_flWaterZ = GetNetVar("DT_TEBubbleTrail", "m_flWaterZ");
		static uintptr_t m_nCount = GetNetVar("DT_TEBubbleTrail", "m_nCount");
		static uintptr_t m_fSpeed = GetNetVar("DT_TEBubbleTrail", "m_fSpeed");
	}

	namespace DT_TEBreakModel
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBreakModel", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEBreakModel", "m_vecOrigin");
		static uintptr_t m_angRotation_0_ = GetNetVar("DT_TEBreakModel", "m_angRotation[0]");
		static uintptr_t m_angRotation_1_ = GetNetVar("DT_TEBreakModel", "m_angRotation[1]");
		static uintptr_t m_angRotation_2_ = GetNetVar("DT_TEBreakModel", "m_angRotation[2]");
		static uintptr_t m_vecSize = GetNetVar("DT_TEBreakModel", "m_vecSize");
		static uintptr_t m_vecVelocity = GetNetVar("DT_TEBreakModel", "m_vecVelocity");
		static uintptr_t m_nModelIndex = GetNetVar("DT_TEBreakModel", "m_nModelIndex");
		static uintptr_t m_nRandomization = GetNetVar("DT_TEBreakModel", "m_nRandomization");
		static uintptr_t m_nCount = GetNetVar("DT_TEBreakModel", "m_nCount");
		static uintptr_t m_fTime = GetNetVar("DT_TEBreakModel", "m_fTime");
		static uintptr_t m_nFlags = GetNetVar("DT_TEBreakModel", "m_nFlags");
	}

	namespace DT_TEBloodStream
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBloodStream", "baseclass");
		static uintptr_t m_vecDirection = GetNetVar("DT_TEBloodStream", "m_vecDirection");
		static uintptr_t r = GetNetVar("DT_TEBloodStream", "r");
		static uintptr_t g = GetNetVar("DT_TEBloodStream", "g");
		static uintptr_t b = GetNetVar("DT_TEBloodStream", "b");
		static uintptr_t a = GetNetVar("DT_TEBloodStream", "a");
		static uintptr_t m_nAmount = GetNetVar("DT_TEBloodStream", "m_nAmount");
	}

	namespace DT_TEBloodSprite
	{
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEBloodSprite", "m_vecOrigin");
		static uintptr_t m_vecDirection = GetNetVar("DT_TEBloodSprite", "m_vecDirection");
		static uintptr_t r = GetNetVar("DT_TEBloodSprite", "r");
		static uintptr_t g = GetNetVar("DT_TEBloodSprite", "g");
		static uintptr_t b = GetNetVar("DT_TEBloodSprite", "b");
		static uintptr_t a = GetNetVar("DT_TEBloodSprite", "a");
		static uintptr_t m_nSprayModel = GetNetVar("DT_TEBloodSprite", "m_nSprayModel");
		static uintptr_t m_nDropModel = GetNetVar("DT_TEBloodSprite", "m_nDropModel");
		static uintptr_t m_nSize = GetNetVar("DT_TEBloodSprite", "m_nSize");
	}

	namespace DT_TEBeamSpline
	{
		static uintptr_t m_nPoints = GetNetVar("DT_TEBeamSpline", "m_nPoints");
		static uintptr_t m_vecPoints_0_ = GetNetVar("DT_TEBeamSpline", "m_vecPoints[0]");
		static uintptr_t m_vecPoints = GetNetVar("DT_TEBeamSpline", "m_vecPoints");
	}

	namespace DT_TEBeamRingPoint
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBeamRingPoint", "baseclass");
		static uintptr_t m_vecCenter = GetNetVar("DT_TEBeamRingPoint", "m_vecCenter");
		static uintptr_t m_flStartRadius = GetNetVar("DT_TEBeamRingPoint", "m_flStartRadius");
		static uintptr_t m_flEndRadius = GetNetVar("DT_TEBeamRingPoint", "m_flEndRadius");
	}

	namespace DT_TEBeamRing
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBeamRing", "baseclass");
		static uintptr_t m_nStartEntity = GetNetVar("DT_TEBeamRing", "m_nStartEntity");
		static uintptr_t m_nEndEntity = GetNetVar("DT_TEBeamRing", "m_nEndEntity");
	}

	namespace DT_TEBeamPoints
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBeamPoints", "baseclass");
		static uintptr_t m_vecStartPoint = GetNetVar("DT_TEBeamPoints", "m_vecStartPoint");
		static uintptr_t m_vecEndPoint = GetNetVar("DT_TEBeamPoints", "m_vecEndPoint");
	}

	namespace DT_TEBeamLaser
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBeamLaser", "baseclass");
		static uintptr_t m_nStartEntity = GetNetVar("DT_TEBeamLaser", "m_nStartEntity");
		static uintptr_t m_nEndEntity = GetNetVar("DT_TEBeamLaser", "m_nEndEntity");
	}

	namespace DT_TEBeamFollow
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBeamFollow", "baseclass");
		static uintptr_t m_iEntIndex = GetNetVar("DT_TEBeamFollow", "m_iEntIndex");
	}

	namespace DT_TEBeamEnts
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBeamEnts", "baseclass");
		static uintptr_t m_nStartEntity = GetNetVar("DT_TEBeamEnts", "m_nStartEntity");
		static uintptr_t m_nEndEntity = GetNetVar("DT_TEBeamEnts", "m_nEndEntity");
	}

	namespace DT_TEBeamEntPoint
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBeamEntPoint", "baseclass");
		static uintptr_t m_nStartEntity = GetNetVar("DT_TEBeamEntPoint", "m_nStartEntity");
		static uintptr_t m_nEndEntity = GetNetVar("DT_TEBeamEntPoint", "m_nEndEntity");
		static uintptr_t m_vecStartPoint = GetNetVar("DT_TEBeamEntPoint", "m_vecStartPoint");
		static uintptr_t m_vecEndPoint = GetNetVar("DT_TEBeamEntPoint", "m_vecEndPoint");
	}

	namespace DT_TEBSPDecal
	{
		static uintptr_t baseclass = GetNetVar("DT_TEBSPDecal", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_TEBSPDecal", "m_vecOrigin");
		static uintptr_t m_nEntity = GetNetVar("DT_TEBSPDecal", "m_nEntity");
		static uintptr_t m_nIndex = GetNetVar("DT_TEBSPDecal", "m_nIndex");
	}

	namespace DT_TEArmorRicochet
	{
		static uintptr_t baseclass = GetNetVar("DT_TEArmorRicochet", "baseclass");
	}

	namespace DT_SurvivalSpawnChopper
	{
		static uintptr_t baseclass = GetNetVar("DT_SurvivalSpawnChopper", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_SurvivalSpawnChopper", "m_vecOrigin");
		static uintptr_t m_vecOrigin_2_ = GetNetVar("DT_SurvivalSpawnChopper", "m_vecOrigin[2]");
	}

	namespace DT_SurvivalGameRules
	{
		static uintptr_t m_vecPlayAreaMins = GetNetVar("DT_SurvivalGameRules", "m_vecPlayAreaMins");
		static uintptr_t m_vecPlayAreaMaxs = GetNetVar("DT_SurvivalGameRules", "m_vecPlayAreaMaxs");
		static uintptr_t m_iPlayerSpawnHexIndices = GetNetVar("DT_SurvivalGameRules", "m_iPlayerSpawnHexIndices");
		static uintptr_t m_SpawnTileState = GetNetVar("DT_SurvivalGameRules", "m_SpawnTileState");
		static uintptr_t m_flSpawnSelectionTimeStart = GetNetVar("DT_SurvivalGameRules", "m_flSpawnSelectionTimeStart");
		static uintptr_t m_flSpawnSelectionTimeEnd = GetNetVar("DT_SurvivalGameRules", "m_flSpawnSelectionTimeEnd");
		static uintptr_t m_flSpawnSelectionTimeLoadout = GetNetVar("DT_SurvivalGameRules", "m_flSpawnSelectionTimeLoadout");
		static uintptr_t m_spawnStage = GetNetVar("DT_SurvivalGameRules", "m_spawnStage");
		static uintptr_t m_flTabletHexOriginX = GetNetVar("DT_SurvivalGameRules", "m_flTabletHexOriginX");
		static uintptr_t m_flTabletHexOriginY = GetNetVar("DT_SurvivalGameRules", "m_flTabletHexOriginY");
		static uintptr_t m_flTabletHexSize = GetNetVar("DT_SurvivalGameRules", "m_flTabletHexSize");
		static uintptr_t m_roundData_playerXuids = GetNetVar("DT_SurvivalGameRules", "m_roundData_playerXuids");
		static uintptr_t m_roundData_playerPositions = GetNetVar("DT_SurvivalGameRules", "m_roundData_playerPositions");
		static uintptr_t m_roundData_playerTeams = GetNetVar("DT_SurvivalGameRules", "m_roundData_playerTeams");
		static uintptr_t m_SurvivalGameRuleDecisionTypes = GetNetVar("DT_SurvivalGameRules", "m_SurvivalGameRuleDecisionTypes");
		static uintptr_t m_SurvivalGameRuleDecisionValues = GetNetVar("DT_SurvivalGameRules", "m_SurvivalGameRuleDecisionValues");
		static uintptr_t m_flSurvivalStartTime = GetNetVar("DT_SurvivalGameRules", "m_flSurvivalStartTime");
	}

	namespace DT_SunlightShadowControl
	{
		static uintptr_t baseclass = GetNetVar("DT_SunlightShadowControl", "baseclass");
		static uintptr_t m_shadowDirection = GetNetVar("DT_SunlightShadowControl", "m_shadowDirection");
		static uintptr_t m_bEnabled = GetNetVar("DT_SunlightShadowControl", "m_bEnabled");
		static uintptr_t m_TextureName = GetNetVar("DT_SunlightShadowControl", "m_TextureName");
		static uintptr_t m_LightColor = GetNetVar("DT_SunlightShadowControl", "m_LightColor");
		static uintptr_t m_flColorTransitionTime = GetNetVar("DT_SunlightShadowControl", "m_flColorTransitionTime");
		static uintptr_t m_flSunDistance = GetNetVar("DT_SunlightShadowControl", "m_flSunDistance");
		static uintptr_t m_flFOV = GetNetVar("DT_SunlightShadowControl", "m_flFOV");
		static uintptr_t m_flNearZ = GetNetVar("DT_SunlightShadowControl", "m_flNearZ");
		static uintptr_t m_flNorthOffset = GetNetVar("DT_SunlightShadowControl", "m_flNorthOffset");
		static uintptr_t m_bEnableShadows = GetNetVar("DT_SunlightShadowControl", "m_bEnableShadows");
	}

	namespace DT_Sun
	{
		static uintptr_t m_clrRender = GetNetVar("DT_Sun", "m_clrRender");
		static uintptr_t m_clrOverlay = GetNetVar("DT_Sun", "m_clrOverlay");
		static uintptr_t m_vDirection = GetNetVar("DT_Sun", "m_vDirection");
		static uintptr_t m_bOn = GetNetVar("DT_Sun", "m_bOn");
		static uintptr_t m_nSize = GetNetVar("DT_Sun", "m_nSize");
		static uintptr_t m_nOverlaySize = GetNetVar("DT_Sun", "m_nOverlaySize");
		static uintptr_t m_nMaterial = GetNetVar("DT_Sun", "m_nMaterial");
		static uintptr_t m_nOverlayMaterial = GetNetVar("DT_Sun", "m_nOverlayMaterial");
		static uintptr_t HDRColorScale = GetNetVar("DT_Sun", "HDRColorScale");
		static uintptr_t glowDistanceScale = GetNetVar("DT_Sun", "glowDistanceScale");
	}

	namespace DT_SteamJet
	{
		static uintptr_t baseclass = GetNetVar("DT_SteamJet", "baseclass");
		static uintptr_t m_SpreadSpeed = GetNetVar("DT_SteamJet", "m_SpreadSpeed");
		static uintptr_t m_Speed = GetNetVar("DT_SteamJet", "m_Speed");
		static uintptr_t m_StartSize = GetNetVar("DT_SteamJet", "m_StartSize");
		static uintptr_t m_EndSize = GetNetVar("DT_SteamJet", "m_EndSize");
		static uintptr_t m_Rate = GetNetVar("DT_SteamJet", "m_Rate");
		static uintptr_t m_JetLength = GetNetVar("DT_SteamJet", "m_JetLength");
		static uintptr_t m_bEmit = GetNetVar("DT_SteamJet", "m_bEmit");
		static uintptr_t m_bFaceLeft = GetNetVar("DT_SteamJet", "m_bFaceLeft");
		static uintptr_t m_nType = GetNetVar("DT_SteamJet", "m_nType");
		static uintptr_t m_spawnflags = GetNetVar("DT_SteamJet", "m_spawnflags");
		static uintptr_t m_flRollSpeed = GetNetVar("DT_SteamJet", "m_flRollSpeed");
	}

	namespace DT_StatueProp
	{
		static uintptr_t baseclass = GetNetVar("DT_StatueProp", "baseclass");
		static uintptr_t m_hInitBaseAnimating = GetNetVar("DT_StatueProp", "m_hInitBaseAnimating");
		static uintptr_t m_bShatter = GetNetVar("DT_StatueProp", "m_bShatter");
		static uintptr_t m_nShatterFlags = GetNetVar("DT_StatueProp", "m_nShatterFlags");
		static uintptr_t m_vShatterPosition = GetNetVar("DT_StatueProp", "m_vShatterPosition");
		static uintptr_t m_vShatterForce = GetNetVar("DT_StatueProp", "m_vShatterForce");
	}

	namespace DT_SpriteTrail
	{
		static uintptr_t baseclass = GetNetVar("DT_SpriteTrail", "baseclass");
		static uintptr_t m_flLifeTime = GetNetVar("DT_SpriteTrail", "m_flLifeTime");
		static uintptr_t m_flStartWidth = GetNetVar("DT_SpriteTrail", "m_flStartWidth");
		static uintptr_t m_flEndWidth = GetNetVar("DT_SpriteTrail", "m_flEndWidth");
		static uintptr_t m_flStartWidthVariance = GetNetVar("DT_SpriteTrail", "m_flStartWidthVariance");
		static uintptr_t m_flTextureRes = GetNetVar("DT_SpriteTrail", "m_flTextureRes");
		static uintptr_t m_flMinFadeLength = GetNetVar("DT_SpriteTrail", "m_flMinFadeLength");
		static uintptr_t m_vecSkyboxOrigin = GetNetVar("DT_SpriteTrail", "m_vecSkyboxOrigin");
		static uintptr_t m_flSkyboxScale = GetNetVar("DT_SpriteTrail", "m_flSkyboxScale");
	}

	namespace DT_SpriteOriented
	{
		static uintptr_t baseclass = GetNetVar("DT_SpriteOriented", "baseclass");
	}

	namespace DT_Sprite
	{
		static uintptr_t baseclass = GetNetVar("DT_Sprite", "baseclass");
		static uintptr_t m_hAttachedToEntity = GetNetVar("DT_Sprite", "m_hAttachedToEntity");
		static uintptr_t m_nAttachment = GetNetVar("DT_Sprite", "m_nAttachment");
		static uintptr_t m_flScaleTime = GetNetVar("DT_Sprite", "m_flScaleTime");
		static uintptr_t m_flSpriteScale = GetNetVar("DT_Sprite", "m_flSpriteScale");
		static uintptr_t m_flSpriteFramerate = GetNetVar("DT_Sprite", "m_flSpriteFramerate");
		static uintptr_t m_flGlowProxySize = GetNetVar("DT_Sprite", "m_flGlowProxySize");
		static uintptr_t m_flHDRColorScale = GetNetVar("DT_Sprite", "m_flHDRColorScale");
		static uintptr_t m_flFrame = GetNetVar("DT_Sprite", "m_flFrame");
		static uintptr_t m_flBrightnessTime = GetNetVar("DT_Sprite", "m_flBrightnessTime");
		static uintptr_t m_nBrightness = GetNetVar("DT_Sprite", "m_nBrightness");
		static uintptr_t m_bWorldSpaceScale = GetNetVar("DT_Sprite", "m_bWorldSpaceScale");
	}

	namespace DT_SpotlightEnd
	{
		static uintptr_t baseclass = GetNetVar("DT_SpotlightEnd", "baseclass");
		static uintptr_t m_flLightScale = GetNetVar("DT_SpotlightEnd", "m_flLightScale");
		static uintptr_t m_Radius = GetNetVar("DT_SpotlightEnd", "m_Radius");
	}

	namespace DT_SporeTrail
	{
		static uintptr_t baseclass = GetNetVar("DT_SporeTrail", "baseclass");
		static uintptr_t m_flSpawnRate = GetNetVar("DT_SporeTrail", "m_flSpawnRate");
		static uintptr_t m_vecEndColor = GetNetVar("DT_SporeTrail", "m_vecEndColor");
		static uintptr_t m_flParticleLifetime = GetNetVar("DT_SporeTrail", "m_flParticleLifetime");
		static uintptr_t m_flStartSize = GetNetVar("DT_SporeTrail", "m_flStartSize");
		static uintptr_t m_flEndSize = GetNetVar("DT_SporeTrail", "m_flEndSize");
		static uintptr_t m_flSpawnRadius = GetNetVar("DT_SporeTrail", "m_flSpawnRadius");
		static uintptr_t m_bEmit = GetNetVar("DT_SporeTrail", "m_bEmit");
	}

	namespace DT_SporeExplosion
	{
		static uintptr_t baseclass = GetNetVar("DT_SporeExplosion", "baseclass");
		static uintptr_t m_flSpawnRate = GetNetVar("DT_SporeExplosion", "m_flSpawnRate");
		static uintptr_t m_flParticleLifetime = GetNetVar("DT_SporeExplosion", "m_flParticleLifetime");
		static uintptr_t m_flStartSize = GetNetVar("DT_SporeExplosion", "m_flStartSize");
		static uintptr_t m_flEndSize = GetNetVar("DT_SporeExplosion", "m_flEndSize");
		static uintptr_t m_flSpawnRadius = GetNetVar("DT_SporeExplosion", "m_flSpawnRadius");
		static uintptr_t m_bEmit = GetNetVar("DT_SporeExplosion", "m_bEmit");
		static uintptr_t m_bDontRemove = GetNetVar("DT_SporeExplosion", "m_bDontRemove");
	}

	namespace DT_SpatialEntity
	{
		static uintptr_t baseclass = GetNetVar("DT_SpatialEntity", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_SpatialEntity", "m_vecOrigin");
		static uintptr_t m_minFalloff = GetNetVar("DT_SpatialEntity", "m_minFalloff");
		static uintptr_t m_maxFalloff = GetNetVar("DT_SpatialEntity", "m_maxFalloff");
		static uintptr_t m_flCurWeight = GetNetVar("DT_SpatialEntity", "m_flCurWeight");
		static uintptr_t m_bEnabled = GetNetVar("DT_SpatialEntity", "m_bEnabled");
	}

	namespace DT_SnowballProjectile
	{
		static uintptr_t baseclass = GetNetVar("DT_SnowballProjectile", "baseclass");
	}

	namespace DT_SnowballPile
	{
		static uintptr_t baseclass = GetNetVar("DT_SnowballPile", "baseclass");
	}

	namespace DT_Snowball
	{
		static uintptr_t baseclass = GetNetVar("DT_Snowball", "baseclass");
	}

	namespace DT_SmokeTrail
	{
		static uintptr_t baseclass = GetNetVar("DT_SmokeTrail", "baseclass");
		static uintptr_t m_SpawnRate = GetNetVar("DT_SmokeTrail", "m_SpawnRate");
		static uintptr_t m_StartColor = GetNetVar("DT_SmokeTrail", "m_StartColor");
		static uintptr_t m_EndColor = GetNetVar("DT_SmokeTrail", "m_EndColor");
		static uintptr_t m_ParticleLifetime = GetNetVar("DT_SmokeTrail", "m_ParticleLifetime");
		static uintptr_t m_StopEmitTime = GetNetVar("DT_SmokeTrail", "m_StopEmitTime");
		static uintptr_t m_MinSpeed = GetNetVar("DT_SmokeTrail", "m_MinSpeed");
		static uintptr_t m_MaxSpeed = GetNetVar("DT_SmokeTrail", "m_MaxSpeed");
		static uintptr_t m_MinDirectedSpeed = GetNetVar("DT_SmokeTrail", "m_MinDirectedSpeed");
		static uintptr_t m_MaxDirectedSpeed = GetNetVar("DT_SmokeTrail", "m_MaxDirectedSpeed");
		static uintptr_t m_StartSize = GetNetVar("DT_SmokeTrail", "m_StartSize");
		static uintptr_t m_EndSize = GetNetVar("DT_SmokeTrail", "m_EndSize");
		static uintptr_t m_SpawnRadius = GetNetVar("DT_SmokeTrail", "m_SpawnRadius");
		static uintptr_t m_bEmit = GetNetVar("DT_SmokeTrail", "m_bEmit");
		static uintptr_t m_nAttachment = GetNetVar("DT_SmokeTrail", "m_nAttachment");
		static uintptr_t m_Opacity = GetNetVar("DT_SmokeTrail", "m_Opacity");
	}

	namespace DT_SmokeStack
	{
		static uintptr_t baseclass = GetNetVar("DT_SmokeStack", "baseclass");
		static uintptr_t m_SpreadSpeed = GetNetVar("DT_SmokeStack", "m_SpreadSpeed");
		static uintptr_t m_Speed = GetNetVar("DT_SmokeStack", "m_Speed");
		static uintptr_t m_StartSize = GetNetVar("DT_SmokeStack", "m_StartSize");
		static uintptr_t m_EndSize = GetNetVar("DT_SmokeStack", "m_EndSize");
		static uintptr_t m_Rate = GetNetVar("DT_SmokeStack", "m_Rate");
		static uintptr_t m_JetLength = GetNetVar("DT_SmokeStack", "m_JetLength");
		static uintptr_t m_bEmit = GetNetVar("DT_SmokeStack", "m_bEmit");
		static uintptr_t m_flBaseSpread = GetNetVar("DT_SmokeStack", "m_flBaseSpread");
		static uintptr_t m_flTwist = GetNetVar("DT_SmokeStack", "m_flTwist");
		static uintptr_t m_flRollSpeed = GetNetVar("DT_SmokeStack", "m_flRollSpeed");
		static uintptr_t m_iMaterialModel = GetNetVar("DT_SmokeStack", "m_iMaterialModel");
		static uintptr_t m_AmbientLight_m_vPos = GetNetVar("DT_SmokeStack", "m_AmbientLight.m_vPos");
		static uintptr_t m_AmbientLight_m_vColor = GetNetVar("DT_SmokeStack", "m_AmbientLight.m_vColor");
		static uintptr_t m_AmbientLight_m_flIntensity = GetNetVar("DT_SmokeStack", "m_AmbientLight.m_flIntensity");
		static uintptr_t m_DirLight_m_vPos = GetNetVar("DT_SmokeStack", "m_DirLight.m_vPos");
		static uintptr_t m_DirLight_m_vColor = GetNetVar("DT_SmokeStack", "m_DirLight.m_vColor");
		static uintptr_t m_DirLight_m_flIntensity = GetNetVar("DT_SmokeStack", "m_DirLight.m_flIntensity");
		static uintptr_t m_vWind = GetNetVar("DT_SmokeStack", "m_vWind");
	}

	namespace DT_SmokeGrenadeProjectile
	{
		static uintptr_t baseclass = GetNetVar("DT_SmokeGrenadeProjectile", "baseclass");
		static uintptr_t m_bDidSmokeEffect = GetNetVar("DT_SmokeGrenadeProjectile", "m_bDidSmokeEffect");
		static uintptr_t m_nSmokeEffectTickBegin = GetNetVar("DT_SmokeGrenadeProjectile", "m_nSmokeEffectTickBegin");
	}

	namespace DT_SmokeGrenade
	{
		static uintptr_t baseclass = GetNetVar("DT_SmokeGrenade", "baseclass");
	}

	namespace DT_SlideshowDisplay
	{
		static uintptr_t baseclass = GetNetVar("DT_SlideshowDisplay", "baseclass");
		static uintptr_t m_bEnabled = GetNetVar("DT_SlideshowDisplay", "m_bEnabled");
		static uintptr_t m_szDisplayText = GetNetVar("DT_SlideshowDisplay", "m_szDisplayText");
		static uintptr_t m_szSlideshowDirectory = GetNetVar("DT_SlideshowDisplay", "m_szSlideshowDirectory");
		static uintptr_t m_chCurrentSlideLists = GetNetVar("DT_SlideshowDisplay", "m_chCurrentSlideLists");
		static uintptr_t m_fMinSlideTime = GetNetVar("DT_SlideshowDisplay", "m_fMinSlideTime");
		static uintptr_t m_fMaxSlideTime = GetNetVar("DT_SlideshowDisplay", "m_fMaxSlideTime");
		static uintptr_t m_iCycleType = GetNetVar("DT_SlideshowDisplay", "m_iCycleType");
		static uintptr_t m_bNoListRepeats = GetNetVar("DT_SlideshowDisplay", "m_bNoListRepeats");
	}

	namespace DT_ShadowControl
	{
		static uintptr_t baseclass = GetNetVar("DT_ShadowControl", "baseclass");
		static uintptr_t m_shadowDirection = GetNetVar("DT_ShadowControl", "m_shadowDirection");
		static uintptr_t m_shadowColor = GetNetVar("DT_ShadowControl", "m_shadowColor");
		static uintptr_t m_flShadowMaxDist = GetNetVar("DT_ShadowControl", "m_flShadowMaxDist");
		static uintptr_t m_bDisableShadows = GetNetVar("DT_ShadowControl", "m_bDisableShadows");
		static uintptr_t m_bEnableLocalLightShadows = GetNetVar("DT_ShadowControl", "m_bEnableLocalLightShadows");
	}

	namespace DT_ServerAnimationData
	{
		static uintptr_t m_flCycle = GetNetVar("DT_ServerAnimationData", "m_flCycle");
	}

	namespace DT_SensorGrenadeProjectile
	{
		static uintptr_t baseclass = GetNetVar("DT_SensorGrenadeProjectile", "baseclass");
	}

	namespace DT_SensorGrenade
	{
		static uintptr_t baseclass = GetNetVar("DT_SensorGrenade", "baseclass");
	}

	namespace DT_ScriptCreatedItem
	{
		static uintptr_t m_iItemDefinitionIndex = GetNetVar("DT_ScriptCreatedItem", "m_iItemDefinitionIndex");
		static uintptr_t m_iEntityLevel = GetNetVar("DT_ScriptCreatedItem", "m_iEntityLevel");
		static uintptr_t m_iItemIDHigh = GetNetVar("DT_ScriptCreatedItem", "m_iItemIDHigh");
		static uintptr_t m_iItemIDLow = GetNetVar("DT_ScriptCreatedItem", "m_iItemIDLow");
		static uintptr_t m_iAccountID = GetNetVar("DT_ScriptCreatedItem", "m_iAccountID");
		static uintptr_t m_iEntityQuality = GetNetVar("DT_ScriptCreatedItem", "m_iEntityQuality");
		static uintptr_t m_bInitialized = GetNetVar("DT_ScriptCreatedItem", "m_bInitialized");
		static uintptr_t m_szCustomName = GetNetVar("DT_ScriptCreatedItem", "m_szCustomName");
		static uintptr_t m_NetworkedDynamicAttributesForDemos = GetNetVar("DT_ScriptCreatedItem", "m_NetworkedDynamicAttributesForDemos");
	}

	namespace DT_SceneEntity
	{
		static uintptr_t baseclass = GetNetVar("DT_SceneEntity", "baseclass");
		static uintptr_t m_nSceneStringIndex = GetNetVar("DT_SceneEntity", "m_nSceneStringIndex");
		static uintptr_t m_bIsPlayingBack = GetNetVar("DT_SceneEntity", "m_bIsPlayingBack");
		static uintptr_t m_bPaused = GetNetVar("DT_SceneEntity", "m_bPaused");
		static uintptr_t m_bMultiplayer = GetNetVar("DT_SceneEntity", "m_bMultiplayer");
		static uintptr_t m_flForceClientTime = GetNetVar("DT_SceneEntity", "m_flForceClientTime");
		static uintptr_t m_hActorList = GetNetVar("DT_SceneEntity", "m_hActorList");
	}

	namespace DT_RopeKeyframe
	{
		static uintptr_t m_nChangeCount = GetNetVar("DT_RopeKeyframe", "m_nChangeCount");
		static uintptr_t m_iRopeMaterialModelIndex = GetNetVar("DT_RopeKeyframe", "m_iRopeMaterialModelIndex");
		static uintptr_t m_hStartPoint = GetNetVar("DT_RopeKeyframe", "m_hStartPoint");
		static uintptr_t m_hEndPoint = GetNetVar("DT_RopeKeyframe", "m_hEndPoint");
		static uintptr_t m_iStartAttachment = GetNetVar("DT_RopeKeyframe", "m_iStartAttachment");
		static uintptr_t m_iEndAttachment = GetNetVar("DT_RopeKeyframe", "m_iEndAttachment");
		static uintptr_t m_fLockedPoints = GetNetVar("DT_RopeKeyframe", "m_fLockedPoints");
		static uintptr_t m_Slack = GetNetVar("DT_RopeKeyframe", "m_Slack");
		static uintptr_t m_RopeLength = GetNetVar("DT_RopeKeyframe", "m_RopeLength");
		static uintptr_t m_RopeFlags = GetNetVar("DT_RopeKeyframe", "m_RopeFlags");
		static uintptr_t m_TextureScale = GetNetVar("DT_RopeKeyframe", "m_TextureScale");
		static uintptr_t m_nSegments = GetNetVar("DT_RopeKeyframe", "m_nSegments");
		static uintptr_t m_bConstrainBetweenEndpoints = GetNetVar("DT_RopeKeyframe", "m_bConstrainBetweenEndpoints");
		static uintptr_t m_Subdiv = GetNetVar("DT_RopeKeyframe", "m_Subdiv");
		static uintptr_t m_Width = GetNetVar("DT_RopeKeyframe", "m_Width");
		static uintptr_t m_flScrollSpeed = GetNetVar("DT_RopeKeyframe", "m_flScrollSpeed");
		static uintptr_t m_vecOrigin = GetNetVar("DT_RopeKeyframe", "m_vecOrigin");
		static uintptr_t moveparent = GetNetVar("DT_RopeKeyframe", "moveparent");
		static uintptr_t m_iParentAttachment = GetNetVar("DT_RopeKeyframe", "m_iParentAttachment");
		static uintptr_t m_iDefaultRopeMaterialModelIndex = GetNetVar("DT_RopeKeyframe", "m_iDefaultRopeMaterialModelIndex");
		static uintptr_t m_nMinCPULevel = GetNetVar("DT_RopeKeyframe", "m_nMinCPULevel");
		static uintptr_t m_nMaxCPULevel = GetNetVar("DT_RopeKeyframe", "m_nMaxCPULevel");
		static uintptr_t m_nMinGPULevel = GetNetVar("DT_RopeKeyframe", "m_nMinGPULevel");
		static uintptr_t m_nMaxGPULevel = GetNetVar("DT_RopeKeyframe", "m_nMaxGPULevel");
	}

	namespace DT_RocketTrail
	{
		static uintptr_t baseclass = GetNetVar("DT_RocketTrail", "baseclass");
		static uintptr_t m_SpawnRate = GetNetVar("DT_RocketTrail", "m_SpawnRate");
		static uintptr_t m_StartColor = GetNetVar("DT_RocketTrail", "m_StartColor");
		static uintptr_t m_EndColor = GetNetVar("DT_RocketTrail", "m_EndColor");
		static uintptr_t m_ParticleLifetime = GetNetVar("DT_RocketTrail", "m_ParticleLifetime");
		static uintptr_t m_StopEmitTime = GetNetVar("DT_RocketTrail", "m_StopEmitTime");
		static uintptr_t m_MinSpeed = GetNetVar("DT_RocketTrail", "m_MinSpeed");
		static uintptr_t m_MaxSpeed = GetNetVar("DT_RocketTrail", "m_MaxSpeed");
		static uintptr_t m_StartSize = GetNetVar("DT_RocketTrail", "m_StartSize");
		static uintptr_t m_EndSize = GetNetVar("DT_RocketTrail", "m_EndSize");
		static uintptr_t m_SpawnRadius = GetNetVar("DT_RocketTrail", "m_SpawnRadius");
		static uintptr_t m_bEmit = GetNetVar("DT_RocketTrail", "m_bEmit");
		static uintptr_t m_nAttachment = GetNetVar("DT_RocketTrail", "m_nAttachment");
		static uintptr_t m_Opacity = GetNetVar("DT_RocketTrail", "m_Opacity");
		static uintptr_t m_bDamaged = GetNetVar("DT_RocketTrail", "m_bDamaged");
		static uintptr_t m_flFlareScale = GetNetVar("DT_RocketTrail", "m_flFlareScale");
	}

	namespace DT_RetakeGameRules
	{
		static uintptr_t m_nMatchSeed = GetNetVar("DT_RetakeGameRules", "m_nMatchSeed");
		static uintptr_t m_bBlockersPresent = GetNetVar("DT_RetakeGameRules", "m_bBlockersPresent");
		static uintptr_t m_bRoundInProgress = GetNetVar("DT_RetakeGameRules", "m_bRoundInProgress");
		static uintptr_t m_iFirstSecondHalfRound = GetNetVar("DT_RetakeGameRules", "m_iFirstSecondHalfRound");
		static uintptr_t m_iBombSite = GetNetVar("DT_RetakeGameRules", "m_iBombSite");
	}

	namespace DT_Ragdoll_Attached
	{
		static uintptr_t baseclass = GetNetVar("DT_Ragdoll_Attached", "baseclass");
		static uintptr_t m_boneIndexAttached = GetNetVar("DT_Ragdoll_Attached", "m_boneIndexAttached");
		static uintptr_t m_ragdollAttachedObjectIndex = GetNetVar("DT_Ragdoll_Attached", "m_ragdollAttachedObjectIndex");
		static uintptr_t m_attachmentPointBoneSpace = GetNetVar("DT_Ragdoll_Attached", "m_attachmentPointBoneSpace");
		static uintptr_t m_attachmentPointRagdollSpace = GetNetVar("DT_Ragdoll_Attached", "m_attachmentPointRagdollSpace");
	}

	namespace DT_RagdollManager
	{
		static uintptr_t m_iCurrentMaxRagdollCount = GetNetVar("DT_RagdollManager", "m_iCurrentMaxRagdollCount");
	}

	namespace DT_Ragdoll
	{
		static uintptr_t baseclass = GetNetVar("DT_Ragdoll", "baseclass");
		static uintptr_t m_ragAngles_0_ = GetNetVar("DT_Ragdoll", "m_ragAngles[0]");
		static uintptr_t m_ragAngles = GetNetVar("DT_Ragdoll", "m_ragAngles");
		static uintptr_t m_ragPos_0_ = GetNetVar("DT_Ragdoll", "m_ragPos[0]");
		static uintptr_t m_ragPos = GetNetVar("DT_Ragdoll", "m_ragPos");
		static uintptr_t m_hUnragdoll = GetNetVar("DT_Ragdoll", "m_hUnragdoll");
		static uintptr_t m_flBlendWeight = GetNetVar("DT_Ragdoll", "m_flBlendWeight");
		static uintptr_t m_nOverlaySequence = GetNetVar("DT_Ragdoll", "m_nOverlaySequence");
	}

	namespace DT_QuadraticBeam
	{
		static uintptr_t baseclass = GetNetVar("DT_QuadraticBeam", "baseclass");
		static uintptr_t m_targetPosition = GetNetVar("DT_QuadraticBeam", "m_targetPosition");
		static uintptr_t m_controlPosition = GetNetVar("DT_QuadraticBeam", "m_controlPosition");
		static uintptr_t m_scrollRate = GetNetVar("DT_QuadraticBeam", "m_scrollRate");
		static uintptr_t m_flWidth = GetNetVar("DT_QuadraticBeam", "m_flWidth");
	}

	namespace DT_ProxyToggle_ProxiedData
	{
		static uintptr_t m_WithProxy = GetNetVar("DT_ProxyToggle_ProxiedData", "m_WithProxy");
	}

	namespace DT_ProxyToggle
	{
		static uintptr_t baseclass = GetNetVar("DT_ProxyToggle", "baseclass");
		static uintptr_t blah = GetNetVar("DT_ProxyToggle", "blah");
	}

	namespace DT_Prop_Hallucination
	{
		static uintptr_t baseclass = GetNetVar("DT_Prop_Hallucination", "baseclass");
		static uintptr_t m_bEnabled = GetNetVar("DT_Prop_Hallucination", "m_bEnabled");
		static uintptr_t m_fVisibleTime = GetNetVar("DT_Prop_Hallucination", "m_fVisibleTime");
		static uintptr_t m_fRechargeTime = GetNetVar("DT_Prop_Hallucination", "m_fRechargeTime");
	}

	namespace DT_PropVehicleDriveable
	{
		static uintptr_t baseclass = GetNetVar("DT_PropVehicleDriveable", "baseclass");
		static uintptr_t m_hPlayer = GetNetVar("DT_PropVehicleDriveable", "m_hPlayer");
		static uintptr_t m_nSpeed = GetNetVar("DT_PropVehicleDriveable", "m_nSpeed");
		static uintptr_t m_nRPM = GetNetVar("DT_PropVehicleDriveable", "m_nRPM");
		static uintptr_t m_flThrottle = GetNetVar("DT_PropVehicleDriveable", "m_flThrottle");
		static uintptr_t m_nBoostTimeLeft = GetNetVar("DT_PropVehicleDriveable", "m_nBoostTimeLeft");
		static uintptr_t m_nHasBoost = GetNetVar("DT_PropVehicleDriveable", "m_nHasBoost");
		static uintptr_t m_nScannerDisabledWeapons = GetNetVar("DT_PropVehicleDriveable", "m_nScannerDisabledWeapons");
		static uintptr_t m_nScannerDisabledVehicle = GetNetVar("DT_PropVehicleDriveable", "m_nScannerDisabledVehicle");
		static uintptr_t m_bEnterAnimOn = GetNetVar("DT_PropVehicleDriveable", "m_bEnterAnimOn");
		static uintptr_t m_bExitAnimOn = GetNetVar("DT_PropVehicleDriveable", "m_bExitAnimOn");
		static uintptr_t m_bUnableToFire = GetNetVar("DT_PropVehicleDriveable", "m_bUnableToFire");
		static uintptr_t m_vecEyeExitEndpoint = GetNetVar("DT_PropVehicleDriveable", "m_vecEyeExitEndpoint");
		static uintptr_t m_bHasGun = GetNetVar("DT_PropVehicleDriveable", "m_bHasGun");
		static uintptr_t m_vecGunCrosshair = GetNetVar("DT_PropVehicleDriveable", "m_vecGunCrosshair");
	}

	namespace DT_PropVehicleChoreoGeneric
	{
		static uintptr_t baseclass = GetNetVar("DT_PropVehicleChoreoGeneric", "baseclass");
		static uintptr_t m_hPlayer = GetNetVar("DT_PropVehicleChoreoGeneric", "m_hPlayer");
		static uintptr_t m_bEnterAnimOn = GetNetVar("DT_PropVehicleChoreoGeneric", "m_bEnterAnimOn");
		static uintptr_t m_bExitAnimOn = GetNetVar("DT_PropVehicleChoreoGeneric", "m_bExitAnimOn");
		static uintptr_t m_bForceEyesToAttachment = GetNetVar("DT_PropVehicleChoreoGeneric", "m_bForceEyesToAttachment");
		static uintptr_t m_vecEyeExitEndpoint = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vecEyeExitEndpoint");
		static uintptr_t m_vehicleView_bClampEyeAngles = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vehicleView.bClampEyeAngles");
		static uintptr_t m_vehicleView_flPitchCurveZero = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vehicleView.flPitchCurveZero");
		static uintptr_t m_vehicleView_flPitchCurveLinear = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vehicleView.flPitchCurveLinear");
		static uintptr_t m_vehicleView_flRollCurveZero = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vehicleView.flRollCurveZero");
		static uintptr_t m_vehicleView_flRollCurveLinear = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vehicleView.flRollCurveLinear");
		static uintptr_t m_vehicleView_flFOV = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vehicleView.flFOV");
		static uintptr_t m_vehicleView_flYawMin = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vehicleView.flYawMin");
		static uintptr_t m_vehicleView_flYawMax = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vehicleView.flYawMax");
		static uintptr_t m_vehicleView_flPitchMin = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vehicleView.flPitchMin");
		static uintptr_t m_vehicleView_flPitchMax = GetNetVar("DT_PropVehicleChoreoGeneric", "m_vehicleView.flPitchMax");
	}

	namespace DT_PropJeep
	{
		static uintptr_t baseclass = GetNetVar("DT_PropJeep", "baseclass");
		static uintptr_t m_bHeadlightIsOn = GetNetVar("DT_PropJeep", "m_bHeadlightIsOn");
	}

	namespace DT_PropDoorRotating
	{
		static uintptr_t baseclass = GetNetVar("DT_PropDoorRotating", "baseclass");
	}

	namespace DT_PropCounter
	{
		static uintptr_t baseclass = GetNetVar("DT_PropCounter", "baseclass");
		static uintptr_t m_flDisplayValue = GetNetVar("DT_PropCounter", "m_flDisplayValue");
	}

	namespace DT_PredictedViewModel
	{
		static uintptr_t baseclass = GetNetVar("DT_PredictedViewModel", "baseclass");
	}

	namespace DT_PrecipitationBlocker
	{
		static uintptr_t baseclass = GetNetVar("DT_PrecipitationBlocker", "baseclass");
	}

	namespace DT_Precipitation
	{
		static uintptr_t baseclass = GetNetVar("DT_Precipitation", "baseclass");
		static uintptr_t m_nPrecipType = GetNetVar("DT_Precipitation", "m_nPrecipType");
	}

	namespace DT_PostProcessController
	{
		static uintptr_t baseclass = GetNetVar("DT_PostProcessController", "baseclass");
		static uintptr_t m_flPostProcessParameters = GetNetVar("DT_PostProcessController", "m_flPostProcessParameters");
		static uintptr_t m_bMaster = GetNetVar("DT_PostProcessController", "m_bMaster");
	}

	namespace DT_PoseController
	{
		static uintptr_t baseclass = GetNetVar("DT_PoseController", "baseclass");
		static uintptr_t m_hProps = GetNetVar("DT_PoseController", "m_hProps");
		static uintptr_t m_chPoseIndex = GetNetVar("DT_PoseController", "m_chPoseIndex");
		static uintptr_t m_bPoseValueParity = GetNetVar("DT_PoseController", "m_bPoseValueParity");
		static uintptr_t m_fPoseValue = GetNetVar("DT_PoseController", "m_fPoseValue");
		static uintptr_t m_fInterpolationTime = GetNetVar("DT_PoseController", "m_fInterpolationTime");
		static uintptr_t m_bInterpolationWrap = GetNetVar("DT_PoseController", "m_bInterpolationWrap");
		static uintptr_t m_fCycleFrequency = GetNetVar("DT_PoseController", "m_fCycleFrequency");
		static uintptr_t m_nFModType = GetNetVar("DT_PoseController", "m_nFModType");
		static uintptr_t m_fFModTimeOffset = GetNetVar("DT_PoseController", "m_fFModTimeOffset");
		static uintptr_t m_fFModRate = GetNetVar("DT_PoseController", "m_fFModRate");
		static uintptr_t m_fFModAmplitude = GetNetVar("DT_PoseController", "m_fFModAmplitude");
	}

	namespace DT_PointWorldText
	{
		static uintptr_t baseclass = GetNetVar("DT_PointWorldText", "baseclass");
		static uintptr_t m_szText = GetNetVar("DT_PointWorldText", "m_szText");
		static uintptr_t m_flTextSize = GetNetVar("DT_PointWorldText", "m_flTextSize");
		static uintptr_t m_textColor = GetNetVar("DT_PointWorldText", "m_textColor");
	}

	namespace DT_PointCommentaryNode
	{
		static uintptr_t baseclass = GetNetVar("DT_PointCommentaryNode", "baseclass");
		static uintptr_t m_bActive = GetNetVar("DT_PointCommentaryNode", "m_bActive");
		static uintptr_t m_flStartTime = GetNetVar("DT_PointCommentaryNode", "m_flStartTime");
		static uintptr_t m_iszCommentaryFile = GetNetVar("DT_PointCommentaryNode", "m_iszCommentaryFile");
		static uintptr_t m_iszCommentaryFileNoHDR = GetNetVar("DT_PointCommentaryNode", "m_iszCommentaryFileNoHDR");
		static uintptr_t m_iszSpeakers = GetNetVar("DT_PointCommentaryNode", "m_iszSpeakers");
		static uintptr_t m_iNodeNumber = GetNetVar("DT_PointCommentaryNode", "m_iNodeNumber");
		static uintptr_t m_iNodeNumberMax = GetNetVar("DT_PointCommentaryNode", "m_iNodeNumberMax");
		static uintptr_t m_hViewPosition = GetNetVar("DT_PointCommentaryNode", "m_hViewPosition");
	}

	namespace DT_PointCamera
	{
		static uintptr_t baseclass = GetNetVar("DT_PointCamera", "baseclass");
		static uintptr_t m_FOV = GetNetVar("DT_PointCamera", "m_FOV");
		static uintptr_t m_Resolution = GetNetVar("DT_PointCamera", "m_Resolution");
		static uintptr_t m_bFogEnable = GetNetVar("DT_PointCamera", "m_bFogEnable");
		static uintptr_t m_FogColor = GetNetVar("DT_PointCamera", "m_FogColor");
		static uintptr_t m_flFogStart = GetNetVar("DT_PointCamera", "m_flFogStart");
		static uintptr_t m_flFogEnd = GetNetVar("DT_PointCamera", "m_flFogEnd");
		static uintptr_t m_flFogMaxDensity = GetNetVar("DT_PointCamera", "m_flFogMaxDensity");
		static uintptr_t m_bActive = GetNetVar("DT_PointCamera", "m_bActive");
		static uintptr_t m_bUseScreenAspectRatio = GetNetVar("DT_PointCamera", "m_bUseScreenAspectRatio");
	}

	namespace DT_PlayerState
	{
		static uintptr_t deadflag = GetNetVar("DT_PlayerState", "deadflag");
	}

	namespace DT_PlayerResource
	{
		static uintptr_t m_iPing = GetNetVar("DT_PlayerResource", "m_iPing");
		static uintptr_t m_iKills = GetNetVar("DT_PlayerResource", "m_iKills");
		static uintptr_t m_iAssists = GetNetVar("DT_PlayerResource", "m_iAssists");
		static uintptr_t m_iDeaths = GetNetVar("DT_PlayerResource", "m_iDeaths");
		static uintptr_t m_bConnected = GetNetVar("DT_PlayerResource", "m_bConnected");
		static uintptr_t m_iTeam = GetNetVar("DT_PlayerResource", "m_iTeam");
		static uintptr_t m_iPendingTeam = GetNetVar("DT_PlayerResource", "m_iPendingTeam");
		static uintptr_t m_bAlive = GetNetVar("DT_PlayerResource", "m_bAlive");
		static uintptr_t m_iHealth = GetNetVar("DT_PlayerResource", "m_iHealth");
		static uintptr_t m_iCoachingTeam = GetNetVar("DT_PlayerResource", "m_iCoachingTeam");
	}

	namespace DT_PlayerPing
	{
		static uintptr_t baseclass = GetNetVar("DT_PlayerPing", "baseclass");
		static uintptr_t m_hPlayer = GetNetVar("DT_PlayerPing", "m_hPlayer");
		static uintptr_t m_hPingedEntity = GetNetVar("DT_PlayerPing", "m_hPingedEntity");
		static uintptr_t m_iType = GetNetVar("DT_PlayerPing", "m_iType");
		static uintptr_t m_bUrgent = GetNetVar("DT_PlayerPing", "m_bUrgent");
		static uintptr_t m_szPlaceName = GetNetVar("DT_PlayerPing", "m_szPlaceName");
	}

	namespace DT_Plasma
	{
		static uintptr_t baseclass = GetNetVar("DT_Plasma", "baseclass");
		static uintptr_t m_flStartScale = GetNetVar("DT_Plasma", "m_flStartScale");
		static uintptr_t m_flScale = GetNetVar("DT_Plasma", "m_flScale");
		static uintptr_t m_flScaleTime = GetNetVar("DT_Plasma", "m_flScaleTime");
		static uintptr_t m_nFlags = GetNetVar("DT_Plasma", "m_nFlags");
		static uintptr_t m_nPlasmaModelIndex = GetNetVar("DT_Plasma", "m_nPlasmaModelIndex");
		static uintptr_t m_nPlasmaModelIndex2 = GetNetVar("DT_Plasma", "m_nPlasmaModelIndex2");
		static uintptr_t m_nGlowModelIndex = GetNetVar("DT_Plasma", "m_nGlowModelIndex");
	}

	namespace DT_PlantedC4
	{
		static uintptr_t baseclass = GetNetVar("DT_PlantedC4", "baseclass");
		static uintptr_t m_bBombTicking = GetNetVar("DT_PlantedC4", "m_bBombTicking");
		static uintptr_t m_nBombSite = GetNetVar("DT_PlantedC4", "m_nBombSite");
		static uintptr_t m_flC4Blow = GetNetVar("DT_PlantedC4", "m_flC4Blow");
		static uintptr_t m_flTimerLength = GetNetVar("DT_PlantedC4", "m_flTimerLength");
		static uintptr_t m_flDefuseLength = GetNetVar("DT_PlantedC4", "m_flDefuseLength");
		static uintptr_t m_flDefuseCountDown = GetNetVar("DT_PlantedC4", "m_flDefuseCountDown");
		static uintptr_t m_bBombDefused = GetNetVar("DT_PlantedC4", "m_bBombDefused");
		static uintptr_t m_hBombDefuser = GetNetVar("DT_PlantedC4", "m_hBombDefuser");
	}

	namespace DT_PhysicsPropMultiplayer
	{
		static uintptr_t baseclass = GetNetVar("DT_PhysicsPropMultiplayer", "baseclass");
		static uintptr_t m_iPhysicsMode = GetNetVar("DT_PhysicsPropMultiplayer", "m_iPhysicsMode");
		static uintptr_t m_fMass = GetNetVar("DT_PhysicsPropMultiplayer", "m_fMass");
		static uintptr_t m_collisionMins = GetNetVar("DT_PhysicsPropMultiplayer", "m_collisionMins");
		static uintptr_t m_collisionMaxs = GetNetVar("DT_PhysicsPropMultiplayer", "m_collisionMaxs");
	}

	namespace DT_PhysicsProp
	{
		static uintptr_t baseclass = GetNetVar("DT_PhysicsProp", "baseclass");
		static uintptr_t m_bAwake = GetNetVar("DT_PhysicsProp", "m_bAwake");
		static uintptr_t m_spawnflags = GetNetVar("DT_PhysicsProp", "m_spawnflags");
	}

	namespace DT_PhysPropWeaponUpgrade
	{
		static uintptr_t baseclass = GetNetVar("DT_PhysPropWeaponUpgrade", "baseclass");
	}

	namespace DT_PhysPropRadarJammer
	{
		static uintptr_t baseclass = GetNetVar("DT_PhysPropRadarJammer", "baseclass");
	}

	namespace DT_PhysPropLootCrate
	{
		static uintptr_t baseclass = GetNetVar("DT_PhysPropLootCrate", "baseclass");
		static uintptr_t m_bRenderInPSPM = GetNetVar("DT_PhysPropLootCrate", "m_bRenderInPSPM");
		static uintptr_t m_bRenderInTablet = GetNetVar("DT_PhysPropLootCrate", "m_bRenderInTablet");
		static uintptr_t m_iHealth = GetNetVar("DT_PhysPropLootCrate", "m_iHealth");
		static uintptr_t m_iMaxHealth = GetNetVar("DT_PhysPropLootCrate", "m_iMaxHealth");
	}

	namespace DT_PhysPropAmmoBox
	{
		static uintptr_t baseclass = GetNetVar("DT_PhysPropAmmoBox", "baseclass");
	}

	namespace DT_PhysMagnet
	{
		static uintptr_t baseclass = GetNetVar("DT_PhysMagnet", "baseclass");
	}

	namespace DT_PhysBoxMultiplayer
	{
		static uintptr_t baseclass = GetNetVar("DT_PhysBoxMultiplayer", "baseclass");
		static uintptr_t m_iPhysicsMode = GetNetVar("DT_PhysBoxMultiplayer", "m_iPhysicsMode");
		static uintptr_t m_fMass = GetNetVar("DT_PhysBoxMultiplayer", "m_fMass");
	}

	namespace DT_PhysBox
	{
		static uintptr_t baseclass = GetNetVar("DT_PhysBox", "baseclass");
		static uintptr_t m_mass = GetNetVar("DT_PhysBox", "m_mass");
	}

	namespace DT_ParticleSystem
	{
		static uintptr_t m_vecOrigin = GetNetVar("DT_ParticleSystem", "m_vecOrigin");
		static uintptr_t m_fEffects = GetNetVar("DT_ParticleSystem", "m_fEffects");
		static uintptr_t m_hOwnerEntity = GetNetVar("DT_ParticleSystem", "m_hOwnerEntity");
		static uintptr_t moveparent = GetNetVar("DT_ParticleSystem", "moveparent");
		static uintptr_t m_iParentAttachment = GetNetVar("DT_ParticleSystem", "m_iParentAttachment");
		static uintptr_t m_angRotation = GetNetVar("DT_ParticleSystem", "m_angRotation");
		static uintptr_t m_iEffectIndex = GetNetVar("DT_ParticleSystem", "m_iEffectIndex");
		static uintptr_t m_bActive = GetNetVar("DT_ParticleSystem", "m_bActive");
		static uintptr_t m_nStopType = GetNetVar("DT_ParticleSystem", "m_nStopType");
		static uintptr_t m_flStartTime = GetNetVar("DT_ParticleSystem", "m_flStartTime");
		static uintptr_t m_szSnapshotFileName = GetNetVar("DT_ParticleSystem", "m_szSnapshotFileName");
		static uintptr_t m_vServerControlPoints = GetNetVar("DT_ParticleSystem", "m_vServerControlPoints");
		static uintptr_t m_iServerControlPointAssignments = GetNetVar("DT_ParticleSystem", "m_iServerControlPointAssignments");
		static uintptr_t m_hControlPointEnts = GetNetVar("DT_ParticleSystem", "m_hControlPointEnts");
		static uintptr_t m_iControlPointParents = GetNetVar("DT_ParticleSystem", "m_iControlPointParents");
	}

	namespace DT_ParticleSmokeGrenade
	{
		static uintptr_t baseclass = GetNetVar("DT_ParticleSmokeGrenade", "baseclass");
		static uintptr_t m_flSpawnTime = GetNetVar("DT_ParticleSmokeGrenade", "m_flSpawnTime");
		static uintptr_t m_FadeStartTime = GetNetVar("DT_ParticleSmokeGrenade", "m_FadeStartTime");
		static uintptr_t m_FadeEndTime = GetNetVar("DT_ParticleSmokeGrenade", "m_FadeEndTime");
		static uintptr_t m_MinColor = GetNetVar("DT_ParticleSmokeGrenade", "m_MinColor");
		static uintptr_t m_MaxColor = GetNetVar("DT_ParticleSmokeGrenade", "m_MaxColor");
		static uintptr_t m_CurrentStage = GetNetVar("DT_ParticleSmokeGrenade", "m_CurrentStage");
	}

	namespace DT_ParticlePerformanceMonitor
	{
		static uintptr_t baseclass = GetNetVar("DT_ParticlePerformanceMonitor", "baseclass");
		static uintptr_t m_bMeasurePerf = GetNetVar("DT_ParticlePerformanceMonitor", "m_bMeasurePerf");
		static uintptr_t m_bDisplayPerf = GetNetVar("DT_ParticlePerformanceMonitor", "m_bDisplayPerf");
	}

	namespace DT_ParticleFire
	{
		static uintptr_t m_vOrigin = GetNetVar("DT_ParticleFire", "m_vOrigin");
		static uintptr_t m_vDirection = GetNetVar("DT_ParticleFire", "m_vDirection");
	}

	namespace DT_ParadropChopper
	{
		static uintptr_t baseclass = GetNetVar("DT_ParadropChopper", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_ParadropChopper", "m_vecOrigin");
		static uintptr_t m_vecOrigin_2_ = GetNetVar("DT_ParadropChopper", "m_vecOrigin[2]");
		static uintptr_t m_hCallingPlayer = GetNetVar("DT_ParadropChopper", "m_hCallingPlayer");
	}

	namespace DT_OverlayVars
	{
		static uintptr_t m_AnimOverlay = GetNetVar("DT_OverlayVars", "m_AnimOverlay");
	}

	namespace DT_NextBot
	{
		static uintptr_t baseclass = GetNetVar("DT_NextBot", "baseclass");
	}

	namespace DT_MovieExplosion
	{
		static uintptr_t baseclass = GetNetVar("DT_MovieExplosion", "baseclass");
	}

	namespace DT_MovieDisplay
	{
		static uintptr_t baseclass = GetNetVar("DT_MovieDisplay", "baseclass");
		static uintptr_t m_bEnabled = GetNetVar("DT_MovieDisplay", "m_bEnabled");
		static uintptr_t m_bLooping = GetNetVar("DT_MovieDisplay", "m_bLooping");
		static uintptr_t m_szMovieFilename = GetNetVar("DT_MovieDisplay", "m_szMovieFilename");
		static uintptr_t m_szGroupName = GetNetVar("DT_MovieDisplay", "m_szGroupName");
		static uintptr_t m_bStretchToFill = GetNetVar("DT_MovieDisplay", "m_bStretchToFill");
		static uintptr_t m_bForcedSlave = GetNetVar("DT_MovieDisplay", "m_bForcedSlave");
		static uintptr_t m_bUseCustomUVs = GetNetVar("DT_MovieDisplay", "m_bUseCustomUVs");
		static uintptr_t m_flUMin = GetNetVar("DT_MovieDisplay", "m_flUMin");
		static uintptr_t m_flUMax = GetNetVar("DT_MovieDisplay", "m_flUMax");
		static uintptr_t m_flVMin = GetNetVar("DT_MovieDisplay", "m_flVMin");
		static uintptr_t m_flVMax = GetNetVar("DT_MovieDisplay", "m_flVMax");
	}

	namespace DT_MolotovProjectile
	{
		static uintptr_t baseclass = GetNetVar("DT_MolotovProjectile", "baseclass");
		static uintptr_t m_bIsIncGrenade = GetNetVar("DT_MolotovProjectile", "m_bIsIncGrenade");
	}

	namespace DT_MolotovGrenade
	{
		static uintptr_t baseclass = GetNetVar("DT_MolotovGrenade", "baseclass");
	}

	namespace DT_MaterialModifyControl
	{
		static uintptr_t baseclass = GetNetVar("DT_MaterialModifyControl", "baseclass");
		static uintptr_t m_szMaterialName = GetNetVar("DT_MaterialModifyControl", "m_szMaterialName");
		static uintptr_t m_szMaterialVar = GetNetVar("DT_MaterialModifyControl", "m_szMaterialVar");
		static uintptr_t m_szMaterialVarValue = GetNetVar("DT_MaterialModifyControl", "m_szMaterialVarValue");
		static uintptr_t m_iFrameStart = GetNetVar("DT_MaterialModifyControl", "m_iFrameStart");
		static uintptr_t m_iFrameEnd = GetNetVar("DT_MaterialModifyControl", "m_iFrameEnd");
		static uintptr_t m_bWrap = GetNetVar("DT_MaterialModifyControl", "m_bWrap");
		static uintptr_t m_flFramerate = GetNetVar("DT_MaterialModifyControl", "m_flFramerate");
		static uintptr_t m_bNewAnimCommandsSemaphore = GetNetVar("DT_MaterialModifyControl", "m_bNewAnimCommandsSemaphore");
		static uintptr_t m_flFloatLerpStartValue = GetNetVar("DT_MaterialModifyControl", "m_flFloatLerpStartValue");
		static uintptr_t m_flFloatLerpEndValue = GetNetVar("DT_MaterialModifyControl", "m_flFloatLerpEndValue");
		static uintptr_t m_flFloatLerpTransitionTime = GetNetVar("DT_MaterialModifyControl", "m_flFloatLerpTransitionTime");
		static uintptr_t m_bFloatLerpWrap = GetNetVar("DT_MaterialModifyControl", "m_bFloatLerpWrap");
		static uintptr_t m_nModifyMode = GetNetVar("DT_MaterialModifyControl", "m_nModifyMode");
	}

	namespace DT_MapVetoPickController
	{
		static uintptr_t baseclass = GetNetVar("DT_MapVetoPickController", "baseclass");
		static uintptr_t m_nDraftType = GetNetVar("DT_MapVetoPickController", "m_nDraftType");
		static uintptr_t m_nTeamWinningCoinToss = GetNetVar("DT_MapVetoPickController", "m_nTeamWinningCoinToss");
		static uintptr_t m_nTeamWithFirstChoice = GetNetVar("DT_MapVetoPickController", "m_nTeamWithFirstChoice");
		static uintptr_t m_nVoteMapIdsList = GetNetVar("DT_MapVetoPickController", "m_nVoteMapIdsList");
		static uintptr_t m_nAccountIDs = GetNetVar("DT_MapVetoPickController", "m_nAccountIDs");
		static uintptr_t m_nMapId0 = GetNetVar("DT_MapVetoPickController", "m_nMapId0");
		static uintptr_t m_nMapId1 = GetNetVar("DT_MapVetoPickController", "m_nMapId1");
		static uintptr_t m_nMapId2 = GetNetVar("DT_MapVetoPickController", "m_nMapId2");
		static uintptr_t m_nMapId3 = GetNetVar("DT_MapVetoPickController", "m_nMapId3");
		static uintptr_t m_nMapId4 = GetNetVar("DT_MapVetoPickController", "m_nMapId4");
		static uintptr_t m_nMapId5 = GetNetVar("DT_MapVetoPickController", "m_nMapId5");
		static uintptr_t m_nStartingSide0 = GetNetVar("DT_MapVetoPickController", "m_nStartingSide0");
		static uintptr_t m_nCurrentPhase = GetNetVar("DT_MapVetoPickController", "m_nCurrentPhase");
		static uintptr_t m_nPhaseStartTick = GetNetVar("DT_MapVetoPickController", "m_nPhaseStartTick");
		static uintptr_t m_nPhaseDurationTicks = GetNetVar("DT_MapVetoPickController", "m_nPhaseDurationTicks");
	}

	namespace DT_LocalWeaponData
	{
		static uintptr_t m_iPrimaryAmmoType = GetNetVar("DT_LocalWeaponData", "m_iPrimaryAmmoType");
		static uintptr_t m_iSecondaryAmmoType = GetNetVar("DT_LocalWeaponData", "m_iSecondaryAmmoType");
		static uintptr_t m_nViewModelIndex = GetNetVar("DT_LocalWeaponData", "m_nViewModelIndex");
		static uintptr_t m_bFlipViewModel = GetNetVar("DT_LocalWeaponData", "m_bFlipViewModel");
		static uintptr_t m_iWeaponOrigin = GetNetVar("DT_LocalWeaponData", "m_iWeaponOrigin");
		static uintptr_t m_iWeaponModule = GetNetVar("DT_LocalWeaponData", "m_iWeaponModule");
	}

	namespace DT_LocalPlayerExclusive
	{
		static uintptr_t m_Local = GetNetVar("DT_LocalPlayerExclusive", "m_Local");
		static uintptr_t m_vecViewOffset_0_ = GetNetVar("DT_LocalPlayerExclusive", "m_vecViewOffset[0]");
		static uintptr_t m_vecViewOffset_1_ = GetNetVar("DT_LocalPlayerExclusive", "m_vecViewOffset[1]");
		static uintptr_t m_vecViewOffset_2_ = GetNetVar("DT_LocalPlayerExclusive", "m_vecViewOffset[2]");
		static uintptr_t m_flFriction = GetNetVar("DT_LocalPlayerExclusive", "m_flFriction");
		static uintptr_t m_fOnTarget = GetNetVar("DT_LocalPlayerExclusive", "m_fOnTarget");
		static uintptr_t m_nTickBase = GetNetVar("DT_LocalPlayerExclusive", "m_nTickBase");
		static uintptr_t m_nNextThinkTick = GetNetVar("DT_LocalPlayerExclusive", "m_nNextThinkTick");
		static uintptr_t m_hLastWeapon = GetNetVar("DT_LocalPlayerExclusive", "m_hLastWeapon");
		static uintptr_t m_vecVelocity_0_ = GetNetVar("DT_LocalPlayerExclusive", "m_vecVelocity[0]");
		static uintptr_t m_vecVelocity_1_ = GetNetVar("DT_LocalPlayerExclusive", "m_vecVelocity[1]");
		static uintptr_t m_vecVelocity_2_ = GetNetVar("DT_LocalPlayerExclusive", "m_vecVelocity[2]");
		static uintptr_t m_vecBaseVelocity = GetNetVar("DT_LocalPlayerExclusive", "m_vecBaseVelocity");
		static uintptr_t m_hConstraintEntity = GetNetVar("DT_LocalPlayerExclusive", "m_hConstraintEntity");
		static uintptr_t m_vecConstraintCenter = GetNetVar("DT_LocalPlayerExclusive", "m_vecConstraintCenter");
		static uintptr_t m_flConstraintRadius = GetNetVar("DT_LocalPlayerExclusive", "m_flConstraintRadius");
		static uintptr_t m_flConstraintWidth = GetNetVar("DT_LocalPlayerExclusive", "m_flConstraintWidth");
		static uintptr_t m_flConstraintSpeedFactor = GetNetVar("DT_LocalPlayerExclusive", "m_flConstraintSpeedFactor");
		static uintptr_t m_bConstraintPastRadius = GetNetVar("DT_LocalPlayerExclusive", "m_bConstraintPastRadius");
		static uintptr_t m_flDeathTime = GetNetVar("DT_LocalPlayerExclusive", "m_flDeathTime");
		static uintptr_t m_flNextDecalTime = GetNetVar("DT_LocalPlayerExclusive", "m_flNextDecalTime");
		static uintptr_t m_fForceTeam = GetNetVar("DT_LocalPlayerExclusive", "m_fForceTeam");
		static uintptr_t m_flLaggedMovementValue = GetNetVar("DT_LocalPlayerExclusive", "m_flLaggedMovementValue");
		static uintptr_t m_hTonemapController = GetNetVar("DT_LocalPlayerExclusive", "m_hTonemapController");
	}

	namespace DT_LocalActiveWeaponData
	{
		static uintptr_t m_flNextPrimaryAttack = GetNetVar("DT_LocalActiveWeaponData", "m_flNextPrimaryAttack");
		static uintptr_t m_flNextSecondaryAttack = GetNetVar("DT_LocalActiveWeaponData", "m_flNextSecondaryAttack");
		static uintptr_t m_nNextThinkTick = GetNetVar("DT_LocalActiveWeaponData", "m_nNextThinkTick");
		static uintptr_t m_flTimeWeaponIdle = GetNetVar("DT_LocalActiveWeaponData", "m_flTimeWeaponIdle");
	}

	namespace DT_Local
	{
		static uintptr_t m_chAreaBits = GetNetVar("DT_Local", "m_chAreaBits");
		static uintptr_t m_chAreaPortalBits = GetNetVar("DT_Local", "m_chAreaPortalBits");
		static uintptr_t m_iHideHUD = GetNetVar("DT_Local", "m_iHideHUD");
		static uintptr_t m_flFOVRate = GetNetVar("DT_Local", "m_flFOVRate");
		static uintptr_t m_bDucked = GetNetVar("DT_Local", "m_bDucked");
		static uintptr_t m_bDucking = GetNetVar("DT_Local", "m_bDucking");
		static uintptr_t m_flLastDuckTime = GetNetVar("DT_Local", "m_flLastDuckTime");
		static uintptr_t m_bInDuckJump = GetNetVar("DT_Local", "m_bInDuckJump");
		static uintptr_t m_nDuckTimeMsecs = GetNetVar("DT_Local", "m_nDuckTimeMsecs");
		static uintptr_t m_nDuckJumpTimeMsecs = GetNetVar("DT_Local", "m_nDuckJumpTimeMsecs");
		static uintptr_t m_nJumpTimeMsecs = GetNetVar("DT_Local", "m_nJumpTimeMsecs");
		static uintptr_t m_flFallVelocity = GetNetVar("DT_Local", "m_flFallVelocity");
		static uintptr_t m_viewPunchAngle = GetNetVar("DT_Local", "m_viewPunchAngle");
		static uintptr_t m_aimPunchAngle = GetNetVar("DT_Local", "m_aimPunchAngle");
		static uintptr_t m_aimPunchAngleVel = GetNetVar("DT_Local", "m_aimPunchAngleVel");
		static uintptr_t m_bDrawViewmodel = GetNetVar("DT_Local", "m_bDrawViewmodel");
		static uintptr_t m_bWearingSuit = GetNetVar("DT_Local", "m_bWearingSuit");
		static uintptr_t m_bPoisoned = GetNetVar("DT_Local", "m_bPoisoned");
		static uintptr_t m_flStepSize = GetNetVar("DT_Local", "m_flStepSize");
		static uintptr_t m_bAllowAutoMovement = GetNetVar("DT_Local", "m_bAllowAutoMovement");
		static uintptr_t m_skybox3d_scale = GetNetVar("DT_Local", "m_skybox3d.scale");
		static uintptr_t m_skybox3d_origin = GetNetVar("DT_Local", "m_skybox3d.origin");
		static uintptr_t m_skybox3d_area = GetNetVar("DT_Local", "m_skybox3d.area");
		static uintptr_t m_skybox3d_fog_enable = GetNetVar("DT_Local", "m_skybox3d.fog.enable");
		static uintptr_t m_skybox3d_fog_blend = GetNetVar("DT_Local", "m_skybox3d.fog.blend");
		static uintptr_t m_skybox3d_fog_dirPrimary = GetNetVar("DT_Local", "m_skybox3d.fog.dirPrimary");
		static uintptr_t m_skybox3d_fog_colorPrimary = GetNetVar("DT_Local", "m_skybox3d.fog.colorPrimary");
		static uintptr_t m_skybox3d_fog_colorSecondary = GetNetVar("DT_Local", "m_skybox3d.fog.colorSecondary");
		static uintptr_t m_skybox3d_fog_start = GetNetVar("DT_Local", "m_skybox3d.fog.start");
		static uintptr_t m_skybox3d_fog_end = GetNetVar("DT_Local", "m_skybox3d.fog.end");
		static uintptr_t m_skybox3d_fog_maxdensity = GetNetVar("DT_Local", "m_skybox3d.fog.maxdensity");
		static uintptr_t m_skybox3d_fog_HDRColorScale = GetNetVar("DT_Local", "m_skybox3d.fog.HDRColorScale");
		static uintptr_t m_audio_localSound_0_ = GetNetVar("DT_Local", "m_audio.localSound[0]");
		static uintptr_t m_audio_localSound_1_ = GetNetVar("DT_Local", "m_audio.localSound[1]");
		static uintptr_t m_audio_localSound_2_ = GetNetVar("DT_Local", "m_audio.localSound[2]");
		static uintptr_t m_audio_localSound_3_ = GetNetVar("DT_Local", "m_audio.localSound[3]");
		static uintptr_t m_audio_localSound_4_ = GetNetVar("DT_Local", "m_audio.localSound[4]");
		static uintptr_t m_audio_localSound_5_ = GetNetVar("DT_Local", "m_audio.localSound[5]");
		static uintptr_t m_audio_localSound_6_ = GetNetVar("DT_Local", "m_audio.localSound[6]");
		static uintptr_t m_audio_localSound_7_ = GetNetVar("DT_Local", "m_audio.localSound[7]");
		static uintptr_t m_audio_soundscapeIndex = GetNetVar("DT_Local", "m_audio.soundscapeIndex");
		static uintptr_t m_audio_localBits = GetNetVar("DT_Local", "m_audio.localBits");
		static uintptr_t m_audio_entIndex = GetNetVar("DT_Local", "m_audio.entIndex");
	}

	namespace DT_LightGlow
	{
		static uintptr_t m_clrRender = GetNetVar("DT_LightGlow", "m_clrRender");
		static uintptr_t m_nHorizontalSize = GetNetVar("DT_LightGlow", "m_nHorizontalSize");
		static uintptr_t m_nVerticalSize = GetNetVar("DT_LightGlow", "m_nVerticalSize");
		static uintptr_t m_nMinDist = GetNetVar("DT_LightGlow", "m_nMinDist");
		static uintptr_t m_nMaxDist = GetNetVar("DT_LightGlow", "m_nMaxDist");
		static uintptr_t m_nOuterMaxDist = GetNetVar("DT_LightGlow", "m_nOuterMaxDist");
		static uintptr_t m_spawnflags = GetNetVar("DT_LightGlow", "m_spawnflags");
		static uintptr_t m_vecOrigin = GetNetVar("DT_LightGlow", "m_vecOrigin");
		static uintptr_t m_angRotation = GetNetVar("DT_LightGlow", "m_angRotation");
		static uintptr_t moveparent = GetNetVar("DT_LightGlow", "moveparent");
		static uintptr_t m_flGlowProxySize = GetNetVar("DT_LightGlow", "m_flGlowProxySize");
		static uintptr_t HDRColorScale = GetNetVar("DT_LightGlow", "HDRColorScale");
	}

	namespace DT_Item_Healthshot
	{
		static uintptr_t baseclass = GetNetVar("DT_Item_Healthshot", "baseclass");
	}

	namespace DT_ItemDogtags
	{
		static uintptr_t baseclass = GetNetVar("DT_ItemDogtags", "baseclass");
		static uintptr_t m_OwningPlayer = GetNetVar("DT_ItemDogtags", "m_OwningPlayer");
		static uintptr_t m_KillingPlayer = GetNetVar("DT_ItemDogtags", "m_KillingPlayer");
	}

	namespace DT_ItemCash
	{
		static uintptr_t baseclass = GetNetVar("DT_ItemCash", "baseclass");
	}

	namespace DT_ItemAssaultSuitUseable
	{
		static uintptr_t baseclass = GetNetVar("DT_ItemAssaultSuitUseable", "baseclass");
		static uintptr_t m_nArmorValue = GetNetVar("DT_ItemAssaultSuitUseable", "m_nArmorValue");
		static uintptr_t m_bIsHeavyAssaultSuit = GetNetVar("DT_ItemAssaultSuitUseable", "m_bIsHeavyAssaultSuit");
	}

	namespace DT_Item
	{
		static uintptr_t baseclass = GetNetVar("DT_Item", "baseclass");
		static uintptr_t m_bShouldGlow = GetNetVar("DT_Item", "m_bShouldGlow");
	}

	namespace DT_InfoOverlayAccessor
	{
		static uintptr_t m_iTextureFrameIndex = GetNetVar("DT_InfoOverlayAccessor", "m_iTextureFrameIndex");
		static uintptr_t m_iOverlayID = GetNetVar("DT_InfoOverlayAccessor", "m_iOverlayID");
	}

	namespace DT_InfoMapRegion
	{
		static uintptr_t baseclass = GetNetVar("DT_InfoMapRegion", "baseclass");
		static uintptr_t m_flRadius = GetNetVar("DT_InfoMapRegion", "m_flRadius");
		static uintptr_t m_szLocToken = GetNetVar("DT_InfoMapRegion", "m_szLocToken");
	}

	namespace DT_InfoLadderDismount
	{
		static uintptr_t baseclass = GetNetVar("DT_InfoLadderDismount", "baseclass");
	}

	namespace DT_Inferno
	{
		static uintptr_t baseclass = GetNetVar("DT_Inferno", "baseclass");
		static uintptr_t m_fireXDelta = GetNetVar("DT_Inferno", "m_fireXDelta");
		static uintptr_t m_fireYDelta = GetNetVar("DT_Inferno", "m_fireYDelta");
		static uintptr_t m_fireZDelta = GetNetVar("DT_Inferno", "m_fireZDelta");
		static uintptr_t m_bFireIsBurning = GetNetVar("DT_Inferno", "m_bFireIsBurning");
		static uintptr_t m_nFireEffectTickBegin = GetNetVar("DT_Inferno", "m_nFireEffectTickBegin");
		static uintptr_t m_fireCount = GetNetVar("DT_Inferno", "m_fireCount");
	}

	namespace DT_IncendiaryGrenade
	{
		static uintptr_t baseclass = GetNetVar("DT_IncendiaryGrenade", "baseclass");
	}

	namespace DT_HostageCarriableProp
	{
		static uintptr_t baseclass = GetNetVar("DT_HostageCarriableProp", "baseclass");
	}

	namespace DT_HandleTest
	{
		static uintptr_t baseclass = GetNetVar("DT_HandleTest", "baseclass");
		static uintptr_t m_Handle = GetNetVar("DT_HandleTest", "m_Handle");
		static uintptr_t m_bSendHandle = GetNetVar("DT_HandleTest", "m_bSendHandle");
	}

	namespace DT_HEGrenade
	{
		static uintptr_t baseclass = GetNetVar("DT_HEGrenade", "baseclass");
	}

	namespace DT_GrassBurn
	{
		static uintptr_t baseclass = GetNetVar("DT_GrassBurn", "baseclass");
		static uintptr_t m_flGrassBurnClearTime = GetNetVar("DT_GrassBurn", "m_flGrassBurnClearTime");
	}

	namespace DT_Func_LOD
	{
		static uintptr_t baseclass = GetNetVar("DT_Func_LOD", "baseclass");
		static uintptr_t m_nDisappearMinDist = GetNetVar("DT_Func_LOD", "m_nDisappearMinDist");
		static uintptr_t m_nDisappearMaxDist = GetNetVar("DT_Func_LOD", "m_nDisappearMaxDist");
	}

	namespace DT_Func_Dust
	{
		static uintptr_t m_Color = GetNetVar("DT_Func_Dust", "m_Color");
		static uintptr_t m_SpawnRate = GetNetVar("DT_Func_Dust", "m_SpawnRate");
		static uintptr_t m_flSizeMin = GetNetVar("DT_Func_Dust", "m_flSizeMin");
		static uintptr_t m_flSizeMax = GetNetVar("DT_Func_Dust", "m_flSizeMax");
		static uintptr_t m_LifetimeMin = GetNetVar("DT_Func_Dust", "m_LifetimeMin");
		static uintptr_t m_LifetimeMax = GetNetVar("DT_Func_Dust", "m_LifetimeMax");
		static uintptr_t m_DustFlags = GetNetVar("DT_Func_Dust", "m_DustFlags");
		static uintptr_t m_SpeedMax = GetNetVar("DT_Func_Dust", "m_SpeedMax");
		static uintptr_t m_DistMax = GetNetVar("DT_Func_Dust", "m_DistMax");
		static uintptr_t m_nModelIndex = GetNetVar("DT_Func_Dust", "m_nModelIndex");
		static uintptr_t m_FallSpeed = GetNetVar("DT_Func_Dust", "m_FallSpeed");
		static uintptr_t m_bAffectedByWind = GetNetVar("DT_Func_Dust", "m_bAffectedByWind");
		static uintptr_t m_Collision = GetNetVar("DT_Func_Dust", "m_Collision");
	}

	namespace DT_FuncTrackTrain
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncTrackTrain", "baseclass");
	}

	namespace DT_FuncSmokeVolume
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncSmokeVolume", "baseclass");
		static uintptr_t m_Color1 = GetNetVar("DT_FuncSmokeVolume", "m_Color1");
		static uintptr_t m_Color2 = GetNetVar("DT_FuncSmokeVolume", "m_Color2");
		static uintptr_t m_MaterialName = GetNetVar("DT_FuncSmokeVolume", "m_MaterialName");
		static uintptr_t m_ParticleDrawWidth = GetNetVar("DT_FuncSmokeVolume", "m_ParticleDrawWidth");
		static uintptr_t m_ParticleSpacingDistance = GetNetVar("DT_FuncSmokeVolume", "m_ParticleSpacingDistance");
		static uintptr_t m_DensityRampSpeed = GetNetVar("DT_FuncSmokeVolume", "m_DensityRampSpeed");
		static uintptr_t m_RotationSpeed = GetNetVar("DT_FuncSmokeVolume", "m_RotationSpeed");
		static uintptr_t m_MovementSpeed = GetNetVar("DT_FuncSmokeVolume", "m_MovementSpeed");
		static uintptr_t m_Density = GetNetVar("DT_FuncSmokeVolume", "m_Density");
		static uintptr_t m_maxDrawDistance = GetNetVar("DT_FuncSmokeVolume", "m_maxDrawDistance");
		static uintptr_t m_spawnflags = GetNetVar("DT_FuncSmokeVolume", "m_spawnflags");
		static uintptr_t m_Collision = GetNetVar("DT_FuncSmokeVolume", "m_Collision");
	}

	namespace DT_FuncRotating
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncRotating", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_FuncRotating", "m_vecOrigin");
		static uintptr_t m_angRotation_0_ = GetNetVar("DT_FuncRotating", "m_angRotation[0]");
		static uintptr_t m_angRotation_1_ = GetNetVar("DT_FuncRotating", "m_angRotation[1]");
		static uintptr_t m_angRotation_2_ = GetNetVar("DT_FuncRotating", "m_angRotation[2]");
		static uintptr_t m_flSimulationTime = GetNetVar("DT_FuncRotating", "m_flSimulationTime");
	}

	namespace DT_FuncReflectiveGlass
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncReflectiveGlass", "baseclass");
	}

	namespace DT_FuncOccluder
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncOccluder", "baseclass");
		static uintptr_t m_bActive = GetNetVar("DT_FuncOccluder", "m_bActive");
		static uintptr_t m_nOccluderIndex = GetNetVar("DT_FuncOccluder", "m_nOccluderIndex");
	}

	namespace DT_FuncMoveLinear
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncMoveLinear", "baseclass");
		static uintptr_t m_vecVelocity = GetNetVar("DT_FuncMoveLinear", "m_vecVelocity");
		static uintptr_t m_fFlags = GetNetVar("DT_FuncMoveLinear", "m_fFlags");
	}

	namespace DT_FuncMonitor
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncMonitor", "baseclass");
	}

	namespace DT_FuncLadder
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncLadder", "baseclass");
		static uintptr_t m_vecPlayerMountPositionTop = GetNetVar("DT_FuncLadder", "m_vecPlayerMountPositionTop");
		static uintptr_t m_vecPlayerMountPositionBottom = GetNetVar("DT_FuncLadder", "m_vecPlayerMountPositionBottom");
		static uintptr_t m_vecLadderDir = GetNetVar("DT_FuncLadder", "m_vecLadderDir");
		static uintptr_t m_bFakeLadder = GetNetVar("DT_FuncLadder", "m_bFakeLadder");
	}

	namespace DT_FuncConveyor
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncConveyor", "baseclass");
		static uintptr_t m_flConveyorSpeed = GetNetVar("DT_FuncConveyor", "m_flConveyorSpeed");
	}

	namespace DT_FuncBrush
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncBrush", "baseclass");
	}

	namespace DT_FuncAreaPortalWindow
	{
		static uintptr_t baseclass = GetNetVar("DT_FuncAreaPortalWindow", "baseclass");
		static uintptr_t m_flFadeStartDist = GetNetVar("DT_FuncAreaPortalWindow", "m_flFadeStartDist");
		static uintptr_t m_flFadeDist = GetNetVar("DT_FuncAreaPortalWindow", "m_flFadeDist");
		static uintptr_t m_flTranslucencyLimit = GetNetVar("DT_FuncAreaPortalWindow", "m_flTranslucencyLimit");
		static uintptr_t m_iBackgroundModelIndex = GetNetVar("DT_FuncAreaPortalWindow", "m_iBackgroundModelIndex");
	}

	namespace DT_FootstepControl
	{
		static uintptr_t baseclass = GetNetVar("DT_FootstepControl", "baseclass");
		static uintptr_t m_source = GetNetVar("DT_FootstepControl", "m_source");
		static uintptr_t m_destination = GetNetVar("DT_FootstepControl", "m_destination");
	}

	namespace DT_FogController
	{
		static uintptr_t m_fog_enable = GetNetVar("DT_FogController", "m_fog.enable");
		static uintptr_t m_fog_blend = GetNetVar("DT_FogController", "m_fog.blend");
		static uintptr_t m_fog_dirPrimary = GetNetVar("DT_FogController", "m_fog.dirPrimary");
		static uintptr_t m_fog_colorPrimary = GetNetVar("DT_FogController", "m_fog.colorPrimary");
		static uintptr_t m_fog_colorSecondary = GetNetVar("DT_FogController", "m_fog.colorSecondary");
		static uintptr_t m_fog_start = GetNetVar("DT_FogController", "m_fog.start");
		static uintptr_t m_fog_end = GetNetVar("DT_FogController", "m_fog.end");
		static uintptr_t m_fog_farz = GetNetVar("DT_FogController", "m_fog.farz");
		static uintptr_t m_fog_maxdensity = GetNetVar("DT_FogController", "m_fog.maxdensity");
		static uintptr_t m_fog_colorPrimaryLerpTo = GetNetVar("DT_FogController", "m_fog.colorPrimaryLerpTo");
		static uintptr_t m_fog_colorSecondaryLerpTo = GetNetVar("DT_FogController", "m_fog.colorSecondaryLerpTo");
		static uintptr_t m_fog_startLerpTo = GetNetVar("DT_FogController", "m_fog.startLerpTo");
		static uintptr_t m_fog_endLerpTo = GetNetVar("DT_FogController", "m_fog.endLerpTo");
		static uintptr_t m_fog_maxdensityLerpTo = GetNetVar("DT_FogController", "m_fog.maxdensityLerpTo");
		static uintptr_t m_fog_lerptime = GetNetVar("DT_FogController", "m_fog.lerptime");
		static uintptr_t m_fog_duration = GetNetVar("DT_FogController", "m_fog.duration");
		static uintptr_t m_fog_HDRColorScale = GetNetVar("DT_FogController", "m_fog.HDRColorScale");
		static uintptr_t m_fog_ZoomFogScale = GetNetVar("DT_FogController", "m_fog.ZoomFogScale");
	}

	namespace DT_Flashbang
	{
		static uintptr_t baseclass = GetNetVar("DT_Flashbang", "baseclass");
	}

	namespace DT_FireTrail
	{
		static uintptr_t baseclass = GetNetVar("DT_FireTrail", "baseclass");
		static uintptr_t m_nAttachment = GetNetVar("DT_FireTrail", "m_nAttachment");
		static uintptr_t m_flLifetime = GetNetVar("DT_FireTrail", "m_flLifetime");
	}

	namespace DT_FireSmoke
	{
		static uintptr_t baseclass = GetNetVar("DT_FireSmoke", "baseclass");
		static uintptr_t m_flStartScale = GetNetVar("DT_FireSmoke", "m_flStartScale");
		static uintptr_t m_flScale = GetNetVar("DT_FireSmoke", "m_flScale");
		static uintptr_t m_flScaleTime = GetNetVar("DT_FireSmoke", "m_flScaleTime");
		static uintptr_t m_nFlags = GetNetVar("DT_FireSmoke", "m_nFlags");
		static uintptr_t m_nFlameModelIndex = GetNetVar("DT_FireSmoke", "m_nFlameModelIndex");
		static uintptr_t m_nFlameFromAboveModelIndex = GetNetVar("DT_FireSmoke", "m_nFlameFromAboveModelIndex");
	}

	namespace DT_FireCrackerBlast
	{
		static uintptr_t baseclass = GetNetVar("DT_FireCrackerBlast", "baseclass");
	}

	namespace DT_FEPlayerDecal
	{
		static uintptr_t baseclass = GetNetVar("DT_FEPlayerDecal", "baseclass");
		static uintptr_t m_nUniqueID = GetNetVar("DT_FEPlayerDecal", "m_nUniqueID");
		static uintptr_t m_unAccountID = GetNetVar("DT_FEPlayerDecal", "m_unAccountID");
		static uintptr_t m_unTraceID = GetNetVar("DT_FEPlayerDecal", "m_unTraceID");
		static uintptr_t m_rtGcTime = GetNetVar("DT_FEPlayerDecal", "m_rtGcTime");
		static uintptr_t m_vecEndPos = GetNetVar("DT_FEPlayerDecal", "m_vecEndPos");
		static uintptr_t m_vecStart = GetNetVar("DT_FEPlayerDecal", "m_vecStart");
		static uintptr_t m_vecRight = GetNetVar("DT_FEPlayerDecal", "m_vecRight");
		static uintptr_t m_vecNormal = GetNetVar("DT_FEPlayerDecal", "m_vecNormal");
		static uintptr_t m_nEntity = GetNetVar("DT_FEPlayerDecal", "m_nEntity");
		static uintptr_t m_nPlayer = GetNetVar("DT_FEPlayerDecal", "m_nPlayer");
		static uintptr_t m_nHitbox = GetNetVar("DT_FEPlayerDecal", "m_nHitbox");
		static uintptr_t m_nTintID = GetNetVar("DT_FEPlayerDecal", "m_nTintID");
		static uintptr_t m_flCreationTime = GetNetVar("DT_FEPlayerDecal", "m_flCreationTime");
		static uintptr_t m_nVersion = GetNetVar("DT_FEPlayerDecal", "m_nVersion");
		static uintptr_t m_ubSignature = GetNetVar("DT_FEPlayerDecal", "m_ubSignature");
	}

	namespace DT_EnvWindShared
	{
		static uintptr_t m_iMinWind = GetNetVar("DT_EnvWindShared", "m_iMinWind");
		static uintptr_t m_iMaxWind = GetNetVar("DT_EnvWindShared", "m_iMaxWind");
		static uintptr_t m_iMinGust = GetNetVar("DT_EnvWindShared", "m_iMinGust");
		static uintptr_t m_iMaxGust = GetNetVar("DT_EnvWindShared", "m_iMaxGust");
		static uintptr_t m_flMinGustDelay = GetNetVar("DT_EnvWindShared", "m_flMinGustDelay");
		static uintptr_t m_flMaxGustDelay = GetNetVar("DT_EnvWindShared", "m_flMaxGustDelay");
		static uintptr_t m_iGustDirChange = GetNetVar("DT_EnvWindShared", "m_iGustDirChange");
		static uintptr_t m_iWindSeed = GetNetVar("DT_EnvWindShared", "m_iWindSeed");
		static uintptr_t m_iInitialWindDir = GetNetVar("DT_EnvWindShared", "m_iInitialWindDir");
		static uintptr_t m_flInitialWindSpeed = GetNetVar("DT_EnvWindShared", "m_flInitialWindSpeed");
		static uintptr_t m_flStartTime = GetNetVar("DT_EnvWindShared", "m_flStartTime");
		static uintptr_t m_flGustDuration = GetNetVar("DT_EnvWindShared", "m_flGustDuration");
	}

	namespace DT_EnvWind
	{
		static uintptr_t baseclass = GetNetVar("DT_EnvWind", "baseclass");
		static uintptr_t m_EnvWindShared = GetNetVar("DT_EnvWind", "m_EnvWindShared");
	}

	namespace DT_EnvTonemapController
	{
		static uintptr_t baseclass = GetNetVar("DT_EnvTonemapController", "baseclass");
		static uintptr_t m_bUseCustomAutoExposureMin = GetNetVar("DT_EnvTonemapController", "m_bUseCustomAutoExposureMin");
		static uintptr_t m_bUseCustomAutoExposureMax = GetNetVar("DT_EnvTonemapController", "m_bUseCustomAutoExposureMax");
		static uintptr_t m_bUseCustomBloomScale = GetNetVar("DT_EnvTonemapController", "m_bUseCustomBloomScale");
		static uintptr_t m_flCustomAutoExposureMin = GetNetVar("DT_EnvTonemapController", "m_flCustomAutoExposureMin");
		static uintptr_t m_flCustomAutoExposureMax = GetNetVar("DT_EnvTonemapController", "m_flCustomAutoExposureMax");
		static uintptr_t m_flCustomBloomScale = GetNetVar("DT_EnvTonemapController", "m_flCustomBloomScale");
		static uintptr_t m_flCustomBloomScaleMinimum = GetNetVar("DT_EnvTonemapController", "m_flCustomBloomScaleMinimum");
		static uintptr_t m_flBloomExponent = GetNetVar("DT_EnvTonemapController", "m_flBloomExponent");
		static uintptr_t m_flBloomSaturation = GetNetVar("DT_EnvTonemapController", "m_flBloomSaturation");
		static uintptr_t m_flTonemapPercentTarget = GetNetVar("DT_EnvTonemapController", "m_flTonemapPercentTarget");
		static uintptr_t m_flTonemapPercentBrightPixels = GetNetVar("DT_EnvTonemapController", "m_flTonemapPercentBrightPixels");
		static uintptr_t m_flTonemapMinAvgLum = GetNetVar("DT_EnvTonemapController", "m_flTonemapMinAvgLum");
		static uintptr_t m_flTonemapRate = GetNetVar("DT_EnvTonemapController", "m_flTonemapRate");
	}

	namespace DT_EnvScreenOverlay
	{
		static uintptr_t baseclass = GetNetVar("DT_EnvScreenOverlay", "baseclass");
		static uintptr_t m_iszOverlayNames_0_ = GetNetVar("DT_EnvScreenOverlay", "m_iszOverlayNames[0]");
		static uintptr_t m_iszOverlayNames = GetNetVar("DT_EnvScreenOverlay", "m_iszOverlayNames");
		static uintptr_t m_flOverlayTimes_0_ = GetNetVar("DT_EnvScreenOverlay", "m_flOverlayTimes[0]");
		static uintptr_t m_flOverlayTimes = GetNetVar("DT_EnvScreenOverlay", "m_flOverlayTimes");
		static uintptr_t m_flStartTime = GetNetVar("DT_EnvScreenOverlay", "m_flStartTime");
		static uintptr_t m_iDesiredOverlay = GetNetVar("DT_EnvScreenOverlay", "m_iDesiredOverlay");
		static uintptr_t m_bIsActive = GetNetVar("DT_EnvScreenOverlay", "m_bIsActive");
	}

	namespace DT_EnvScreenEffect
	{
		static uintptr_t baseclass = GetNetVar("DT_EnvScreenEffect", "baseclass");
		static uintptr_t m_flDuration = GetNetVar("DT_EnvScreenEffect", "m_flDuration");
		static uintptr_t m_nType = GetNetVar("DT_EnvScreenEffect", "m_nType");
	}

	namespace DT_EnvProjectedTexture
	{
		static uintptr_t baseclass = GetNetVar("DT_EnvProjectedTexture", "baseclass");
		static uintptr_t m_hTargetEntity = GetNetVar("DT_EnvProjectedTexture", "m_hTargetEntity");
		static uintptr_t m_bState = GetNetVar("DT_EnvProjectedTexture", "m_bState");
		static uintptr_t m_bAlwaysUpdate = GetNetVar("DT_EnvProjectedTexture", "m_bAlwaysUpdate");
		static uintptr_t m_flLightFOV = GetNetVar("DT_EnvProjectedTexture", "m_flLightFOV");
		static uintptr_t m_bEnableShadows = GetNetVar("DT_EnvProjectedTexture", "m_bEnableShadows");
		static uintptr_t m_bSimpleProjection = GetNetVar("DT_EnvProjectedTexture", "m_bSimpleProjection");
		static uintptr_t m_bLightOnlyTarget = GetNetVar("DT_EnvProjectedTexture", "m_bLightOnlyTarget");
		static uintptr_t m_bLightWorld = GetNetVar("DT_EnvProjectedTexture", "m_bLightWorld");
		static uintptr_t m_bCameraSpace = GetNetVar("DT_EnvProjectedTexture", "m_bCameraSpace");
		static uintptr_t m_flBrightnessScale = GetNetVar("DT_EnvProjectedTexture", "m_flBrightnessScale");
		static uintptr_t m_LightColor = GetNetVar("DT_EnvProjectedTexture", "m_LightColor");
		static uintptr_t m_flColorTransitionTime = GetNetVar("DT_EnvProjectedTexture", "m_flColorTransitionTime");
		static uintptr_t m_flAmbient = GetNetVar("DT_EnvProjectedTexture", "m_flAmbient");
		static uintptr_t m_SpotlightTextureName = GetNetVar("DT_EnvProjectedTexture", "m_SpotlightTextureName");
		static uintptr_t m_nSpotlightTextureFrame = GetNetVar("DT_EnvProjectedTexture", "m_nSpotlightTextureFrame");
		static uintptr_t m_flNearZ = GetNetVar("DT_EnvProjectedTexture", "m_flNearZ");
		static uintptr_t m_flFarZ = GetNetVar("DT_EnvProjectedTexture", "m_flFarZ");
		static uintptr_t m_nShadowQuality = GetNetVar("DT_EnvProjectedTexture", "m_nShadowQuality");
		static uintptr_t m_flProjectionSize = GetNetVar("DT_EnvProjectedTexture", "m_flProjectionSize");
		static uintptr_t m_flRotation = GetNetVar("DT_EnvProjectedTexture", "m_flRotation");
		static uintptr_t m_iStyle = GetNetVar("DT_EnvProjectedTexture", "m_iStyle");
	}

	namespace DT_EnvParticleScript
	{
		static uintptr_t baseclass = GetNetVar("DT_EnvParticleScript", "baseclass");
		static uintptr_t m_flSequenceScale = GetNetVar("DT_EnvParticleScript", "m_flSequenceScale");
	}

	namespace DT_EnvGasCanister
	{
		static uintptr_t baseclass = GetNetVar("DT_EnvGasCanister", "baseclass");
		static uintptr_t m_flFlightSpeed = GetNetVar("DT_EnvGasCanister", "m_flFlightSpeed");
		static uintptr_t m_flLaunchTime = GetNetVar("DT_EnvGasCanister", "m_flLaunchTime");
		static uintptr_t m_vecParabolaDirection = GetNetVar("DT_EnvGasCanister", "m_vecParabolaDirection");
		static uintptr_t m_flFlightTime = GetNetVar("DT_EnvGasCanister", "m_flFlightTime");
		static uintptr_t m_flWorldEnterTime = GetNetVar("DT_EnvGasCanister", "m_flWorldEnterTime");
		static uintptr_t m_flInitialZSpeed = GetNetVar("DT_EnvGasCanister", "m_flInitialZSpeed");
		static uintptr_t m_flZAcceleration = GetNetVar("DT_EnvGasCanister", "m_flZAcceleration");
		static uintptr_t m_flHorizSpeed = GetNetVar("DT_EnvGasCanister", "m_flHorizSpeed");
		static uintptr_t m_bLaunchedFromWithinWorld = GetNetVar("DT_EnvGasCanister", "m_bLaunchedFromWithinWorld");
		static uintptr_t m_vecImpactPosition = GetNetVar("DT_EnvGasCanister", "m_vecImpactPosition");
		static uintptr_t m_vecStartPosition = GetNetVar("DT_EnvGasCanister", "m_vecStartPosition");
		static uintptr_t m_vecEnterWorldPosition = GetNetVar("DT_EnvGasCanister", "m_vecEnterWorldPosition");
		static uintptr_t m_vecDirection = GetNetVar("DT_EnvGasCanister", "m_vecDirection");
		static uintptr_t m_vecStartAngles = GetNetVar("DT_EnvGasCanister", "m_vecStartAngles");
		static uintptr_t m_vecSkyboxOrigin = GetNetVar("DT_EnvGasCanister", "m_vecSkyboxOrigin");
		static uintptr_t m_flSkyboxScale = GetNetVar("DT_EnvGasCanister", "m_flSkyboxScale");
		static uintptr_t m_bInSkybox = GetNetVar("DT_EnvGasCanister", "m_bInSkybox");
		static uintptr_t m_bDoImpactEffects = GetNetVar("DT_EnvGasCanister", "m_bDoImpactEffects");
		static uintptr_t m_bLanded = GetNetVar("DT_EnvGasCanister", "m_bLanded");
		static uintptr_t m_hSkyboxCopy = GetNetVar("DT_EnvGasCanister", "m_hSkyboxCopy");
		static uintptr_t m_nMyZoneIndex = GetNetVar("DT_EnvGasCanister", "m_nMyZoneIndex");
		static uintptr_t m_vecOrigin = GetNetVar("DT_EnvGasCanister", "m_vecOrigin");
		static uintptr_t m_vecOrigin_2_ = GetNetVar("DT_EnvGasCanister", "m_vecOrigin[2]");
	}

	namespace DT_EnvDOFController
	{
		static uintptr_t baseclass = GetNetVar("DT_EnvDOFController", "baseclass");
		static uintptr_t m_bDOFEnabled = GetNetVar("DT_EnvDOFController", "m_bDOFEnabled");
		static uintptr_t m_flNearBlurDepth = GetNetVar("DT_EnvDOFController", "m_flNearBlurDepth");
		static uintptr_t m_flNearFocusDepth = GetNetVar("DT_EnvDOFController", "m_flNearFocusDepth");
		static uintptr_t m_flFarFocusDepth = GetNetVar("DT_EnvDOFController", "m_flFarFocusDepth");
		static uintptr_t m_flFarBlurDepth = GetNetVar("DT_EnvDOFController", "m_flFarBlurDepth");
		static uintptr_t m_flNearBlurRadius = GetNetVar("DT_EnvDOFController", "m_flNearBlurRadius");
		static uintptr_t m_flFarBlurRadius = GetNetVar("DT_EnvDOFController", "m_flFarBlurRadius");
	}
	namespace DT_EnvAmbientLight
	{
		static uintptr_t baseclass = GetNetVar("DT_EnvAmbientLight", "baseclass");
		static uintptr_t m_vecColor = GetNetVar("DT_EnvAmbientLight", "m_vecColor");
	}

	namespace DT_EntityParticleTrailInfo
	{
		static uintptr_t m_flLifetime = GetNetVar("DT_EntityParticleTrailInfo", "m_flLifetime");
		static uintptr_t m_flStartSize = GetNetVar("DT_EntityParticleTrailInfo", "m_flStartSize");
		static uintptr_t m_flEndSize = GetNetVar("DT_EntityParticleTrailInfo", "m_flEndSize");
	}

	namespace DT_EntityParticleTrail
	{
		static uintptr_t baseclass = GetNetVar("DT_EntityParticleTrail", "baseclass");
		static uintptr_t m_iMaterialName = GetNetVar("DT_EntityParticleTrail", "m_iMaterialName");
		static uintptr_t m_Info = GetNetVar("DT_EntityParticleTrail", "m_Info");
		static uintptr_t m_hConstraintEntity = GetNetVar("DT_EntityParticleTrail", "m_hConstraintEntity");
	}

	namespace DT_EntityFreezing
	{
		static uintptr_t baseclass = GetNetVar("DT_EntityFreezing", "baseclass");
		static uintptr_t m_vFreezingOrigin = GetNetVar("DT_EntityFreezing", "m_vFreezingOrigin");
		static uintptr_t m_flFrozenPerHitbox = GetNetVar("DT_EntityFreezing", "m_flFrozenPerHitbox");
		static uintptr_t m_flFrozen = GetNetVar("DT_EntityFreezing", "m_flFrozen");
		static uintptr_t m_bFinishFreezing = GetNetVar("DT_EntityFreezing", "m_bFinishFreezing");
	}

	namespace DT_EntityFlame
	{
		static uintptr_t baseclass = GetNetVar("DT_EntityFlame", "baseclass");
		static uintptr_t m_hEntAttached = GetNetVar("DT_EntityFlame", "m_hEntAttached");
		static uintptr_t m_bCheapEffect = GetNetVar("DT_EntityFlame", "m_bCheapEffect");
	}

	namespace DT_EntityDissolve
	{
		static uintptr_t baseclass = GetNetVar("DT_EntityDissolve", "baseclass");
		static uintptr_t m_flStartTime = GetNetVar("DT_EntityDissolve", "m_flStartTime");
		static uintptr_t m_flFadeOutStart = GetNetVar("DT_EntityDissolve", "m_flFadeOutStart");
		static uintptr_t m_flFadeOutLength = GetNetVar("DT_EntityDissolve", "m_flFadeOutLength");
		static uintptr_t m_flFadeOutModelStart = GetNetVar("DT_EntityDissolve", "m_flFadeOutModelStart");
		static uintptr_t m_flFadeOutModelLength = GetNetVar("DT_EntityDissolve", "m_flFadeOutModelLength");
		static uintptr_t m_flFadeInStart = GetNetVar("DT_EntityDissolve", "m_flFadeInStart");
		static uintptr_t m_flFadeInLength = GetNetVar("DT_EntityDissolve", "m_flFadeInLength");
		static uintptr_t m_nDissolveType = GetNetVar("DT_EntityDissolve", "m_nDissolveType");
		static uintptr_t m_vDissolverOrigin = GetNetVar("DT_EntityDissolve", "m_vDissolverOrigin");
		static uintptr_t m_nMagnitude = GetNetVar("DT_EntityDissolve", "m_nMagnitude");
	}

	namespace DT_Embers
	{
		static uintptr_t baseclass = GetNetVar("DT_Embers", "baseclass");
		static uintptr_t m_nDensity = GetNetVar("DT_Embers", "m_nDensity");
		static uintptr_t m_nLifetime = GetNetVar("DT_Embers", "m_nLifetime");
		static uintptr_t m_nSpeed = GetNetVar("DT_Embers", "m_nSpeed");
		static uintptr_t m_bEmit = GetNetVar("DT_Embers", "m_bEmit");
	}

	namespace DT_EffectData
	{
		static uintptr_t m_vOrigin_x = GetNetVar("DT_EffectData", "m_vOrigin.x");
		static uintptr_t m_vOrigin_y = GetNetVar("DT_EffectData", "m_vOrigin.y");
		static uintptr_t m_vOrigin_z = GetNetVar("DT_EffectData", "m_vOrigin.z");
		static uintptr_t m_vStart_x = GetNetVar("DT_EffectData", "m_vStart.x");
		static uintptr_t m_vStart_y = GetNetVar("DT_EffectData", "m_vStart.y");
		static uintptr_t m_vStart_z = GetNetVar("DT_EffectData", "m_vStart.z");
		static uintptr_t m_vAngles = GetNetVar("DT_EffectData", "m_vAngles");
		static uintptr_t m_vNormal = GetNetVar("DT_EffectData", "m_vNormal");
		static uintptr_t m_fFlags = GetNetVar("DT_EffectData", "m_fFlags");
		static uintptr_t m_flMagnitude = GetNetVar("DT_EffectData", "m_flMagnitude");
		static uintptr_t m_flScale = GetNetVar("DT_EffectData", "m_flScale");
		static uintptr_t m_nAttachmentIndex = GetNetVar("DT_EffectData", "m_nAttachmentIndex");
		static uintptr_t m_nSurfaceProp = GetNetVar("DT_EffectData", "m_nSurfaceProp");
		static uintptr_t m_iEffectName = GetNetVar("DT_EffectData", "m_iEffectName");
		static uintptr_t m_nMaterial = GetNetVar("DT_EffectData", "m_nMaterial");
		static uintptr_t m_nDamageType = GetNetVar("DT_EffectData", "m_nDamageType");
		static uintptr_t m_nHitBox = GetNetVar("DT_EffectData", "m_nHitBox");
		static uintptr_t entindex = GetNetVar("DT_EffectData", "entindex");
		static uintptr_t m_nOtherEntIndex = GetNetVar("DT_EffectData", "m_nOtherEntIndex");
		static uintptr_t m_nColor = GetNetVar("DT_EffectData", "m_nColor");
		static uintptr_t m_flRadius = GetNetVar("DT_EffectData", "m_flRadius");
		static uintptr_t m_bPositionsAreRelativeToEntity = GetNetVar("DT_EffectData", "m_bPositionsAreRelativeToEntity");
	}

	namespace DT_EconEntity
	{
		static uintptr_t baseclass = GetNetVar("DT_EconEntity", "baseclass");
		static uintptr_t m_AttributeManager = GetNetVar("DT_EconEntity", "m_AttributeManager");
		static uintptr_t m_OriginalOwnerXuidLow = GetNetVar("DT_EconEntity", "m_OriginalOwnerXuidLow");
		static uintptr_t m_OriginalOwnerXuidHigh = GetNetVar("DT_EconEntity", "m_OriginalOwnerXuidHigh");
		static uintptr_t m_nFallbackPaintKit = GetNetVar("DT_EconEntity", "m_nFallbackPaintKit");
		static uintptr_t m_nFallbackSeed = GetNetVar("DT_EconEntity", "m_nFallbackSeed");
		static uintptr_t m_flFallbackWear = GetNetVar("DT_EconEntity", "m_flFallbackWear");
		static uintptr_t m_nFallbackStatTrak = GetNetVar("DT_EconEntity", "m_nFallbackStatTrak");
	}

	namespace DT_DynamicProp
	{
		static uintptr_t baseclass = GetNetVar("DT_DynamicProp", "baseclass");
		static uintptr_t m_bUseHitboxesForRenderBox = GetNetVar("DT_DynamicProp", "m_bUseHitboxesForRenderBox");
		static uintptr_t m_flGlowMaxDist = GetNetVar("DT_DynamicProp", "m_flGlowMaxDist");
		static uintptr_t m_bShouldGlow = GetNetVar("DT_DynamicProp", "m_bShouldGlow");
		static uintptr_t m_clrGlow = GetNetVar("DT_DynamicProp", "m_clrGlow");
		static uintptr_t m_nGlowStyle = GetNetVar("DT_DynamicProp", "m_nGlowStyle");
	}

	namespace DT_DynamicLight
	{
		static uintptr_t baseclass = GetNetVar("DT_DynamicLight", "baseclass");
		static uintptr_t m_Flags = GetNetVar("DT_DynamicLight", "m_Flags");
		static uintptr_t m_LightStyle = GetNetVar("DT_DynamicLight", "m_LightStyle");
		static uintptr_t m_Radius = GetNetVar("DT_DynamicLight", "m_Radius");
		static uintptr_t m_Exponent = GetNetVar("DT_DynamicLight", "m_Exponent");
		static uintptr_t m_InnerAngle = GetNetVar("DT_DynamicLight", "m_InnerAngle");
		static uintptr_t m_OuterAngle = GetNetVar("DT_DynamicLight", "m_OuterAngle");
		static uintptr_t m_SpotRadius = GetNetVar("DT_DynamicLight", "m_SpotRadius");
	}
	namespace DT_DustTrail
	{
		static uintptr_t baseclass = GetNetVar("DT_DustTrail", "baseclass");
		static uintptr_t m_SpawnRate = GetNetVar("DT_DustTrail", "m_SpawnRate");
		static uintptr_t m_Color = GetNetVar("DT_DustTrail", "m_Color");
		static uintptr_t m_ParticleLifetime = GetNetVar("DT_DustTrail", "m_ParticleLifetime");
		static uintptr_t m_StopEmitTime = GetNetVar("DT_DustTrail", "m_StopEmitTime");
		static uintptr_t m_MinSpeed = GetNetVar("DT_DustTrail", "m_MinSpeed");
		static uintptr_t m_MaxSpeed = GetNetVar("DT_DustTrail", "m_MaxSpeed");
		static uintptr_t m_MinDirectedSpeed = GetNetVar("DT_DustTrail", "m_MinDirectedSpeed");
		static uintptr_t m_MaxDirectedSpeed = GetNetVar("DT_DustTrail", "m_MaxDirectedSpeed");
		static uintptr_t m_StartSize = GetNetVar("DT_DustTrail", "m_StartSize");
		static uintptr_t m_EndSize = GetNetVar("DT_DustTrail", "m_EndSize");
		static uintptr_t m_SpawnRadius = GetNetVar("DT_DustTrail", "m_SpawnRadius");
		static uintptr_t m_bEmit = GetNetVar("DT_DustTrail", "m_bEmit");
		static uintptr_t m_Opacity = GetNetVar("DT_DustTrail", "m_Opacity");
	}

	namespace DT_Dronegun
	{
		static uintptr_t baseclass = GetNetVar("DT_Dronegun", "baseclass");
		static uintptr_t m_vecAttentionTarget = GetNetVar("DT_Dronegun", "m_vecAttentionTarget");
		static uintptr_t m_vecTargetOffset = GetNetVar("DT_Dronegun", "m_vecTargetOffset");
		static uintptr_t m_iHealth = GetNetVar("DT_Dronegun", "m_iHealth");
		static uintptr_t m_bHasTarget = GetNetVar("DT_Dronegun", "m_bHasTarget");
	}

	namespace DT_Drone
	{
		static uintptr_t baseclass = GetNetVar("DT_Drone", "baseclass");
		static uintptr_t m_hMoveToThisEntity = GetNetVar("DT_Drone", "m_hMoveToThisEntity");
		static uintptr_t m_hDeliveryCargo = GetNetVar("DT_Drone", "m_hDeliveryCargo");
		static uintptr_t m_bPilotTakeoverAllowed = GetNetVar("DT_Drone", "m_bPilotTakeoverAllowed");
		static uintptr_t m_hPotentialCargo = GetNetVar("DT_Drone", "m_hPotentialCargo");
		static uintptr_t m_hCurrentPilot = GetNetVar("DT_Drone", "m_hCurrentPilot");
		static uintptr_t m_vecTagPositions_0_ = GetNetVar("DT_Drone", "m_vecTagPositions[0]");
		static uintptr_t m_vecTagPositions = GetNetVar("DT_Drone", "m_vecTagPositions");
		static uintptr_t m_vecTagIncrements_0_ = GetNetVar("DT_Drone", "m_vecTagIncrements[0]");
		static uintptr_t m_vecTagIncrements = GetNetVar("DT_Drone", "m_vecTagIncrements");
	}

	namespace DT_DetailController
	{
		static uintptr_t m_flFadeStartDist = GetNetVar("DT_DetailController", "m_flFadeStartDist");
		static uintptr_t m_flFadeEndDist = GetNetVar("DT_DetailController", "m_flFadeEndDist");
	}

	namespace DT_DecoyProjectile
	{
		static uintptr_t baseclass = GetNetVar("DT_DecoyProjectile", "baseclass");
	}

	namespace DT_DecoyGrenade
	{
		static uintptr_t baseclass = GetNetVar("DT_DecoyGrenade", "baseclass");
	}

	namespace DT_DangerZoneController
	{
		static uintptr_t baseclass = GetNetVar("DT_DangerZoneController", "baseclass");
		static uintptr_t m_bDangerZoneControllerEnabled = GetNetVar("DT_DangerZoneController", "m_bDangerZoneControllerEnabled");
		static uintptr_t m_bMissionControlledExplosions = GetNetVar("DT_DangerZoneController", "m_bMissionControlledExplosions");
		static uintptr_t m_flStartTime = GetNetVar("DT_DangerZoneController", "m_flStartTime");
		static uintptr_t m_flFinalExpansionTime = GetNetVar("DT_DangerZoneController", "m_flFinalExpansionTime");
		static uintptr_t m_vecEndGameCircleStart = GetNetVar("DT_DangerZoneController", "m_vecEndGameCircleStart");
		static uintptr_t m_vecEndGameCircleEnd = GetNetVar("DT_DangerZoneController", "m_vecEndGameCircleEnd");
		static uintptr_t m_DangerZones = GetNetVar("DT_DangerZoneController", "m_DangerZones");
		static uintptr_t m_flWaveEndTimes = GetNetVar("DT_DangerZoneController", "m_flWaveEndTimes");
		static uintptr_t m_hTheFinalZone = GetNetVar("DT_DangerZoneController", "m_hTheFinalZone");
	}

	namespace DT_DangerZone
	{
		static uintptr_t baseclass = GetNetVar("DT_DangerZone", "baseclass");
		static uintptr_t m_vecDangerZoneOriginStartedAt = GetNetVar("DT_DangerZone", "m_vecDangerZoneOriginStartedAt");
		static uintptr_t m_flBombLaunchTime = GetNetVar("DT_DangerZone", "m_flBombLaunchTime");
		static uintptr_t m_flExtraRadius = GetNetVar("DT_DangerZone", "m_flExtraRadius");
		static uintptr_t m_flExtraRadiusStartTime = GetNetVar("DT_DangerZone", "m_flExtraRadiusStartTime");
		static uintptr_t m_flExtraRadiusTotalLerpTime = GetNetVar("DT_DangerZone", "m_flExtraRadiusTotalLerpTime");
		static uintptr_t m_nDropOrder = GetNetVar("DT_DangerZone", "m_nDropOrder");
		static uintptr_t m_iWave = GetNetVar("DT_DangerZone", "m_iWave");
	}

	namespace DT_ColorCorrectionVolume
	{
		static uintptr_t baseclass = GetNetVar("DT_ColorCorrectionVolume", "baseclass");
		static uintptr_t m_bEnabled = GetNetVar("DT_ColorCorrectionVolume", "m_bEnabled");
		static uintptr_t m_MaxWeight = GetNetVar("DT_ColorCorrectionVolume", "m_MaxWeight");
		static uintptr_t m_FadeDuration = GetNetVar("DT_ColorCorrectionVolume", "m_FadeDuration");
		static uintptr_t m_Weight = GetNetVar("DT_ColorCorrectionVolume", "m_Weight");
		static uintptr_t m_lookupFilename = GetNetVar("DT_ColorCorrectionVolume", "m_lookupFilename");
	}

	namespace DT_ColorCorrection
	{
		static uintptr_t baseclass = GetNetVar("DT_ColorCorrection", "baseclass");
		static uintptr_t m_vecOrigin = GetNetVar("DT_ColorCorrection", "m_vecOrigin");
		static uintptr_t m_minFalloff = GetNetVar("DT_ColorCorrection", "m_minFalloff");
		static uintptr_t m_maxFalloff = GetNetVar("DT_ColorCorrection", "m_maxFalloff");
		static uintptr_t m_flCurWeight = GetNetVar("DT_ColorCorrection", "m_flCurWeight");
		static uintptr_t m_flMaxWeight = GetNetVar("DT_ColorCorrection", "m_flMaxWeight");
		static uintptr_t m_flFadeInDuration = GetNetVar("DT_ColorCorrection", "m_flFadeInDuration");
		static uintptr_t m_flFadeOutDuration = GetNetVar("DT_ColorCorrection", "m_flFadeOutDuration");
		static uintptr_t m_netLookupFilename = GetNetVar("DT_ColorCorrection", "m_netLookupFilename");
		static uintptr_t m_bEnabled = GetNetVar("DT_ColorCorrection", "m_bEnabled");
		static uintptr_t m_bMaster = GetNetVar("DT_ColorCorrection", "m_bMaster");
		static uintptr_t m_bClientSide = GetNetVar("DT_ColorCorrection", "m_bClientSide");
		static uintptr_t m_bExclusive = GetNetVar("DT_ColorCorrection", "m_bExclusive");
	}

	namespace DT_CollisionProperty
	{
		static uintptr_t m_vecMins = GetNetVar("DT_CollisionProperty", "m_vecMins");
		static uintptr_t m_vecMaxs = GetNetVar("DT_CollisionProperty", "m_vecMaxs");
		static uintptr_t m_nSolidType = GetNetVar("DT_CollisionProperty", "m_nSolidType");
		static uintptr_t m_usSolidFlags = GetNetVar("DT_CollisionProperty", "m_usSolidFlags");
		static uintptr_t m_nSurroundType = GetNetVar("DT_CollisionProperty", "m_nSurroundType");
		static uintptr_t m_triggerBloat = GetNetVar("DT_CollisionProperty", "m_triggerBloat");
		static uintptr_t m_vecSpecifiedSurroundingMins = GetNetVar("DT_CollisionProperty", "m_vecSpecifiedSurroundingMins");
		static uintptr_t m_vecSpecifiedSurroundingMaxs = GetNetVar("DT_CollisionProperty", "m_vecSpecifiedSurroundingMaxs");
	}

	namespace DT_CascadeLight
	{
		static uintptr_t baseclass = GetNetVar("DT_CascadeLight", "baseclass");
		static uintptr_t m_shadowDirection = GetNetVar("DT_CascadeLight", "m_shadowDirection");
		static uintptr_t m_envLightShadowDirection = GetNetVar("DT_CascadeLight", "m_envLightShadowDirection");
		static uintptr_t m_bEnabled = GetNetVar("DT_CascadeLight", "m_bEnabled");
		static uintptr_t m_bUseLightEnvAngles = GetNetVar("DT_CascadeLight", "m_bUseLightEnvAngles");
		static uintptr_t m_LightColor = GetNetVar("DT_CascadeLight", "m_LightColor");
		static uintptr_t m_LightColorScale = GetNetVar("DT_CascadeLight", "m_LightColorScale");
		static uintptr_t m_flMaxShadowDist = GetNetVar("DT_CascadeLight", "m_flMaxShadowDist");
	}

	namespace DT_CSTeamExclusive
	{
		static uintptr_t m_iWeaponPurchasesThisMatch = GetNetVar("DT_CSTeamExclusive", "m_iWeaponPurchasesThisMatch");
		static uintptr_t m_EquippedLoadoutItemDefIndices = GetNetVar("DT_CSTeamExclusive", "m_EquippedLoadoutItemDefIndices");
	}

	namespace DT_CSTeam
	{
		static uintptr_t baseclass = GetNetVar("DT_CSTeam", "baseclass");
	}

	namespace DT_CSRagdoll
	{
		static uintptr_t m_vecOrigin = GetNetVar("DT_CSRagdoll", "m_vecOrigin");
		static uintptr_t m_vecRagdollOrigin = GetNetVar("DT_CSRagdoll", "m_vecRagdollOrigin");
		static uintptr_t m_hPlayer = GetNetVar("DT_CSRagdoll", "m_hPlayer");
		static uintptr_t m_nModelIndex = GetNetVar("DT_CSRagdoll", "m_nModelIndex");
		static uintptr_t m_nForceBone = GetNetVar("DT_CSRagdoll", "m_nForceBone");
		static uintptr_t m_vecForce = GetNetVar("DT_CSRagdoll", "m_vecForce");
		static uintptr_t m_vecRagdollVelocity = GetNetVar("DT_CSRagdoll", "m_vecRagdollVelocity");
		static uintptr_t m_iDeathPose = GetNetVar("DT_CSRagdoll", "m_iDeathPose");
		static uintptr_t m_iDeathFrame = GetNetVar("DT_CSRagdoll", "m_iDeathFrame");
		static uintptr_t m_iTeamNum = GetNetVar("DT_CSRagdoll", "m_iTeamNum");
		static uintptr_t m_bClientSideAnimation = GetNetVar("DT_CSRagdoll", "m_bClientSideAnimation");
		static uintptr_t m_flDeathYaw = GetNetVar("DT_CSRagdoll", "m_flDeathYaw");
		static uintptr_t m_flAbsYaw = GetNetVar("DT_CSRagdoll", "m_flAbsYaw");
		static uintptr_t m_bDiedAirborne = GetNetVar("DT_CSRagdoll", "m_bDiedAirborne");
	}

	namespace DT_CSPlayerResource
	{
		static uintptr_t baseclass = GetNetVar("DT_CSPlayerResource", "baseclass");
		static uintptr_t m_iPlayerC4 = GetNetVar("DT_CSPlayerResource", "m_iPlayerC4");
		static uintptr_t m_iPlayerVIP = GetNetVar("DT_CSPlayerResource", "m_iPlayerVIP");
		static uintptr_t m_bHostageAlive = GetNetVar("DT_CSPlayerResource", "m_bHostageAlive");
		static uintptr_t m_isHostageFollowingSomeone = GetNetVar("DT_CSPlayerResource", "m_isHostageFollowingSomeone");
		static uintptr_t m_iHostageEntityIDs = GetNetVar("DT_CSPlayerResource", "m_iHostageEntityIDs");
		static uintptr_t m_bombsiteCenterA = GetNetVar("DT_CSPlayerResource", "m_bombsiteCenterA");
		static uintptr_t m_bombsiteCenterB = GetNetVar("DT_CSPlayerResource", "m_bombsiteCenterB");
		static uintptr_t m_hostageRescueX = GetNetVar("DT_CSPlayerResource", "m_hostageRescueX");
		static uintptr_t m_hostageRescueY = GetNetVar("DT_CSPlayerResource", "m_hostageRescueY");
		static uintptr_t m_hostageRescueZ = GetNetVar("DT_CSPlayerResource", "m_hostageRescueZ");
		static uintptr_t m_iMVPs = GetNetVar("DT_CSPlayerResource", "m_iMVPs");
		static uintptr_t m_iArmor = GetNetVar("DT_CSPlayerResource", "m_iArmor");
		static uintptr_t m_bHasHelmet = GetNetVar("DT_CSPlayerResource", "m_bHasHelmet");
		static uintptr_t m_bHasDefuser = GetNetVar("DT_CSPlayerResource", "m_bHasDefuser");
		static uintptr_t m_iScore = GetNetVar("DT_CSPlayerResource", "m_iScore");
		static uintptr_t m_iCompetitiveRanking = GetNetVar("DT_CSPlayerResource", "m_iCompetitiveRanking");
		static uintptr_t m_iCompetitiveWins = GetNetVar("DT_CSPlayerResource", "m_iCompetitiveWins");
		static uintptr_t m_iCompetitiveRankType = GetNetVar("DT_CSPlayerResource", "m_iCompetitiveRankType");
		static uintptr_t m_iCompTeammateColor = GetNetVar("DT_CSPlayerResource", "m_iCompTeammateColor");
		static uintptr_t m_iLifetimeStart = GetNetVar("DT_CSPlayerResource", "m_iLifetimeStart");
		static uintptr_t m_iLifetimeEnd = GetNetVar("DT_CSPlayerResource", "m_iLifetimeEnd");
		static uintptr_t m_bControllingBot = GetNetVar("DT_CSPlayerResource", "m_bControllingBot");
		static uintptr_t m_iControlledPlayer = GetNetVar("DT_CSPlayerResource", "m_iControlledPlayer");
		static uintptr_t m_iControlledByPlayer = GetNetVar("DT_CSPlayerResource", "m_iControlledByPlayer");
		static uintptr_t m_iBotDifficulty = GetNetVar("DT_CSPlayerResource", "m_iBotDifficulty");
		static uintptr_t m_szClan = GetNetVar("DT_CSPlayerResource", "m_szClan");
		static uintptr_t m_nCharacterDefIndex = GetNetVar("DT_CSPlayerResource", "m_nCharacterDefIndex");
		static uintptr_t m_iTotalCashSpent = GetNetVar("DT_CSPlayerResource", "m_iTotalCashSpent");
		static uintptr_t m_iGunGameLevel = GetNetVar("DT_CSPlayerResource", "m_iGunGameLevel");
		static uintptr_t m_iCashSpentThisRound = GetNetVar("DT_CSPlayerResource", "m_iCashSpentThisRound");
		static uintptr_t m_nEndMatchNextMapVotes = GetNetVar("DT_CSPlayerResource", "m_nEndMatchNextMapVotes");
		static uintptr_t m_bEndMatchNextMapAllVoted = GetNetVar("DT_CSPlayerResource", "m_bEndMatchNextMapAllVoted");
		static uintptr_t m_nActiveCoinRank = GetNetVar("DT_CSPlayerResource", "m_nActiveCoinRank");
		static uintptr_t m_nMusicID = GetNetVar("DT_CSPlayerResource", "m_nMusicID");
		static uintptr_t m_nPersonaDataPublicLevel = GetNetVar("DT_CSPlayerResource", "m_nPersonaDataPublicLevel");
		static uintptr_t m_nPersonaDataPublicCommendsLeader = GetNetVar("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsLeader");
		static uintptr_t m_nPersonaDataPublicCommendsTeacher = GetNetVar("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsTeacher");
		static uintptr_t m_nPersonaDataPublicCommendsFriendly = GetNetVar("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsFriendly");
		static uintptr_t m_bHasCommunicationAbuseMute = GetNetVar("DT_CSPlayerResource", "m_bHasCommunicationAbuseMute");
		static uintptr_t m_szCrosshairCodes = GetNetVar("DT_CSPlayerResource", "m_szCrosshairCodes");
		static uintptr_t m_iMatchStats_Kills_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_Kills_Total");
		static uintptr_t m_iMatchStats_5k_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_5k_Total");
		static uintptr_t m_iMatchStats_4k_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_4k_Total");
		static uintptr_t m_iMatchStats_3k_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_3k_Total");
		static uintptr_t m_iMatchStats_Damage_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_Damage_Total");
		static uintptr_t m_iMatchStats_EquipmentValue_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_EquipmentValue_Total");
		static uintptr_t m_iMatchStats_KillReward_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_KillReward_Total");
		static uintptr_t m_iMatchStats_LiveTime_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_LiveTime_Total");
		static uintptr_t m_iMatchStats_Deaths_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_Deaths_Total");
		static uintptr_t m_iMatchStats_Assists_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_Assists_Total");
		static uintptr_t m_iMatchStats_HeadShotKills_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_HeadShotKills_Total");
		static uintptr_t m_iMatchStats_Objective_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_Objective_Total");
		static uintptr_t m_iMatchStats_CashEarned_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_CashEarned_Total");
		static uintptr_t m_iMatchStats_UtilityDamage_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_UtilityDamage_Total");
		static uintptr_t m_iMatchStats_EnemiesFlashed_Total = GetNetVar("DT_CSPlayerResource", "m_iMatchStats_EnemiesFlashed_Total");
	}

	namespace DT_CSPlayer
	{
		static uintptr_t baseclass = GetNetVar("DT_CSPlayer", "baseclass");
		static uintptr_t cslocaldata = GetNetVar("DT_CSPlayer", "cslocaldata");
		static uintptr_t csnonlocaldata = GetNetVar("DT_CSPlayer", "csnonlocaldata");
		static uintptr_t csteamdata = GetNetVar("DT_CSPlayer", "csteamdata");
		static uintptr_t m_angEyeAngles_0_ = GetNetVar("DT_CSPlayer", "m_angEyeAngles[0]");
		static uintptr_t m_angEyeAngles_1_ = GetNetVar("DT_CSPlayer", "m_angEyeAngles[1]");
		static uintptr_t m_iAddonBits = GetNetVar("DT_CSPlayer", "m_iAddonBits");
		static uintptr_t m_iPrimaryAddon = GetNetVar("DT_CSPlayer", "m_iPrimaryAddon");
		static uintptr_t m_iSecondaryAddon = GetNetVar("DT_CSPlayer", "m_iSecondaryAddon");
		static uintptr_t m_iThrowGrenadeCounter = GetNetVar("DT_CSPlayer", "m_iThrowGrenadeCounter");
		static uintptr_t m_bWaitForNoAttack = GetNetVar("DT_CSPlayer", "m_bWaitForNoAttack");
		static uintptr_t m_bIsRespawningForDMBonus = GetNetVar("DT_CSPlayer", "m_bIsRespawningForDMBonus");
		static uintptr_t m_iPlayerState = GetNetVar("DT_CSPlayer", "m_iPlayerState");
		static uintptr_t m_iAccount = GetNetVar("DT_CSPlayer", "m_iAccount");
		static uintptr_t m_iStartAccount = GetNetVar("DT_CSPlayer", "m_iStartAccount");
		static uintptr_t m_totalHitsOnServer = GetNetVar("DT_CSPlayer", "m_totalHitsOnServer");
		static uintptr_t m_bInBombZone = GetNetVar("DT_CSPlayer", "m_bInBombZone");
		static uintptr_t m_bInBuyZone = GetNetVar("DT_CSPlayer", "m_bInBuyZone");
		static uintptr_t m_bInNoDefuseArea = GetNetVar("DT_CSPlayer", "m_bInNoDefuseArea");
		static uintptr_t m_bKilledByTaser = GetNetVar("DT_CSPlayer", "m_bKilledByTaser");
		static uintptr_t m_iMoveState = GetNetVar("DT_CSPlayer", "m_iMoveState");
		static uintptr_t m_iClass = GetNetVar("DT_CSPlayer", "m_iClass");
		static uintptr_t m_ArmorValue = GetNetVar("DT_CSPlayer", "m_ArmorValue");
		static uintptr_t m_angEyeAngles = GetNetVar("DT_CSPlayer", "m_angEyeAngles");
		static uintptr_t m_bHasDefuser = GetNetVar("DT_CSPlayer", "m_bHasDefuser");
		static uintptr_t m_bNightVisionOn = GetNetVar("DT_CSPlayer", "m_bNightVisionOn");
		static uintptr_t m_bHasNightVision = GetNetVar("DT_CSPlayer", "m_bHasNightVision");
		static uintptr_t m_bInHostageRescueZone = GetNetVar("DT_CSPlayer", "m_bInHostageRescueZone");
		static uintptr_t m_bIsDefusing = GetNetVar("DT_CSPlayer", "m_bIsDefusing");
		static uintptr_t m_bIsGrabbingHostage = GetNetVar("DT_CSPlayer", "m_bIsGrabbingHostage");
		static uintptr_t m_iBlockingUseActionInProgress = GetNetVar("DT_CSPlayer", "m_iBlockingUseActionInProgress");
		static uintptr_t m_bIsScoped = GetNetVar("DT_CSPlayer", "m_bIsScoped");
		static uintptr_t m_bIsWalking = GetNetVar("DT_CSPlayer", "m_bIsWalking");
		static uintptr_t m_nIsAutoMounting = GetNetVar("DT_CSPlayer", "m_nIsAutoMounting");
		static uintptr_t m_bResumeZoom = GetNetVar("DT_CSPlayer", "m_bResumeZoom");
		static uintptr_t m_fImmuneToGunGameDamageTime = GetNetVar("DT_CSPlayer", "m_fImmuneToGunGameDamageTime");
		static uintptr_t m_bGunGameImmunity = GetNetVar("DT_CSPlayer", "m_bGunGameImmunity");
		static uintptr_t m_bHasMovedSinceSpawn = GetNetVar("DT_CSPlayer", "m_bHasMovedSinceSpawn");
		static uintptr_t m_bMadeFinalGunGameProgressiveKill = GetNetVar("DT_CSPlayer", "m_bMadeFinalGunGameProgressiveKill");
		static uintptr_t m_iGunGameProgressiveWeaponIndex = GetNetVar("DT_CSPlayer", "m_iGunGameProgressiveWeaponIndex");
		static uintptr_t m_iNumGunGameTRKillPoints = GetNetVar("DT_CSPlayer", "m_iNumGunGameTRKillPoints");
		static uintptr_t m_iNumGunGameKillsWithCurrentWeapon = GetNetVar("DT_CSPlayer", "m_iNumGunGameKillsWithCurrentWeapon");
		static uintptr_t m_iNumRoundKills = GetNetVar("DT_CSPlayer", "m_iNumRoundKills");
		static uintptr_t m_fMolotovUseTime = GetNetVar("DT_CSPlayer", "m_fMolotovUseTime");
		static uintptr_t m_fMolotovDamageTime = GetNetVar("DT_CSPlayer", "m_fMolotovDamageTime");
		static uintptr_t m_szArmsModel = GetNetVar("DT_CSPlayer", "m_szArmsModel");
		static uintptr_t m_hCarriedHostage = GetNetVar("DT_CSPlayer", "m_hCarriedHostage");
		static uintptr_t m_hCarriedHostageProp = GetNetVar("DT_CSPlayer", "m_hCarriedHostageProp");
		static uintptr_t m_bIsRescuing = GetNetVar("DT_CSPlayer", "m_bIsRescuing");
		static uintptr_t m_flGroundAccelLinearFracLastTime = GetNetVar("DT_CSPlayer", "m_flGroundAccelLinearFracLastTime");
		static uintptr_t m_bCanMoveDuringFreezePeriod = GetNetVar("DT_CSPlayer", "m_bCanMoveDuringFreezePeriod");
		static uintptr_t m_isCurrentGunGameLeader = GetNetVar("DT_CSPlayer", "m_isCurrentGunGameLeader");
		static uintptr_t m_isCurrentGunGameTeamLeader = GetNetVar("DT_CSPlayer", "m_isCurrentGunGameTeamLeader");
		static uintptr_t m_flGuardianTooFarDistFrac = GetNetVar("DT_CSPlayer", "m_flGuardianTooFarDistFrac");
		static uintptr_t m_flDetectedByEnemySensorTime = GetNetVar("DT_CSPlayer", "m_flDetectedByEnemySensorTime");
		static uintptr_t m_bIsPlayerGhost = GetNetVar("DT_CSPlayer", "m_bIsPlayerGhost");
		static uintptr_t m_iMatchStats_Kills = GetNetVar("DT_CSPlayer", "m_iMatchStats_Kills");
		static uintptr_t m_iMatchStats_Damage = GetNetVar("DT_CSPlayer", "m_iMatchStats_Damage");
		static uintptr_t m_iMatchStats_EquipmentValue = GetNetVar("DT_CSPlayer", "m_iMatchStats_EquipmentValue");
		static uintptr_t m_iMatchStats_MoneySaved = GetNetVar("DT_CSPlayer", "m_iMatchStats_MoneySaved");
		static uintptr_t m_iMatchStats_KillReward = GetNetVar("DT_CSPlayer", "m_iMatchStats_KillReward");
		static uintptr_t m_iMatchStats_LiveTime = GetNetVar("DT_CSPlayer", "m_iMatchStats_LiveTime");
		static uintptr_t m_iMatchStats_Deaths = GetNetVar("DT_CSPlayer", "m_iMatchStats_Deaths");
		static uintptr_t m_iMatchStats_Assists = GetNetVar("DT_CSPlayer", "m_iMatchStats_Assists");
		static uintptr_t m_iMatchStats_HeadShotKills = GetNetVar("DT_CSPlayer", "m_iMatchStats_HeadShotKills");
		static uintptr_t m_iMatchStats_Objective = GetNetVar("DT_CSPlayer", "m_iMatchStats_Objective");
		static uintptr_t m_iMatchStats_CashEarned = GetNetVar("DT_CSPlayer", "m_iMatchStats_CashEarned");
		static uintptr_t m_iMatchStats_UtilityDamage = GetNetVar("DT_CSPlayer", "m_iMatchStats_UtilityDamage");
		static uintptr_t m_iMatchStats_EnemiesFlashed = GetNetVar("DT_CSPlayer", "m_iMatchStats_EnemiesFlashed");
		static uintptr_t m_rank = GetNetVar("DT_CSPlayer", "m_rank");
		static uintptr_t m_passiveItems = GetNetVar("DT_CSPlayer", "m_passiveItems");
		static uintptr_t m_bHasParachute = GetNetVar("DT_CSPlayer", "m_bHasParachute");
		static uintptr_t m_unMusicID = GetNetVar("DT_CSPlayer", "m_unMusicID");
		static uintptr_t m_bHasHelmet = GetNetVar("DT_CSPlayer", "m_bHasHelmet");
		static uintptr_t m_bHasHeavyArmor = GetNetVar("DT_CSPlayer", "m_bHasHeavyArmor");
		static uintptr_t m_nHeavyAssaultSuitCooldownRemaining = GetNetVar("DT_CSPlayer", "m_nHeavyAssaultSuitCooldownRemaining");
		static uintptr_t m_flFlashDuration = GetNetVar("DT_CSPlayer", "m_flFlashDuration");
		static uintptr_t m_flFlashMaxAlpha = GetNetVar("DT_CSPlayer", "m_flFlashMaxAlpha");
		static uintptr_t m_iProgressBarDuration = GetNetVar("DT_CSPlayer", "m_iProgressBarDuration");
		static uintptr_t m_flProgressBarStartTime = GetNetVar("DT_CSPlayer", "m_flProgressBarStartTime");
		static uintptr_t m_hRagdoll = GetNetVar("DT_CSPlayer", "m_hRagdoll");
		static uintptr_t m_hPlayerPing = GetNetVar("DT_CSPlayer", "m_hPlayerPing");
		static uintptr_t m_cycleLatch = GetNetVar("DT_CSPlayer", "m_cycleLatch");
		static uintptr_t m_unCurrentEquipmentValue = GetNetVar("DT_CSPlayer", "m_unCurrentEquipmentValue");
		static uintptr_t m_unRoundStartEquipmentValue = GetNetVar("DT_CSPlayer", "m_unRoundStartEquipmentValue");
		static uintptr_t m_unFreezetimeEndEquipmentValue = GetNetVar("DT_CSPlayer", "m_unFreezetimeEndEquipmentValue");
		static uintptr_t m_bIsControllingBot = GetNetVar("DT_CSPlayer", "m_bIsControllingBot");
		static uintptr_t m_bHasControlledBotThisRound = GetNetVar("DT_CSPlayer", "m_bHasControlledBotThisRound");
		static uintptr_t m_bCanControlObservedBot = GetNetVar("DT_CSPlayer", "m_bCanControlObservedBot");
		static uintptr_t m_iControlledBotEntIndex = GetNetVar("DT_CSPlayer", "m_iControlledBotEntIndex");
		static uintptr_t m_vecAutomoveTargetEnd = GetNetVar("DT_CSPlayer", "m_vecAutomoveTargetEnd");
		static uintptr_t m_flAutoMoveStartTime = GetNetVar("DT_CSPlayer", "m_flAutoMoveStartTime");
		static uintptr_t m_flAutoMoveTargetTime = GetNetVar("DT_CSPlayer", "m_flAutoMoveTargetTime");
		static uintptr_t m_bIsAssassinationTarget = GetNetVar("DT_CSPlayer", "m_bIsAssassinationTarget");
		static uintptr_t m_bHud_MiniScoreHidden = GetNetVar("DT_CSPlayer", "m_bHud_MiniScoreHidden");
		static uintptr_t m_bHud_RadarHidden = GetNetVar("DT_CSPlayer", "m_bHud_RadarHidden");
		static uintptr_t m_nLastKillerIndex = GetNetVar("DT_CSPlayer", "m_nLastKillerIndex");
		static uintptr_t m_nLastConcurrentKilled = GetNetVar("DT_CSPlayer", "m_nLastConcurrentKilled");
		static uintptr_t m_nDeathCamMusic = GetNetVar("DT_CSPlayer", "m_nDeathCamMusic");
		static uintptr_t m_bIsHoldingLookAtWeapon = GetNetVar("DT_CSPlayer", "m_bIsHoldingLookAtWeapon");
		static uintptr_t m_bIsLookingAtWeapon = GetNetVar("DT_CSPlayer", "m_bIsLookingAtWeapon");
		static uintptr_t m_iNumRoundKillsHeadshots = GetNetVar("DT_CSPlayer", "m_iNumRoundKillsHeadshots");
		static uintptr_t m_unTotalRoundDamageDealt = GetNetVar("DT_CSPlayer", "m_unTotalRoundDamageDealt");
		static uintptr_t m_flLowerBodyYawTarget = GetNetVar("DT_CSPlayer", "m_flLowerBodyYawTarget");
		static uintptr_t m_bStrafing = GetNetVar("DT_CSPlayer", "m_bStrafing");
		static uintptr_t m_flThirdpersonRecoil = GetNetVar("DT_CSPlayer", "m_flThirdpersonRecoil");
		static uintptr_t m_bHideTargetID = GetNetVar("DT_CSPlayer", "m_bHideTargetID");
		static uintptr_t m_bIsSpawnRappelling = GetNetVar("DT_CSPlayer", "m_bIsSpawnRappelling");
		static uintptr_t m_vecSpawnRappellingRopeOrigin = GetNetVar("DT_CSPlayer", "m_vecSpawnRappellingRopeOrigin");
		static uintptr_t m_nSurvivalTeam = GetNetVar("DT_CSPlayer", "m_nSurvivalTeam");
		static uintptr_t m_hSurvivalAssassinationTarget = GetNetVar("DT_CSPlayer", "m_hSurvivalAssassinationTarget");
		static uintptr_t m_flHealthShotBoostExpirationTime = GetNetVar("DT_CSPlayer", "m_flHealthShotBoostExpirationTime");
		static uintptr_t m_flLastExoJumpTime = GetNetVar("DT_CSPlayer", "m_flLastExoJumpTime");
		static uintptr_t m_vecPlayerPatchEconIndices = GetNetVar("DT_CSPlayer", "m_vecPlayerPatchEconIndices");

		// manually added
		static uintptr_t m_vecViewOffset_0_ = GetNetVar("DT_CSPlayer", "m_vecViewOffset[0]");
		static uintptr_t m_iShotsFired = GetNetVar("DT_CSPlayer", "m_iShotsFired");
		static uintptr_t m_aimPunchAngle = GetNetVar("DT_CSPlayer", "m_aimPunchAngle");
	}

	namespace DT_CSNonLocalPlayerExclusive
	{
		static uintptr_t m_vecOrigin = GetNetVar("DT_CSNonLocalPlayerExclusive", "m_vecOrigin");
		static uintptr_t m_vecOrigin_2_ = GetNetVar("DT_CSNonLocalPlayerExclusive", "m_vecOrigin[2]");
	}

	namespace DT_CSLocalPlayerExclusive
	{
		static uintptr_t m_vecOrigin = GetNetVar("DT_CSLocalPlayerExclusive", "m_vecOrigin");
		static uintptr_t m_vecOrigin_2_ = GetNetVar("DT_CSLocalPlayerExclusive", "m_vecOrigin[2]");
		static uintptr_t m_flStamina = GetNetVar("DT_CSLocalPlayerExclusive", "m_flStamina");
		static uintptr_t m_iDirection = GetNetVar("DT_CSLocalPlayerExclusive", "m_iDirection");
		static uintptr_t m_iShotsFired = GetNetVar("DT_CSLocalPlayerExclusive", "m_iShotsFired");
		static uintptr_t m_nNumFastDucks = GetNetVar("DT_CSLocalPlayerExclusive", "m_nNumFastDucks");
		static uintptr_t m_bDuckOverride = GetNetVar("DT_CSLocalPlayerExclusive", "m_bDuckOverride");
		static uintptr_t m_flVelocityModifier = GetNetVar("DT_CSLocalPlayerExclusive", "m_flVelocityModifier");
		static uintptr_t m_bPlayerDominated = GetNetVar("DT_CSLocalPlayerExclusive", "m_bPlayerDominated");
		static uintptr_t m_bPlayerDominatingMe = GetNetVar("DT_CSLocalPlayerExclusive", "m_bPlayerDominatingMe");
		static uintptr_t m_iWeaponPurchasesThisRound = GetNetVar("DT_CSLocalPlayerExclusive", "m_iWeaponPurchasesThisRound");
		static uintptr_t m_unActiveQuestId = GetNetVar("DT_CSLocalPlayerExclusive", "m_unActiveQuestId");
		static uintptr_t m_nQuestProgressReason = GetNetVar("DT_CSLocalPlayerExclusive", "m_nQuestProgressReason");
		static uintptr_t m_iRetakesOffering = GetNetVar("DT_CSLocalPlayerExclusive", "m_iRetakesOffering");
		static uintptr_t m_iRetakesOfferingCard = GetNetVar("DT_CSLocalPlayerExclusive", "m_iRetakesOfferingCard");
		static uintptr_t m_bRetakesHasDefuseKit = GetNetVar("DT_CSLocalPlayerExclusive", "m_bRetakesHasDefuseKit");
		static uintptr_t m_bRetakesMVPLastRound = GetNetVar("DT_CSLocalPlayerExclusive", "m_bRetakesMVPLastRound");
		static uintptr_t m_iRetakesMVPBoostItem = GetNetVar("DT_CSLocalPlayerExclusive", "m_iRetakesMVPBoostItem");
		static uintptr_t m_RetakesMVPBoostExtraUtility = GetNetVar("DT_CSLocalPlayerExclusive", "m_RetakesMVPBoostExtraUtility");
		static uintptr_t m_unPlayerTvControlFlags = GetNetVar("DT_CSLocalPlayerExclusive", "m_unPlayerTvControlFlags");
	}

	namespace DT_CSGameRulesProxy
	{
		static uintptr_t baseclass = GetNetVar("DT_CSGameRulesProxy", "baseclass");
		static uintptr_t cs_gamerules_data = GetNetVar("DT_CSGameRulesProxy", "cs_gamerules_data");
	}

	namespace DT_CSGameRules
	{
		static uintptr_t m_bFreezePeriod = GetNetVar("DT_CSGameRules", "m_bFreezePeriod");
		static uintptr_t m_bMatchWaitingForResume = GetNetVar("DT_CSGameRules", "m_bMatchWaitingForResume");
		static uintptr_t m_bWarmupPeriod = GetNetVar("DT_CSGameRules", "m_bWarmupPeriod");
		static uintptr_t m_fWarmupPeriodEnd = GetNetVar("DT_CSGameRules", "m_fWarmupPeriodEnd");
		static uintptr_t m_fWarmupPeriodStart = GetNetVar("DT_CSGameRules", "m_fWarmupPeriodStart");
		static uintptr_t m_bTerroristTimeOutActive = GetNetVar("DT_CSGameRules", "m_bTerroristTimeOutActive");
		static uintptr_t m_bCTTimeOutActive = GetNetVar("DT_CSGameRules", "m_bCTTimeOutActive");
		static uintptr_t m_flTerroristTimeOutRemaining = GetNetVar("DT_CSGameRules", "m_flTerroristTimeOutRemaining");
		static uintptr_t m_flCTTimeOutRemaining = GetNetVar("DT_CSGameRules", "m_flCTTimeOutRemaining");
		static uintptr_t m_nTerroristTimeOuts = GetNetVar("DT_CSGameRules", "m_nTerroristTimeOuts");
		static uintptr_t m_nCTTimeOuts = GetNetVar("DT_CSGameRules", "m_nCTTimeOuts");
		static uintptr_t m_bTechnicalTimeOut = GetNetVar("DT_CSGameRules", "m_bTechnicalTimeOut");
		static uintptr_t m_iRoundTime = GetNetVar("DT_CSGameRules", "m_iRoundTime");
		static uintptr_t m_gamePhase = GetNetVar("DT_CSGameRules", "m_gamePhase");
		static uintptr_t m_totalRoundsPlayed = GetNetVar("DT_CSGameRules", "m_totalRoundsPlayed");
		static uintptr_t m_nOvertimePlaying = GetNetVar("DT_CSGameRules", "m_nOvertimePlaying");
		static uintptr_t m_timeUntilNextPhaseStarts = GetNetVar("DT_CSGameRules", "m_timeUntilNextPhaseStarts");
		static uintptr_t m_flCMMItemDropRevealStartTime = GetNetVar("DT_CSGameRules", "m_flCMMItemDropRevealStartTime");
		static uintptr_t m_flCMMItemDropRevealEndTime = GetNetVar("DT_CSGameRules", "m_flCMMItemDropRevealEndTime");
		static uintptr_t m_fRoundStartTime = GetNetVar("DT_CSGameRules", "m_fRoundStartTime");
		static uintptr_t m_bGameRestart = GetNetVar("DT_CSGameRules", "m_bGameRestart");
		static uintptr_t m_flRestartRoundTime = GetNetVar("DT_CSGameRules", "m_flRestartRoundTime");
		static uintptr_t m_flGameStartTime = GetNetVar("DT_CSGameRules", "m_flGameStartTime");
		static uintptr_t m_iHostagesRemaining = GetNetVar("DT_CSGameRules", "m_iHostagesRemaining");
		static uintptr_t m_bAnyHostageReached = GetNetVar("DT_CSGameRules", "m_bAnyHostageReached");
		static uintptr_t m_bMapHasBombTarget = GetNetVar("DT_CSGameRules", "m_bMapHasBombTarget");
		static uintptr_t m_bMapHasRescueZone = GetNetVar("DT_CSGameRules", "m_bMapHasRescueZone");
		static uintptr_t m_bMapHasBuyZone = GetNetVar("DT_CSGameRules", "m_bMapHasBuyZone");
		static uintptr_t m_bIsQueuedMatchmaking = GetNetVar("DT_CSGameRules", "m_bIsQueuedMatchmaking");
		static uintptr_t m_nQueuedMatchmakingMode = GetNetVar("DT_CSGameRules", "m_nQueuedMatchmakingMode");
		static uintptr_t m_bIsValveDS = GetNetVar("DT_CSGameRules", "m_bIsValveDS");
		static uintptr_t m_bIsQuestEligible = GetNetVar("DT_CSGameRules", "m_bIsQuestEligible");
		static uintptr_t m_bLogoMap = GetNetVar("DT_CSGameRules", "m_bLogoMap");
		static uintptr_t m_bPlayAllStepSoundsOnServer = GetNetVar("DT_CSGameRules", "m_bPlayAllStepSoundsOnServer");
		static uintptr_t m_iNumGunGameProgressiveWeaponsCT = GetNetVar("DT_CSGameRules", "m_iNumGunGameProgressiveWeaponsCT");
		static uintptr_t m_iNumGunGameProgressiveWeaponsT = GetNetVar("DT_CSGameRules", "m_iNumGunGameProgressiveWeaponsT");
		static uintptr_t m_iSpectatorSlotCount = GetNetVar("DT_CSGameRules", "m_iSpectatorSlotCount");
		static uintptr_t m_bBombDropped = GetNetVar("DT_CSGameRules", "m_bBombDropped");
		static uintptr_t m_bBombPlanted = GetNetVar("DT_CSGameRules", "m_bBombPlanted");
		static uintptr_t m_iRoundWinStatus = GetNetVar("DT_CSGameRules", "m_iRoundWinStatus");
		static uintptr_t m_eRoundWinReason = GetNetVar("DT_CSGameRules", "m_eRoundWinReason");
		static uintptr_t m_flDMBonusStartTime = GetNetVar("DT_CSGameRules", "m_flDMBonusStartTime");
		static uintptr_t m_flDMBonusTimeLength = GetNetVar("DT_CSGameRules", "m_flDMBonusTimeLength");
		static uintptr_t m_unDMBonusWeaponLoadoutSlot = GetNetVar("DT_CSGameRules", "m_unDMBonusWeaponLoadoutSlot");
		static uintptr_t m_bDMBonusActive = GetNetVar("DT_CSGameRules", "m_bDMBonusActive");
		static uintptr_t m_bTCantBuy = GetNetVar("DT_CSGameRules", "m_bTCantBuy");
		static uintptr_t m_bCTCantBuy = GetNetVar("DT_CSGameRules", "m_bCTCantBuy");
		static uintptr_t m_flGuardianBuyUntilTime = GetNetVar("DT_CSGameRules", "m_flGuardianBuyUntilTime");
		static uintptr_t m_iMatchStats_RoundResults = GetNetVar("DT_CSGameRules", "m_iMatchStats_RoundResults");
		static uintptr_t m_iMatchStats_PlayersAlive_T = GetNetVar("DT_CSGameRules", "m_iMatchStats_PlayersAlive_T");
		static uintptr_t m_iMatchStats_PlayersAlive_CT = GetNetVar("DT_CSGameRules", "m_iMatchStats_PlayersAlive_CT");
		static uintptr_t m_GGProgressiveWeaponOrderCT = GetNetVar("DT_CSGameRules", "m_GGProgressiveWeaponOrderCT");
		static uintptr_t m_GGProgressiveWeaponOrderT = GetNetVar("DT_CSGameRules", "m_GGProgressiveWeaponOrderT");
		static uintptr_t m_GGProgressiveWeaponKillUpgradeOrderCT = GetNetVar("DT_CSGameRules", "m_GGProgressiveWeaponKillUpgradeOrderCT");
		static uintptr_t m_GGProgressiveWeaponKillUpgradeOrderT = GetNetVar("DT_CSGameRules", "m_GGProgressiveWeaponKillUpgradeOrderT");
		static uintptr_t m_MatchDevice = GetNetVar("DT_CSGameRules", "m_MatchDevice");
		static uintptr_t m_bHasMatchStarted = GetNetVar("DT_CSGameRules", "m_bHasMatchStarted");
		static uintptr_t m_TeamRespawnWaveTimes = GetNetVar("DT_CSGameRules", "m_TeamRespawnWaveTimes");
		static uintptr_t m_flNextRespawnWave = GetNetVar("DT_CSGameRules", "m_flNextRespawnWave");
		static uintptr_t m_nNextMapInMapgroup = GetNetVar("DT_CSGameRules", "m_nNextMapInMapgroup");
		static uintptr_t m_nEndMatchMapGroupVoteTypes = GetNetVar("DT_CSGameRules", "m_nEndMatchMapGroupVoteTypes");
		static uintptr_t m_nEndMatchMapGroupVoteOptions = GetNetVar("DT_CSGameRules", "m_nEndMatchMapGroupVoteOptions");
		static uintptr_t m_nEndMatchMapVoteWinner = GetNetVar("DT_CSGameRules", "m_nEndMatchMapVoteWinner");
		static uintptr_t m_bIsDroppingItems = GetNetVar("DT_CSGameRules", "m_bIsDroppingItems");
		static uintptr_t m_iActiveAssassinationTargetMissionID = GetNetVar("DT_CSGameRules", "m_iActiveAssassinationTargetMissionID");
		static uintptr_t m_fMatchStartTime = GetNetVar("DT_CSGameRules", "m_fMatchStartTime");
		static uintptr_t m_szTournamentEventName = GetNetVar("DT_CSGameRules", "m_szTournamentEventName");
		static uintptr_t m_szTournamentEventStage = GetNetVar("DT_CSGameRules", "m_szTournamentEventStage");
		static uintptr_t m_szTournamentPredictionsTxt = GetNetVar("DT_CSGameRules", "m_szTournamentPredictionsTxt");
		static uintptr_t m_nTournamentPredictionsPct = GetNetVar("DT_CSGameRules", "m_nTournamentPredictionsPct");
		static uintptr_t m_szMatchStatTxt = GetNetVar("DT_CSGameRules", "m_szMatchStatTxt");
		static uintptr_t m_nGuardianModeWaveNumber = GetNetVar("DT_CSGameRules", "m_nGuardianModeWaveNumber");
		static uintptr_t m_nGuardianModeSpecialKillsRemaining = GetNetVar("DT_CSGameRules", "m_nGuardianModeSpecialKillsRemaining");
		static uintptr_t m_nGuardianModeSpecialWeaponNeeded = GetNetVar("DT_CSGameRules", "m_nGuardianModeSpecialWeaponNeeded");
		static uintptr_t m_nHalloweenMaskListSeed = GetNetVar("DT_CSGameRules", "m_nHalloweenMaskListSeed");
		static uintptr_t m_numGlobalGiftsGiven = GetNetVar("DT_CSGameRules", "m_numGlobalGiftsGiven");
		static uintptr_t m_numGlobalGifters = GetNetVar("DT_CSGameRules", "m_numGlobalGifters");
		static uintptr_t m_numGlobalGiftsPeriodSeconds = GetNetVar("DT_CSGameRules", "m_numGlobalGiftsPeriodSeconds");
		static uintptr_t m_arrFeaturedGiftersAccounts = GetNetVar("DT_CSGameRules", "m_arrFeaturedGiftersAccounts");
		static uintptr_t m_arrFeaturedGiftersGifts = GetNetVar("DT_CSGameRules", "m_arrFeaturedGiftersGifts");
		static uintptr_t m_arrProhibitedItemIndices = GetNetVar("DT_CSGameRules", "m_arrProhibitedItemIndices");
		static uintptr_t m_numBestOfMaps = GetNetVar("DT_CSGameRules", "m_numBestOfMaps");
		static uintptr_t m_arrTournamentActiveCasterAccounts = GetNetVar("DT_CSGameRules", "m_arrTournamentActiveCasterAccounts");
		static uintptr_t m_iNumConsecutiveCTLoses = GetNetVar("DT_CSGameRules", "m_iNumConsecutiveCTLoses");
		static uintptr_t m_iNumConsecutiveTerroristLoses = GetNetVar("DT_CSGameRules", "m_iNumConsecutiveTerroristLoses");
		static uintptr_t m_SurvivalRules = GetNetVar("DT_CSGameRules", "m_SurvivalRules");
		static uintptr_t m_RetakeRules = GetNetVar("DT_CSGameRules", "m_RetakeRules");
	}

	namespace DT_CHostage
	{
		static uintptr_t baseclass = GetNetVar("DT_CHostage", "baseclass");
		static uintptr_t m_isRescued = GetNetVar("DT_CHostage", "m_isRescued");
		static uintptr_t m_jumpedThisFrame = GetNetVar("DT_CHostage", "m_jumpedThisFrame");
		static uintptr_t m_iHealth = GetNetVar("DT_CHostage", "m_iHealth");
		static uintptr_t m_iMaxHealth = GetNetVar("DT_CHostage", "m_iMaxHealth");
		static uintptr_t m_lifeState = GetNetVar("DT_CHostage", "m_lifeState");
		static uintptr_t m_fFlags = GetNetVar("DT_CHostage", "m_fFlags");
		static uintptr_t m_nHostageState = GetNetVar("DT_CHostage", "m_nHostageState");
		static uintptr_t m_flRescueStartTime = GetNetVar("DT_CHostage", "m_flRescueStartTime");
		static uintptr_t m_flGrabSuccessTime = GetNetVar("DT_CHostage", "m_flGrabSuccessTime");
		static uintptr_t m_flDropStartTime = GetNetVar("DT_CHostage", "m_flDropStartTime");
		static uintptr_t m_vel = GetNetVar("DT_CHostage", "m_vel");
		static uintptr_t m_leader = GetNetVar("DT_CHostage", "m_leader");
	}

	namespace DT_CFish
	{
		static uintptr_t m_poolOrigin = GetNetVar("DT_CFish", "m_poolOrigin");
		static uintptr_t m_angle = GetNetVar("DT_CFish", "m_angle");
		static uintptr_t m_nModelIndex = GetNetVar("DT_CFish", "m_nModelIndex");
		static uintptr_t m_lifeState = GetNetVar("DT_CFish", "m_lifeState");
		static uintptr_t m_waterLevel = GetNetVar("DT_CFish", "m_waterLevel");
	}

	namespace DT_CChicken
	{
		static uintptr_t baseclass = GetNetVar("DT_CChicken", "baseclass");
		static uintptr_t m_jumpedThisFrame = GetNetVar("DT_CChicken", "m_jumpedThisFrame");
		static uintptr_t m_leader = GetNetVar("DT_CChicken", "m_leader");
	}

	namespace DT_BumpMineProjectile
	{
		static uintptr_t baseclass = GetNetVar("DT_BumpMineProjectile", "baseclass");
		static uintptr_t m_nParentBoneIndex = GetNetVar("DT_BumpMineProjectile", "m_nParentBoneIndex");
		static uintptr_t m_vecParentBonePos = GetNetVar("DT_BumpMineProjectile", "m_vecParentBonePos");
		static uintptr_t m_bArmed = GetNetVar("DT_BumpMineProjectile", "m_bArmed");
	}

	namespace DT_BreakableSurface
	{
		static uintptr_t baseclass = GetNetVar("DT_BreakableSurface", "baseclass");
		static uintptr_t m_nNumWide = GetNetVar("DT_BreakableSurface", "m_nNumWide");
		static uintptr_t m_nNumHigh = GetNetVar("DT_BreakableSurface", "m_nNumHigh");
		static uintptr_t m_flPanelWidth = GetNetVar("DT_BreakableSurface", "m_flPanelWidth");
		static uintptr_t m_flPanelHeight = GetNetVar("DT_BreakableSurface", "m_flPanelHeight");
		static uintptr_t m_vNormal = GetNetVar("DT_BreakableSurface", "m_vNormal");
		static uintptr_t m_vCorner = GetNetVar("DT_BreakableSurface", "m_vCorner");
		static uintptr_t m_bIsBroken = GetNetVar("DT_BreakableSurface", "m_bIsBroken");
		static uintptr_t m_nSurfaceType = GetNetVar("DT_BreakableSurface", "m_nSurfaceType");
		static uintptr_t m_RawPanelBitVec = GetNetVar("DT_BreakableSurface", "m_RawPanelBitVec");
	}

	namespace DT_BreakableProp
	{
		static uintptr_t baseclass = GetNetVar("DT_BreakableProp", "baseclass");
		static uintptr_t m_qPreferredPlayerCarryAngles = GetNetVar("DT_BreakableProp", "m_qPreferredPlayerCarryAngles");
		static uintptr_t m_bClientPhysics = GetNetVar("DT_BreakableProp", "m_bClientPhysics");
	}
	namespace DT_BreachChargeProjectile
	{
		static uintptr_t baseclass = GetNetVar("DT_BreachChargeProjectile", "baseclass");
		static uintptr_t m_bShouldExplode = GetNetVar("DT_BreachChargeProjectile", "m_bShouldExplode");
		static uintptr_t m_weaponThatThrewMe = GetNetVar("DT_BreachChargeProjectile", "m_weaponThatThrewMe");
		static uintptr_t m_nParentBoneIndex = GetNetVar("DT_BreachChargeProjectile", "m_nParentBoneIndex");
		static uintptr_t m_vecParentBonePos = GetNetVar("DT_BreachChargeProjectile", "m_vecParentBonePos");
	}

	namespace DT_BoneFollower
	{
		static uintptr_t baseclass = GetNetVar("DT_BoneFollower", "baseclass");
		static uintptr_t m_modelIndex = GetNetVar("DT_BoneFollower", "m_modelIndex");
		static uintptr_t m_solidIndex = GetNetVar("DT_BoneFollower", "m_solidIndex");
	}

	namespace DT_BeamSpotlight
	{
		static uintptr_t baseclass = GetNetVar("DT_BeamSpotlight", "baseclass");
		static uintptr_t m_nHaloIndex = GetNetVar("DT_BeamSpotlight", "m_nHaloIndex");
		static uintptr_t m_bSpotlightOn = GetNetVar("DT_BeamSpotlight", "m_bSpotlightOn");
		static uintptr_t m_bHasDynamicLight = GetNetVar("DT_BeamSpotlight", "m_bHasDynamicLight");
		static uintptr_t m_flSpotlightMaxLength = GetNetVar("DT_BeamSpotlight", "m_flSpotlightMaxLength");
		static uintptr_t m_flSpotlightGoalWidth = GetNetVar("DT_BeamSpotlight", "m_flSpotlightGoalWidth");
		static uintptr_t m_flHDRColorScale = GetNetVar("DT_BeamSpotlight", "m_flHDRColorScale");
		static uintptr_t m_nRotationAxis = GetNetVar("DT_BeamSpotlight", "m_nRotationAxis");
		static uintptr_t m_flRotationSpeed = GetNetVar("DT_BeamSpotlight", "m_flRotationSpeed");
	}

	namespace DT_Beam
	{
		static uintptr_t m_nBeamType = GetNetVar("DT_Beam", "m_nBeamType");
		static uintptr_t m_nBeamFlags = GetNetVar("DT_Beam", "m_nBeamFlags");
		static uintptr_t m_nNumBeamEnts = GetNetVar("DT_Beam", "m_nNumBeamEnts");
		static uintptr_t m_hAttachEntity = GetNetVar("DT_Beam", "m_hAttachEntity");
		static uintptr_t m_nAttachIndex = GetNetVar("DT_Beam", "m_nAttachIndex");
		static uintptr_t m_nHaloIndex = GetNetVar("DT_Beam", "m_nHaloIndex");
		static uintptr_t m_fHaloScale = GetNetVar("DT_Beam", "m_fHaloScale");
		static uintptr_t m_fWidth = GetNetVar("DT_Beam", "m_fWidth");
		static uintptr_t m_fEndWidth = GetNetVar("DT_Beam", "m_fEndWidth");
		static uintptr_t m_fFadeLength = GetNetVar("DT_Beam", "m_fFadeLength");
		static uintptr_t m_fAmplitude = GetNetVar("DT_Beam", "m_fAmplitude");
		static uintptr_t m_fStartFrame = GetNetVar("DT_Beam", "m_fStartFrame");
		static uintptr_t m_fSpeed = GetNetVar("DT_Beam", "m_fSpeed");
		static uintptr_t m_flFrameRate = GetNetVar("DT_Beam", "m_flFrameRate");
		static uintptr_t m_flHDRColorScale = GetNetVar("DT_Beam", "m_flHDRColorScale");
		static uintptr_t m_clrRender = GetNetVar("DT_Beam", "m_clrRender");
		static uintptr_t m_nRenderFX = GetNetVar("DT_Beam", "m_nRenderFX");
		static uintptr_t m_nRenderMode = GetNetVar("DT_Beam", "m_nRenderMode");
		static uintptr_t m_flFrame = GetNetVar("DT_Beam", "m_flFrame");
		static uintptr_t m_nClipStyle = GetNetVar("DT_Beam", "m_nClipStyle");
		static uintptr_t m_vecEndPos = GetNetVar("DT_Beam", "m_vecEndPos");
		static uintptr_t m_nModelIndex = GetNetVar("DT_Beam", "m_nModelIndex");
		static uintptr_t m_vecOrigin = GetNetVar("DT_Beam", "m_vecOrigin");
		static uintptr_t moveparent = GetNetVar("DT_Beam", "moveparent");
	}

	namespace DT_BaseWeaponWorldModel
	{
		static uintptr_t m_nModelIndex = GetNetVar("DT_BaseWeaponWorldModel", "m_nModelIndex");
		static uintptr_t m_nBody = GetNetVar("DT_BaseWeaponWorldModel", "m_nBody");
		static uintptr_t m_fEffects = GetNetVar("DT_BaseWeaponWorldModel", "m_fEffects");
		static uintptr_t moveparent = GetNetVar("DT_BaseWeaponWorldModel", "moveparent");
		static uintptr_t m_hCombatWeaponParent = GetNetVar("DT_BaseWeaponWorldModel", "m_hCombatWeaponParent");
	}

	namespace DT_BaseViewModel
	{
		static uintptr_t m_nModelIndex = GetNetVar("DT_BaseViewModel", "m_nModelIndex");
		static uintptr_t m_hWeapon = GetNetVar("DT_BaseViewModel", "m_hWeapon");
		static uintptr_t m_nSkin = GetNetVar("DT_BaseViewModel", "m_nSkin");
		static uintptr_t m_nBody = GetNetVar("DT_BaseViewModel", "m_nBody");
		static uintptr_t m_nSequence = GetNetVar("DT_BaseViewModel", "m_nSequence");
		static uintptr_t m_nViewModelIndex = GetNetVar("DT_BaseViewModel", "m_nViewModelIndex");
		static uintptr_t m_flPlaybackRate = GetNetVar("DT_BaseViewModel", "m_flPlaybackRate");
		static uintptr_t m_fEffects = GetNetVar("DT_BaseViewModel", "m_fEffects");
		static uintptr_t m_nAnimationParity = GetNetVar("DT_BaseViewModel", "m_nAnimationParity");
		static uintptr_t m_hOwner = GetNetVar("DT_BaseViewModel", "m_hOwner");
		static uintptr_t m_nNewSequenceParity = GetNetVar("DT_BaseViewModel", "m_nNewSequenceParity");
		static uintptr_t m_nResetEventsParity = GetNetVar("DT_BaseViewModel", "m_nResetEventsParity");
		static uintptr_t m_nMuzzleFlashParity = GetNetVar("DT_BaseViewModel", "m_nMuzzleFlashParity");
		static uintptr_t m_bShouldIgnoreOffsetAndAccuracy = GetNetVar("DT_BaseViewModel", "m_bShouldIgnoreOffsetAndAccuracy");
	}

	namespace DT_BaseVPhysicsTrigger
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseVPhysicsTrigger", "baseclass");
	}

	namespace DT_BaseTrigger
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseTrigger", "baseclass");
		static uintptr_t m_bClientSidePredicted = GetNetVar("DT_BaseTrigger", "m_bClientSidePredicted");
		static uintptr_t m_spawnflags = GetNetVar("DT_BaseTrigger", "m_spawnflags");
	}

	namespace DT_BaseToggle
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseToggle", "baseclass");
		static uintptr_t m_vecFinalDest = GetNetVar("DT_BaseToggle", "m_vecFinalDest");
		static uintptr_t m_movementType = GetNetVar("DT_BaseToggle", "m_movementType");
		static uintptr_t m_flMoveTargetTime = GetNetVar("DT_BaseToggle", "m_flMoveTargetTime");
	}
	namespace DT_BaseTeamObjectiveResource
	{
		static uintptr_t m_iTimerToShowInHUD = GetNetVar("DT_BaseTeamObjectiveResource", "m_iTimerToShowInHUD");
		static uintptr_t m_iStopWatchTimer = GetNetVar("DT_BaseTeamObjectiveResource", "m_iStopWatchTimer");
		static uintptr_t m_iNumControlPoints = GetNetVar("DT_BaseTeamObjectiveResource", "m_iNumControlPoints");
		static uintptr_t m_bPlayingMiniRounds = GetNetVar("DT_BaseTeamObjectiveResource", "m_bPlayingMiniRounds");
		static uintptr_t m_bControlPointsReset = GetNetVar("DT_BaseTeamObjectiveResource", "m_bControlPointsReset");
		static uintptr_t m_iUpdateCapHudParity = GetNetVar("DT_BaseTeamObjectiveResource", "m_iUpdateCapHudParity");
		static uintptr_t m_vCPPositions_0_ = GetNetVar("DT_BaseTeamObjectiveResource", "m_vCPPositions[0]");
		static uintptr_t m_vCPPositions = GetNetVar("DT_BaseTeamObjectiveResource", "m_vCPPositions");
		static uintptr_t m_bCPIsVisible = GetNetVar("DT_BaseTeamObjectiveResource", "m_bCPIsVisible");
		static uintptr_t m_flLazyCapPerc = GetNetVar("DT_BaseTeamObjectiveResource", "m_flLazyCapPerc");
		static uintptr_t m_iTeamIcons = GetNetVar("DT_BaseTeamObjectiveResource", "m_iTeamIcons");
		static uintptr_t m_iTeamOverlays = GetNetVar("DT_BaseTeamObjectiveResource", "m_iTeamOverlays");
		static uintptr_t m_iTeamReqCappers = GetNetVar("DT_BaseTeamObjectiveResource", "m_iTeamReqCappers");
		static uintptr_t m_flTeamCapTime = GetNetVar("DT_BaseTeamObjectiveResource", "m_flTeamCapTime");
		static uintptr_t m_iPreviousPoints = GetNetVar("DT_BaseTeamObjectiveResource", "m_iPreviousPoints");
		static uintptr_t m_bTeamCanCap = GetNetVar("DT_BaseTeamObjectiveResource", "m_bTeamCanCap");
		static uintptr_t m_iTeamBaseIcons = GetNetVar("DT_BaseTeamObjectiveResource", "m_iTeamBaseIcons");
		static uintptr_t m_iBaseControlPoints = GetNetVar("DT_BaseTeamObjectiveResource", "m_iBaseControlPoints");
		static uintptr_t m_bInMiniRound = GetNetVar("DT_BaseTeamObjectiveResource", "m_bInMiniRound");
		static uintptr_t m_iWarnOnCap = GetNetVar("DT_BaseTeamObjectiveResource", "m_iWarnOnCap");
		static uintptr_t m_iszWarnSound_0_ = GetNetVar("DT_BaseTeamObjectiveResource", "m_iszWarnSound[0]");
		static uintptr_t m_iszWarnSound = GetNetVar("DT_BaseTeamObjectiveResource", "m_iszWarnSound");
		static uintptr_t m_flPathDistance = GetNetVar("DT_BaseTeamObjectiveResource", "m_flPathDistance");
		static uintptr_t m_iNumTeamMembers = GetNetVar("DT_BaseTeamObjectiveResource", "m_iNumTeamMembers");
		static uintptr_t m_iCappingTeam = GetNetVar("DT_BaseTeamObjectiveResource", "m_iCappingTeam");
		static uintptr_t m_iTeamInZone = GetNetVar("DT_BaseTeamObjectiveResource", "m_iTeamInZone");
		static uintptr_t m_bBlocked = GetNetVar("DT_BaseTeamObjectiveResource", "m_bBlocked");
		static uintptr_t m_iOwner = GetNetVar("DT_BaseTeamObjectiveResource", "m_iOwner");
		static uintptr_t m_pszCapLayoutInHUD = GetNetVar("DT_BaseTeamObjectiveResource", "m_pszCapLayoutInHUD");
	}

	namespace DT_BasePropDoor
	{
		static uintptr_t baseclass = GetNetVar("DT_BasePropDoor", "baseclass");
	}

	namespace DT_BasePlayer
	{
		static uintptr_t baseclass = GetNetVar("DT_BasePlayer", "baseclass");
		static uintptr_t localdata = GetNetVar("DT_BasePlayer", "localdata");
		static uintptr_t pl = GetNetVar("DT_BasePlayer", "pl");
		static uintptr_t m_iFOV = GetNetVar("DT_BasePlayer", "m_iFOV");
		static uintptr_t m_iFOVStart = GetNetVar("DT_BasePlayer", "m_iFOVStart");
		static uintptr_t m_flFOVTime = GetNetVar("DT_BasePlayer", "m_flFOVTime");
		static uintptr_t m_iDefaultFOV = GetNetVar("DT_BasePlayer", "m_iDefaultFOV");
		static uintptr_t m_hZoomOwner = GetNetVar("DT_BasePlayer", "m_hZoomOwner");
		static uintptr_t m_afPhysicsFlags = GetNetVar("DT_BasePlayer", "m_afPhysicsFlags");
		static uintptr_t m_hVehicle = GetNetVar("DT_BasePlayer", "m_hVehicle");
		static uintptr_t m_hUseEntity = GetNetVar("DT_BasePlayer", "m_hUseEntity");
		static uintptr_t m_hGroundEntity = GetNetVar("DT_BasePlayer", "m_hGroundEntity");
		static uintptr_t m_iHealth = GetNetVar("DT_BasePlayer", "m_iHealth");
		static uintptr_t m_lifeState = GetNetVar("DT_BasePlayer", "m_lifeState");
		static uintptr_t m_iAmmo = GetNetVar("DT_BasePlayer", "m_iAmmo");
		static uintptr_t m_iBonusProgress = GetNetVar("DT_BasePlayer", "m_iBonusProgress");
		static uintptr_t m_iBonusChallenge = GetNetVar("DT_BasePlayer", "m_iBonusChallenge");
		static uintptr_t m_flMaxspeed = GetNetVar("DT_BasePlayer", "m_flMaxspeed");
		static uintptr_t m_fFlags = GetNetVar("DT_BasePlayer", "m_fFlags");
		static uintptr_t m_iObserverMode = GetNetVar("DT_BasePlayer", "m_iObserverMode");
		static uintptr_t m_bActiveCameraMan = GetNetVar("DT_BasePlayer", "m_bActiveCameraMan");
		static uintptr_t m_bCameraManXRay = GetNetVar("DT_BasePlayer", "m_bCameraManXRay");
		static uintptr_t m_bCameraManOverview = GetNetVar("DT_BasePlayer", "m_bCameraManOverview");
		static uintptr_t m_bCameraManScoreBoard = GetNetVar("DT_BasePlayer", "m_bCameraManScoreBoard");
		static uintptr_t m_uCameraManGraphs = GetNetVar("DT_BasePlayer", "m_uCameraManGraphs");
		static uintptr_t m_iDeathPostEffect = GetNetVar("DT_BasePlayer", "m_iDeathPostEffect");
		static uintptr_t m_hObserverTarget = GetNetVar("DT_BasePlayer", "m_hObserverTarget");
		static uintptr_t m_hViewModel_0_ = GetNetVar("DT_BasePlayer", "m_hViewModel[0]");
		static uintptr_t m_hViewModel = GetNetVar("DT_BasePlayer", "m_hViewModel");
		static uintptr_t m_iCoachingTeam = GetNetVar("DT_BasePlayer", "m_iCoachingTeam");
		static uintptr_t m_szLastPlaceName = GetNetVar("DT_BasePlayer", "m_szLastPlaceName");
		static uintptr_t m_vecLadderNormal = GetNetVar("DT_BasePlayer", "m_vecLadderNormal");
		static uintptr_t m_ladderSurfaceProps = GetNetVar("DT_BasePlayer", "m_ladderSurfaceProps");
		static uintptr_t m_ubEFNoInterpParity = GetNetVar("DT_BasePlayer", "m_ubEFNoInterpParity");
		static uintptr_t m_hPostProcessCtrl = GetNetVar("DT_BasePlayer", "m_hPostProcessCtrl");
		static uintptr_t m_hColorCorrectionCtrl = GetNetVar("DT_BasePlayer", "m_hColorCorrectionCtrl");
		static uintptr_t m_PlayerFog_m_hCtrl = GetNetVar("DT_BasePlayer", "m_PlayerFog.m_hCtrl");
		static uintptr_t m_vphysicsCollisionState = GetNetVar("DT_BasePlayer", "m_vphysicsCollisionState");
		static uintptr_t m_hViewEntity = GetNetVar("DT_BasePlayer", "m_hViewEntity");
		static uintptr_t m_bShouldDrawPlayerWhileUsingViewEntity = GetNetVar("DT_BasePlayer", "m_bShouldDrawPlayerWhileUsingViewEntity");
		static uintptr_t m_flDuckAmount = GetNetVar("DT_BasePlayer", "m_flDuckAmount");
		static uintptr_t m_flDuckSpeed = GetNetVar("DT_BasePlayer", "m_flDuckSpeed");
		static uintptr_t m_nWaterLevel = GetNetVar("DT_BasePlayer", "m_nWaterLevel");
	}

	namespace DT_BaseParticleEntity
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseParticleEntity", "baseclass");
	}

	namespace DT_BaseGrenade
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseGrenade", "baseclass");
		static uintptr_t m_flDamage = GetNetVar("DT_BaseGrenade", "m_flDamage");
		static uintptr_t m_DmgRadius = GetNetVar("DT_BaseGrenade", "m_DmgRadius");
		static uintptr_t m_bIsLive = GetNetVar("DT_BaseGrenade", "m_bIsLive");
		static uintptr_t m_hThrower = GetNetVar("DT_BaseGrenade", "m_hThrower");
		static uintptr_t m_vecVelocity = GetNetVar("DT_BaseGrenade", "m_vecVelocity");
		static uintptr_t m_fFlags = GetNetVar("DT_BaseGrenade", "m_fFlags");
	}

	namespace DT_BaseFlex
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseFlex", "baseclass");
		static uintptr_t m_flexWeight = GetNetVar("DT_BaseFlex", "m_flexWeight");
		static uintptr_t m_blinktoggle = GetNetVar("DT_BaseFlex", "m_blinktoggle");
		static uintptr_t m_viewtarget = GetNetVar("DT_BaseFlex", "m_viewtarget");
	}

	namespace DT_BaseEntity
	{
		static uintptr_t AnimTimeMustBeFirst = GetNetVar("DT_BaseEntity", "AnimTimeMustBeFirst");
		static uintptr_t m_flSimulationTime = GetNetVar("DT_BaseEntity", "m_flSimulationTime");
		static uintptr_t m_cellbits = GetNetVar("DT_BaseEntity", "m_cellbits");
		static uintptr_t m_cellX = GetNetVar("DT_BaseEntity", "m_cellX");
		static uintptr_t m_cellY = GetNetVar("DT_BaseEntity", "m_cellY");
		static uintptr_t m_cellZ = GetNetVar("DT_BaseEntity", "m_cellZ");
		static uintptr_t m_vecOrigin = GetNetVar("DT_BaseEntity", "m_vecOrigin");
		static uintptr_t m_angRotation = GetNetVar("DT_BaseEntity", "m_angRotation");
		static uintptr_t m_nModelIndex = GetNetVar("DT_BaseEntity", "m_nModelIndex");
		static uintptr_t m_fEffects = GetNetVar("DT_BaseEntity", "m_fEffects");
		static uintptr_t m_nRenderMode = GetNetVar("DT_BaseEntity", "m_nRenderMode");
		static uintptr_t m_nRenderFX = GetNetVar("DT_BaseEntity", "m_nRenderFX");
		static uintptr_t m_clrRender = GetNetVar("DT_BaseEntity", "m_clrRender");
		static uintptr_t m_iTeamNum = GetNetVar("DT_BaseEntity", "m_iTeamNum");
		static uintptr_t m_iPendingTeamNum = GetNetVar("DT_BaseEntity", "m_iPendingTeamNum");
		static uintptr_t m_CollisionGroup = GetNetVar("DT_BaseEntity", "m_CollisionGroup");
		static uintptr_t m_flElasticity = GetNetVar("DT_BaseEntity", "m_flElasticity");
		static uintptr_t m_flShadowCastDistance = GetNetVar("DT_BaseEntity", "m_flShadowCastDistance");
		static uintptr_t m_hOwnerEntity = GetNetVar("DT_BaseEntity", "m_hOwnerEntity");
		static uintptr_t m_hEffectEntity = GetNetVar("DT_BaseEntity", "m_hEffectEntity");
		static uintptr_t moveparent = GetNetVar("DT_BaseEntity", "moveparent");
		static uintptr_t m_iParentAttachment = GetNetVar("DT_BaseEntity", "m_iParentAttachment");
		static uintptr_t m_iName = GetNetVar("DT_BaseEntity", "m_iName");
		static uintptr_t movetype = GetNetVar("DT_BaseEntity", "movetype");
		static uintptr_t movecollide = GetNetVar("DT_BaseEntity", "movecollide");
		static uintptr_t m_Collision = GetNetVar("DT_BaseEntity", "m_Collision");
		static uintptr_t m_iTextureFrameIndex = GetNetVar("DT_BaseEntity", "m_iTextureFrameIndex");
		static uintptr_t m_bSimulatedEveryTick = GetNetVar("DT_BaseEntity", "m_bSimulatedEveryTick");
		static uintptr_t m_bAnimatedEveryTick = GetNetVar("DT_BaseEntity", "m_bAnimatedEveryTick");
		static uintptr_t m_bAlternateSorting = GetNetVar("DT_BaseEntity", "m_bAlternateSorting");
		static uintptr_t m_bSpotted = GetNetVar("DT_BaseEntity", "m_bSpotted");
		static uintptr_t m_bSpottedBy = GetNetVar("DT_BaseEntity", "m_bSpottedBy");
		static uintptr_t m_bSpottedByMask = GetNetVar("DT_BaseEntity", "m_bSpottedByMask");
		static uintptr_t m_bIsAutoaimTarget = GetNetVar("DT_BaseEntity", "m_bIsAutoaimTarget");
		static uintptr_t m_fadeMinDist = GetNetVar("DT_BaseEntity", "m_fadeMinDist");
		static uintptr_t m_fadeMaxDist = GetNetVar("DT_BaseEntity", "m_fadeMaxDist");
		static uintptr_t m_flFadeScale = GetNetVar("DT_BaseEntity", "m_flFadeScale");
		static uintptr_t m_nMinCPULevel = GetNetVar("DT_BaseEntity", "m_nMinCPULevel");
		static uintptr_t m_nMaxCPULevel = GetNetVar("DT_BaseEntity", "m_nMaxCPULevel");
		static uintptr_t m_nMinGPULevel = GetNetVar("DT_BaseEntity", "m_nMinGPULevel");
		static uintptr_t m_nMaxGPULevel = GetNetVar("DT_BaseEntity", "m_nMaxGPULevel");
		static uintptr_t m_flUseLookAtAngle = GetNetVar("DT_BaseEntity", "m_flUseLookAtAngle");
		static uintptr_t m_flLastMadeNoiseTime = GetNetVar("DT_BaseEntity", "m_flLastMadeNoiseTime");
		static uintptr_t m_flMaxFallVelocity = GetNetVar("DT_BaseEntity", "m_flMaxFallVelocity");
		static uintptr_t m_bEligibleForScreenHighlight = GetNetVar("DT_BaseEntity", "m_bEligibleForScreenHighlight");
	}

	namespace DT_BaseDoor
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseDoor", "baseclass");
		static uintptr_t m_flWaveHeight = GetNetVar("DT_BaseDoor", "m_flWaveHeight");
	}

	namespace DT_BaseCombatWeapon
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseCombatWeapon", "baseclass");
		static uintptr_t LocalWeaponData = GetNetVar("DT_BaseCombatWeapon", "LocalWeaponData");
		static uintptr_t LocalActiveWeaponData = GetNetVar("DT_BaseCombatWeapon", "LocalActiveWeaponData");
		static uintptr_t m_iViewModelIndex = GetNetVar("DT_BaseCombatWeapon", "m_iViewModelIndex");
		static uintptr_t m_iWorldModelIndex = GetNetVar("DT_BaseCombatWeapon", "m_iWorldModelIndex");
		static uintptr_t m_iWorldDroppedModelIndex = GetNetVar("DT_BaseCombatWeapon", "m_iWorldDroppedModelIndex");
		static uintptr_t m_iState = GetNetVar("DT_BaseCombatWeapon", "m_iState");
		static uintptr_t m_hOwner = GetNetVar("DT_BaseCombatWeapon", "m_hOwner");
		static uintptr_t m_iClip1 = GetNetVar("DT_BaseCombatWeapon", "m_iClip1");
		static uintptr_t m_iClip2 = GetNetVar("DT_BaseCombatWeapon", "m_iClip2");
		static uintptr_t m_iPrimaryReserveAmmoCount = GetNetVar("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
		static uintptr_t m_iSecondaryReserveAmmoCount = GetNetVar("DT_BaseCombatWeapon", "m_iSecondaryReserveAmmoCount");
		static uintptr_t m_hWeaponWorldModel = GetNetVar("DT_BaseCombatWeapon", "m_hWeaponWorldModel");
		static uintptr_t m_iNumEmptyAttacks = GetNetVar("DT_BaseCombatWeapon", "m_iNumEmptyAttacks");
	}

	namespace DT_BaseCombatCharacter
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseCombatCharacter", "baseclass");
		static uintptr_t bcc_localdata = GetNetVar("DT_BaseCombatCharacter", "bcc_localdata");
		static uintptr_t bcc_nonlocaldata = GetNetVar("DT_BaseCombatCharacter", "bcc_nonlocaldata");
		static uintptr_t m_LastHitGroup = GetNetVar("DT_BaseCombatCharacter", "m_LastHitGroup");
		static uintptr_t m_hActiveWeapon = GetNetVar("DT_BaseCombatCharacter", "m_hActiveWeapon");
		static uintptr_t m_flTimeOfLastInjury = GetNetVar("DT_BaseCombatCharacter", "m_flTimeOfLastInjury");
		static uintptr_t m_nRelativeDirectionOfLastInjury = GetNetVar("DT_BaseCombatCharacter", "m_nRelativeDirectionOfLastInjury");
		static uintptr_t m_hMyWeapons = GetNetVar("DT_BaseCombatCharacter", "m_hMyWeapons");
		static uintptr_t m_hMyWearables = GetNetVar("DT_BaseCombatCharacter", "m_hMyWearables");
	}

	namespace DT_BaseCSGrenadeProjectile
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseCSGrenadeProjectile", "baseclass");
		static uintptr_t m_vInitialVelocity = GetNetVar("DT_BaseCSGrenadeProjectile", "m_vInitialVelocity");
		static uintptr_t m_nBounces = GetNetVar("DT_BaseCSGrenadeProjectile", "m_nBounces");
		static uintptr_t m_nExplodeEffectIndex = GetNetVar("DT_BaseCSGrenadeProjectile", "m_nExplodeEffectIndex");
		static uintptr_t m_nExplodeEffectTickBegin = GetNetVar("DT_BaseCSGrenadeProjectile", "m_nExplodeEffectTickBegin");
		static uintptr_t m_vecExplodeEffectOrigin = GetNetVar("DT_BaseCSGrenadeProjectile", "m_vecExplodeEffectOrigin");
	}

	namespace DT_BaseCSGrenade
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseCSGrenade", "baseclass");
		static uintptr_t m_bRedraw = GetNetVar("DT_BaseCSGrenade", "m_bRedraw");
		static uintptr_t m_bIsHeldByPlayer = GetNetVar("DT_BaseCSGrenade", "m_bIsHeldByPlayer");
		static uintptr_t m_bPinPulled = GetNetVar("DT_BaseCSGrenade", "m_bPinPulled");
		static uintptr_t m_fThrowTime = GetNetVar("DT_BaseCSGrenade", "m_fThrowTime");
		static uintptr_t m_bLoopingSoundPlaying = GetNetVar("DT_BaseCSGrenade", "m_bLoopingSoundPlaying");
		static uintptr_t m_flThrowStrength = GetNetVar("DT_BaseCSGrenade", "m_flThrowStrength");
		static uintptr_t m_fDropTime = GetNetVar("DT_BaseCSGrenade", "m_fDropTime");
	}

	namespace DT_BaseButton
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseButton", "baseclass");
		static uintptr_t m_usable = GetNetVar("DT_BaseButton", "m_usable");
	}

	namespace DT_BaseBeam
	{
		static uintptr_t m_nModelIndex = GetNetVar("DT_BaseBeam", "m_nModelIndex");
		static uintptr_t m_nHaloIndex = GetNetVar("DT_BaseBeam", "m_nHaloIndex");
		static uintptr_t m_nStartFrame = GetNetVar("DT_BaseBeam", "m_nStartFrame");
		static uintptr_t m_nFrameRate = GetNetVar("DT_BaseBeam", "m_nFrameRate");
		static uintptr_t m_fLife = GetNetVar("DT_BaseBeam", "m_fLife");
		static uintptr_t m_fWidth = GetNetVar("DT_BaseBeam", "m_fWidth");
		static uintptr_t m_fEndWidth = GetNetVar("DT_BaseBeam", "m_fEndWidth");
		static uintptr_t m_nFadeLength = GetNetVar("DT_BaseBeam", "m_nFadeLength");
		static uintptr_t m_fAmplitude = GetNetVar("DT_BaseBeam", "m_fAmplitude");
		static uintptr_t m_nSpeed = GetNetVar("DT_BaseBeam", "m_nSpeed");
		static uintptr_t r = GetNetVar("DT_BaseBeam", "r");
		static uintptr_t g = GetNetVar("DT_BaseBeam", "g");
		static uintptr_t b = GetNetVar("DT_BaseBeam", "b");
		static uintptr_t a = GetNetVar("DT_BaseBeam", "a");
		static uintptr_t m_nFlags = GetNetVar("DT_BaseBeam", "m_nFlags");
	}

	namespace DT_BaseAttributableItem
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseAttributableItem", "baseclass");
		static uintptr_t m_AttributeManager = GetNetVar("DT_BaseAttributableItem", "m_AttributeManager");
		static uintptr_t m_OriginalOwnerXuidLow = GetNetVar("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
		static uintptr_t m_OriginalOwnerXuidHigh = GetNetVar("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
		static uintptr_t m_nFallbackPaintKit = GetNetVar("DT_BaseAttributableItem", "m_nFallbackPaintKit");
		static uintptr_t m_nFallbackSeed = GetNetVar("DT_BaseAttributableItem", "m_nFallbackSeed");
		static uintptr_t m_flFallbackWear = GetNetVar("DT_BaseAttributableItem", "m_flFallbackWear");
		static uintptr_t m_nFallbackStatTrak = GetNetVar("DT_BaseAttributableItem", "m_nFallbackStatTrak");
	}

	namespace DT_BaseAnimatingOverlay
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseAnimatingOverlay", "baseclass");
		static uintptr_t overlay_vars = GetNetVar("DT_BaseAnimatingOverlay", "overlay_vars");
	}

	namespace DT_BaseAnimating
	{
		static uintptr_t baseclass = GetNetVar("DT_BaseAnimating", "baseclass");
		static uintptr_t m_nSequence = GetNetVar("DT_BaseAnimating", "m_nSequence");
		static uintptr_t m_nForceBone = GetNetVar("DT_BaseAnimating", "m_nForceBone");
		static uintptr_t m_vecForce = GetNetVar("DT_BaseAnimating", "m_vecForce");
		static uintptr_t m_nSkin = GetNetVar("DT_BaseAnimating", "m_nSkin");
		static uintptr_t m_nBody = GetNetVar("DT_BaseAnimating", "m_nBody");
		static uintptr_t m_nHitboxSet = GetNetVar("DT_BaseAnimating", "m_nHitboxSet");
		static uintptr_t m_flModelScale = GetNetVar("DT_BaseAnimating", "m_flModelScale");
		static uintptr_t m_flPoseParameter = GetNetVar("DT_BaseAnimating", "m_flPoseParameter");
		static uintptr_t m_flPlaybackRate = GetNetVar("DT_BaseAnimating", "m_flPlaybackRate");
		static uintptr_t m_flEncodedController = GetNetVar("DT_BaseAnimating", "m_flEncodedController");
		static uintptr_t m_bClientSideAnimation = GetNetVar("DT_BaseAnimating", "m_bClientSideAnimation");
		static uintptr_t m_bClientSideFrameReset = GetNetVar("DT_BaseAnimating", "m_bClientSideFrameReset");
		static uintptr_t m_bClientSideRagdoll = GetNetVar("DT_BaseAnimating", "m_bClientSideRagdoll");
		static uintptr_t m_nNewSequenceParity = GetNetVar("DT_BaseAnimating", "m_nNewSequenceParity");
		static uintptr_t m_nResetEventsParity = GetNetVar("DT_BaseAnimating", "m_nResetEventsParity");
		static uintptr_t m_nMuzzleFlashParity = GetNetVar("DT_BaseAnimating", "m_nMuzzleFlashParity");
		static uintptr_t m_hLightingOrigin = GetNetVar("DT_BaseAnimating", "m_hLightingOrigin");
		static uintptr_t serveranimdata = GetNetVar("DT_BaseAnimating", "serveranimdata");
		static uintptr_t m_flFrozen = GetNetVar("DT_BaseAnimating", "m_flFrozen");
		static uintptr_t m_ScaleType = GetNetVar("DT_BaseAnimating", "m_ScaleType");
		static uintptr_t m_bSuppressAnimSounds = GetNetVar("DT_BaseAnimating", "m_bSuppressAnimSounds");
		static uintptr_t m_nHighlightColorR = GetNetVar("DT_BaseAnimating", "m_nHighlightColorR");
		static uintptr_t m_nHighlightColorG = GetNetVar("DT_BaseAnimating", "m_nHighlightColorG");
		static uintptr_t m_nHighlightColorB = GetNetVar("DT_BaseAnimating", "m_nHighlightColorB");
	}

	namespace DT_BRC4Target
	{
		static uintptr_t baseclass = GetNetVar("DT_BRC4Target", "baseclass");
		static uintptr_t m_bBrokenOpen = GetNetVar("DT_BRC4Target", "m_bBrokenOpen");
		static uintptr_t m_flRadius = GetNetVar("DT_BRC4Target", "m_flRadius");
	}

	namespace DT_BCCNonLocalPlayerExclusive
	{
		static uintptr_t m_hMyWeapons = GetNetVar("DT_BCCNonLocalPlayerExclusive", "m_hMyWeapons");
	}

	namespace DT_BCCLocalPlayerExclusive
	{
		static uintptr_t m_flNextAttack = GetNetVar("DT_BCCLocalPlayerExclusive", "m_flNextAttack");
	}

	namespace DT_AttributeList
	{
		static uintptr_t m_Attributes = GetNetVar("DT_AttributeList", "m_Attributes");
	}

	namespace DT_AttributeContainer
	{
		static uintptr_t m_hOuter = GetNetVar("DT_AttributeContainer", "m_hOuter");
		static uintptr_t m_ProviderType = GetNetVar("DT_AttributeContainer", "m_ProviderType");
		static uintptr_t m_iReapplyProvisionParity = GetNetVar("DT_AttributeContainer", "m_iReapplyProvisionParity");
		static uintptr_t m_Item = GetNetVar("DT_AttributeContainer", "m_Item");
	}

	namespace DT_AnimTimeMustBeFirst
	{
		static uintptr_t m_flAnimTime = GetNetVar("DT_AnimTimeMustBeFirst", "m_flAnimTime");
	}

	namespace DT_AI_BaseNPC
	{
		static uintptr_t baseclass = GetNetVar("DT_AI_BaseNPC", "baseclass");
		static uintptr_t m_lifeState = GetNetVar("DT_AI_BaseNPC", "m_lifeState");
		static uintptr_t m_bPerformAvoidance = GetNetVar("DT_AI_BaseNPC", "m_bPerformAvoidance");
		static uintptr_t m_bIsMoving = GetNetVar("DT_AI_BaseNPC", "m_bIsMoving");
		static uintptr_t m_bFadeCorpse = GetNetVar("DT_AI_BaseNPC", "m_bFadeCorpse");
		static uintptr_t m_iDeathPose = GetNetVar("DT_AI_BaseNPC", "m_iDeathPose");
		static uintptr_t m_iDeathFrame = GetNetVar("DT_AI_BaseNPC", "m_iDeathFrame");
		static uintptr_t m_iSpeedModRadius = GetNetVar("DT_AI_BaseNPC", "m_iSpeedModRadius");
		static uintptr_t m_iSpeedModSpeed = GetNetVar("DT_AI_BaseNPC", "m_iSpeedModSpeed");
		static uintptr_t m_bSpeedModActive = GetNetVar("DT_AI_BaseNPC", "m_bSpeedModActive");
		static uintptr_t m_bImportanRagdoll = GetNetVar("DT_AI_BaseNPC", "m_bImportanRagdoll");
		static uintptr_t m_flTimePingEffect = GetNetVar("DT_AI_BaseNPC", "m_flTimePingEffect");
	}

}

#endif