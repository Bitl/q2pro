/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#define MAPERR( x )		case x: return #x;

	MAPERR( WSAEINTR )
	MAPERR( WSAEBADF )
	MAPERR( WSAEACCES )
	MAPERR( WSAEFAULT )
	MAPERR( WSAEINVAL )
	MAPERR( WSAEMFILE )
	MAPERR( WSAEWOULDBLOCK )
	MAPERR( WSAEINPROGRESS )
	MAPERR( WSAEALREADY )
	MAPERR( WSAENOTSOCK )
	MAPERR( WSAEDESTADDRREQ )
	MAPERR( WSAEMSGSIZE )
	MAPERR( WSAEPROTOTYPE )
	MAPERR( WSAENOPROTOOPT )
	MAPERR( WSAEPROTONOSUPPORT )
	MAPERR( WSAESOCKTNOSUPPORT )
	MAPERR( WSAEOPNOTSUPP )
	MAPERR( WSAEPFNOSUPPORT )
	MAPERR( WSAEAFNOSUPPORT )
	MAPERR( WSAEADDRINUSE )
	MAPERR( WSAEADDRNOTAVAIL )
	MAPERR( WSAENETDOWN )
	MAPERR( WSAENETUNREACH )
	MAPERR( WSAENETRESET )
	MAPERR( WSAECONNABORTED )
	MAPERR( WSAECONNRESET )
	MAPERR( WSAENOBUFS )
	MAPERR( WSAEISCONN )
	MAPERR( WSAENOTCONN )
	MAPERR( WSAESHUTDOWN )
	MAPERR( WSAETOOMANYREFS )
	MAPERR( WSAETIMEDOUT )
	MAPERR( WSAECONNREFUSED )
	MAPERR( WSAELOOP )
	MAPERR( WSAENAMETOOLONG )
	MAPERR( WSAEHOSTDOWN )
	MAPERR( WSAEHOSTUNREACH )
	MAPERR( WSAENOTEMPTY )
	MAPERR( WSAEPROCLIM )
	MAPERR( WSAEUSERS )
	MAPERR( WSAEDQUOT )
	MAPERR( WSAESTALE )
	MAPERR( WSAEREMOTE )
	MAPERR( WSASYSNOTREADY )
	MAPERR( WSAVERNOTSUPPORTED )
	MAPERR( WSANOTINITIALISED )
	MAPERR( WSAEDISCON )
	MAPERR( WSAENOMORE )
	MAPERR( WSAECANCELLED )
	MAPERR( WSAEINVALIDPROCTABLE )
	MAPERR( WSAEINVALIDPROVIDER )
	MAPERR( WSAEPROVIDERFAILEDINIT )
	MAPERR( WSASYSCALLFAILURE )
	MAPERR( WSASERVICE_NOT_FOUND )
	MAPERR( WSATYPE_NOT_FOUND )
	MAPERR( WSA_E_NO_MORE )
	MAPERR( WSA_E_CANCELLED )
	MAPERR( WSAEREFUSED )
	MAPERR( WSAHOST_NOT_FOUND )
	MAPERR( WSATRY_AGAIN )
	MAPERR( WSANO_RECOVERY )
	MAPERR( WSANO_DATA )

#undef MAPERR