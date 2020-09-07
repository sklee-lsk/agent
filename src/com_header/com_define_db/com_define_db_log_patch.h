
#ifndef COM_DEFINE_DB_LOG_PATCH_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_LOG_PATCH_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
//block type
#define SS_LOG_PATCH_STATUS_TYPE_FIND					1
#define SS_LOG_PATCH_STATUS_TYPE_DOWN					2
#define SS_LOG_PATCH_STATUS_TYPE_DOWN_FAIL				3
#define SS_LOG_PATCH_STATUS_TYPE_DOWN_FAIL_REF_OVER		4

#define SS_LOG_PATCH_STATUS_TYPE_WAIT_USER				10

#define SS_LOG_PATCH_STATUS_TYPE_WAIT_AUTO				15

#define SS_LOG_PATCH_STATUS_TYPE_APPLY_AUTO				20
#define SS_LOG_PATCH_STATUS_TYPE_APPLY_USER				21

#define SS_LOG_PATCH_STATUS_TYPE_END_RESTART			30
#define SS_LOG_PATCH_STATUS_TYPE_END					40

#define SS_LOG_PATCH_STATUS_TYPE_ROLLBACK				100

//--------------------------------------------------------------------
#endif	//COM_DEFINE_DB_LOG_PATCH_H_938EF200_F60B_452A_BD30_A10E8507EDCC