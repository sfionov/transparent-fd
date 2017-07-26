cmake_minimum_required(VERSION 3.6)
project(iptables_1_6_0)

set(CMAKE_CXX_STANDARD 11)

set(OLD_SRCS
        extensions/dscp_helper.c
        extensions/libarpt_mangle.c
        extensions/libebt_802_3.c
        extensions/libebt_ip.c
        extensions/libebt_limit.c
        extensions/libebt_log.c
        extensions/libebt_mark.c
        extensions/libebt_mark_m.c
        extensions/libebt_nflog.c
        extensions/libipt_ah.c
        extensions/libipt_CLUSTERIP.c
        extensions/libipt_DNAT.c
        extensions/libipt_ECN.c
        extensions/libipt_icmp.c
        extensions/libipt_LOG.c
        extensions/libipt_MASQUERADE.c
        extensions/libipt_NETMAP.c
        extensions/libipt_realm.c
        extensions/libipt_REDIRECT.c
        extensions/libipt_REJECT.c
        extensions/libipt_SNAT.c
        extensions/libipt_TTL.c
        extensions/libipt_ttl.c
        extensions/libipt_ULOG.c
        extensions/libxt_addrtype.c
        extensions/libxt_AUDIT.c
        extensions/libxt_bpf.c
        extensions/libxt_cgroup.c
        extensions/libxt_CHECKSUM.c
        extensions/libxt_CLASSIFY.c
        extensions/libxt_cluster.c
        extensions/libxt_comment.c
        extensions/libxt_connbytes.c
        #        extensions/libxt_connlabel.c
        extensions/libxt_connlimit.c
        extensions/libxt_CONNMARK.c
        extensions/libxt_connmark.c
        extensions/libxt_CONNSECMARK.c
        extensions/libxt_conntrack.c
        extensions/libxt_cpu.c
        extensions/libxt_CT.c
        extensions/libxt_dccp.c
        extensions/libxt_devgroup.c
        extensions/libxt_DSCP.c
        extensions/libxt_dscp.c
        extensions/libxt_ecn.c
        extensions/libxt_esp.c
        extensions/libxt_hashlimit.c
        extensions/libxt_helper.c
        extensions/libxt_HMARK.c
        extensions/libxt_IDLETIMER.c
        extensions/libxt_ipcomp.c
        extensions/libxt_iprange.c
        extensions/libxt_ipvs.c
        extensions/libxt_LED.c
        extensions/libxt_length.c
        extensions/libxt_limit.c
        extensions/libxt_mac.c
        extensions/libxt_mangle.c
        extensions/libxt_MARK.c
        extensions/libxt_mark.c
        extensions/libxt_multiport.c
        extensions/libxt_nfacct.c
        extensions/libxt_NFLOG.c
        extensions/libxt_NFQUEUE.c
        extensions/libxt_osf.c
        extensions/libxt_owner.c
        extensions/libxt_physdev.c
        extensions/libxt_pkttype.c
        extensions/libxt_policy.c
        extensions/libxt_quota.c
        extensions/libxt_RATEEST.c
        extensions/libxt_rateest.c
        extensions/libxt_recent.c
        extensions/libxt_rpfilter.c
        extensions/libxt_sctp.c
        extensions/libxt_SECMARK.c
        extensions/libxt_SET.c
        extensions/libxt_set.c
        extensions/libxt_socket.c
        extensions/libxt_standard.c
        extensions/libxt_statistic.c
        extensions/libxt_string.c
        extensions/libxt_SYNPROXY.c
        extensions/libxt_tcp.c
        extensions/libxt_TCPMSS.c
        extensions/libxt_tcpmss.c
        extensions/libxt_TCPOPTSTRIP.c
        extensions/libxt_TEE.c
        extensions/libxt_time.c
        extensions/libxt_TOS.c
        extensions/libxt_tos.c
        extensions/libxt_TPROXY.c
        extensions/libxt_TRACE.c
        extensions/libxt_u32.c
        extensions/libxt_udp.c
        extensions/tos_values.c
        )

set(OLD_SRCS6
        extensions/dscp_helper.c
        extensions/libarpt_mangle.c
        extensions/libebt_802_3.c
        extensions/libebt_ip.c
        extensions/libebt_limit.c
        extensions/libebt_log.c
        extensions/libebt_mark.c
        extensions/libebt_mark_m.c
        extensions/libebt_nflog.c
        extensions/tos_values.c
        )

