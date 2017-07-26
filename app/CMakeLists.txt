cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(native-lib SHARED src/main/cpp/native-lib.cpp)

#set(CMAKE_EXE_C_FLAGS "${ANDROID_C_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS "${ANDROID_LINKER_FLAGS}")
#add_executable(create_transparent_socket_sdk15 src/main/cpp/create_transparent_socket.c)
#set_property(TARGET create_transparent_socket_sdk15 PROPERTY POSITION_INDEPENDENT_CODE FALSE)
add_executable(create_transparent_socket_pie src/main/cpp/create_transparent_socket.c)
#set_property(TARGET create_transparent_socket_pie PROPERTY POSITION_INDEPENDENT_CODE TRUE)
#set_property(TARGET create_transparent_socket_pie PROPERTY LINK_FLAGS "-fPIE -pie")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")

set(EXTENSIONS
        src/main/cpp/iptables-1.6.0/extensions/libxt_addrtype.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_AUDIT.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_bpf.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_cgroup.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_CHECKSUM.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_CLASSIFY.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_cluster.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_comment.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_connbytes.c
#        src/main/cpp/iptables-1.6.0/extensions/libxt_connlabel.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_connlimit.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_CONNMARK.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_connmark.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_CONNSECMARK.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_conntrack.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_cpu.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_CT.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_dccp.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_devgroup.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_DSCP.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_dscp.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_ecn.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_esp.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_hashlimit.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_helper.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_HMARK.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_IDLETIMER.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_ipcomp.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_iprange.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_ipvs.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_LED.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_length.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_limit.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_mac.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_mangle.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_MARK.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_mark.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_multiport.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_nfacct.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_NFLOG.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_NFQUEUE.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_osf.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_owner.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_physdev.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_pkttype.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_policy.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_quota.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_RATEEST.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_rateest.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_recent.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_rpfilter.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_sctp.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_SECMARK.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_SET.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_set.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_socket.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_standard.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_statistic.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_string.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_SYNPROXY.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_tcp.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_TCPMSS.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_tcpmss.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_TCPOPTSTRIP.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_TEE.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_time.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_TOS.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_tos.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_TPROXY.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_TRACE.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_u32.c
        src/main/cpp/iptables-1.6.0/extensions/libxt_udp.c
        )

set(EXTENSIONS4
        src/main/cpp/iptables-1.6.0/extensions/libipt_ah.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_CLUSTERIP.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_DNAT.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_ECN.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_icmp.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_LOG.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_MASQUERADE.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_NETMAP.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_realm.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_REDIRECT.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_REJECT.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_SNAT.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_TTL.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_ttl.c
        src/main/cpp/iptables-1.6.0/extensions/libipt_ULOG.c
        )
set(EXTENSIONS6
        src/main/cpp/iptables-1.6.0/extensions/libip6t_ah.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_DNAT.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_DNPT.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_dst.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_eui64.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_frag.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_hbh.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_HL.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_hl.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_icmp6.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_ipv6header.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_LOG.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_MASQUERADE.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_mh.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_NETMAP.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_REDIRECT.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_REJECT.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_rt.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_SNAT.c
        src/main/cpp/iptables-1.6.0/extensions/libip6t_SNPT.c
        )

set(IPTABLES_SOURCE_FILES
        src/main/cpp/iptables-1.6.0/iptables/getethertype.c
        src/main/cpp/iptables-1.6.0/iptables/iptables-restore.c
        src/main/cpp/iptables-1.6.0/iptables/iptables-save.c
        src/main/cpp/iptables-1.6.0/iptables/iptables-standalone.c
        src/main/cpp/iptables-1.6.0/iptables/iptables-xml.c
        src/main/cpp/iptables-1.6.0/iptables/iptables.c
        src/main/cpp/iptables-1.6.0/iptables/xshared.c
        src/main/cpp/iptables-1.6.0/iptables/xtables-multi.c
        src/main/cpp/iptables-1.6.0/libipq/libipq.c
        src/main/cpp/iptables-1.6.0/libiptc/libip4tc.c
        src/main/cpp/iptables-1.6.0/libxtables/xtables.c
        src/main/cpp/iptables-1.6.0/libxtables/xtoptions.c
        src/main/cpp/iptables-1.6.0/config.h
        ${CMAKE_BINARY_DIR}/initext.c
        ${CMAKE_BINARY_DIR}/initext4.c
        )

set(IP6TABLES_SOURCE_FILES
        src/main/cpp/iptables-1.6.0/iptables/getethertype.c
        src/main/cpp/iptables-1.6.0/iptables/ip6tables-restore.c
        src/main/cpp/iptables-1.6.0/iptables/ip6tables-save.c
        src/main/cpp/iptables-1.6.0/iptables/ip6tables-standalone.c
        src/main/cpp/iptables-1.6.0/iptables/ip6tables.c
        src/main/cpp/iptables-1.6.0/iptables/iptables-xml.c
        src/main/cpp/iptables-1.6.0/iptables/xshared.c
        src/main/cpp/iptables-1.6.0/iptables/xtables-multi.c
        src/main/cpp/iptables-1.6.0/libipq/libipq.c
        src/main/cpp/iptables-1.6.0/libiptc/libip6tc.c
        src/main/cpp/iptables-1.6.0/libxtables/xtables.c
        src/main/cpp/iptables-1.6.0/libxtables/xtoptions.c
        src/main/cpp/iptables-1.6.0/config.h
        ${CMAKE_BINARY_DIR}/initext.c
        ${CMAKE_BINARY_DIR}/initext6.c
        )


