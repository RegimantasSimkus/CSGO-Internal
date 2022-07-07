#pragma once

#ifndef ICLIENTENTITYLIST_H_
#define ICLIENTENTITYLIST_H_

struct EntityCacheInfo_t
{
	// Cached off because GetClientNetworkable is called a *lot*
	void* m_pNetworkable;
	unsigned short m_BaseEntitiesIndex;	// Index into m_BaseEntities (or m_BaseEntities.InvalidIndex() if none).
	unsigned short m_bDormant;	// cached dormant state - this is only a bit
};

class C_BasePlayer;

class IClientEntityList
{
public:
	// Get IClientNetworkable interface for specified entity
	virtual void* GetClientNetworkable(int entnum) = 0;
	virtual void* GetClientNetworkableFromHandle(void* hEnt) = 0;
	virtual void* GetClientUnknownFromHandle(void* hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual C_BasePlayer* GetClientEntity(int entnum) = 0;
	virtual void* GetClientEntityFromHandle(void* hEnt) = 0;

	// Returns number of entities currently in use
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	// Returns highest index actually used
	virtual int					GetHighestEntityIndex(void) = 0;

	// Sizes entity list to specified size
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
	virtual EntityCacheInfo_t* GetClientNetworkableArray() = 0;
};

#endif