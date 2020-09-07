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



#include "stdafx.h"
#include "com_struct.h"
#include "DBMgrPoHostNotifyPkg.h"

//---------------------------------------------------------------------------

CDBMgrPoHostNotifyPkg*		t_DBMgrPoHostNotifyPkg = NULL;

//---------------------------------------------------------------------------

CDBMgrPoHostNotifyPkg::CDBMgrPoHostNotifyPkg()
{
	m_strDBTName = "po_host_notify_pkg";
}
//---------------------------------------------------------------------------

CDBMgrPoHostNotifyPkg::~CDBMgrPoHostNotifyPkg()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostNotifyPkg::SetInitalize()
{
    {
    	
	}
	//WriteLogN("current file dbms : [po_host_clear_pkg][%d]", m_nDBSVer);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostNotifyPkg::LoadDB(TListDBPoHostNotifyPkg& tDBPoHostNotifyPkgList)
{
    UINT32 nReadCnt = 0;
    DB_PO_HOST_NOTIFY_PKG dphpsp;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_PKG_HDR_SELECT
						" FROM po_host_notify_pkg WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dphpsp.tDPH;

		tDPH						= GetDBField_PoPkgHDR(nIndex);
		
        tDBPoHostNotifyPkgList.push_back(dphpsp);
        if(m_nLoadMaxID < UINT32(tDPH.nID))	m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoHostNotifyPkgList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostNotifyPkg::InsertPoHostNotifyPkg(DB_PO_HOST_NOTIFY_PKG& dphnp)
{
	DB_PO_HEADER& tDPH = dphnp.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_host_notify_pkg("
						DBMS_POLICY_QUERY_PKG_HDR_INSERT_NAME
						") VALUES (%s"
						");",
                        GetPoPkgHDRQuery_InsertValue(tDPH).c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostNotifyPkg::UpdatePoHostNotifyPkg(DB_PO_HOST_NOTIFY_PKG& dphnp)
{
	DB_PO_HEADER& tDPH = dphnp.tDPH;

	m_strQuery = SPrintf("UPDATE po_host_notify_pkg SET "
						"%s"
						" WHERE id=%u;",
						GetPoPkgHDRQuery_Update(tDPH).c_str(), 
						tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_UPDATE_FAIL;

    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------  
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32	CDBMgrPoHostNotifyPkg::LoadExecute(PVOID lpTempletList)
{
	TListDBPoHostNotifyPkg* ptDBList = (TListDBPoHostNotifyPkg*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoHostNotifyPkg::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_HOST_NOTIFY_PKG pd_t = (PDB_PO_HOST_NOTIFY_PKG)lpTemplet;

    return InsertPoHostNotifyPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoHostNotifyPkg::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_HOST_NOTIFY_PKG pd_t = (PDB_PO_HOST_NOTIFY_PKG)lpTemplet;

    return UpdatePoHostNotifyPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoHostNotifyPkg::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






