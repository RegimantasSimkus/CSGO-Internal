#pragma once

class ICHLClient
{
public:
	ICHLClient();

	virtual int						Connect(void* appSystemFactory, void* pGlobals);
	virtual void                    Disconnect();
	virtual int						Init(void* appSystemFactory, void* pGlobals);

	virtual void					PostInit();
	virtual void					Shutdown(void);

	virtual void					LevelInitPreEntity(const char* pMapName);
	virtual void					LevelInitPostEntity();
	virtual void					LevelShutdown(void);

	virtual ClientClass* GetAllClasses(void);

	virtual int						HudVidInit(void);
	virtual void					HudProcessInput(bool bActive);
	virtual void					HudUpdate(bool bActive);
	virtual void					HudReset(void);
	virtual void					HudText(const char* message);

	// Mouse Input Interfaces
	virtual void					IN_ActivateMouse(void);
	virtual void					IN_DeactivateMouse(void);
	virtual void					IN_Accumulate(void);
	virtual void					IN_ClearStates(void);
	virtual bool					IN_IsKeyDown(const char* name, bool& isdown);
	// Raw signal
	virtual int						IN_KeyEvent(int eventcode, void* keynum, const char* pszCurrentBinding);
	virtual void					IN_SetSampleTime(float frametime);
	// Create movement command
	virtual void					CreateMove(int sequence_number, float input_sample_frametime, bool active);
	virtual void					ExtraMouseSample(float frametime, bool active);
	virtual bool					WriteUsercmdDeltaToBuffer(int nSlot, void* buf, int from, int to, bool isnewcommand);
	virtual void					EncodeUserCmdToBuffer(int nSlot, void*& buf, int slot);
	virtual void					DecodeUserCmdFromBuffer(int nSlot, void*& buf, int slot);


	virtual void					View_Render(void* rect);
	virtual void					RenderView(const void*& view, int nClearFlags, int whatToDraw);
	virtual void					View_Fade(void* pSF);

	virtual void					SetCrosshairAngle(const void*& angle);

	virtual void					InitSprite(void* pSprite, const char* loadname);
	virtual void					ShutdownSprite(void* pSprite);

	virtual int						GetSpriteSize(void) const;

	virtual void					VoiceStatus(int entindex, int iSsSlot, void* bTalking);

	virtual bool					PlayerAudible(int iPlayerIndex);

	virtual void					InstallStringTableCallback(const char* tableName);

	virtual void					FrameStageNotify(void* curStage);

	virtual bool					DispatchUserMessage(int msg_type, int nFlags, int size, const void* msg);

	// Save/restore system hooks
	virtual void*			SaveInit(int size);
	virtual void			SaveWriteFields(void*, const char*, void*, void*, void*, int);
	virtual void			SaveReadFields(void*, const char*, void*, void*, void*, int);
	virtual void			PreSave(void*);
	virtual void			Save(void*);
	virtual void			WriteSaveHeaders(void*);
	virtual void			ReadRestoreHeaders(void*);
	virtual void			Restore(void*, bool);
	virtual void			DispatchOnRestore();
	virtual void			WriteSaveGameScreenshot(const char* pFilename);

	// Given a list of "S(wavname) S(wavname2)" tokens, look up the localized text and emit
	//  the appropriate close caption if running with closecaption = 1
	virtual void			EmitSentenceCloseCaption(char const* tokenstream);
	virtual void			EmitCloseCaption(char const* captionname, float duration);

	virtual void* GetStandardRecvProxies();

	virtual bool			CanRecordDemo(char* errorMsg, int length) const;
	virtual bool			CanStopRecordDemo(char* errorMsg, int length) const;

	virtual void			OnDemoRecordStart(char const* pDemoBaseName);
	virtual void			OnDemoRecordStop();
	virtual void			OnDemoPlaybackStart(char const* pDemoBaseName);
	virtual void			OnDemoPlaybackRestart();
	virtual void			OnDemoPlaybackStop();
	virtual void			SetDemoPlaybackHighlightXuid(unsigned __int64 xuid, bool bLowlights);
	virtual void			ShowHighlightSkippingMessage(bool bState, int nCurrentTick = 0, int nTickStart = 0, int nTickStop = 0);

	virtual void			RecordDemoPolishUserInput(int nCmdIndex);

	// Cache replay ragdolls
	virtual bool			CacheReplayRagdolls(const char* pFilename, int nStartTick);

	// Send a message to the replay browser
	virtual void			ReplayUI_SendMessage(void* pMsg);

	// Get the client replay factory
	virtual void* GetReplayFactory();

	// Clear out the local player's replay pointer so it doesn't get deleted
	virtual void			ClearLocalPlayerReplayPtr();

	virtual bool			ShouldDrawDropdownConsole();

	// Get client screen dimensions
	virtual int				GetScreenWidth();
	virtual int				GetScreenHeight();

	// save game screenshot writing
	virtual void			WriteSaveGameScreenshotOfSize(const char* pFilename, int width, int height, bool bCreatePowerOf2Padded/*=false*/, bool bWriteVTF/*=false*/);

