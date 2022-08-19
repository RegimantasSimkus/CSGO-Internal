#pragma once
#include "Vector.h"

#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	0x80

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	

// unused 
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
#define CONTENTS_UNUSED6		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace


// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define	SURF_LIGHT		0x0001		// value will hold the light strength
#define	SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define	SURF_SKY		0x0004		// don't draw, but add to skybox
#define	SURF_WARP		0x0008		// turbulent water warp
#define	SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define	SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define	SURF_NODRAW		0x0080	// don't bother referencing the texture

#define	SURF_HINT		0x0100	// make a primary bsp splitter

#define	SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface 
#define SURF_HITBOX		0x8000	// surface is part of a hitbox



// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define	MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

class ITraceFilter
{
public:
	ITraceFilter()
	{

	}

	virtual bool ShouldHitEntity(void* pEntity, int contentsMask) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};

struct OcclusionTestResults_t
{
	void* vEndMin;
	void* vEndMax;
};

//-----------------------------------------------------------------------------
// Classes are expected to inherit these + implement the ShouldHitEntity method
//-----------------------------------------------------------------------------

// This is the one most normal traces will inherit from
class CTraceFilter : public ITraceFilter
{
public:
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
};

class CTraceFilterEntitiesOnly : public ITraceFilter
{
public:
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_ENTITIES_ONLY;
	}
};

class C_BasePlayer;

struct csurface_t
{
	const char* name;
	short		surfaceProps;
	unsigned short	flags;		// BUGBUG: These are declared per surface, not per material, but this database is per-material now
};

class trace_t
{
public:
	float			fractionleftsolid;	// time we left a solid, only valid if we started in solid
	csurface_t		surface;			// surface hit (impact surface)

	int				hitgroup;			// 0 == generic, non-zero is specific body part

	short			physicsbone;		// physics bone hit by trace in studio
	unsigned short	worldSurfaceIndex;	// Index of the msurface2_t, if applicable

	C_BasePlayer* m_pEnt;
};

class matrix3x4_t;

struct Ray_t
{
	Vector  m_Start;	// starting point, centered within the extents
	Vector  m_Delta;	// direction + length of the ray
	Vector  m_StartOffset;	// Add this to m_Start to get the actual ray start
	Vector  m_Extents;	// Describes an axis aligned box extruded along a ray
	const matrix3x4_t* m_pWorldAxisTransform;
	bool	m_IsRay;	// are the extents zero?
	bool	m_IsSwept;	// is delta != 0?

	Ray_t() : m_pWorldAxisTransform(NULL) {}

	void Init(Vector const& start, Vector const& end)
	{
		m_Delta = start;
		m_Delta.Sub(end);

		m_IsSwept = m_Delta.IsZero(); //(m_Delta.LengthSqr() != 0);

		m_Extents.Zero();
		m_pWorldAxisTransform = NULL;
		m_IsRay = true;

		// Offset m_Start to be in the center of the box...
		m_StartOffset.Zero();
		m_Start = { start.x, start.y, start.z };
	}

	//void Init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs)
	//{
	//	Assert(&end);
	//	VectorSubtract(end, start, m_Delta);

	//	m_pWorldAxisTransform = NULL;
	//	m_IsSwept = (m_Delta.LengthSqr() != 0);

	//	VectorSubtract(maxs, mins, m_Extents);
	//	m_Extents *= 0.5f;
	//	m_IsRay = (m_Extents.LengthSqr() < 1e-6);

	//	Assert(m_Extents.x >= 0 && m_Extents.y >= 0 && m_Extents.z >= 0);
	//	// Offset m_Start to be in the center of the box...
	//	VectorAdd(mins, maxs, m_StartOffset);
	//	m_StartOffset *= 0.5f;
	//	VectorAdd(start, m_StartOffset, m_Start);
	//	m_StartOffset *= -1.0f;
	//}

private:
};

class IEngineTrace
{
public:
	// Returns the contents mask + entity at a particular world-space position
	virtual int		GetPointContents(const Vector & vecAbsPosition, int contentsMask = 0, void* *ppEntity = NULL) = 0;

	// Returns the contents mask of the world only @ the world-space position (static props are ignored)
	virtual int		GetPointContents_WorldOnly(const Vector& vecAbsPosition, int contentsMask = 0) = 0;

	// A version that simply accepts a ray (can work as a traceline or tracehull)
	virtual void	TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;

	// Get the point contents, but only test the specific entity. This works
	// on static props and brush models.
	//
	// If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
	// bFailed to true if bFailed is non-null.
	virtual int		GetPointContents_Collideable(void* pCollide, const Vector& vecAbsPosition) = 0;