file(WRITE ${CMAKE_BINARY_DIR}/initext.c)
foreach(f IN LISTS EXTENSIONS)
    get_filename_component(b ${f} NAME_WE)
    set_source_files_properties(${f} PROPERTIES COMPILE_DEFINITIONS "_INIT=${b}_init")
    file(APPEND ${CMAKE_BINARY_DIR}/initext.c "extern void ${b}_init(void);\n")
endforeach()
file(WRITE ${CMAKE_BINARY_DIR}/initext4.c)
foreach(f IN LISTS EXTENSIONS4)
    get_filename_component(b ${f} NAME_WE)
    set_source_files_properties(${f} PROPERTIES COMPILE_DEFINITIONS "_INIT=${b}_init")
    file(APPEND ${CMAKE_BINARY_DIR}/initext4.c "extern void ${b}_init(void);\n")
endforeach()
file(WRITE ${CMAKE_BINARY_DIR}/initext6.c)
foreach(f IN LISTS EXTENSIONS6)
    get_filename_component(b ${f} NAME_WE)
    set_source_files_properties(${f} PROPERTIES COMPILE_DEFINITIONS "_INIT=${b}_init")
    file(APPEND ${CMAKE_BINARY_DIR}/initext6.c "extern void ${b}_init(void);\n")
endforeach()
file(APPEND ${CMAKE_BINARY_DIR}/initext.c "\nvoid init_extensions(void) {\n")
foreach(f IN LISTS EXTENSIONS)
    get_filename_component(b ${f} NAME_WE)
    file(APPEND ${CMAKE_BINARY_DIR}/initext.c "    ${b}_init();\n")
endforeach()
file(APPEND ${CMAKE_BINARY_DIR}/initext.c "}\n")
file(APPEND ${CMAKE_BINARY_DIR}/initext4.c "\nvoid init_extensions4(void) {\n")
foreach(f IN LISTS EXTENSIONS4)
    get_filename_component(b ${f} NAME_WE)
    file(APPEND ${CMAKE_BINARY_DIR}/initext4.c "    ${b}_init();\n")
endforeach()
file(APPEND ${CMAKE_BINARY_DIR}/initext4.c "}\n")
file(APPEND ${CMAKE_BINARY_DIR}/initext6.c "\nvoid init_extensions6(void) {\n")
foreach(f IN LISTS EXTENSIONS6)
    get_filename_component(b ${f} NAME_WE)
    file(APPEND ${CMAKE_BINARY_DIR}/initext6.c "    ${b}_init();\n")
endforeach()
file(APPEND ${CMAKE_BINARY_DIR}/initext6.c "}\n")

include(CheckTypeSize)
set(CMAKE_EXTRA_INCLUDE_FILES netinet/ip6.h)
check_type_size("struct ip6_hdr" SIZEOF_STRUCT_IP6_HDR)
set(CMAKE_EXTRA_INCLUDE_FILES netinet/ip6.h)

configure_file(src/main/cpp/iptables-1.6.0-android/config.h.cmakein ${CMAKE_BINARY_DIR}/config.h)

add_executable(iptables_pie ${IPTABLES_SOURCE_FILES} ${EXTENSIONS} ${EXTENSIONS4})
target_compile_definitions(iptables_pie PRIVATE ENABLE_IPV4 XTABLES_INTERNAL ALL_INCLUSIVE NO_SHARED_LIBS XTABLES_LIBDIR=\"/usr/local/lib/xtables\")
target_include_directories(iptables_pie PRIVATE src/main/cpp/iptables-1.6.0/include)
target_include_directories(iptables_pie PRIVATE src/main/cpp/iptables-1.6.0/iptables)
target_include_directories(iptables_pie PRIVATE src/main/cpp/iptables-1.6.0-android)
target_include_directories(iptables_pie PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(iptables_pie m)
add_executable(ip6tables_pie ${IP6TABLES_SOURCE_FILES} ${EXTENSIONS} ${EXTENSIONS6})
target_compile_definitions(ip6tables_pie PRIVATE ENABLE_IPV6 XTABLES_INTERNAL ALL_INCLUSIVE NO_SHARED_LIBS XTABLES_LIBDIR=\"/usr/local/lib/xtables\")
target_include_directories(ip6tables_pie PRIVATE src/main/cpp/iptables-1.6.0/include)
target_include_directories(ip6tables_pie PRIVATE src/main/cpp/iptables-1.6.0/iptables)
target_include_directories(ip6tables_pie PRIVATE src/main/cpp/iptables-1.6.0-android)
target_include_directories(ip6tables_pie PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(ip6tables_pie m)

if(ANDROID)
set_property(TARGET create_transparent_socket_pie PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/main/assets/${ANDROID_ABI}")
set_property(TARGET ip6tables_pie PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/main/assets/${ANDROID_ABI}")
endif()