	// Write a .VTF screenshot to disk for the replay system
	virtual void			WriteReplayScreenshot(void*& params);

	// Reallocate memory for replay screenshots - called if user changes resolution or if the convar "replay_screenshotresolution" changes
	virtual void			UpdateReplayScreenshotCache();

	// Gets the location of the player viewpoint
	virtual bool			GetPlayerView(void*& playerView);

	virtual bool			ShouldHideLoadingPlaque(void);

	virtual void			InvalidateMdlCache();

	virtual void			OnActiveSplitscreenPlayerChanged(int nNewSlot);
	virtual void			OnSplitScreenStateChanged();
	virtual int 			GetSpectatorTarget(void* pObserverMode);
	virtual void			CenterStringOff();


	virtual void			OnScreenSizeChanged(int nOldWidth, int nOldHeight);
	virtual void* InstantiateMaterialProxy(const char* proxyName);

	virtual void*	GetFullscreenClientDLLVPanel(void);
	virtual void			MarkEntitiesAsTouching(void* e1, void* e2);
	virtual void			OnKeyBindingChanged(void* buttonCode, char const* pchKeyName, char const* pchNewBinding);
	virtual bool			HandleGameUIEvent(const void*& event);

	virtual bool			GetSoundSpatialization(void*& info);

public:
	void					PrecacheMaterial(const char* pMaterialName);
	void					PrecacheMovie(const char* pMovieName);

	virtual void			SetBlurFade(float scale);

	virtual void			ResetHudCloseCaption();

	virtual void			Hud_SaveStarted();

	virtual void			ShutdownMovies();

	virtual void			GetStatus(char* buffer, int bufsize);

#if defined ( CSTRIKE15 )
	virtual bool			IsChatRaised(void);
	virtual bool			IsRadioPanelRaised(void);
	virtual bool			IsBindMenuRaised(void);
	virtual bool			IsTeamMenuRaised(void);
	virtual bool			IsLoadingScreenRaised(void);
#endif

#if defined(_PS3)
	virtual int				GetDrawFlags(void);
	virtual int				GetBuildViewID(void);
	virtual bool			IsSPUBuildWRJobsOn(void);
	virtual void			CacheFrustumData(Frustum_t* pFrustum, Frustum_t* pAreaFrustum, void* pRenderAreaBits, int numArea, bool bViewerInSolidSpace);
	virtual void* GetBuildViewVolumeCuller(void);
	virtual Frustum_t* GetBuildViewFrustum(void);
	virtual Frustum_t* GetBuildViewAreaFrustum(void);
	virtual unsigned char* GetBuildViewRenderAreaBits(void);
#else
	virtual bool			IsBuildWRThreaded(void);
	virtual void			QueueBuildWorldListJob(void* pJob);
	virtual void			CacheFrustumData(const void*& frustum, const void*& aeraFrustums);
	virtual const void* GetBuildViewFrustum(void) const;
	virtual const void* GetBuildViewAeraFrustums(void) const;
#endif

	virtual bool IsSubscribedMap(const char* pchMapName, bool bOnlyOnDisk);
	virtual bool IsFeaturedMap(const char* pchMapName, bool bOnlyOnDisk);

	virtual void DownloadCommunityMapFile(void* id);
	virtual float GetUGCFileDownloadProgress(void* id);

	virtual void RecordUIEvent(const char* szEvent);
	virtual void OnHltvReplay(const void*& msg); //{ g_HltvReplaySystem.OnHltvReplay(msg); }
	virtual void OnHltvReplayTick(); // { g_HltvReplaySystem.OnHltvReplayTick(); }
	virtual int GetHltvReplayDelay(); // { return g_HltvReplaySystem.GetHltvReplayDelay(); }
	virtual void OnDemoPlaybackTimeJump();

	// Inventory access
	virtual float FindInventoryItemWithMaxAttributeValue(char const* szItemType, char const* szAttrClass);
	virtual void DetermineSubscriptionKvToAdvertise(void* kvLocalPlayer);

	// Overwatchsupport for engine
	virtual bool ValidateSignedEvidenceHeader(char const* szKey, void const* pvHeader, void* pPlaybackParameters);
	virtual void PrepareSignedEvidenceData(void* pvData, int numBytes, void const* pPlaybackParameters);
	virtual bool ShouldSkipEvidencePlayback(void const* pPlaybackParameters);

	// Scaleform slot controller
	virtual void* GetScaleformSlotInitController();

	virtual bool IsConnectedUserInfoChangeAllowed(void* pCvar);
	virtual void OnCommandDuringPlayback(char const* cmd);

	virtual void RetireAllPlayerDecals(bool bRenderContextValid);

	virtual void EngineGotvSyncPacket(const void* pPkt);

	virtual void OnTickPre(int tickcount);

	virtual char const* GetRichPresenceStatusString();

	virtual int GetInEyeEntity() const;

private:
	void					UncacheAllMaterials();
	void					UncacheAllMovies();
	void					ResetStringTablePointers();

	void*	m_CachedMaterials;
	void*				m_CachedMovies;

	void* m_pHudCloseCaption;
};