set(EXTENSIONS
        extensions/libxt_addrtype.c
        extensions/libxt_AUDIT.c
        extensions/libxt_bpf.c
        extensions/libxt_cgroup.c
        extensions/libxt_CHECKSUM.c
        extensions/libxt_CLASSIFY.c
        extensions/libxt_cluster.c
        extensions/libxt_comment.c
        extensions/libxt_connbytes.c
        #        extensions/libxt_connlabel.c
        extensions/libxt_connlimit.c
        extensions/libxt_CONNMARK.c
        extensions/libxt_connmark.c
        extensions/libxt_CONNSECMARK.c
        extensions/libxt_conntrack.c
        extensions/libxt_cpu.c
        extensions/libxt_CT.c
        extensions/libxt_dccp.c
        extensions/libxt_devgroup.c
        extensions/libxt_DSCP.c
        extensions/libxt_dscp.c
        extensions/libxt_ecn.c
        extensions/libxt_esp.c
        extensions/libxt_hashlimit.c
        extensions/libxt_helper.c
        extensions/libxt_HMARK.c
        extensions/libxt_IDLETIMER.c
        extensions/libxt_ipcomp.c
        extensions/libxt_iprange.c
        extensions/libxt_ipvs.c
        extensions/libxt_LED.c
        extensions/libxt_length.c
        extensions/libxt_limit.c
        extensions/libxt_mac.c
        extensions/libxt_mangle.c
        extensions/libxt_MARK.c
        extensions/libxt_mark.c
        extensions/libxt_multiport.c
        extensions/libxt_nfacct.c
        extensions/libxt_NFLOG.c
        extensions/libxt_NFQUEUE.c
        extensions/libxt_osf.c
        extensions/libxt_owner.c
        extensions/libxt_physdev.c
        extensions/libxt_pkttype.c
        extensions/libxt_policy.c
        extensions/libxt_quota.c
        extensions/libxt_RATEEST.c
        extensions/libxt_rateest.c
        extensions/libxt_recent.c
        extensions/libxt_rpfilter.c
        extensions/libxt_sctp.c
        extensions/libxt_SECMARK.c
        extensions/libxt_SET.c
        extensions/libxt_set.c
        extensions/libxt_socket.c
        extensions/libxt_standard.c
        extensions/libxt_statistic.c
        extensions/libxt_string.c
        extensions/libxt_SYNPROXY.c
        extensions/libxt_tcp.c
        extensions/libxt_TCPMSS.c
        extensions/libxt_tcpmss.c
        extensions/libxt_TCPOPTSTRIP.c
        extensions/libxt_TEE.c
        extensions/libxt_time.c
        extensions/libxt_TOS.c
        extensions/libxt_tos.c
        extensions/libxt_TPROXY.c
        extensions/libxt_TRACE.c
        extensions/libxt_u32.c
        extensions/libxt_udp.c
        )

set(EXTENSIONS4
        extensions/libipt_ah.c
        extensions/libipt_CLUSTERIP.c
        extensions/libipt_DNAT.c
        extensions/libipt_ECN.c
        extensions/libipt_icmp.c
        extensions/libipt_LOG.c
        extensions/libipt_MASQUERADE.c
        extensions/libipt_NETMAP.c
        extensions/libipt_realm.c
        extensions/libipt_REDIRECT.c
        extensions/libipt_REJECT.c
        extensions/libipt_SNAT.c
        extensions/libipt_TTL.c
        extensions/libipt_ttl.c
        extensions/libipt_ULOG.c
        )
set(EXTENSIONS6
        extensions/libip6t_ah.c
        extensions/libip6t_DNAT.c
        extensions/libip6t_DNPT.c
        extensions/libip6t_dst.c
        extensions/libip6t_eui64.c
        extensions/libip6t_frag.c
        extensions/libip6t_hbh.c
        extensions/libip6t_HL.c
        extensions/libip6t_hl.c
        extensions/libip6t_icmp6.c
        extensions/libip6t_ipv6header.c
        extensions/libip6t_LOG.c
        extensions/libip6t_MASQUERADE.c
        extensions/libip6t_mh.c
        extensions/libip6t_NETMAP.c
        extensions/libip6t_REDIRECT.c
        extensions/libip6t_REJECT.c
        extensions/libip6t_rt.c
        extensions/libip6t_SNAT.c
        extensions/libip6t_SNPT.c
        )

set(SOURCE_FILES
        iptables/getethertype.c
        iptables/iptables-restore.c
        iptables/iptables-save.c
        iptables/iptables-standalone.c
        iptables/iptables-xml.c
        iptables/iptables.c
        iptables/xshared.c
        iptables/xtables-multi.c
        libipq/libipq.c
        libiptc/libip4tc.c
        libxtables/xtables.c
        libxtables/xtoptions.c
        config.h
        ${CMAKE_BINARY_DIR}/initext.c
        ${CMAKE_BINARY_DIR}/initext4.c
        )

set(SOURCE6_FILES
        iptables/getethertype.c
        iptables/ip6tables-restore.c
        iptables/ip6tables-save.c
        iptables/ip6tables-standalone.c
        iptables/ip6tables.c
        iptables/iptables-xml.c
        iptables/xshared.c
        iptables/xtables-multi.c
        libipq/libipq.c
        libiptc/libip6tc.c
        libxtables/xtables.c
        libxtables/xtoptions.c
        config.h
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

configure_file(android/config.h.cmakein ${CMAKE_BINARY_DIR}/config.h)

add_executable(iptables_pie ${SOURCE_FILES} ${EXTENSIONS} ${EXTENSIONS4})
target_compile_definitions(iptables_pie PRIVATE ENABLE_IPV4 XTABLES_INTERNAL ALL_INCLUSIVE NO_SHARED_LIBS XTABLES_LIBDIR=\"/usr/local/lib/xtables\")
target_include_directories(iptables_pie PRIVATE include)
target_include_directories(iptables_pie PRIVATE iptables)
target_include_directories(iptables_pie PRIVATE android)
target_include_directories(iptables_pie PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(iptables_pie m)
add_executable(ip6tables_pie ${SOURCE6_FILES} ${EXTENSIONS} ${EXTENSIONS6})
target_compile_definitions(ip6tables_pie PRIVATE ENABLE_IPV6 XTABLES_INTERNAL ALL_INCLUSIVE NO_SHARED_LIBS XTABLES_LIBDIR=\"/usr/local/lib/xtables\")
target_include_directories(ip6tables_pie PRIVATE include)
target_include_directories(ip6tables_pie PRIVATE iptables)
target_include_directories(ip6tables_pie PRIVATE android)
target_include_directories(ip6tables_pie PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(ip6tables_pie m)
