
#include <cstdio>
#include <sapi/api/ApiObject.hpp>

#include "datc_api.h"
#include "wsf_trace.h"


#include "wsf_types.h"
#include "wsf_os.h"
#include "util/bstream.h"

#include "datc/datc_api.h"

#include "hci_handler.h"
#include "dm_handler.h"
#include "l2c_handler.h"
#include "att_handler.h"
#include "smp_handler.h"
#include "l2c_api.h"
#include "att_api.h"
#include "smp_api.h"
#include "app_api.h"
#include "hci_core.h"
#include "svc_dis.h"
#include "svc_core.h"
#include "sec_api.h"
#include "hci_defs.h"

static void StackInitDatc(void);

int main(int argc, char * argv[]){

	WsfTraceEnable(true);
	printf("Datc Start\n");

	StackInitDatc();
	DatcStart();

	WsfOsEnterMainLoop();

	printf("done\n");
	return 0;
}


void StackInitDatc(void){
	wsfHandlerId_t handlerId;

	SecInit();
	SecAesInit();
	SecCmacInit();
	SecEccInit();

	handlerId = WsfOsSetNextHandler(HciHandler);
	HciHandlerInit(handlerId);

	handlerId = WsfOsSetNextHandler(DmHandler);
	DmDevVsInit(0);
	DmDevPrivInit();
	DmConnInit();
	DmScanInit();
	DmConnMasterInit();
	DmSecInit();
	DmSecLescInit();
	DmPrivInit();
	DmHandlerInit(handlerId);

	L2cInit();
	L2cMasterInit();

	handlerId = WsfOsSetNextHandler(AttHandler);
	AttHandlerInit(handlerId);
	AttsInit();
	AttsIndInit();
	AttcInit();

	handlerId = WsfOsSetNextHandler(SmpHandler);
	SmpHandlerInit(handlerId);
	SmpiInit();
	SmpiScInit();
	HciSetMaxRxAclLen(100);

	handlerId = WsfOsSetNextHandler(AppHandler);
	AppHandlerInit(handlerId);

	handlerId = WsfOsSetNextHandler(DatcHandler);
	DatcHandlerInit(handlerId);
}