	// Traces a ray against a particular entity
	virtual void	ClipRayToEntity(const void*& ray, unsigned int fMask, void* pEnt, trace_t* pTrace) = 0;

	// Traces a ray against a particular entity
	virtual void	ClipRayToCollideable(const void*& ray, unsigned int fMask, void* pCollide, trace_t* pTrace) = 0;


	// A version that sets up the leaf and entity lists and allows you to pass those in for collision.
	virtual void	SetupLeafAndEntityListRay(const void*& ray, void* pTraceData) = 0;
	virtual void    SetupLeafAndEntityListBox(const Vector& vecBoxMin, const Vector& vecBoxMax, void* pTraceData) = 0;
	virtual void	TraceRayAgainstLeafAndEntityList(const Ray_t& ray, void* pTraceData, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;

	// A version that sweeps a collideable through the world
	// abs start + abs end represents the collision origins you want to sweep the collideable through
	// vecAngles represents the collision angles of the collideable during the sweep
	virtual void	SweepCollideable(void* pCollide, const Vector& vecAbsStart, const Vector& vecAbsEnd,
		const void*& vecAngles, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;

	// Enumerates over all entities along a ray
	// If triggers == true, it enumerates all triggers along a ray
	virtual void	EnumerateEntities(const Ray_t& ray, bool triggers, void* pEnumerator) = 0;

	// Same thing, but enumerate entitys within a box
	virtual void	EnumerateEntities(const Vector& vecAbsMins, const Vector& vecAbsMaxs, void* pEnumerator) = 0;

	// Convert a handle entity to a collideable.  Useful inside enumer
	virtual void* GetCollideable(void* pEntity) = 0;

	// HACKHACK: Temp for performance measurments
	virtual int GetStatByIndex(int index, bool bClear) = 0;


	//finds brushes in an AABB, prone to some false positives
	virtual void GetBrushesInAABB(const Vector& vMins, const Vector& vMaxs, void*& BrushQuery, int iContentsMask = 0xFFFFFFFF, int cmodelIndex = 0) = 0;

	//Creates a CPhysCollide out of all displacements wholly or partially contained in the specified AABB
	virtual void* GetCollidableFromDisplacementsInAABB(const Vector& vMins, const Vector& vMaxs) = 0;

	// gets the number of displacements in the world
	virtual int GetNumDisplacements() = 0;

	// gets a specific diplacement mesh
	virtual void GetDisplacementMesh(int nIndex, void* pMeshTriList) = 0;

	//retrieve brush planes and contents, returns zero if the brush doesn't exist, 
	//returns positive number of sides filled out if the array can hold them all, negative number of slots needed to hold info if the array is too small
	virtual int GetBrushInfo(int iBrush, int& ContentsOut, void* pBrushSideInfoOut, int iBrushSideInfoArraySize) = 0;

	virtual bool PointOutsideWorld(const Vector& ptTest) = 0; //Tests a point to see if it's outside any playable area

	// Walks bsp to find the leaf containing the specified point
	virtual int GetLeafContainingPoint(const Vector& ptTest) = 0;

	virtual void* AllocTraceListData() = 0;
	virtual void FreeTraceListData(void*) = 0;

	/// Used only in debugging: get/set/clear/increment the trace debug counter. See comment below for details.
	virtual int GetSetDebugTraceCounter(int value, void* behavior) = 0;

	//Similar to GetCollidableFromDisplacementsInAABB(). But returns the intermediate mesh data instead of a collideable
	virtual int GetMeshesFromDisplacementsInAABB(const Vector& vMins, const Vector& vMaxs, void* pOutputMeshes, int iMaxOutputMeshes) = 0;

	virtual void GetBrushesInCollideable(void* pCollideable, void*& BrushQuery) = 0;

	virtual bool IsFullyOccluded(int nOcclusionKey, const void*& aabb1, const void*& aabb2, const Vector& vShadow) = 0;

	virtual void SuspendOcclusionTests() = 0;
	virtual void ResumeOcclusionTests() = 0;
	class CAutoSuspendOcclusionTests
	{
		IEngineTrace* m_pEngineTrace;
	public:
		CAutoSuspendOcclusionTests(IEngineTrace* pEngineTrace) : m_pEngineTrace(pEngineTrace) { pEngineTrace->SuspendOcclusionTests(); }
		~CAutoSuspendOcclusionTests() { m_pEngineTrace->ResumeOcclusionTests(); }
	};

	virtual void FlushOcclusionQueries() = 0;
};
