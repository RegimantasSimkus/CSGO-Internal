#pragma once


class CUserCmd
{
public:
	char __padding[0x4];

	// For matching server and client commands for debugging
	int		command_number;

	// the tick the client created this command
	int		tick_count;

	// Player instantaneous view angles.
	Vector	viewangles;
	float	aimdirection[3];	// For pointing devices. 
	// Intended velocities
	//	forward velocity.
	float	forwardmove;
	//  sideways velocity.
	float	sidemove;
	//  upward velocity.
	float	upmove;
	// Attack button states
	int		buttons;
	// Impulse command issued.
	char    impulse;
	// Current weapon id
	int		weaponselect;
	int		weaponsubtype;

	int		random_seed;	// For shared random functions

#ifndef CLIENT_DLL
	int		server_random_seed; // Only the server populates this seed
#endif

	short	mousedx;		// mouse accum in x from create move
	short	mousedy;		// mouse accum in y from create move

	// Client only, tracks whether we've predicted this command at least once
	bool	hasbeenpredicted;

	// TrackIR
	float headangles[3];
	float headoffset[3];
	// TrackIR
};