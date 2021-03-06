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

#include "stdafx.h"
#include "com_struct.h"
#include "ManagePoInAcSfUnitObjPkg.h"

//---------------------------------------------------------------------------

CManagePoInAcSfUnitObjPkg*	t_ManagePoInAcSfUnitObjPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInAcSfUnitObjPkg::CManagePoInAcSfUnitObjPkg()
{
	t_DBMgrPoInAcSfUnitObjPkg	= new CDBMgrPoInAcSfUnitObjPkg();
}
//---------------------------------------------------------------------------

CManagePoInAcSfUnitObjPkg::~CManagePoInAcSfUnitObjPkg()
{
	if(t_DBMgrPoInAcSfUnitObjPkg)	{	delete t_DBMgrPoInAcSfUnitObjPkg;	t_DBMgrPoInAcSfUnitObjPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcSfUnitObjPkg::LoadDBMS()
{
	TListDBPoInAcSfUnitObjPkg tDBPoInAcSfUnitObjPkgList;
    TListDBPoInAcSfUnitObjPkgItor begin, end;
	if(SetER(t_DBMgrPoInAcSfUnitObjPkg->LoadExecute(&tDBPoInAcSfUnitObjPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcSfUnitObjPkgList.begin();	end = tDBPoInAcSfUnitObjPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::InitPkg()
{
	TMapDBPoInAcSfUnitObjPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_SF_UNIT pdpfou = t_ManagePoInAcSfUnit->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfou)
		{
			WriteLogE("not find po_in_ac_sf_unit information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfou->tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT, begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_SF_UNIT_OBJ_PKG pdpiafuop 			= NULL;
	{
		if( (pdpiafuop = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_sf_unit_obj_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		t_ManagePoInAcSfObjUnit->GetHash(pdpiafuop->tDPH.nUnitID, EmptyStr(m_strHashValue));
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::AddPoInAcSfUnitObjPkg(DB_PO_IN_AC_SF_UNIT_OBJ_PKG&	dpiafuop)
{
	if(SetER(t_DBMgrPoInAcSfUnitObjPkg->InsertExecute(&dpiafuop)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpiafuop.tDPH.nID, dpiafuop);
	AddKeyIDList(&dpiafuop);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::EditPoInAcSfUnitObjPkg(DB_PO_IN_AC_SF_UNIT_OBJ_PKG&	dpiafuop)
{
	PDB_PO_IN_AC_SF_UNIT_OBJ_PKG pdpiafuop = FindItem(dpiafuop.tDPH.nID);
	if(!pdpiafuop)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcSfUnitObjPkg->UpdateExecute(&dpiafuop)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafuop.tDPH.nID, dpiafuop);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::DelPoInAcSfUnitObjPkg(UINT32 nID)
{
	PDB_PO_IN_AC_SF_UNIT_OBJ_PKG pdpiafuop = FindItem(nID);
	if(!pdpiafuop)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcSfUnitObjPkg->DeleteExecute(pdpiafuop->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpiafuop);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::GetPoIDListFromUnitPkg(UINT32 nUnitID, TListID& tListID)
{
	TMapID tPoIDMap;
	TListID tUnitIDList;
	GetPoIDFromPkgList(nUnitID, tUnitIDList);
	
	{
		TListIDItor begin, end;
		begin = tUnitIDList.begin();	end = tUnitIDList.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInAcSfPkg->GetPoIDFromPkgMap(*begin, tPoIDMap);	
		}
	}
	ConvertMapToList(tPoIDMap, tListID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_SF_UNIT_OBJ_PKG pdpiafuop = FindItem(*begin);
		if(pdpiafuop->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInAcSfUnitObjPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
{	
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_HEADER pDPH = GetPoHdr(*begin);
		if(!pDPH || pDPH->nPolicyID != nPolicyID)		continue;

		if(IsMultiUsedUnit(nPolicyID, pDPH->nUnitID) == 0)
		{
			t_ManagePoInAcSfObjUnit->DelPoInAcSfObjUnit(pDPH->nUnitID);
		}

		DelPoInAcSfUnitObjPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInAcSfUnitObjPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_SF_UNIT_OBJ_PKG pdpiafuop = FindItem(nID);
    if(!pdpiafuop)	return "";
    return pdpiafuop->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcSfUnitObjPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_SF_UNIT_OBJ_PKG pdpiafuop = FindItem(nID);
	if(!pdpiafuop)	return -1;

	return SetPkt(pdpiafuop, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::SetPkt(PDB_PO_IN_AC_SF_UNIT_OBJ_PKG pdpiafuop, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafuop->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_SF_UNIT_OBJ_PKG& dpiafuop)
{
	if (!RecvToken.TokenDel_DPH(dpiafuop.tDPH))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitObjPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_SF_UNIT_OBJ_PKG pdpiafuop = FindItem(nID);
	if(!pdpiafuop)	return -1;

	SetPkt(pdpiafuop, SendToken);

	return t_ManagePoInAcSfObjUnit->SetPkt(pdpiafuop->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



