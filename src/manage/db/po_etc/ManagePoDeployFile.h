/*
 * Copyright (C) 2020-2025 ASHINi corp. 
 * 
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version. 
 * 
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * Lesser General Public License for more details. 
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA 
 * 
 */

//---------------------------------------------------------------------------

#ifndef ManagePoDeployFileH
#define ManagePoDeployFileH
//---------------------------------------------------------------------------

class CManagePoDeployFile : public CManagePoBase<DB_PO_DEPLOY_FILE>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitHash();
	INT32					InitHash(UINT32 nID);

public:
	INT32					AddPoDeployFile(DB_PO_DEPLOY_FILE&	dpdf);
    INT32					EditPoDeployFile(DB_PO_DEPLOY_FILE&	dpdf);
	INT32					DelPoDeployFile(UINT32 nID);
	INT32					ApplyPoDeployFile(DB_PO_DEPLOY_FILE&	dpdf);

public:
	String					GetName(UINT32 nID);    

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPktHost(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_PO_DEPLOY_FILE pdpdf, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_PO_DEPLOY_FILE& dpdf);

public:
	CManagePoDeployFile();
    ~CManagePoDeployFile();

};

extern CManagePoDeployFile*	t_ManagePoDeployFile;

#endif
