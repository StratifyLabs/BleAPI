cmake_minimum_required (VERSION 3.6)


# Grab the SDK location
if(NOT DEFINED SOS_SDK_PATH)
	if(DEFINED ENV{SOS_SDK_PATH})
		set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH /Applications/StratifyLabs-SDK)
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH C:/StratifyLabs-SDK)
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH /StratifyLabs-SDK)
	endif()
endif()
if(NOT DEFINED SOS_SDK_PATH)
	message(FATAL_ERROR "Please set environment variable SOS_SDK_PATH to location of the StratifyLabs-SDK directory")
endif()
set(SOS_TOOLCHAIN_CMAKE_PATH ${SOS_SDK_PATH}/Tools/gcc/arm-none-eabi/cmake)

include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-variables.cmake)

if( ${SOS_BUILD_CONFIG} STREQUAL arm )
  set(CMAKE_TOOLCHAIN_FILE ${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib-toolchain.cmake)
elseif( ${SOS_BUILD_CONFIG} STREQUAL link )
  set(CMAKE_TOOLCHAIN_FILE ${SOS_TOOLCHAIN_CMAKE_PATH}/link-toolchain.cmake)
endif()

set(SOS_NAME BleAPI)
project(${SOS_NAME} CXX C ASM)

set(SOS_DEFINITIONS 

  )

set(STACKS_DIR ${CMAKE_SOURCE_DIR}/stacks)
set(HOST_DIR ${STACKS_DIR}/ble-host)
set(WSF_DIR ${STACKS_DIR}/wsf)
set(PROFILES_DIR ${STACKS_DIR}/ble-profiles)
set(SERVICES_DIR ${PROFILES_DIR}/sources/services)
set(PORTING_DIR ${CMAKE_SOURCE_DIR}/porting)
set(APP_DIR ${STACKS_DIR}/ble-apps/sources)

list(APPEND
  SOS_INCLUDE_DIRECTORIES
	${STACKS_DIR}/ble-host/sources/hci/dual_chip
  ${HOST_DIR}/include
	${HOST_DIR}/sources/stack/att
	${HOST_DIR}/sources/stack/dm
	${HOST_DIR}/sources/stack/hci
	${HOST_DIR}/sources/stack/l2c
	${HOST_DIR}/sources/stack/smp
	${HOST_DIR}/sources/stack/smp
	${WSF_DIR}/include
	${STACKS_DIR}/platform/include
	${APP_DIR}
	${PROFILES_DIR}/include
  ${PROFILES_DIR}/sources/services
	${PROFILES_DIR}/sources/profiles/include
  ${PROFILES_DIR}/sources/profiles
  ${PROFILES_DIR}/sources/af
  ${PORTING_DIR}/cfg
	)

#Add sources to the project


set(HOST_SOURCES
  ${HOST_DIR}/sources/stack/att/att_main.c
  ${HOST_DIR}/sources/stack/att/att_uuid.c
  ${HOST_DIR}/sources/stack/att/att_eatt.c
  ${HOST_DIR}/sources/stack/att/attc_disc.c
  ${HOST_DIR}/sources/stack/att/attc_main.c
  ${HOST_DIR}/sources/stack/att/attc_proc.c
  ${HOST_DIR}/sources/stack/att/attc_read.c
  ${HOST_DIR}/sources/stack/att/attc_sign.c
  ${HOST_DIR}/sources/stack/att/attc_write.c
  ${HOST_DIR}/sources/stack/att/attc_eatt.c
  ${HOST_DIR}/sources/stack/att/atts_ccc.c
  ${HOST_DIR}/sources/stack/att/atts_csf.c
  ${HOST_DIR}/sources/stack/att/atts_dyn.c
  ${HOST_DIR}/sources/stack/att/atts_ind.c
  ${HOST_DIR}/sources/stack/att/atts_main.c
  ${HOST_DIR}/sources/stack/att/atts_proc.c
  ${HOST_DIR}/sources/stack/att/atts_read.c
  ${HOST_DIR}/sources/stack/att/atts_sign.c
  ${HOST_DIR}/sources/stack/att/atts_write.c
  ${HOST_DIR}/sources/stack/att/atts_eatt.c
  ${HOST_DIR}/sources/stack/dm/dm_adv.c
  ${HOST_DIR}/sources/stack/dm/dm_adv_ae.c
  ${HOST_DIR}/sources/stack/dm/dm_adv_leg.c
  ${HOST_DIR}/sources/stack/dm/dm_bis_master.c
  ${HOST_DIR}/sources/stack/dm/dm_bis_slave.c
  ${HOST_DIR}/sources/stack/dm/dm_cis.c
  ${HOST_DIR}/sources/stack/dm/dm_cis_master.c
  ${HOST_DIR}/sources/stack/dm/dm_cis_slave.c
  ${HOST_DIR}/sources/stack/dm/dm_cis_sm.c
  ${HOST_DIR}/sources/stack/dm/dm_conn.c
  ${HOST_DIR}/sources/stack/dm/dm_conn_cte.c
  ${HOST_DIR}/sources/stack/dm/dm_conn_master.c
  ${HOST_DIR}/sources/stack/dm/dm_conn_master_ae.c
  ${HOST_DIR}/sources/stack/dm/dm_conn_master_leg.c
  ${HOST_DIR}/sources/stack/dm/dm_conn_slave.c
  ${HOST_DIR}/sources/stack/dm/dm_conn_slave_ae.c
  ${HOST_DIR}/sources/stack/dm/dm_conn_slave_leg.c
  ${HOST_DIR}/sources/stack/dm/dm_conn_sm.c
  ${HOST_DIR}/sources/stack/dm/dm_dev.c
  ${HOST_DIR}/sources/stack/dm/dm_dev_priv.c
  ${HOST_DIR}/sources/stack/dm/dm_iso.c
  ${HOST_DIR}/sources/stack/dm/dm_main.c
  ${HOST_DIR}/sources/stack/dm/dm_past.c
  ${HOST_DIR}/sources/stack/dm/dm_phy.c
  ${HOST_DIR}/sources/stack/dm/dm_priv.c
  ${HOST_DIR}/sources/stack/dm/dm_scan.c
  ${HOST_DIR}/sources/stack/dm/dm_scan_ae.c
  ${HOST_DIR}/sources/stack/dm/dm_scan_leg.c
  ${HOST_DIR}/sources/stack/dm/dm_sec.c
  ${HOST_DIR}/sources/stack/dm/dm_sec_lesc.c
  ${HOST_DIR}/sources/stack/dm/dm_sec_master.c
  ${HOST_DIR}/sources/stack/dm/dm_sec_slave.c
  ${HOST_DIR}/sources/stack/dm/dm_sync_ae.c
  ${HOST_DIR}/sources/stack/hci/hci_main.c
  ${HOST_DIR}/sources/stack/l2c/l2c_coc.c
  ${HOST_DIR}/sources/stack/l2c/l2c_main.c
  ${HOST_DIR}/sources/stack/l2c/l2c_master.c
  ${HOST_DIR}/sources/stack/l2c/l2c_slave.c
  ${HOST_DIR}/sources/stack/smp/smp_act.c
  ${HOST_DIR}/sources/stack/smp/smp_db.c
  ${HOST_DIR}/sources/stack/smp/smp_main.c
  ${HOST_DIR}/sources/stack/smp/smp_non.c
  ${HOST_DIR}/sources/stack/smp/smp_sc_act.c
  ${HOST_DIR}/sources/stack/smp/smp_sc_main.c
  ${HOST_DIR}/sources/stack/smp/smpi_act.c
  ${HOST_DIR}/sources/stack/smp/smpi_sc_act.c
  ${HOST_DIR}/sources/stack/smp/smpi_sc_sm.c
  ${HOST_DIR}/sources/stack/smp/smpi_sm.c
  ${HOST_DIR}/sources/stack/smp/smpr_act.c
  ${HOST_DIR}/sources/stack/smp/smpr_sc_act.c
  ${HOST_DIR}/sources/stack/smp/smpr_sc_sm.c
  ${HOST_DIR}/sources/stack/smp/smpr_sm.c
  ${HOST_DIR}/sources/sec/common/sec_aes.c
  ${HOST_DIR}/sources/sec/common/sec_aes_rev.c
  ${HOST_DIR}/sources/sec/common/sec_ccm_hci.c
  ${HOST_DIR}/sources/sec/common/sec_cmac_hci.c
  ${HOST_DIR}/sources/sec/common/sec_ecc_debug.c
  ${HOST_DIR}/sources/sec/common/sec_ecc_hci.c
  ${HOST_DIR}/sources/sec/common/sec_main.c
	${HOST_DIR}/sources/hci/common/hci_core.c
	${HOST_DIR}/sources/hci/common/hci_tr.c
	${HOST_DIR}/sources/hci/dual_chip/hci_cmd.c
	${HOST_DIR}/sources/hci/dual_chip/hci_cmd_ae.c
	${HOST_DIR}/sources/hci/dual_chip/hci_cmd_bis.c
	${HOST_DIR}/sources/hci/dual_chip/hci_cmd_cis.c
	${HOST_DIR}/sources/hci/dual_chip/hci_cmd_cte.c
	${HOST_DIR}/sources/hci/dual_chip/hci_cmd_iso.c
	${HOST_DIR}/sources/hci/dual_chip/hci_cmd_past.c
	${HOST_DIR}/sources/hci/dual_chip/hci_cmd_phy.c
	${HOST_DIR}/sources/hci/dual_chip/hci_core_ps.c
	${HOST_DIR}/sources/hci/dual_chip/hci_core_ps.h
	${HOST_DIR}/sources/hci/dual_chip/hci_evt.c
	${HOST_DIR}/sources/hci/dual_chip/hci_vs.c
	${HOST_DIR}/sources/hci/dual_chip/hci_vs_ae.c
)

set(SERVICES_SOURCES
  ${PROFILES_DIR}/sources/services/svc_alert.c
  ${PROFILES_DIR}/sources/services/svc_batt.c
  ${PROFILES_DIR}/sources/services/svc_bps.c
  ${PROFILES_DIR}/sources/services/svc_core.c
  ${PROFILES_DIR}/sources/services/svc_cps.c
  ${PROFILES_DIR}/sources/services/svc_cscs.c
  ${PROFILES_DIR}/sources/services/svc_dis.c
  ${PROFILES_DIR}/sources/services/svc_gls.c
  ${PROFILES_DIR}/sources/services/svc_gyro.c
  ${PROFILES_DIR}/sources/services/svc_hid.c
  ${PROFILES_DIR}/sources/services/svc_hrs.c
  ${PROFILES_DIR}/sources/services/svc_hts.c
  ${PROFILES_DIR}/sources/services/svc_ipss.c
  ${PROFILES_DIR}/sources/services/svc_plxs.c
  ${PROFILES_DIR}/sources/services/svc_px.c
  ${PROFILES_DIR}/sources/services/svc_rscs.c
  ${PROFILES_DIR}/sources/services/svc_scpss.c
  ${PROFILES_DIR}/sources/services/svc_temp.c
  ${PROFILES_DIR}/sources/services/svc_time.c
  ${PROFILES_DIR}/sources/services/svc_uricfg.c
  ${PROFILES_DIR}/sources/services/svc_wdxs.c
  ${PROFILES_DIR}/sources/services/svc_wp.c
  ${PROFILES_DIR}/sources/services/svc_wss.c
)

set(PROFILES_SOURCES
  ${PROFILES_DIR}/sources/profiles/anpc/anpc_main.c
  ${PROFILES_DIR}/sources/profiles/atpc/atpc_main.c
  ${PROFILES_DIR}/sources/profiles/atps/atps_main.c
  ${PROFILES_DIR}/sources/profiles/bas/bas_main.c
  ${PROFILES_DIR}/sources/profiles/blpc/blpc_main.c
  ${PROFILES_DIR}/sources/profiles/blps/blps_main.c
  ${PROFILES_DIR}/sources/profiles/cpp/cpps_main.c
  ${PROFILES_DIR}/sources/profiles/cscp/cscps_main.c
  ${PROFILES_DIR}/sources/profiles/dis/dis_main.c
  ${PROFILES_DIR}/sources/profiles/fmpl/fmpl_main.c
  ${PROFILES_DIR}/sources/profiles/gap/gap_main.c
  ${PROFILES_DIR}/sources/profiles/gatt/gatt_main.c
  ${PROFILES_DIR}/sources/profiles/glpc/glpc_main.c
  ${PROFILES_DIR}/sources/profiles/glps/glps_db.c
  ${PROFILES_DIR}/sources/profiles/glps/glps_main.c
  ${PROFILES_DIR}/sources/profiles/hid/hid_main.c
  ${PROFILES_DIR}/sources/profiles/hrpc/hrpc_main.c
  ${PROFILES_DIR}/sources/profiles/hrps/hrps_main.c
  ${PROFILES_DIR}/sources/profiles/htpc/htpc_main.c
  ${PROFILES_DIR}/sources/profiles/htps/htps_main.c
  ${PROFILES_DIR}/sources/profiles/paspc/paspc_main.c
  ${PROFILES_DIR}/sources/profiles/plxpc/plxpc_main.c
  ${PROFILES_DIR}/sources/profiles/plxps/plxps_db.c
  ${PROFILES_DIR}/sources/profiles/plxps/plxps_main.c
  ${PROFILES_DIR}/sources/profiles/rscp/rscps_main.c
  ${PROFILES_DIR}/sources/profiles/scpps/scpps_main.c
  ${PROFILES_DIR}/sources/profiles/sensor/gyro_main.c
  ${PROFILES_DIR}/sources/profiles/sensor/temp_main.c
  ${PROFILES_DIR}/sources/profiles/tipc/tipc_main.c
  ${PROFILES_DIR}/sources/profiles/udsc/udsc_main.c
  ${PROFILES_DIR}/sources/profiles/uribeacon/uricfg_main.c
  ${PROFILES_DIR}/sources/profiles/wdxc/wdxc_ft.c
  ${PROFILES_DIR}/sources/profiles/wdxc/wdxc_main.c
  ${PROFILES_DIR}/sources/profiles/wdxc/wdxc_stream.c
  ${PROFILES_DIR}/sources/profiles/wdxs/wdxs_au.c
  ${PROFILES_DIR}/sources/profiles/wdxs/wdxs_dc.c
  ${PROFILES_DIR}/sources/profiles/wdxs/wdxs_ft.c
  ${PROFILES_DIR}/sources/profiles/wdxs/wdxs_main.c
  ${PROFILES_DIR}/sources/profiles/wdxs/wdxs_phy.c
  ${PROFILES_DIR}/sources/profiles/wdxs/wdxs_stream.c
  ${PROFILES_DIR}/sources/profiles/wpc/wpc_main.c
  ${PROFILES_DIR}/sources/profiles/wspc/wspc_main.c
  ${PROFILES_DIR}/sources/profiles/wsps/wsps_main.c
)

set(AF_SOURCES
  ${PROFILES_DIR}/sources/af/app_disc.c
  ${PROFILES_DIR}/sources/af/app_main.c
  ${PROFILES_DIR}/sources/af/app_master.c
  ${PROFILES_DIR}/sources/af/app_master_ae.c
  ${PROFILES_DIR}/sources/af/app_master_leg.c
  ${PROFILES_DIR}/sources/af/app_server.c
  ${PROFILES_DIR}/sources/af/app_slave.c
  ${PROFILES_DIR}/sources/af/app_slave_ae.c
  ${PROFILES_DIR}/sources/af/app_slave_leg.c
  ${PROFILES_DIR}/sources/af/app_terminal.c
  ${PROFILES_DIR}/sources/af/common/app_db.c
  ${PROFILES_DIR}/sources/af/common/app_hw.c
  ${PROFILES_DIR}/sources/af/common/app_ui.c
  ${PROFILES_DIR}/sources/af/common/ui_console.c
  ${PROFILES_DIR}/sources/af/common/ui_lcd.c
  ${PROFILES_DIR}/sources/af/common/ui_main.c
  ${PROFILES_DIR}/sources/af/common/ui_platform.c
  ${PROFILES_DIR}/sources/af/common/ui_timer.c
)

set(APP_SOURCES
	${APP_DIR}/assettag/assettag_api.h
	${APP_DIR}/assettag/assettag_main.c
	${APP_DIR}/cycling/cycling_api.h
	${APP_DIR}/cycling/cycling_main.c
	${APP_DIR}/datc/datc_api.h
	${APP_DIR}/datc/datc_main.c
	${APP_DIR}/dats/dats_api.h
	${APP_DIR}/dats/dats_main.c
	${APP_DIR}/fit/fit_api.h
	${APP_DIR}/fit/fit_main.c
	${APP_DIR}/gluc/gluc_api.h
	${APP_DIR}/gluc/gluc_main.c
	${APP_DIR}/hidapp/hidapp_api.h
	${APP_DIR}/hidapp/hidapp_main.c
	${APP_DIR}/locator/locator_api.h
	${APP_DIR}/locator/locator_main.c
	${APP_DIR}/medc/medc_api.h
	${APP_DIR}/medc/medc_blp.c
	${APP_DIR}/medc/medc_glp.c
	${APP_DIR}/medc/medc_hrp.c
	${APP_DIR}/medc/medc_htp.c
	${APP_DIR}/medc/medc_main.c
	${APP_DIR}/medc/medc_main.h
	${APP_DIR}/medc/medc_plx.c
	${APP_DIR}/medc/medc_wsp.c
	${APP_DIR}/meds/meds_api.h
	${APP_DIR}/meds/meds_blp.c
	${APP_DIR}/meds/meds_glp.c
	${APP_DIR}/meds/meds_htp.c
	${APP_DIR}/meds/meds_main.c
	${APP_DIR}/meds/meds_main.h
	${APP_DIR}/meds/meds_plx.c
	${APP_DIR}/meds/meds_wsp.c
	${APP_DIR}/sensor/sensor_api.h
	${APP_DIR}/sensor/sensor_main.c
	${APP_DIR}/tag/tag_api.h
	${APP_DIR}/tag/tag_main.c
	${APP_DIR}/tag/tag_main_wdxs.c
	${APP_DIR}/uribeacon/uribeacon_api.h
	${APP_DIR}/uribeacon/uribeacon_main.c
	${APP_DIR}/watch/watch_api.h
	${APP_DIR}/watch/watch_main.c
	)

set(WSF_SOURCES
	${WSF_DIR}/sources/util/bda.c
	${WSF_DIR}/sources/util/bstream.c
	${WSF_DIR}/sources/util/calc128.c
	${WSF_DIR}/sources/util/crc32.c
	${WSF_DIR}/sources/util/fcs.c
	${WSF_DIR}/sources/util/prand.c
	${WSF_DIR}/sources/util/wstr.c
	)

set(PORTING_SOURCES
  ${PORTING_DIR}/wsf_assert.c
  ${PORTING_DIR}/wsf_buf.c
  ${PORTING_DIR}/wsf_bufio.c
  ${PORTING_DIR}/wsf_cs.c
  ${PORTING_DIR}/wsf_detoken.c
  ${PORTING_DIR}/wsf_efs.c
  ${PORTING_DIR}/wsf_heap.c
  ${PORTING_DIR}/wsf_msg.c
  ${PORTING_DIR}/wsf_nvm.c
  ${PORTING_DIR}/wsf_os.c
  ${PORTING_DIR}/wsf_queue.c
  ${PORTING_DIR}/wsf_timer.c
	${PORTING_DIR}/wsf_trace.c
	${PORTING_DIR}/hci_tr.c
	${PORTING_DIR}/cfg/cfg_stack.c
	${PORTING_DIR}/cfg/cfg_stack.h
)

set(SOS_SOURCELIST
  ${HOST_SOURCES}
  ${SERVICES_SOURCES}
  ${PROFILES_SOURCES}
  ${AF_SOURCES}
	${WSF_SOURCES}
  ${PORTING_SOURCES}
	${APP_SOURCES}
)

SET(SOS_DEFINITIONS
	WSF_TRACE_ENABLED=1
	WSF_TOKEN_ENABLED=1
	MODULE_ID=4
	WSF_ASSERT_ENABLED=1
	)

#install(DIRECTORY zephyr/include/bluetooth DESTINATION include/zephyr_ble)
include( ${CMAKE_SOURCE_DIR}/${SOS_BUILD_CONFIG}.cmake )
